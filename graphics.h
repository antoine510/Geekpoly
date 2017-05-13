#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef enum {VERTICAL, HORIZONTAL} Orientation;

void draw_rectangle (SDL_Surface*, unsigned int, unsigned int, unsigned int, unsigned int, Uint32);
void draw_line (SDL_Surface*, unsigned int, unsigned int, unsigned int, Uint32, Orientation);
void draw_house (SDL_Surface*, SDL_Surface*, unsigned int, unsigned int);
void setPixel (SDL_Surface*, unsigned int, unsigned int, Uint32);
void draw_player (SDL_Surface*, SDL_Surface*, SDL_Rect*);
void setcolor (SDL_Color*, int, int, int);

#endif // GRAPHICS_H
