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
#ifndef _NET_COMMON_H_
#define _NET_COMMON_H_

#define NET_MAX_MSG		(1024)
#define NET_MSS			(1460)

#ifndef TAG_WELCOME
#define TAG_WELCOME		(0)
#endif
#ifndef TAG_DEAD
#define TAG_DEAD		(42)
#endif

#define STATE_NEW		(0)
#define STATE_DEAD		(1)
#define STATE_DROP		(2)
#define STATE_FAIL_RECV		(3)
#define STATE_PLAYER	(4)

typedef struct		s_trame
{
  short			tag;
  unsigned int		len;
  char			*msg;
  unsigned int		pos;
}			t_trame;

typedef struct		s_ctrame
{
/* options de cryptage... */
/*   unsigned char		tag; */
/*   unsigned long		sign; */
/*   unsigned long		md5; */
  t_trame		trame;
}			t_ctrame;

typedef struct		s_client
{
  unsigned int		pos_recv;
  unsigned int		pos_exec;
  unsigned int		pos_send;
  unsigned int		pos_stock;
  t_trame		recv[NET_MAX_MSG];
  t_trame		send[NET_MAX_MSG];
  TCPsocket		sock;
  unsigned long		loss;
}			t_client;

typedef struct		s_tmp
{
  int			state;
  t_client		c;
  struct s_tmp		*next;
}			t_tmp;

extern struct s_connections	*cnt;

/*
** recv.c
*/
int		my_recv(TCPsocket sock, void *data, int maxlen);
Uint32		get_msg(struct s_client *client);
int		LIBNETTOOL_API exec_msg(struct s_client *client, struct s_trame *t);

/*
** send.c
*/
int		my_send(TCPsocket sock, void *datap, int len);
int		put_msg(struct s_client *client);
int		LIBNETTOOL_API stock_msg(struct s_client *client, short tag,
			  unsigned int len, void *msg);

/*
** list.c
*/
void		free_list_client(struct s_tmp *newtmp);
void		put_in_tmp_client(struct s_tmp **begin, struct s_client *c);
struct s_tmp	*del_in_list(struct s_tmp *newtmp, struct s_client *c);
void		put_in_client(struct s_tmp **begin, TCPsocket sock, int state);

/*
** check_sockets.c
*/
int		check_tmp(struct s_tmp **newtmp, fd_set *maskr,
			  fd_set *maskw, int *res);
int		manage_client(struct s_client **client, fd_set *maskr,
			      fd_set *maskw, int *res);
int		check_clients(fd_set *maskr, fd_set *maskw, int *res);
int		check_server(fd_set *maskr, fd_set *maskw, int *res);

/*
** old.c // deprecated
*/
int			is_valid_trame(t_trame *t, short tag);
void			send_trame(t_client *clt, t_trame *tlv);
int			recv_trame(t_client *client, t_trame *trame);
int			receive_one_request(t_trame *req);
int			recv_client_req(t_client *client, t_trame *req);
/*
** solo
*/
int		LIBNETTOOL_API msg_wait(struct s_client *client);
void		move_last_player(int no);
int		loss_client(struct s_client *c);
void		free_client(struct s_client *c);
int		LIBNETTOOL_API check_select(Uint32 timeout);
void		init_msg(struct s_trame *msg);
void		init_client(struct s_client *client);
int		LIBNETTOOL_API init_connection(int port);
int		LIBNETTOOL_API init_connection(char *ip, int port);
void	LIBNETTOOL_API 	close_connection();
void		add_client();
int		new_client(struct s_tmp **newtmp);
void	LIBNETTOOL_API	drop_client(struct s_client *clt);
#endif
