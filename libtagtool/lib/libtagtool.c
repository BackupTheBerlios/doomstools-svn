// Copyright (C) 2006 Doomsday <doomsday@mailclub.net>

// This file is part of libtagtool.

// libtagtool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libtagtool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with ligtagtool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include <stdio.h>
#include <sqlite3.h>

#include "libstdtool.h"
#include "libtagtool.h"
#include "libtagtool-priv.h"

#define SQL_MAXLEN (512)

sqlite3		*gl_db = NULL;
char		*gl_sql = NULL;
eTagReturn	gl_lastret = 0;

//
// database :
//
// ========================
// table tag_id
// -----------------------
// id	|   tag
//
// =======================
// table tag_name
// -----------------------
// id	|   name
//
// =======================
// table tag_link
// -----------------------
// id	|   idtag  | idname
//

// init, tags informations will be loaded and saved into "file"
eTagReturn	tag_init(char *file)
{
  int		exists = 0;

  // open database
  if (sqlite3_open(file, &gl_db) != SQLITE_OK)
    {
      sqlite3_close(gl_db);
      return (tagNonExisting);
    }

  // init vars
  gl_sql = xmalloc(SQL_MAXLEN);

  // check if we open an existing file
  strcpy(gl_sql, "select name from sqlite_master;");
  if (_exec_sql(_tag_exist_callback, &exists) != tagSuccess)
    {
      tag_exit();
      return (gl_lastret);
    }

  // if db has been initialized, we stop here
  if (exists)
    return (tagSuccess);

  // init tables
  strcpy(gl_sql, "create table tag_id (id INTEGER PRIMARY KEY, tag TEXT);");
  if (_exec_sql(NULL, NULL) != tagSuccess)
    {
      tag_exit();
      return (gl_lastret);
    }

  strcpy(gl_sql, "create table tag_name (id INTEGER PRIMARY KEY, name TEXT);");
  if (_exec_sql(NULL, NULL) != tagSuccess)
    {
      tag_exit();
      return (gl_lastret);
    }

  strcpy(gl_sql, "create table tag_link (id INTEGER PRIMARY KEY,"
	 "idtag INTEGER, idname INTEGER);");
  if (_exec_sql(NULL, NULL) != tagSuccess)
    {
      tag_exit();
      return (gl_lastret);
    }
  return (tagSuccess);
}

// free all handles
void		tag_exit()
{
  if (gl_db)
    {
      sqlite3_close(gl_db);
      gl_db = NULL;
    }
  if (gl_sql)
    {
      xfree(gl_sql);
      gl_sql = NULL;
    }
}

// create a tag
eTagReturn	tag_create(char *tag)
{
  if (gl_db)
    {
      int	res = 0;

      // if tag exists, we return error
      sprintf(gl_sql, "select id from tag_id where tag='%s';", tag);
      if (_exec_sql(_tag_exist_callback, &res) != tagSuccess)
	return (gl_lastret);

      if (res == TRUE)
	return (tagExisting);

      // else we insert a row with the new tag
      sprintf(gl_sql, "insert into tag_id (tag) values('%s');", tag);
      return (_exec_sql(NULL, NULL));
    }
  return (tagSuccess);
}

// delete a tag and all associated entry
eTagReturn	tag_delete(char *tag)
{
  if (gl_db)
    {
      // delete all linked reference
      sprintf(gl_sql, "delete from tag_link where idtag in "
	      "(select id from tag_id where tag='%s');", tag);
      if (_exec_sql(NULL, NULL) != tagSuccess)
	return (gl_lastret);

      // delete item
      sprintf(gl_sql, "delete from tag_id where tag='%s';", tag);
      return (_exec_sql(NULL, NULL));
    }
  return (tagSuccess);
}

// rename a tag
eTagReturn	tag_rename(char *oldtag, char *newtag)
{
  if (gl_db)
    {
      sprintf(gl_sql, "update tag_id set tag='%s' where tag='%s';",
	      newtag, oldtag);
      return (_exec_sql(NULL, NULL));
    }
  return (tagSuccess);
}

// search
tagList*	tag_list()
{
  if (gl_db)
    {
      tagList*	res = NULL;

      sprintf(gl_sql, "select tag from tag_id order by tag;");
      if (_exec_sql(_tag_list_callback, &res) != tagSuccess)
	return (NULL);

      return (res);
    }
  return (NULL);
}

