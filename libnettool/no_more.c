#include "libnettool.h"

int	no_more(t_client *c)
{
  t_tmp *list;
  int	i;

  for (list = cnt->newclient; list; list = list->next)
    if (list->c == c)
      return (0);
  for (i = 0; cnt->clients[i]; i++)
    if (cnt->clients[i] == c)
      return (0);
  return (1);
}
