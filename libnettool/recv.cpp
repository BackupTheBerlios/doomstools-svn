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
** recv.c for network in /u/ept2/huot_j/network_engine
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Wed Jun 16 10:48:55 2004 jonathan huot
// Last update Tue Jun 29 17:53:14 2004 jonathan huot
*/

#include "libnettool.h"

#ifdef MACOS_OPENTRANSPORT
// no modified.. waiting for a MAC!
int	recv(TCPsocket sock, void *data, int maxlen)
{
	int len = 0;
	OSStatus res;
	/* Server sockets are for accepting connections only */
	if ( sock->sflag ) {
		SDLNet_SetError("Server sockets cannot receive");
		return(-1);
	}
	do
	{
		res = OTRcv(sock->channel, data, maxlen-len, 0);
		if (res > 0) {
			len = res;
		}
		AsyncTCPPopEvent(sock);
		if( res == kOTLookErr )
		{
			res = OTLook(sock->channel );
			continue;
		}
	} while ( (len == 0) && (res == kOTNoDataErr) );

	sock->ready = 0;
	if ( len == 0 ) { /* Open Transport error */
		return(-1);
	}
	return(len);
}

#else
int	my_recv(TCPsocket sock, void *data, int maxlen)
{
  int	len;

  /* Server sockets are for accepting connections only */
  if (sock->sflag)
    {
      SDLNet_SetError("Server sockets cannot receive");
      return(-1);
    }
  errno = 0;
/*   do { */
    len = recv(sock->channel, (char *) data, maxlen, 0);
/*   } while ( errno == EINTR ); */
/*   sock->ready = 0; */
  return (len);
}
#endif /* MACOS_OPENTRANSPORT */

int		cut_trame_in_msg(t_client *client, char *msg, int result)
{
  int		tmp;
  int		got_one;

  got_one = 0;
  while (result > 0)
    {
      tmp = sizeof(TAG_RECV(client)) + sizeof(LEN_RECV(client)) -
	POS_RECV(client);
      if (tmp > 0)
	{
	  if (result < tmp)
	    tmp = result;
	  memcpy(&TAG_RECV(client) + POS_RECV(client), msg, tmp);
	  POS_RECV(client) += tmp;
	  msg += tmp;
	  result -= tmp;
	}
      if (result > 0 && LEN_RECV(client) > 0)
	{
	  tmp = (LEN_RECV(client) * sizeof(*MSG_RECV(client)))
	    + ((tmp < 0) ? (tmp) : (0));
	  if (result < tmp)
	    tmp = result;
	  if (!MSG_RECV(client))
	    MSG_RECV(client) = (char*)xmalloc(sizeof(*MSG_RECV(client)) *
					      LEN_RECV(client));
	  memcpy(MSG_RECV(client) + POS_RECV(client) -
		 sizeof(TAG_RECV(client)) - sizeof(LEN_RECV(client)),
		 msg, tmp);
	  POS_RECV(client) += tmp;
	  msg += tmp;
	  result -= tmp;
	}
      if (result > 0 || (!result &&
			 POS_RECV(client) == sizeof(TAG_RECV(client)) +
			 sizeof(LEN_RECV(client)) +
			 (LEN_RECV(client) * sizeof(*MSG_RECV(client)))))
	{
	  got_one = 1;
	  if (++client->pos_recv >= NET_MAX_MSG)
	    client->pos_recv = 0;
	}
    }
  return (got_one);
}

Uint32		get_msg(t_client *client)
{
  int		result;
  static char	*data = 0;

  if (!data)
    data = (char*)xmalloc(sizeof(*data) * NET_MSS);
  // if (POS_RECV(client) < sizeof(TAG_RECV(client)) + sizeof(LEN_RECV(client)))
  //   result = my_recv(client->sock, &TAG_RECV(client) + POS_RECV(client),
 	//	     sizeof(TAG_RECV(client)) + sizeof(LEN_RECV(client)));
  // else
  //   {
  //     if (!MSG_RECV(client))
 	//MSG_RECV(client) = (char*)xmalloc(sizeof(*MSG_RECV(client)) *
 	//				  LEN_RECV(client));
  //     result = my_recv(client->sock, MSG_RECV(client) + POS_RECV(client) -
 	//		sizeof(TAG_RECV(client)) - sizeof(LEN_RECV(client)),
 	//	       (sizeof(*MSG_RECV(client)) * LEN_RECV(client)) -
 	//	       POS_RECV(client) +
 	//	       sizeof(TAG_RECV(client)) +
 	//	       sizeof(LEN_RECV(client)));
  //   }
  result = my_recv(client->sock, data, NET_MSS);
  if (result <= 0)
    {
      if (SDLNet_GetError() && strlen(SDLNet_GetError()))
	{
	  NETDEBUG(SDLNet_GetError());
	}
      client->loss = (unsigned long)STATE_FAIL_RECV;
	  fprintf(fd_log, "loss :%s, %d, %d\n", strerror(errno), result, data);
      // met dans list deadclient, avec un etat 'fail_recv'
      // (essaie donc d'ecrire qd meme sur la socket)

      // ou la liste de commandes est trop importante..
      return (0);
    }
  if (cut_trame_in_msg(client, data, result))
    return (1);
  // POS_RECV(client) += result;
  // if (POS_RECV(client) >= (LEN_RECV(client) * sizeof(*MSG_RECV(client))) +
  //     sizeof(TAG_RECV(client)) + sizeof(LEN_RECV(client)))
  //   {
  //     if (++client->pos_recv >= NET_MAX_MSG)
 	//client->pos_recv = 0;
  //     return (1);
  //   }
  return (0);
}

int		exec_msg(t_client *client, t_trame *t)
{
  if (!t)
    return (0);
  if (msg_wait(client))
    {
      t->tag = TAG_EXEC(client);
      t->len = LEN_EXEC(client);
      t->msg = MSG_EXEC(client);
      init_msg(&client->recv[client->pos_exec]);
      if (++client->pos_exec >= NET_MAX_MSG)
	client->pos_exec = 0;
      return (1);
    }
  return (0);
}
