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

void		call_newhandler(t_client *client,
				const t_trame *trame)
{
  if (cnt->f_newclient)
    cnt->f_newclient(client, trame, cnt->data_newclient);
  else
    fprintf(stderr, "warning: no ptr func for newclient\n");
}

void		call_deadhandler(t_client *client,
				 const t_trame *trame)
{
  if (cnt->f_deadclient)
    cnt->f_deadclient(client, trame, cnt->data_deadclient);
  else
    fprintf(stderr, "warning: no ptr func for deadclient\n"); 
}

void		call_clienthandler(t_client *client,
				   const t_trame *trame)
{
   if (cnt->f_clients)
    cnt->f_clients(client, trame, cnt->data_clients);
  else
    fprintf(stderr, "warning: no ptr func for clients\n"); 
}
