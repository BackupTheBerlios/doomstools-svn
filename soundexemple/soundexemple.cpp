#include "libsoundtool.h"

int	main(int ac, char **av)
{
  int	bloahh;

  if (!soundtool_init())
    return (1);
  if ((bloahh = load_sound("bloahh.wav")) < 0)
    return (2);
  play_sound(bloahh);
  soundtool_quit();
  return (0);
}
