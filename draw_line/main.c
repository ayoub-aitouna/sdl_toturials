#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct pos
{
    int x;
    int y;
} pos_t;

typedef struct color
{
    int R;
    int G;
    int B;
    int A;
} color_t;

void draw_line(SDL_Renderer *renderer, pos_t start, float angle, int width, color_t color)
{
    float i_raduise;

    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    i_raduise = 0;
    while (i_raduise < width)
    {
        int new_x = start.x + i_raduise * cos(angle);
        int new_y = start.y + i_raduise * sin(angle);
        SDL_RenderDrawPoint(renderer, new_x, new_y);
        i_raduise += .5;
    }
}
void clear(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void update(SDL_Renderer *renderer, float play_angle)
{
    float angle = play_angle - 1;
    int i = 0;

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

int main()
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int player_angle = 80;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("draw_line", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    update(renderer, player_angle);
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                exit(0);
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_LEFT:
                    update(renderer, --player_angle);
                    break;
                case SDL_SCANCODE_RIGHT:
                    update(renderer, ++player_angle);
                    break;
                default:
                    break;
                }
            }
        }
    }

    return (0);
}