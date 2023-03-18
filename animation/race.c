#include "animation.h"

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

void	draw_block(SDL_Renderer *renderer, pos_t position, color_t *color,
		int block_size)
{
	int		x;
	int		y;
	color_t	outline;

	x = position.x + 1,
	y = position.y + 1;
	outline.A = 255;
	outline.B = 255;
	outline.R = 100;
	outline.G = 0;
	while (x < position.x + block_size - 1)
	{
		y = position.y;
		while (y < position.y + block_size - 1)
		{
			if (x == 0 || y == 0 || x == position.x + block_size - 2
				|| y == position.y + block_size - 2)
				SDL_SetRenderDrawColor(renderer, outline.R, outline.G,
						outline.B, outline.A);
			else
				SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B,
						color->A);
			SDL_RenderDrawPoint(renderer, x, y);
			y++;
		}
		x++;
	}
}

int	section(SDL_Renderer *renderer, color_t *color, char **map, int start,
		int end, int draw_pos)
{
	int		block_size;
	pos_t	cur_pos;
	int		j;
	int		i;

	j = 0;
	block_size = 20;
	i = draw_pos;
	while (start < end)
	{
		j = 0;
		while (map[start][j])
		{
			if (map[start][j] == '1')
			{
				cur_pos.x = j * block_size;
				cur_pos.y = i * block_size;
				draw_block(renderer, cur_pos, color, block_size);
			}
			j++;
		}
		i++;
		start++;
	}
	return (i);
}

void	map(SDL_Renderer *renderer, color_t *color, char **map, int start)
{
	int	list_len;
	int	end;

	list_len = list_lenght(map) - 1;
	printf("len %d \n", list_len);
	end = section(renderer, color, map, start, list_len, 0);
	printf("end %d , start %d\n", end, start);
	if (end < list_len)
		section(renderer, color, map, 0, start, end);
}

void	update(SDL_Renderer *renderer, pos_t player_pos, int start,
		char **map_config)
{
	float	angle;
	int		i;

	i = 0;
	color_t color = {
		.A = 255,
		.B = 255,
		.G = 255,
		.R = 255};
	clear(renderer);
	map(renderer, &color, map_config, start);
	SDL_RenderPresent(renderer);
}

SDL_Renderer	*create_window(char *title, int width, int height)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, 0);
	return (SDL_CreateRenderer(window, -1, 0));
}

int	main(void)
{
	SDL_Renderer	*renderer;
	SDL_Event		event;
	char			**map;
	pos_t			player_pos;
	int				start_pos;
	int				list_len;

	player_pos.x = 5;
	player_pos.y = 1;
	map = get_map();
	start_pos = 0;
	renderer = create_window("racing game", 360, 450);
	list_len = list_lenght(map) - 1;
	while (TRUE)
	{
		update(renderer, player_pos, start_pos, map);
		start_pos++;
		if (start_pos >= list_len)
			start_pos = 0;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(0);
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						// left clicked
					}
				}
			}
		}
		SDL_Delay(1000 / FRAME_RATE);
	}
	return (0);
}
