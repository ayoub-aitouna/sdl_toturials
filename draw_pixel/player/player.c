#include "../draw_pixel.h"

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

void Rays(SDL_Renderer *renderer, pos_t start, float play_angle, color_t color)
{
    float angle = play_angle - 1;

    while (angle <= play_angle)
    {
        draw_line(renderer, start, angle, 250, color);
        angle += .01;
    }
}
void draw_player(SDL_Renderer *renderer, pos_t center_position, int raduise, color_t color)
{
    float angle = 0;
    float i_raduise = 0;
    SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
    while (i_raduise < raduise)
    {
        angle = 0;
        while (angle <= 360)
        {
            int new_x = center_position.x + i_raduise * cos(angle);
            int new_y = center_position.y + i_raduise * sin(angle);
            SDL_RenderDrawPoint(renderer, new_x, new_y);
            angle += .5;
        }
        i_raduise += .5;
    }
    Rays(renderer, center_position, center_position.angle, color);
}