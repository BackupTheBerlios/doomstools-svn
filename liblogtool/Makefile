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
NAME	=	logtool
SRCS	=	lib$(NAME).cpp
OBJS	=	$(SRCS:.cpp=.o)
CC	=	g++
CXXFLAGS=	-Wall

$(NAME)	:	$(OBJS)
		ar r lib$(NAME).a $(OBJS)
		ranlib lib$(NAME).a
all	:	$(NAME)

clean	:	
		$(RM) $(OBJS) *~
fclean	:	clean 
		$(RM) lib$(NAME).a
re	:	fclean all
