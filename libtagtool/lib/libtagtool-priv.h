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

#ifndef __LIBTAGTOOL_PRIV_H__
#define __LIBTAGTOOL_PRIV_H__

#include <sqlite3.h>
#include "libtagtool.h"

extern		sqlite3		*gl_db;
extern		char		*gl_sql;
extern		eTagReturn	gl_lastret;

////////////////////
// commun functions:

// use gl_sql and execute it
eTagReturn	_exec_sql(sqlite3_callback func, void* arg);

/////////////////////////////
// functions to an easier use:

// fill an int with the first column of sql request
int		_tag_getid_callback(void *data, int ac, char **av, char **col_name);

// fill an int if result of query is > 0
int		_tag_exist_callback(void *data, int ac, char **av, char **col_name);

// fill a list from results
int		_tag_list_callback(void *data, int ac, char **av, char **col_name);

#endif // __LIBTAGTOOL_PRIV_H__
