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
** my_net.c for zappy in /sgoinfre/freewar/SDL_net-1.2.5
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Mon May 31 15:25:32 2004 jonathan huot
// Last update Tue Jun 29 19:20:51 2004 jonathan huot
*/

#include "libnettool.h"

struct SDLNet_Socket {
	int ready;
	SOCKET channel;
#ifdef MACOS_OPENTRANSPORT
	OTEventCode curEvent;
#endif
};

t_connections		*cnt = 0;

SOCKET			fill_fd(fd_set *maskr, fd_set *maskw)
{
  SOCKET		maxfd;
  int			n;
  t_tmp			*list;

  if (cnt->server.sock)
    {
      FD_SET(cnt->server.sock->channel, maskr);
      maxfd = cnt->server.sock->channel;
    }
  else
    maxfd = 0;
  for (list = cnt->newclient; list; list = list->next)
    {
      if (list->c.sock->channel > maxfd)
	maxfd = list->c.sock->channel;
      FD_SET(list->c.sock->channel, maskr);
      if (STAG_SEND(list->c) >= 0)
	FD_SET(list->c.sock->channel, maskw);
    }
  for (n = 0; cnt->clients[n].sock; n++)
    {
      if (cnt->clients[n].sock->channel > maxfd)
	maxfd = cnt->clients[n].sock->channel;
      FD_SET(cnt->clients[n].sock->channel, maskr);
      if (STAG_SEND(cnt->clients[n]) >= 0)
	FD_SET(cnt->clients[n].sock->channel, maskw);
    }
  for (list = cnt->deadclient; list; list = list->next)
    {
      if (list->c.sock->channel > maxfd)
	maxfd = list->c.sock->channel;
      if (STAG_SEND(list->c) >= 0)
	FD_SET(list->c.sock->channel, maskw);
    }
  return (maxfd);
}

#ifndef macintosh
int			check_select(Uint32 timeout)
{
  SOCKET		maxfd;
  int			retval;
  struct timeval	tv;
  fd_set		maskr;
  fd_set		maskw;
  int			done;

  FD_ZERO(&maskr);
  FD_ZERO(&maskw);
  maxfd = fill_fd(&maskr, &maskw);
  tv.tv_sec = timeout / 1000;
  tv.tv_usec = (timeout % 1000) * 1000;
  retval = select((int)maxfd + 1, &maskr, &maskw, NULL, &tv);
  done = 0;
  cnt->last_recv = 0;
  if (retval > 0 && check_clients(&maskr, &maskw, &retval))
    done += 4;
  if (retval > 0 && check_tmp(&cnt->newclient, &maskr, &maskw, &retval))
    done += 1;
  if (retval > 0 && check_tmp(&cnt->deadclient, &maskr, &maskw, &retval))
    done += 2;
  if (retval > 0 && check_server(&maskr, &maskw, &retval))
    done += 8;
#ifdef NETWORK_DEBUG
  if (retval)
    {
      if (retval < 0 && errno != EINTR)
	fprintf(stderr, "select: %s", strerror(errno));
      else
	fprintf(stderr, "select: on m'aurait mentit (reste:%d) ?\n", retval);
      exit(-1);
    }
#endif
  return (done);
}

#else // qqn a un mac?
int			my_select(t_connections *cnt, Uint32 timeout)
{
  return (0);
}
#endif
