// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of libxmltool.

// libxmltool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libxmltool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with ligxmltool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef _XML_H_
#define _XML_H_

#include "tinyxml.h"
#include "tinystr.h"


double		xml_getfloat(char *str);
char		*xml_getstr(char *str);
int		xml_next(char *str);
void		xml_out();
int		xml_getint(char *str);
int		xml_init(char *db);

#endif
