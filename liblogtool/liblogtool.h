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
/*
** prototypes.h for freewar in /u/ept2/huot_j/Freewar/src
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Mon May 10 19:37:57 2004 jonathan huot
** Last update Mon Jul 12 17:27:49 2004 
*/

#ifndef _LIBLOGTOOL_H_
#define _LIBLOGTOOL_H_

#include <iostream>
#include <stdio.h>

#define LOG_STDERR (1)
#define LOG_STDOUT (1 << 2)
#define LOG_FILE   (1 << 3)

#define W ("Warning: ")
#define E ("Error: ")
#define C ("Critical error: ")

#ifndef LOG_FILE
#define LOG_FILE ("default.log")
#endif

class		c_log
{
 private:
  // if a file:
  FILE*		_fd_log;

  // where we put ?
  bool		_stdout;
  bool		_stderr;
  bool		_file;

 public:
  c_log();
  c_log(string file);
  ~c_log();
  bool		init(string file);
  void		put(string s);
  void		close();
  void		set_out(short out);
};

#endif
