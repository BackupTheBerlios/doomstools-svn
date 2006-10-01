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

void	syntax(char *progname)
{
  printf("Syntax error: %s [-F filename] name\n"
	 "Default filename is %s\n", progname, DEFAULT_FILENAME);
}

int	display_tag(char *name);

int	main(int ac, char **av)
{
  char	*file;
  char	*name;
  int	ret;

  if (ac < 2)
    syntax(av[0]);
  else 
    {
      // get correct filename
      if (!strcmp(av[1], "-F"))
	{
	  if (ac < 4)
	    {
	      syntax(av[0]);
	      return (0);
	    }
	  else
	    {
	      file = av[2];
	      name = av[3];
	    }
	}
      else
	{
	  file = DEFAULT_FILENAME;
	  name = av[1];
	}

      // call libtag functions
      if ((ret = tag_init(file)) == tagSuccess)
	return (display_tag(name));
      tag_exit();

      if (ret == tagNonExisting)
	{
	  printf("File don't exist\n");
	  return (-1);
	}
      printf("Lib error %d\n", ret);
    }
  return (-1);
}

int		display_tag(char *name)
{
  tagList*	res;

  res = tag_info(name);
  if (!res)
    {
      printf("Name %s has no tags.\n", name);
      return (-1);
    }
  printf("Name %s has tags:\n", name);
  while (res)
    {
      printf("tag: %s\n", res->name);
      res = res->next;
    }
  tag_free_list(res);
  tag_exit();
  return (0);
}
