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

#include "libnettool.h"

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
      close_socket(&list->c->sock);
      delete_client(list->c);
    }
  cnt->allclients = NULL;
  cnt->clients = (t_client**)_net_xmalloc(sizeof(*cnt->clients));
  cnt->clients[0] = NULL;
}

void		close_server_connection()
{
  close_socket(&cnt->server.sock);
  cnt->server.sock = 0;
}

void		close_client_connection(t_client *client)
{
  if (!client || no_more(client))
    return;
  loss_client(client);
  client->state = STATE_DROP;
}
