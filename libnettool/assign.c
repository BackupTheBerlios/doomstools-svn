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

void	assign_newclient(void (*f)(t_client *t, const t_trame *t, void *d),
			 void *data)
{
  // appeler t = NULL dans le cas de la connexion, puis avec un argument 
  // jusqu'a ce qu'il soit transferé en client normal. (cf authorize_client())
  cnt->f_newclient = f;
  cnt->data_newclient = data;
}

void	assign_deadclient(void (*f)(t_client *t, const t_trame *t, void *d),
			  void *data)
{
  // appeler dans le cas d'une deconnexion d'un newclient, ou d'un client.
  cnt->f_deadclient = f;
  cnt->data_deadclient = data;
}

void	assign_clients(void (*f)(t_client *t, const t_trame *t, void *d),
		       void *data)
{
  // appeler des reception d'une trame complete d'un client normal.
  cnt->f_clients = f;
  cnt->data_clients = data;
}

