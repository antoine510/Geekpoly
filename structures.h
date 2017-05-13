#pragma once

#include <SDL.h>

#include "Button.h"

typedef enum {MAUVE = 1, BLEUCLAIR = 2, VIOLET = 3, ORANGE = 4, ROUGE = 5, JAUNE = 6, VERT = 7, BLEU = 8} Couleurs;
typedef enum {CENTER_ECRAN, CENTER_PLATEAU, CENTER_CARTE, TEXT_CARTE, NUMERO_CARTE, STATUS_MESSAGE, CENTER_POSITION, POS_NONE} Positions;
typedef enum { NOTHING, TERRAIN, CHANCE, STATION, WATER } Showing;

typedef struct
{
    SDL_Rect Pos_pion;
    SDL_Surface *ImgPion;
} Param_Pion;

typedef struct
{
    int position;
    int money;
    int perdu;
    int in_jail;
    int nbr_station_owned;
    int nbr_house_owned;
    int nbr_hotel_owned;
    Param_Pion pion;
    char *name;
} Param_Joueurs;

typedef struct
{
    char status_text[300];
} Text_Buffer;

typedef struct
{
    int tour;
    int nbr_joueurs;
    int quit;
    int money_in_parc_gratuit;
    int de_already_threw;
    int de_result;
    Showing showing;
} Param_State;

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Texture *ecranTex;
    SDL_Surface *ecran;
    SDL_Surface *black;
    SDL_Surface *plateau;
    SDL_Surface *des;
    SDL_Surface *carte;
    SDL_Surface *house;
    SDL_Surface *hotel;
    SDL_Surface *chance;

    SDL_Rect pos_des;
    SDL_Rect pos_plateau;
    SDL_Rect pos_carte;
    SDL_Rect pos_chance;
} Param_Surfaces;

typedef struct
{
    SDL_Rect pos_text;
    SDL_Color color_text;
    SDL_Surface *text;
    char temp_text[100];
    char font[50];
} Param_Text;

typedef struct
{
    char title[40];
    int owned;
    int builded;
    int loyer[6];
    int tobuild;
    int tobuy;
    Couleurs couleur;
} Param_Cartes;

typedef struct
{
    char text[200];
    int type;
    int action;
} Param_Chance;

typedef struct
{
    Param_Chance *Chance;
    int nbr_items;
    int current_item;
} Param_Chances;

typedef struct
{
    Param_Joueurs *Joueurs;
    Param_Surfaces Surfaces;
    Param_Text Text;
    Param_Cartes Cartes[41];
    Param_State State;
    Param_Chances Chances;
    Text_Buffer T_buffer;
    Param_Button *button[BUTTON_NUMBER];
    char **Messages;
} Params_;

