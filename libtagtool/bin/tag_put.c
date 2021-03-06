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
  printf("Syntax error: %s [-F filename] tag name\n"
	 "Default filename is %s\n", progname, DEFAULT_FILENAME);
}

int	main(int ac, char **av)
{
  char	*file;
  char	*tag;
  char	*name;
  int	ret;

  if (ac < 3)
    syntax(av[0]);
  else 
    {
      // get correct filename
      if (!strcmp(av[1], "-F"))
	{
	  if (ac < 5)
	    {
	      syntax(av[0]);
	      return (0);
	    }
	  else
	    {
	      file = av[2];
	      tag = av[3];
	      name = av[4];
	    }
	}
      else
	{
	  file = DEFAULT_FILENAME;
	  tag = av[1];
	  name = av[2];
	}

      // call libtag functions
      if ((ret = tag_init(file)) != tagSuccess)
	{
	  if (ret == tagNonExisting)
	    {
	      printf("File don't exist\n");
	      tag_exit();
	      return (-1);
	    }
	}
      else if ((ret = tag_put(tag, name)) == tagSuccess)
	{
	  tag_exit();
	  printf("Tag %s linked with %s.\n", tag, name);
	  return (0);
	}
      tag_exit();
      if (ret == tagNonExisting)
	printf("Tag or name doesn't exist\n");
      else
	printf("Lib error %d.\n", ret);
    }
  return (-1);
}
