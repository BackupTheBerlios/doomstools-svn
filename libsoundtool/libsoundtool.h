#ifndef _LIBSOUNDTOOL_H_
#define _LIBSOUNDTOOL_H_

#include <stdlib.h>
#include <stdio.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/alut.h>

extern struct s_soundtool	*snd;

typedef struct	s_soundtool
{
  ALCdevice	*dev;
}		t_soundtool;

bool	soundtool_init();
void	soundtool_quit();
int	load_sound(char *file);
void	play_sound(int id);


/*
** xstd
*/
void		*_sound_xmalloc(size_t len);
void		*_sound_xrealloc(void *ptr, size_t len);
void            _sound_my_free_ptr_ptr(char **p);
void		_sound_xfree(void *p);

#endif