tagList*	tag_info(char *name)
{
  if (gl_db)
    {
      tagList*	res = NULL;
      int	idname = 0;

      sprintf(gl_sql, "select id from tag_name where name='%s';", name);
      if (_exec_sql(_tag_getid_callback, &idname) != tagSuccess)
	return (NULL);

      // if name is unreachable
      if (!idname)
	return (NULL);

      sprintf(gl_sql, "select tag from tag_id where id in "
	      "(select idtag from tag_link where idname=%d) order by tag;", idname);
      if (_exec_sql(_tag_list_callback, &res) != tagSuccess)
	return (NULL);

      return (res);
    }
  return (NULL);
}

tagList*	tag_search(char *tag)
{
  if (gl_db)
    {
      tagList*	res = NULL;
      int	idtag = 0;

      sprintf(gl_sql, "select id from tag_id where tag='%s';", tag);
      if (_exec_sql(_tag_getid_callback, &idtag) != tagSuccess)
	return (NULL);

      // if tag is unreachable
      if (!idtag)
	return (NULL);

      sprintf(gl_sql, "select name from tag_name where id in "
	      "(select idname from tag_link where idtag=%d) order by name;", idtag);
      if (_exec_sql(_tag_list_callback, &res) != tagSuccess)
	return (NULL);

      return (res);    }
  return (NULL);
  
}

void		tag_free_list(tagList *list)
{
  tagList	*next;

  while (list)
    {
      next = list->next;
      if (list->name)
	xfree(list->name);
      xfree(list);
      list = next;
    }
}

// associate name with tag
eTagReturn	tag_put(char *tag, char *name)
{
  if (gl_db)
    {
      int	idtag = 0;
      int	idname = 0;

      // select both ids from args
      sprintf(gl_sql, "select id from tag_id where tag='%s';", tag);
      if (_exec_sql(_tag_getid_callback, &idtag) != tagSuccess)
	return (gl_lastret);

      // if tag is not created, user must create it!
      if (!idtag)
	return (tagNonExisting);

      sprintf(gl_sql, "select id from tag_name where name='%s';", name);
      if (_exec_sql(_tag_getid_callback, &idname) != tagSuccess)
	return (gl_lastret);

      // if name was never added, we add to tag_name table
      if (!idname)
	{
	  // insert name
	  sprintf(gl_sql, "insert into tag_name (name) values('%s');", name);
	  if (_exec_sql(NULL, NULL) != tagSuccess)
	    return (gl_lastret);

	  // reselect id from name
	  sprintf(gl_sql, "select id from tag_name where name='%s';", name);
	  if (_exec_sql(_tag_getid_callback, &idname) != tagSuccess)
	    return (gl_lastret);
	  if (!idname)
	    return (tagInternalError);
	}
      else
	{
	  int	exists = 0;

	  // check if ids was already insered
	  sprintf(gl_sql, "select id from tag_link where idtag=%d and idname=%d;",
		  idtag, idname);
	  if (_exec_sql(_tag_exist_callback, &exists) != tagSuccess)
	    return (gl_lastret);

	  // "tag" is already linked with "name" !
	  if (exists)
	    return (tagExisting);
	}

      // insert previously got ids
      sprintf(gl_sql,
	      "insert into tag_link (idtag, idname) values(%d, %d);",
	      idtag, idname);
      return (_exec_sql(NULL, NULL));
    }
  return (tagSuccess);
}

eTagReturn	tag_remove(char *tag, char *name)
{
  if (gl_db)
    {
      int	exists = 0;
      int	idtag = 0;
      int	idname = 0;

      // select both ids from args
      sprintf(gl_sql, "select id from tag_id where tag='%s';", tag);
      if (_exec_sql(_tag_getid_callback, &idtag) != tagSuccess)
	return (gl_lastret);

      sprintf(gl_sql, "select id from tag_name where name='%s';", name);
      if (_exec_sql(_tag_getid_callback, &idname) != tagSuccess)
	return (gl_lastret);

      // if tag is not created, user must create it!
      if (!idtag || !idname)
	return (tagNonExisting);

      // delete the link between elements
      sprintf(gl_sql, "delete from tag_link where idtag=%d and idname=%d;", idtag, idname);
      if (_exec_sql(NULL, NULL) != tagSuccess)
	return (gl_lastret);

      // delete name if it is unreferenced
      sprintf(gl_sql, "select id from tag_link where idname=%d;", idname);
      if (_exec_sql(_tag_exist_callback, &exists) != tagSuccess)
	return (gl_lastret);

      // references are still in function, then we return!
      if (exists)
	return (tagSuccess);

      sprintf(gl_sql, "delete from tag_name where name='%s';", idname);
      return (_exec_sql(NULL, NULL));
    }
  return (tagSuccess);
}
