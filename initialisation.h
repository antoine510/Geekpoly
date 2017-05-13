#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "structures.h"
#include "Button.h"
#include "GUI.h"
#include "jeu.h"
#include "string.h"
#include "defines.h"

void UpdateEcran(Params_ *Params);

void init_surfaces (Param_Surfaces*, char *WindowCaption);
void init_text (Param_Text*);
void init_state (Param_State*);
void init_cartes (Param_Cartes*);
void init_joueurs (Params_*);
void init_chances (Param_Chances*);
void init_messages (Params_*);
void init_buttons (Param_Button**, Param_Surfaces*);

#endif // INITIALISATION_H
