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
//
// std.cpp for freewar in /u/ept2/ribas_j/freewar/src
// 
// Made by jonathan ribas
// Login   <ribas_j@epita.fr>
// 
// Started on  Mon May  3 13:19:28 2004 jonathan ribas
// Last update Wed Jun 30 16:04:39 2004 
//

#include "libstdtool.h"

void		*xmalloc(size_t len)
{
  void		*p;

  p = malloc(len);
#ifdef MALLOCDEBUG
  printf("MALLOC: %d allouer\n", p);
  fflush(stdout);
#endif
  if (!p)
    {
      fprintf(fd_log, "Out of memory (%d bytes needed).\n", len);
      exit(-1);
    }
  return (p);
}

void		*xrealloc(void *ptr, size_t len)
{
  void		*p;

  p = realloc(ptr, len);
#ifdef MALLOCDEBUG
  printf("MALLOC: %d transform en %d\n", ptr, p);
  fflush(stdout);
#endif
  if (!p)
    {
      fprintf(fd_log, "Out of memory (%d bytes needed)\n", len);
      exit(-1);
    }
  return (p);
}

char		*xstrdup(char *s)
{
  char		*ptr;

  if (!s)
    return (0);
  ptr = strdup(s);
#ifdef MALLOCDEBUG
  printf("MALLOC: %d allouer\n", ptr);
  fflush(stdout);
#endif
  if (!ptr)
    {
      fprintf(fd_log, "out of memory\n");
      exit(-1);
    }
  return (ptr);
}

char		*xstrndup(char *s, size_t len)
{
  char		*ptr;

  if (!s)
    return (0);
  if (len < strlen(s))
    ptr = (char*)xmalloc((unsigned int)len + 1);
  else
    ptr = (char*)xmalloc((unsigned int)strlen(s) + 1);
  strncpy(ptr, s, len);
  ptr[len] = 0;
#ifdef MALLOCDEBUG
  printf("MALLOC: %d allouer\n", ptr);
  fflush(stdout);
#endif
  if (!ptr)
    {
      fprintf(fd_log, "out of memory\n");
      exit(-1);
    }
  return (ptr);
}

int		xstrlen(char *s)
{
  if (s)
    return ((int)strlen(s));
  else
    return (0);
}

char		*xstrcpy(char *dst, char *src)
{
  if (dst && src)
    return(strcpy(dst, src));
  else
    return(dst);
}

char		*xstrncpy(char *dst, char *src, size_t len)
{
  if (dst && src)
    return(strncpy(dst, src, len));
  else
    return(dst);
}

FILE            *xfopen(char *s, char *mode)
{
  FILE          *fd;

  fd = fopen(s, mode);
  if (!fd)
    {
      put_error("Failed to open file'");
      return (0);
    }
  return (fd);
}

size_t		xfread(void *ptr, size_t size,
		       size_t nmemb, FILE *stream)
{
  size_t           ret;

  ret = fread(ptr, size, nmemb, stream);
  if (size && nmemb && ret < nmemb)
    return (put_error("Read failed on file descriptor"));
  return (0);
}

size_t		xfwrite(void *ptr, size_t size,
			size_t nmemb, FILE *stream)
{
  size_t        ret;

  ret = fwrite(ptr, size, nmemb, stream);
  if (size && nmemb && ret < nmemb)
    return (put_error("Write failed on file descriptor"));
  return (0);
}

void		xfree(void *p)
{
#ifdef MALLOCDEBUG
  printf("MALLOC: %d liberer\n", p);
  fflush(stdout);
#endif
  free(p);
}

void            my_free_ptr_ptr(char **p)
{
  int           i;

  for (i = 0; p[i]; i++)
    xfree(p[i]);
  xfree(p);
}


