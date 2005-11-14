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

struct SDLNet_Socket {
	int ready;
	SOCKET channel;
#ifdef MACOS_OPENTRANSPORT
	OTEventCode curEvent;
#endif
};

t_connections		*cnt = NULL;

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
      if (list->c->sock->channel > maxfd)
	maxfd = list->c->sock->channel;
      FD_SET(list->c->sock->channel, maskr);
      if (TAG_SEND(list->c) >= 0)
	FD_SET(list->c->sock->channel, maskw);
    }
  for (n = 0; cnt->clients[n]; n++)
    {
      if (cnt->clients[n]->sock->channel > maxfd)
	maxfd = cnt->clients[n]->sock->channel;
      FD_SET(cnt->clients[n]->sock->channel, maskr);
      if (TAG_SEND(cnt->clients[n]) >= 0)
	FD_SET(cnt->clients[n]->sock->channel, maskw);
    }
  return (maxfd);
}

#ifndef macintosh
int			check_select(Uint32 timeout)
{
  SOCKET		maxfd;
  int			retval;
  struct timeval	tv;
  struct timeval	before;
  struct timeval	left;
  fd_set		maskr;
  fd_set		maskw;
  int			done;

  check_dead();
  FD_ZERO(&maskr);
  FD_ZERO(&maskw);
  maxfd = fill_fd(&maskr, &maskw); 
  tv.tv_sec = timeout / 1000;
  tv.tv_usec = (timeout % 1000) * 1000;
  done = 0;
  while (!done)
    {
      cnt->select_recv = 0;
      gettimeofday(&before, NULL);
      retval = select((int)maxfd + 1, &maskr, &maskw, NULL, &tv);
      done = 0;
      if (retval > 0 && check_clients(&maskr, &maskw, &retval))
	done += 1;
      if (retval > 0 && check_server(&maskr, &maskw, &retval))
	done += 8;
      if (retval)
	{
	  if (retval < 0 && errno != EINTR)
	    fprintf(stderr, "select: %s", strerror(errno));
	  else
	    fprintf(stderr, "select: on m'aurait mentit (reste:%d) ?\n",
		    retval);
	  exit(-1);
	}
      check_dead();
      if (!timeout)
	return (done);
      gettimeofday(&left, NULL);
      left.tv_sec -= before.tv_sec;
      left.tv_usec -= before.tv_usec;
      if (cnt->select_recv &&
	  left.tv_sec < tv.tv_sec && left.tv_usec < tv.tv_usec)
	{
	  done = 0;
	  memcpy(&tv, &left, sizeof(left));
	}
    }
  return (done);
}

#else // qqn a un mac?
int			check_select(Uint32 timeout)
{
  return (0);
}
#endif
