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

void		nop(int sig)
{
#ifndef WIN32
  if (sig == SIGPIPE)
    fprintf(stderr, "Caught \"Broken Pipe\", skipping..\n");
#endif
}

int		init_connection(int port)
{
  if (!cnt)
    {
      cnt = (t_connections*)xmalloc(sizeof(*cnt));
#ifndef WIN32
      signal(SIGPIPE, &nop);
#endif
      if (SDLNet_Init() == -1)
	{
	  fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	  return (1);
	}
      atexit(SDLNet_Quit);
	  cnt->host = 0;
      cnt->newclient = 0;
      cnt->deadclient = 0;
	  cnt->server.sock = 0;
      cnt->clients = (t_client*)xmalloc(sizeof(*cnt->clients));
      init_client(&cnt->clients[0]);
    }
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
  int		i;

  printf("se connecte:%s (%d)\n", connectip, port);
  fprintf(stderr, "se connecte:%s (%d)\n", connectip, port);
  if (!cnt)
    {
      cnt = (t_connections*)xmalloc(sizeof(*cnt));
#ifndef WIN32
      signal(SIGPIPE, &nop);
#endif
      if (SDLNet_Init() == -1)
	{
	  fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	  return (1);
	}
      atexit(SDLNet_Quit);
	  cnt->host = 0;
      cnt->server.sock = 0;
      cnt->newclient = 0;
      cnt->deadclient = 0;
      cnt->clients = (t_client*)xmalloc(sizeof(*cnt->clients));
      init_client(&cnt->clients[0]);
    }
  if (SDLNet_ResolveHost(&cnt->ip, connectip, port) == -1)
    {
      fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
      return (1);
    }
  for (i = 0; cnt->clients[i].sock; i++)
    ;
  cnt->clients = (t_client*)xrealloc(cnt->clients,
				     sizeof(*cnt->clients) * (i + 2));
  cnt->clients[i].sock = SDLNet_TCP_Open(&cnt->ip);
  if (!cnt->clients[i].sock)
    {
      fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
      return (1);
    }
  init_client(&cnt->clients[i + 1]);
  return (0);
}
