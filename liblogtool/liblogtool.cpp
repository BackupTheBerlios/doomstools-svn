// Copyright (C) 2004 Doomsday <doomsday@mailclub.net>

// This file is part of liblogtool.

// liblogtool is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.

// liblogtool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser Public License for more details.

// You should have received a copy of the GNU Lesser Public License
// along with liglogtool; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "liblogtool.h"

using namespace	std;

c_log::c_log()
{
  init("\0");
}

c_log::c_log(string file)
{
  init(file);
}

c_log::~c_log()
{
  close();
}

bool		c_log::init(string file)
{
  FILE		*fd;

  if (!file.size())
    file = LOG_FILE;
  if((fd = fopen(file.c_str(), "w")) == NULL)
    {
      cerr << file << " fopen failed" << endl;
      _fd_log = NULL;
      return (false);
    }
  else
    {
      _fd_log = fd;
      fprintf(_fd_log, "<LOG START>\n");
    }
  return (true);
}

void		c_log::close()
{
  if (_fd_log)
    fclose(_fd_log);
  _fd_log = NULL;
}

void		c_log::set_out(short out)
{
  cout << "set this " << out << endl;
}

int		c_log::put(string s)
{
  if (_fd_log)
    {
      fprintf(_fd_log, "%s\n", s.c_str());
    }
  else
    printf("Warning: log is not initialised\n");
  printf("%s\n", s.c_str());
//   if (C)
//     throw s;
  return (1);
}
