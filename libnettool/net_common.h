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
#define STATE_FAIL_RECV		(1)
#define STATE_FAIL_SEND		(2)
#define STATE_DROP		(3)

typedef TCPsocket	t_socket;

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
  t_socket		sock;
  unsigned short	authorized;
  unsigned long		loss;
  int			state;
  void			*data; // le no du player associe' par exemple.
}			t_client;

typedef struct		s_tmp
{
  t_client		*c;
  struct s_tmp		*next;
}			t_tmp;

extern struct s_connections	*cnt;

/*
** assign.c
*/
void	assign_newclient(void (*f)(t_client *c, const t_trame *t, void *d),
			 void *d);
void	assign_deadclient(void (*f)(t_client *c, const t_trame *t, void *d),
			  void *d);
void	assign_clients(void (*f)(t_client *c, const t_trame *t, void *d),
		       void *d);

/*
** recv.c
*/
int		my_recv(TCPsocket sock, void *data, int maxlen);
Uint32		get_msg(struct s_client *client);
const t_trame	*_get_trame(t_client *client);
// OLDVERSION:
/* int		exec_msg(struct s_client *client, struct s_trame *t); */
// NEWONE:
const t_trame	*exec_msg(struct s_client *client);

/*
** send.c
*/
int		my_send(TCPsocket sock, void *datap, int len);
int		put_msg(struct s_client *client);

int		stock_msg(struct s_client *client, short tag,
			  unsigned int len, void *msg);
int		stock_remote_msg(short tag, unsigned int len, void *msg);

/*
** list.c
*/
void		_freelist(struct s_tmp **newtmp);
void		put_in_tmp_client(struct s_tmp **begin, struct s_client *c);
struct s_tmp	*del_in_list(struct s_tmp *newtmp, struct s_client *c);
void		put_in_client(struct s_tmp **begin, TCPsocket sock, int state);

/*
** check_sockets.c
*/
int		manage_client(struct s_client *client, fd_set *maskr,
			      fd_set *maskw, int *res);
int		check_clients(fd_set *maskr, fd_set *maskw, int *res);
int		check_server(fd_set *maskr, fd_set *maskw, int *res);
void		check_dead();

/*
** close_connection.c
*/
void		close_client_connection(t_client *client);
void		close_connection();
void		close_server_connection();

/*
** solo
*/
int		msg_wait(struct s_client *client);
int		check_select(Uint32 timeout);
int		init_server_connection(int port);
int		init_connection(char *ip, int port);
void		drop_client(struct s_client *clt);
void		init_nettool();
void		nettool_quit();
void		move_last_client(unsigned int no);
void		free_client_data(struct s_client *c);
void		delete_client(struct s_client *c);
void		init_msg(struct s_trame *msg);
void		init_client(struct s_client *client);
void		add_client();
int		new_client(struct s_tmp **newtmp);
void		authorize_client(t_client *c);
void		insert_client(t_client *c);
t_client	*create_client();
void		set_data_client(t_client *c, void *p);
int		is_quitting(t_client *c);
int		no_more(t_client *c);

/*
** some shit
*/
void		*_net_xmalloc(size_t len);
void		*_net_xrealloc(void *ptr, size_t len);
void            _net_my_free_ptr_ptr(char **p);
void		_net_xfree(void *p);

/*
** call_handler.c
*/
void		call_clienthandler(t_client *client,
				   const t_trame *trame);
void		call_deadhandler(t_client *client,
				 const t_trame *trame);
void		call_newhandler(t_client *client,
				const t_trame *trame);
void		call_handler(t_client *client,
			     const t_trame *trame);
/*
** loss_client
*/
void		del_from_tmp(struct s_client *c);
void		del_from_clients(struct s_client *c);
void		loss_client(struct s_client *c);
/*
** close_socket.c
*/
void		close_socket(t_socket *sock);
/*
** old.c
*/
int			is_valid_trame(t_trame *t, short tag);
void			send_trame(t_client *clt, t_trame *tlv);
/* int			recv_trame(t_client *client, t_trame *trame); */
/* int			receive_one_request(t_trame *req); */
/* int			recv_client_req(t_client *client, t_trame *req); */

#endif
