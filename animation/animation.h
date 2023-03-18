#ifndef RACING_GAME_H
# define RACING_GAME_H

# include "get_next_line/get_next_line.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define FRAME_RATE 20
# define TRUE 1

typedef struct pos
{
	int	x;
	int	y;
}		pos_t;

typedef struct color
{
	int	R;
	int	G;
	int	B;
	int	A;
}		color_t;

char	**get_map(void);
size_t	list_lenght(char **list);
#endif