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

void	nop(int sig)
{
#ifndef WIN32
  if (sig == SIGPIPE)
    fprintf(stderr, "Caught \"Broken Pipe\", skipping..\n");
#endif
}

void	init_nettool()
{
  if (cnt)
    nettool_quit();
  cnt = (t_connections*)_net_xmalloc(sizeof(*cnt));
#ifndef WIN32
  signal(SIGPIPE, &nop);
#endif
  if (SDLNet_Init() == -1)
    {
      fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
      exit(-1);
    }
  atexit(SDLNet_Quit);
  cnt->host = 0;
  cnt->newclient = NULL;
  cnt->deadclient = NULL;
  cnt->server.sock = 0;
  cnt->allclients = NULL;
  cnt->clients = (t_client**)_net_xmalloc(sizeof(*cnt->clients));
  cnt->clients[0] = NULL;
}
