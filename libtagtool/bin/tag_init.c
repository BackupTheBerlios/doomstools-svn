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

#define DEFAULT_FILENAME	(".tagdb")

int	main(int ac, char **av)
{
  char*	file;

  if (ac > 2)
    printf("Syntax error: %s filename\n", av[0]);
  else 
    {
      file = (ac == 2) ? (av[1]) : (DEFAULT_FILENAME);
      if (tag_init(file) == tagSuccess)
	{
	  printf("Database %s created.\n", file);
	  tag_exit();
	  return (0);
	}
      tag_exit();
    }
  return (-1);
}
