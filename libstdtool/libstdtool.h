// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of libstdtool.

// libstdtool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libstdtool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with ligstdtool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef _LIBSTDTOOL_H_
#define _LIBSTDTOOL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	xfree(void *ptr);
void	*xmalloc(unsigned int size);
char	*xstrdup(char *s);
FILE	*xfopen(char *s, char *mode);
size_t  xfread(void *ptr, size_t size, size_t nmemb, FILE *stream);
char	*xstrncpy(char *dst, char *src, size_t len);
char	*xstrcpy(char *dst, char *src);
void	*xrealloc(void *ptr, size_t len);
char	*xstrndup(char *s, size_t len);
int	xstrlen(char *s);

#ifdef __cplusplus
}
#endif

#endif
