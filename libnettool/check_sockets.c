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

void		check_dead()
{
  t_tmp		*list;
  t_tmp		*next;

  //  printf("beffore\n");fflush(stdout);
  for (list = cnt->deadclient; list; list = next)
    {
      //      printf("durinnnng\n");fflush(stdout);
      next = list->next;
      call_handler(list->c, NULL);
      //      printf("duriinnnng2\n");fflush(stdout);
      delete_client(list->c);
      //      printf("during2.4\n");fflush(stdout);
      _net_xfree(list);
      //      printf("during3\n");fflush(stdout); 
   }
  //  printf("beffore after\n");fflush(stdout);
  cnt->deadclient = NULL;
}

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
      if (client->state)
	return (-1);
    }
  return (0);
}

int		check_client(fd_set *maskr, fd_set *maskw,
			     int *res, t_client *client)
{
  int		ret;

  if (is_quitting(client) ||
      (ret = manage_client(client, maskr, maskw, res)) < 0)
    {
      if (client->state != STATE_DROP)
	loss_client(client);
      return (-1);
    }
  else if (ret == 1)
    {
      const t_trame	*trame;
      
      cnt->select_recv = 1;
      while ((trame = exec_msg(client)))
	{
	  call_handler(client, trame);
	  if (is_quitting(client))
	    {
	      if (client->state != STATE_DROP)
		loss_client(client);
	      return (-1);
	    }
	}
      return (1);
    }
  return (0);
}

int		check_clients(fd_set *maskr, fd_set *maskw, int *res)
{
  t_tmp		*list;
  t_tmp		*next;
  int		i;
  int		ret;
  int		flg;

  flg = 0;
  // list des clients régularisés
  for (i = 0; *res > 0 && cnt->clients[i]; i++)
    {
      if ((ret = check_client(maskr, maskw, res, cnt->clients[i])))
	flg = 1;
      else if (ret < 0)
	i--;
    }
  // list des "new" clients
  for (list = cnt->newclient; *res > 0 && list; list = next)
    {
      next = list->next;
      if (check_client(maskr, maskw, res, list->c))
	flg = 1;
      list = next;
    }
  return (flg);
}

int		check_server(fd_set *maskr, fd_set *maskw, int *res)
{
  //  printf("bifton\n");fflush(stdout);
  if (cnt->server.sock)
    if (*res > 0 && FD_ISSET(cnt->server.sock->channel, maskr))
      {
	//	printf("bifton2\n");fflush(stdout);
	(*res)--;
	if (new_client(&cnt->newclient))
	  ;
	//	printf("bifton3\n");fflush(stdout);
	return (1);
      }
  //  printf("bifton4\n");fflush(stdout);
  return (0);
}
