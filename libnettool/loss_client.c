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

void		del_from_clients(t_client *c)
{
  int		i;

  printf("loss_client\n");fflush(stdout);
  for (i = 0; cnt->clients[i]; i++)
    if (cnt->clients[i] == c)
      break;
  move_last_client(i);
}

void		del_from_tmp(t_client *c)
{
  printf("loss_ctmplient\n");fflush(stdout);
  cnt->newclient = del_in_list(cnt->newclient, c);
}

void assert_my_asshole(t_client *c)
{
  int i;
  t_tmp *list;

  for (i = 0; cnt->clients[i]; i++)
    if (cnt->clients[i] == c)
      exit(42);
  for (list = cnt->newclient; list; list = list->next)
    if (list->c == c)
      exit(43);
}

void		loss_client(t_client *c)
{
  printf("loss client %d\n", (int)c);fflush(stdout);
  if (c->authorized)
   del_from_clients(c);
  else
   del_from_tmp(c);
  close_socket(&c->sock);
  put_in_tmp_client(&cnt->deadclient, c);
  assert_my_asshole(c);
}
