#include <SDL.h>
#include "graphics.h"

//these function are useless for now but will be usefull with other ways of drawing (e.g. 3D)

void draw_rectangle (SDL_Surface *surface, unsigned int x, unsigned int y, unsigned int w, unsigned int h, Uint32 pixel)
{
    draw_line(surface, x, y, w, pixel, HORIZONTAL);
    draw_line(surface, x, (y + 1), (h - 2), pixel, VERTICAL);
    draw_line(surface, x, (y + h - 1), w, pixel, HORIZONTAL);
    draw_line(surface, (x + w - 1), (y + 1), (h - 2), pixel, VERTICAL);
}

void draw_line (SDL_Surface *surface, unsigned int x, unsigned int y, unsigned int l, Uint32 pixel, Orientation orient)
{
    unsigned int i;

    if (orient == HORIZONTAL)
    {
        for (i = 0; i < l; i++)
        {
            setPixel(surface, x + i, y, pixel);
        }
    }
    else
    {
        for (i = 0; i < l; i++)
        {
            setPixel(surface, x, y + i, pixel);
        }
    }
}

void draw_house (SDL_Surface* surface, SDL_Surface* house, unsigned int x, unsigned int y)
{
    SDL_Rect position = {x, y, 0, 0};
    SDL_BlitSurface(house, NULL, surface, &position);
}

void setPixel (SDL_Surface *surface, unsigned int x, unsigned int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void draw_player (SDL_Surface* surface, SDL_Surface* pion, SDL_Rect* position)
{
    SDL_BlitSurface(pion, NULL, surface, position);
}

void setcolor (SDL_Color* color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}
