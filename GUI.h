#ifndef GUI_H
#define GUI_H

#include "structures.h"
#include "defines.h"
#include "graphics.h"


#define ESPACE_ENTRE_CASE 77
#define BORDURE 18
#define TAILLE_COINS 128
#define SEPARATION_DE_BORDURE 30

void show_players (Params_*);
void show_stats (Params_*);
void show_carte (Params_*);
void show_plateau (Params_*);
void show_chance(Params_*);
void show_station (Params_*);
void show_water (Params_*);
void show_buildings (Params_*);
void show_building_group (unsigned int, SDL_Rect, Param_Surfaces*, Orientation);
void show_text (const char*, unsigned int, unsigned int, unsigned int, Params_*, Positions);
void show_buffered_text(Params_*);
void show_buttons (Params_*);

#endif // GUI_H
