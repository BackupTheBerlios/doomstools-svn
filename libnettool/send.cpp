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
** send.c for zappy in /u/ept2/huot_j/zappy
** 
** Made by jonathan huot
** Login   <huot_j@epita.fr>
** 
** Started on  Mon May 24 16:33:02 2004 jonathan huot
// Last update Tue Jun 29 19:29:46 2004 jonathan huot
*/

#include "libnettool.h"

int	my_send(TCPsocket sock, void *datap, int len)
{
//   Uint8 *data = (Uint8 *)datap;	/* For pointer arithmetic */
  int	sent;

  if (sock->sflag)
    {
      SDLNet_SetError("Server sockets cannot send");
      return (-1);
    }
  errno = 0;
#ifdef MACOS_OPENTRANSPORT
  sent = OTSnd(sock-.channel, datap, len, 0);
#else
  sent = send(sock->channel, (const char *) datap, len, 0);
  if (errno != EINTR && errno)
    SDLNet_SetError(strerror(errno));
#endif
  return (sent);
}

int		get_full_msg(t_client *client, char *msg,
			     unsigned int first)
{
  int		len;
  int		more;
  int		tmp;
  bool		thisone;

  more = NET_MSS;
  len = 0;
  while (more > 0 && (first != client->pos_send || !len) &&
	 TAG_SEND(client) >= 0)
    {
      thisone = false;
      tmp = sizeof(TAG_SEND(client)) + sizeof(LEN_SEND(client)) -
	POS_SEND(client);
      if (tmp > 0)
	{
	  if (tmp >= more)
	    {
	      memcpy(msg, &TAG_SEND(client) + POS_SEND(client), more);
	      len += more;
		  msg += more;
	      break;
	    }
	  else
	    {
	      memcpy(msg, &TAG_SEND(client) + POS_SEND(client), tmp);
	      more -= tmp;
	      len += tmp;
		  msg += tmp;
	      thisone = true;
	    }
	}
      if (LEN_SEND(client) > 0)
	{
	  tmp = LEN_SEND(client) - ((tmp < 0) ? (tmp) : (0));
	  if (tmp >= more)
	    {
	      memcpy(msg, MSG_SEND(client) +
		     ((thisone == false) ?
		      (POS_SEND(client) - sizeof(TAG_SEND(client)) -
		       sizeof(LEN_SEND(client))) : (0)), more);
	      len += more;
		  msg += more;
	      break;
	    }
	  else
	    {
	      memcpy(msg, MSG_SEND(client) , tmp);
	      more -= tmp;
	      len += tmp;
  		  msg += tmp;
	    }
	}
      if (++client->pos_send >= NET_MAX_MSG)
	client->pos_send = 0;
    }
  return (len);
}

int		update_sent_msg(t_client *client, int len,
				int result, int first)
{
  int		start;
  unsigned int	save;
  int		tmp;

  save = client->pos_send;
  client->pos_send = first;
  start = 0;
  while (result > 0)
    {
      tmp = sizeof(TAG_SEND(client)) + sizeof(LEN_SEND(client)) -
	POS_SEND(client);
      if (tmp > 0)
	{
	  if (result >= tmp)
	    {
	      result -= tmp;
	      start += tmp;
	      POS_SEND(client) += tmp;
	    }
	  else
	    {
	      POS_SEND(client) += result;
	      break;
	    }
	}
      if (LEN_SEND(client) > 0)
	{
	  tmp = LEN_SEND(client) - ((tmp < 0) ? (tmp) : (0));
	  if (tmp > 0)
	    {
	      if (result >= tmp)
		{
		  result -= tmp;
		  start += tmp;
		  POS_SEND(client) += tmp;
		}
	      else
		{
		  POS_SEND(client) += result;
		  break;
		}
	    }
	}
      if (MSG_SEND(client))
	free(MSG_SEND(client));
      init_msg(&client->send[client->pos_send]);
      if (++client->pos_send >= NET_MAX_MSG)
	client->pos_send = 0;
    }
  if (client->pos_send != save)
    {
      fprintf(stderr, "bug...%d, %d\n", client->pos_send, save);
    }
  return (0);
}

int		put_msg(t_client *client)
{
  int		result;
  static char	*msg = 0;
  int		len;
  unsigned int	first;

   if (!msg)
     msg = (char*)xmalloc(sizeof(*msg) * NET_MSS);
   first = client->pos_send;
   len = get_full_msg(client, msg, first);
//  if (TAG_SEND(client) >= 0)
//    {
//      if (POS_SEND(client) < sizeof(TAG_SEND(client)) +
// 	 sizeof(LEN_SEND(client)))
// 	result = my_send(client->sock, &TAG_SEND(client) + POS_SEND(client),
// 			 sizeof(TAG_SEND(client)) + sizeof(LEN_SEND(client)));
//      else
// 	result = my_send(client->sock, MSG_SEND(client) + POS_SEND(client) -
// 			 sizeof(TAG_SEND(client)) - sizeof(LEN_SEND(client)),
// 			 (sizeof(*MSG_SEND(client)) * LEN_SEND(client)) -
// 			 POS_SEND(client) +
// 			 sizeof(TAG_SEND(client)) +
// 			 sizeof(LEN_SEND(client)));
//    }
   result = my_send(client->sock, msg, len);
   if (result <= 0)
     {
       NETDEBUG(SDLNet_GetError());
       client->loss = STATE_DROP;
	fprintf(stderr, "STATE_FAIL_RECV ! (%d, %s)\n", result, strerror(errno));
       // met dans list deadclient, avec un etat 'drop'
       return (0);
     }
   update_sent_msg(client, len, result, first);
//  POS_SEND(client) += result;
//  if (POS_SEND(client) >= sizeof(TAG_SEND(client)) +
//      sizeof(LEN_SEND(client)) + (sizeof(*MSG_SEND(client)) *
// 				  LEN_SEND(client)))
//    {
//      if (MSG_SEND(client))
// 	free(MSG_SEND(client));
//      init_msg(&client->send[client->pos_send]);
//      if (++client->pos_send >= NET_MAX_MSG)
// 	client->pos_send = 0;
//    }
  return (result);
}

int		stock_msg(t_client *client, short tag,
			  unsigned int len, void *msg)
{
  if (client->pos_stock == client->pos_send && TAG_SEND(client) >= 0)
    {
      fprintf(stderr, "WARNING: Too much request, skipping\n");
      return (0);
    }
  TAG_STOCK(client) = tag;
  LEN_STOCK(client) = len;
  POS_STOCK(client) = 0;
  if (len)
    {
      MSG_STOCK(client) = (char*)xmalloc(sizeof(*MSG_STOCK(client)) * len);
      memcpy(MSG_STOCK(client), msg, len);
    }
  else
    MSG_STOCK(client) = 0;
  if (++client->pos_stock >= NET_MAX_MSG)
    client->pos_stock = 0;
  return (1);
}
