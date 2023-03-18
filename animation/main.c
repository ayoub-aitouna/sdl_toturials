#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#define FRAME_RATE 20

typedef struct pos
{
	int			x;
	int			y;
}				pos_t;

typedef struct frams
{
	u_int64_t	fm1;
	u_int64_t	fm2;
}				frams_t;

typedef struct color
{
	int			R;
	int			G;
	int			B;
	int			A;
}				color_t;

void	draw_line(SDL_Renderer *renderer, pos_t start, float angle, int width,
		color_t color)
{
	float	i_raduise;
	int		new_x;
	int		new_y;

	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	i_raduise = 0;
	while (i_raduise < width)
	{
		new_x = start.x + i_raduise * cos(angle);
		new_y = start.y + i_raduise * sin(angle);
		SDL_RenderDrawPoint(renderer, new_x, new_y);
		i_raduise += .5;
	}
}

void	clear(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void	update(SDL_Renderer *renderer, float play_angle)
{
	float	angle;
	int		i;

	angle = play_angle - 0.5;
	i = 0;
	pos_t start = {
		.x = 500,
		.y = 250};
	color_t color = {
		.A = 255,
		.B = 255,
		.G = 255,
		.R = 255};
	clear(renderer);
	while (angle <= play_angle)
	{
		draw_line(renderer, start, angle, 250, color);
		angle += .01;
	}
	SDL_RenderPresent(renderer);
}

long int	get_time(void)
{
	long int		curr_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (curr_time);
}
int	main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	frams_t			T;
	SDL_Event		event;
	float			player_angle;
	float			rotation_speed;

	player_angle = 80;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("draw_line", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 500, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	T.fm1 = get_time();
	T.fm2 = get_time();
	rotation_speed = 0.5;
	while (1)
	{
		player_angle += rotation_speed;
		if (player_angle >= 360)
			player_angle = 0;
		update(renderer, player_angle);
		T.fm2 = T.fm1;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(0);
			if (event.type == SDL_KEYDOWN)
			{					
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
					update(renderer, --player_angle);
			}
		}
		SDL_Delay(1000 / FRAME_RATE);
	}
	return (0);
}
