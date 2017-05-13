#pragma once

#define BUTTON_NUMBER 5

#define BUTTON_acheter 0
#define BUTTON_annuler 1
#define BUTTON_construire 2
#define BUTTON_ok 3
#define BUTTON_fin 4

#define BUTTON_STATE_hiden -1
#define BUTTON_STATE_default 0
#define BUTTON_STATE_selected 1

typedef struct
{
    SDL_Color fontcolor[2];
    SDL_Color backcolor[2];
    SDL_Color bordercolor[2];
    int fontsize;
    int bordersize;
} ButtonStyle;

typedef struct Param_Button
{
    SDL_Surface* surface[2];
    SDL_Rect position;
    int state;
    char* text;
} Param_Button;

Param_Button* create_button (char*, ButtonStyle);
void blit_button (Param_Button*, SDL_Surface*);
void move_button (Param_Button*, unsigned int, unsigned int);
void free_button (Param_Button*);

