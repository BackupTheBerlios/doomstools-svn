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
** check_sockets.c for zappy in /u/ept2/huot_j
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Tue May 25 13:08:39 2004 jonathan huot
// Last update Tue Jun 29 18:03:45 2004 jonathan huot
*/

#include "libnettool.h"

int		manage_client(t_client *client, fd_set *maskr, fd_set *maskw,
			      int *res)
{
  if (FD_ISSET(client->sock->channel, maskw))
    {
      (*res)--;
      if (!put_msg(client))
	return (-1);
    }
  if (*res > 0 && FD_ISSET(client->sock->channel, maskr))
    {
      (*res)--;
      if (get_msg(client))
	return (1);
      if (client->loss)
	return (-1);
    }
  return (0);
}

int		check_tmp(t_tmp **newclt, fd_set *maskr, fd_set *maskw,
			  int *res)
{
  t_tmp		*list;
  t_tmp		*next;
  int		flg;
  int		ret;

  flg = 0;
  for (list = *newclt; *res > 0 && list; list = next)
    {
      next = list->next;
      if ((ret = manage_client(list->c, maskr, maskw, res)) < 0)
	{
	  call_deadhandler(cnt->deadclient->c, NULL);
	  SDLNet_TCP_Close(list->c->sock);
	  *newclt = del_in_list(*newclt, list->c);
	  delete_client(list->c);
	}
      if (ret == 1)
	{
	  const t_trame	*trame;
	  t_client	*clt;

	  // obligatoirement dans newlist
	  flg = 1;
	  clt = list->c;
	  while ((trame = exec_msg(clt)))
	    if (!clt->authorized)
	      call_newhandler(clt, trame);
	    else
	      call_clienthandler(clt, trame);
	}
      if (*res <= 0)
	return (flg);
      list = next;
    }
  return (flg);
}

int		check_clients(fd_set *maskr, fd_set *maskw, int *res)
{
  int		i;
  int		ret;
  int		flg;

  flg = 0;
  for (i = 0; *res > 0 && cnt->clients[i]; i++)
    {
      if ((ret = manage_client(cnt->clients[i], maskr, maskw, res)) < 0)
	{
	  loss_client(cnt->clients[i]);
	  i = -1;
	}
      if (ret == 1)
	{
	  const t_trame	*trame;

	  flg = 1;
	  while ((trame = exec_msg(cnt->clients[i])))
	    call_clienthandler(cnt->clients[i], trame);
	}
      if (*res <= 0)
	return (flg);
    }
  return (flg);
}

int		check_server(fd_set *maskr, fd_set *maskw, int *res)
{
  if (cnt->server.sock)
    if (*res > 0 && FD_ISSET(cnt->server.sock->channel, maskr))
      {
	(*res)--;
	if (new_client(&cnt->newclient))
	  ;
	return (1);
      }
  return (0);
}
