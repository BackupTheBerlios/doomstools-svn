#include "libsoundtool.h"

t_soundtool	*snd = NULL;

bool	soundtool_init()
{
  ALCdevice *dev;

  if (!snd)
    snd = (t_soundtool*)_sound_xmalloc(sizeof(*snd));
  if (!(dev = alcOpenDevice(NULL)))
    return (false);
  snd->dev = dev;
  return (true);
}

void	soundtool_quit()
{
  alcCloseDevice(snd->dev);
}

int	load_sound(char *file)
{
  return (0);
}

void	play_sound(int id)
{
  
}
