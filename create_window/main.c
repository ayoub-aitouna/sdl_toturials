
// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>

int	linsten_to_eventes(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (0);
	}
	return (1);
}

int	main(void)
{
	SDL_Window	*window;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("App", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	(void)window;
	while (1)
	{
		if (!linsten_to_eventes())
			break ;
	}
	return (0);
}
