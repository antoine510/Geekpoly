#ifndef CLICS_MANAGEMENT_H
#define CLICS_MANAGEMENT_H

#include <SDL.h>
#include "structures.h"
#include "GUI.h"
#include "jeu.h"
#include "frees.h"
#include "defines.h"

void mouse_management(int, int,int, Params_*);

void de_clicked (Params_*);
void ok_chance_clicked (Params_*);
void cancel_clicked (Params_*);
void buy_terrain_clicked(Params_*);
void buy_station_clicked(Params_*);
void buy_water_clicked (Params_*);
void build_clicked (Params_*);
void fin_clicked (Params_*);

#endif // CLICS_MANAGEMENT_H
