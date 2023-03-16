
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 1260
#define HEIGHT 660

typedef struct pos
{
	int		x;
	int		y;
}			pos_t;

typedef struct color
{
	int		R;
	int		G;
	int		B;
	int		A;
}			color_t;

color_t	*new_color(int R, int G, int B, int A)
{
	color_t	*color;

	color = malloc(sizeof(color_t));
	color->R = R;
	color->G = G;
	color->B = B;
	color->A = A;
	return (color);
}

void	draw_block(SDL_Renderer *renderer, pos_t center_position, int width,
		int height, color_t color)
{
	int start_vertical, start_horizontal, x, y;
	start_vertical = center_position.x - (width / 2);
	start_horizontal = center_position.y - (height / 2);
	if (start_vertical < 0)
		start_vertical = 0;
	if (start_horizontal < 0)
		start_horizontal = 0;
	x = start_vertical;
	y = start_horizontal ;
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	while (x < start_horizontal + height)
	{
		y = start_vertical;
		while (y < start_vertical + HEIGHT)
		{
			if (y == start_vertical || y == start_vertical + width - 1
				|| x == start_horizontal || x == start_horizontal + height - 1)
				SDL_RenderDrawPoint(renderer, x, y);
			y++;
		}
		start_vertical++;
	}
	SDL_RenderPresent(renderer);
}
void	handle_colusion(pos_t *pos)
{
	if (pos->x + 60 >= WIDTH)
		pos->x = WIDTH - 60;
	if (pos->x - 60 <= 0)
		pos->x = 60;
	if (pos->y + 60 >= HEIGHT)
		pos->y = HEIGHT - 60;
	if (pos->y - 60 <= 0)
		pos->y = 60;
}
void	draw_map(SDL_Renderer *renderer, pos_t *pos, color_t *color)
{
	int		i;
	int		j;
	pos_t	cur_pos;

	char map[11][21] = {
		"111111111111111111111",
		"1      1   1        1",
		"1   1111   1111111  1",
		"1   1               1",
		"1   1111 111111111 11",
		"1   1  1 1         11",
		"1   1    1       1 11",
		"1      1 1       1 11",
		"1   1111 111111111 11",
		"1  1             1  1",
		"111111111111111111111"};
	while (i < 10)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				cur_pos.x = j * 60;
				cur_pos.y = i * 60;
				draw_block(renderer, cur_pos, 60, 60, *color);
			}
			j++;
		}
		i++;
	}
}
void	update(SDL_Renderer *renderer, pos_t *pos, color_t *color)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	draw_block(renderer, *pos, 60, 60, *color);
	draw_map(renderer, pos, new_color(255, 255, 255, 255));
	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
	SDL_RenderDrawPoint(renderer, pos->x, pos->y);
}
SDL_Event	*linsten_to_eventes(SDL_Renderer *renderer, pos_t *pos,
		color_t *color)
{
	SDL_Event	event;
	static int	speed;

	speed = 1;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		if (event.type == SDL_KEYUP)
			speed = 1;
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_UP:
				pos->y -= 10 * speed++;
				break ;
			case SDL_SCANCODE_DOWN:
				pos->y += 10 * speed++;
				break ;
			case SDL_SCANCODE_RIGHT:
				pos->x += 10 * speed++;
				break ;
			case SDL_SCANCODE_LEFT:
				pos->x -= 10 * speed++;
				break ;
			default:
				break ;
			}
			if (speed >= 10)
				speed = 10;
			handle_colusion(pos);
			update(renderer, pos, color);
		}
	}
	return (NULL);
}

char	**create_map(void)
{
	int		i;
	int		j;
	char	**map;

	map = malloc(((HEIGHT / 60) + 2) * sizeof(char *));
	i = 0;
	while (i < HEIGHT / 60)
	{
		map[i] = malloc(((WIDTH / 60) + 2) * sizeof(char));
		j = 0;
		while (j < WIDTH / 60)
		{
			if (j % 2)
				map[i][j] = '1';
			else
				map[i][j] = '0';
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	color_t			*color;
	pos_t			pos;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("App", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	color = new_color(0, 255, 255, 255);
	pos.x = 2 * 60;
	pos.y = 2 * 60;
	update(renderer, &pos, color);
	while (1)
	{
		linsten_to_eventes(renderer, &pos, color);
	}
	return (0);
}
