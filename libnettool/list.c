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

void		_freelist(t_tmp **origin)
{
  t_tmp		*next;
  t_tmp		*list;

  list = *origin;
  while (list)
    {
      next = list->next;
      _net_xfree(list);
      list = next;
    }
  *origin = NULL;
}

t_tmp	*del_in_list(t_tmp *newclt, t_client *c)
{
  t_tmp	*prev;
  t_tmp	*next;
  t_tmp	*first;

  if (!newclt)
    return (0);
  first = newclt;
  prev = 0;
  while (newclt)
    {
      if (newclt->c == c)
	{
	  next = newclt->next;
	  _net_xfree(newclt);
	  if (!prev)
	    return (next);
	  prev->next = next;
	  break;
	}
      prev = newclt;
      newclt = newclt->next;
    }
  return (first);
}

void	put_in_tmp_client(t_tmp **begin, t_client *c)
{
  t_tmp	*newclt;

  newclt = (t_tmp*)_net_xmalloc(sizeof(*newclt));
  newclt->c = c;
  newclt->next = *begin;
  *begin = newclt;
}

void	put_in_client(t_tmp **begin, TCPsocket sock, int state)
{
  t_tmp	*newclt;

  NETDEBUG("client ready to put\n");
  newclt = (t_tmp*)_net_xmalloc(sizeof(*newclt));
  newclt->c = create_client();
  newclt->c->sock = sock;
  newclt->c->state = state;
  newclt->next = *begin;
  *begin = newclt;
  NETDEBUG("client put\n");
}
