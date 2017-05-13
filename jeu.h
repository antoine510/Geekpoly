#ifndef JEU_H
#define JEU_H

#include "structures.h"
#include "initialisation.h"
#include "frees.h"
#include "boxes_management.h"
#include "mouse_management.h"
#include "defines.h"

#include <stdio.h>


void start ();
void boucle_de_jeu (Params_*);
void tour_suivant (Params_*);
int file_lenght (FILE*, int);
int line_lenght (FILE*);
void replace_letter (char*, const char, const char);
void search_lines (const char*, unsigned int, unsigned int, unsigned int, Params_*, Positions);
void refresh (Params_*);
int substract_money (Param_Joueurs*, int);
int check_group (Params_*);
void unselect_buttons (Params_*);

#endif // JEU_H
