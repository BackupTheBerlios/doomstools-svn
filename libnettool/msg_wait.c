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
/*
** msg_wait.c for network engine in /u/ept2/huot_j/network_engine
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Tue Jun 22 17:52:38 2004 jonathan huot
// Last update Tue Jun 29 19:25:24 2004 jonathan huot
*/

#include "libnettool.h"

int		msg_wait(t_client *client)
{
  if (!client)
    return (0);
  if (TAG_EXEC(client) >= 0 &&
      POS_EXEC(client) >= (LEN_EXEC(client) * sizeof(*MSG_EXEC(client))) +
      sizeof(TAG_EXEC(client)) + sizeof(LEN_EXEC(client)))
    return (1);
  return (0);
}
