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
** init_client.c for network engine in /u/ept2/huot_j/network_engine
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Tue Jun 22 18:18:56 2004 jonathan huot
** Last update Tue Jun 22 18:19:11 2004 jonathan huot
*/

#include "libnettool.h"

void		init_client(t_client *client)
{
  int		i;

  client->pos_recv = 0;
  client->pos_exec = 0;
  client->pos_send = 0;
  client->pos_stock = 0;
  for (i = 0; i < NET_MAX_MSG; i++)
    {
      init_msg(&(client->recv[i]));
      init_msg(&(client->send[i]));
    }
  client->sock = 0;
  client->loss = 0;
}
