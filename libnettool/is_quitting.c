#include "libnettool.h"

int		is_quitting(t_client *c)
{
  if (c->state == STATE_DROP ||
      c->state == STATE_FAIL_RECV ||
      c->state == STATE_FAIL_SEND)
    return (1);
  return (0);
}
