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

#ifndef __LIBTAGTOOL_H__
#define __LIBTAGTOOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif


// return values
typedef enum
  {
    tagSuccess = 0,
    tagExisting,
    tagNonExisting,
    tagInternalError
  } eTagReturn;


// simple list
typedef struct		s_tagList
{
  char			*name;
  struct s_tagList	*next;
}			tagList;


// init, tags informations will be loaded and saved into "file"
// informations are saved on-the-fly, then no save() function are needed
eTagReturn	tag_init(char *file);
void		tag_exit();


// create and modifications
eTagReturn	tag_create(char *tag);
eTagReturn	tag_delete(char *tag);
eTagReturn	tag_rename(char *oldtag, char *newtag);


// search
tagList*	tag_list();		// list all availables tags
tagList*	tag_info(char *name);	// get all tags from a name
tagList*	tag_search(char *tag);	// get all names from a tag

void		tag_free_list(tagList *list);		// free list

// associate name with tag
eTagReturn	tag_put(char *tag, char *name);
eTagReturn	tag_remove(char *tag, char *name);


#ifdef __cplusplus
}
#endif



#endif // __LIBTAGTOOL_H__
