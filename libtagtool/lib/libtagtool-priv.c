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
#include <string.h>

#include "libtagtool-priv.h"

// execute sql request stored in gl_sql variable.
// Take 2 args only for proceed result
eTagReturn	_exec_sql(sqlite3_callback func, void* arg)
{
  int		ret;
  char		*err = NULL;

  if ((ret = sqlite3_exec(gl_db, gl_sql, func, arg, &err)) != SQLITE_OK)
    {
      fprintf(stderr, "Internal tag error (%d) : %s\n", ret, err);
      if (err)
	sqlite3_free(err);

      gl_lastret = tagInternalError;
      return (gl_lastret);
    }
  gl_lastret = tagSuccess;
  return (gl_lastret);
}

void		_tag_put_in_list(tagList** list, char *data)
{
  tagList	*part;

  part = (tagList*)xmalloc(sizeof(tagList));
  part->name = data;
  part->next = *list;
  *list = part;
}

// if it doesn't exists, callback is NOT called
int		_tag_exist_callback(void *data, int ac, char **av, char **col_name)
{
  // if tag exist
  if (ac > 0)
    *(int*)data = TRUE;
  return (0);
}

// if it doesn't exists, callback is NOT called
int		_tag_getid_callback(void *data, int ac, char **av, char **col_name)
{
  if (ac > 0)
    *(int*)data = atoi(av[0]);
  return (0);
}

// if its doesn't exists, callback is NOT called
int		_tag_list_callback(void *data, int ac, char **av, char **col_name)
{
  tagList**	list = (tagList**)data;
  int		i;

  if (ac > 0)
    _tag_put_in_list(list, strdup(av[0]));
  return (0);
}
