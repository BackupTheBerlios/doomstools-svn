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
** init_connection.c for zappy in /u/ept2/ribas_j/c/rendu/zappy
** 
** Made by jonathan ribas
** Login   <ribas_j@epita.fr>
** 
** Started on  Sun May 23 13:27:02 2004 jonathan ribas
// Last update Tue Jun 29 19:22:13 2004 jonathan huot
*/

#include "libnettool.h"

int		init_server_connection(int port)
{
  if (SDLNet_ResolveHost(&cnt->ip, NULL, port) == -1)
    {
      fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      return (1);
    }
  if (cnt->server.sock)
    SDLNet_TCP_Close(cnt->server.sock);
  cnt->server.sock = SDLNet_TCP_Open(&cnt->ip);
  if (!cnt->server.sock)
    {
      fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      return (1);
    }
  return (0);
}

int		init_connection(char *connectip, int port)
{
  t_client	*newclient;

  printf("se connecte:%s (%d)\n", connectip, port);
  if (SDLNet_ResolveHost(&cnt->ip, connectip, port) == -1)
    {
      fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      return (1);
    }
  newclient = create_client();
  newclient->sock = SDLNet_TCP_Open(&cnt->ip);
  if (!newclient->sock)
    {
      fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      delete_client(newclient);
      return (1);
    }
  insert_client(newclient);
  return (0);
}
