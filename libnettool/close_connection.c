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
** close_connection.c for network engine in /u/ept2/huot_j/network_engine
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Wed Jun 23 14:55:12 2004 jonathan huot
** Last update Wed Jun 23 15:03:20 2004 jonathan huot
*/

#include "libnettool.h"

void		_freelist(t_tmp **origin)
{
  t_tmp		*next;
  t_tmp		*list;

  list = *origin;
  while (list)
    {
      next = list->next;
      free(list);
      list = next;
    }
  *origin = NULL;
}

void		close_connection()
{
  t_tmp		*list;
  t_tmp		*next;

  _freelist(&cnt->newclient);
  _freelist(&cnt->deadclient);
  _net_xfree(cnt->clients);
  for (list = cnt->allclients; list; list = next)
    {
      next = list->next;
      SDLNet_TCP_Close(list->c->sock);
      delete_client(list->c);
      _net_xfree(list);
    }
  _net_xfree(cnt->allclients);
  cnt->allclients = NULL;
  cnt->clients = (t_client**)_net_xmalloc(sizeof(*cnt->clients));
  cnt->clients[0] = NULL;
}

void		close_server_connection()
{
  if (cnt->server.sock)
    SDLNet_TCP_Close(cnt->server.sock);
  cnt->server.sock = 0;
}

void		close_client_connection(t_client *client)
{
  int		i;

  if (!client)
    return;
  if (client->sock)
    SDLNet_TCP_Close(client->sock);
  cnt->newclient = del_in_list(cnt->newclient, client);
  cnt->newclient = del_in_list(cnt->deadclient, client);
  for (i = 0; cnt->clients[i]; i++)
    if (cnt->clients[i] == client)
      move_last_client(i);
  delete_client(client);
}
