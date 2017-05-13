#ifndef OPTION_H
#define OPTION_H

#include "structures.h"

typedef struct
{
    unsigned int def_x;
    unsigned int def_y;
    int is_fullscreen;
} Options;

void select_options (Params_*);
void write_options (Options*);
void read_options (Options*);
void change_res (SDL_Surface*, unsigned int, unsigned int, int);

#endif // OPTION_H
