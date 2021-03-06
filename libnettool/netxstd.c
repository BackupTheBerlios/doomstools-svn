// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of libnettool.

// libnettool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// libnettool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with libnettool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "libnettool.h"

void		*_net_xmalloc(size_t len)
{
  void		*p;
 
  p = malloc(len);
#ifdef MALLOCDEBUG
  printf("MALLOC: %d allouer\n", (int)p);
  fflush(stdout);
#endif
  if (!p)
    {
      fprintf(stderr, "Out of memory (%d bytes needed).\n", len);
      exit(-1);
    }
  return (p);
}

void		*_net_xrealloc(void *ptr, size_t len)
{
  void		*p;

  p = realloc(ptr, len);
#ifdef MALLOCDEBUG
  printf("MALLOC: %d transform en %d\n", (int)ptr, (int)p);
  fflush(stdout);
#endif
  if (!p)
    {
      fprintf(stderr, "Out of memory (%d bytes needed)\n", len);
      exit(-1);
    }
  return (p);
}

void		_net_xfree(void *p)
{
#ifdef MALLOCDEBUG
  printf("MALLOC: %d liberer\n", (int)p);
  fflush(stdout);
#endif
  free(p);
}

void            _net_my_free_ptr_ptr(char **p)
{
  int           i;

  for (i = 0; p[i]; i++)
    _net_xfree(p[i]);
  _net_xfree(p);
}


