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
** loss_client.c for network engine in /u/ept2/huot_j/network_engine
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Wed Jun 23 14:51:21 2004 jonathan huot
// Last update Tue Jun 29 20:02:37 2004 jonathan huot
*/

#include "libnettool.h"

int		loss_client(t_client *c)
{
  int		i;

  for (i = 0; cnt->clients[i]; i++)
    if (cnt->clients[i] == c)
      break;
  if (!cnt->clients[i])
    return (0);
  if (cnt->clients[i]->loss == STATE_DROP)
    {
      SDLNet_TCP_Close(cnt->clients[i]->sock);
      delete_client(cnt->clients[i]);
    }
  else if (cnt->clients[i]->loss == STATE_DEAD ||
	   cnt->clients[i]->loss == STATE_FAIL_RECV)
    {
      put_in_tmp_client(&cnt->deadclient, cnt->clients[i]);
      call_deadhandler(cnt->deadclient->c, NULL);
    }
  else
    fprintf(stderr, "warning: unknown state (%d)\n", cnt->clients[i]->loss);
  move_last_client(i);
  return (1);
}
