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

#include "libtagtool.h"
#include <stdio.h>
#include <string.h>

#define DEFAULT_FILENAME	(".tagdb")

void		syntax(char *progname)
{
  printf("Syntax : %s [-F filename]\n"
	 "Default filename is %s\n", progname, DEFAULT_FILENAME);
}

int		main(int ac, char **av)
{
  char*		file;
  int		ret;
  tagList*	res;

  syntax(av[0]);
  if (ac == 3)
    {
      if (!strcmp(av[1], "-F"))
	file = av[2];
      else
	return (0);
    }
  else
    file = DEFAULT_FILENAME;

  // call libtag functions
  if ((ret = tag_init(file)) != tagSuccess)
    {
      if (ret == tagNonExisting)
	{
	  printf("File don't exist\n");
	  return (-1);
	}
    }
  else
    {
      printf("\n");
      res = tag_list();

      if (!res)
	{
	  printf("List of tags is empty\n");
	  return (0);
	}

      printf("List of tags available :\n");
      while (res)
	{
	  printf("\t%s\n", res->name);
	  res = res->next;
	}
      return (0);
    }
  printf("Lib error %d\n", ret);
  return (-1);
}
