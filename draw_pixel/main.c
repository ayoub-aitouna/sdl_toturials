
#include "draw_pixel.h"

void clear_window(SDL_Renderer *renderer, color_t color)
{
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	SDL_RenderClear(renderer);
}

color_t *new_color(int R, int G, int B, int A)
{
	color_t *color;

	color = malloc(sizeof(color_t));
	color->R = R;
	color->G = G;
	color->B = B;
	color->A = A;
	return (color);
}

void draw_block(SDL_Renderer *renderer, pos_t position)
{
	int x = position.x + 1, y = position.y + 1;
	while (x < position.x + 60 - 1)
	{
		y = position.y;
		while (y < position.y + 60 - 1)
		{
			SDL_RenderDrawPoint(renderer, x, y);
			y++;
		}
		x++;
	}
}

int handle_colusion(int new_x, int new_y, int player_size, char **map, int move)
{
	if (new_x <= 0 || new_y <= 0)
		return (0);
	int tal_x = new_x / 60, tal_y = new_y / 60;
	if (map[tal_y][tal_x] == '1')
		return (0);
	return (move);
}

void draw_map(SDL_Renderer *renderer, pos_t *pos, color_t *color, char **map)
{
	int i = 0, j = 0;
	pos_t cur_pos;
	SDL_SetRenderDrawColor(renderer, color->R, color->G, color->B, color->A);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				cur_pos.x = j * 60;
				cur_pos.y = i * 60;
				draw_block(renderer, cur_pos);
			}
			j++;
		}
		i++;
	}
}

void update(SDL_Renderer *renderer, pos_t *pos, color_t *color, char **map)
{
	clear_window(renderer, *new_color(0, 0, 0, 255));
	draw_map(renderer, pos, new_color(255, 255, 255, 255), map);
	draw_player(renderer, *pos, 15, *new_color(180, 180, 255, 255));
	SDL_RenderPresent(renderer);
}
SDL_Event *linsten_to_eventes(SDL_Renderer *renderer, pos_t *pos, color_t *color, char **map)
{
	SDL_Event event;
	static int speed = 2;
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
				pos->y -= handle_colusion(pos->x, pos->y - 10 * speed, 30, map, 10 * speed);
				break;
			case SDL_SCANCODE_DOWN:
				pos->y += handle_colusion(pos->x, pos->y + 10 * speed, 30, map, 10 * speed);
				break;
			case SDL_SCANCODE_RIGHT:
				pos->x += handle_colusion(pos->x + 10 * speed, pos->y, 30, map, 10 * speed);
				pos->angle++;
				break;
			case SDL_SCANCODE_LEFT:
				pos->x -= handle_colusion(pos->x - 10 * speed, pos->y, 30, map, 10 * speed);
				pos->angle--;
				break;
				default:
				break;
			}
			update(renderer, pos, color, map);
		}
	}
	return (NULL);
}

int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	pos_t pos;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("App", SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	pos.x = 2 * 60;
	pos.y = 2 * 60;
	pos.angle = 90;
	char **map = get_map();
	update(renderer, &pos, new_color(0, 255, 255, 255), map);
	while (1)
	{
		linsten_to_eventes(renderer, &pos, new_color(0, 255, 255, 255), map);
	}
	return (0);
}
