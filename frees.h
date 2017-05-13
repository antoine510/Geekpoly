#ifndef FREES_H
#define FREES_H

#include <stdlib.h>
#include <SDL.h>
#include "structures.h"
#include "defines.h"

void free_joueurs (Param_Joueurs*, int);
void free_messages (char**);
void empty_buffer (Text_Buffer*);
void make_button_state (Param_Button**, int);

#endif // FREES_H
