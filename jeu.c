#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include "GUI.h"
#include "jeu.h"

void start ()
{
    SDL_Init(SDL_INIT_VIDEO);       //initialisation de la librairie graphique
    TTF_Init();                     //initialisation de la librairie textuelle
    srand((unsigned int)time(NULL));              //generateur de hasard

	Params_ Params = { 0 };

	init_messages(&Params);
    init_surfaces (&Params.Surfaces, Params.Messages[MES_window_caption]);
    init_text (&Params.Text);
    init_cartes (Params.Cartes);
    init_chances (&Params.Chances);
    init_state (&Params.State);
    init_buttons (Params.button, &Params.Surfaces);
    init_joueurs (&Params);

    if (!Params.State.quit)
    {
        sprintf(Params.T_buffer.status_text, Params.Messages[MES_bienvenue]);
        refresh(&Params);

        boucle_de_jeu(&Params);

        free_joueurs(Params.Joueurs, Params.State.nbr_joueurs);
        free_messages(Params.Messages);
    }

    TTF_Quit();
    SDL_Quit();
}

void boucle_de_jeu (Params_ *Params)
{

    SDL_Event event;
    int time_base = 0, time_now = 0;

    while (!Params->State.quit)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                Params->State.quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Params->State.quit = 1;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_management(event.button.x, event.button.y, 1, Params);
                break;
            case SDL_MOUSEMOTION:
                time_now = SDL_GetTicks();
                if ((time_now - time_base) > 50)
                {
                    mouse_management(event.motion.x, event.motion.y, 2, Params);
                    time_base = time_now;
                }
            default:
                break;
        }
    }
}

void tour_suivant (Params_ *Params)
{
    if (Params->State.tour < (Params->State.nbr_joueurs - 1))
    {
        Params->State.tour++;
    }
    else
    {
        Params->State.tour = 0;
    }
}

int file_lenght (FILE *file, int max_line_lenght)
{
    char *line = NULL;
    int nbr_lines = 0;
    line = malloc(max_line_lenght * sizeof(char));

    while (fgets(line, max_line_lenght, file) != NULL)
    {
        nbr_lines++;
    }
    rewind(file);

    free(line);

    return nbr_lines;
}

int line_lenght (FILE *file)
{
    char temp_letter = 1;
    int nbr_letters = 0, i = 0;

    while (temp_letter != '\n' && temp_letter != -1 && i < 1000)
    {
        temp_letter = fgetc(file);
        i++;
        nbr_letters++;
    }

    if (i == 1000)
    {
        return -1;
    }

    fseek(file, -(nbr_letters + 1), SEEK_CUR);

    return nbr_letters;
}

void replace_letter (char *string, const char replaced, const char replacing)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == replaced)
        {
            string[i] = replacing;
        }
        i++;
    }
}

void search_lines (const char *text, unsigned int posx, unsigned int posy, unsigned int taille_police, Params_ *Params, Positions Position)
{
    char* limit = NULL;
    limit = strchr(text, '\n');

    if (limit != NULL)
    {
        int i = 0, lenght = strlen(text) - strlen(limit);
        char* text_before = malloc((lenght + 1) * sizeof(char));
        char* text_after = malloc((strlen(limit) + 1) * sizeof(char));
        strcpy(text_after, limit);

        for (i = 0; i < lenght; i++)
        {
            text_before[i] = text[i];
        }
        text_before[lenght] = '\0';
        if (Position == STATUS_MESSAGE)
        {
            Position = CENTER_PLATEAU;
            posy = 280 + Params->Surfaces.pos_plateau.y;
        }
        show_text (text_before, posx, posy, taille_police, Params, Position);
        free(text_before);
        text_after[0] = ' ';
        search_lines (text_after, posx, posy + taille_police, taille_police, Params, Position);
        free(text_after);
    }
    else
    {
        show_text (text, posx, posy, taille_police, Params, Position);
    }
}

void refresh (Params_ *Params)
{
    show_plateau(Params);
    SDL_BlitSurface(Params->Surfaces.des, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_des);
    show_stats(Params);
    show_players(Params);
    show_buildings(Params);
    make_button_state(Params->button, BUTTON_STATE_hiden);
    if (Params->State.showing == NOTHING)
    {
        show_buffered_text(Params);
        Params->button[BUTTON_construire]->state = BUTTON_STATE_default;
        Params->button[BUTTON_fin]->state = BUTTON_STATE_default;
    }
    else if (Params->State.showing == TERRAIN)
    {
        show_carte(Params);
        Params->button[BUTTON_annuler]->state = BUTTON_STATE_default;
        Params->button[BUTTON_acheter]->state = BUTTON_STATE_default;
    }
    else if (Params->State.showing == CHANCE)
    {
        show_chance(Params);
        Params->button[BUTTON_ok]->state = BUTTON_STATE_default;
    }
    else if (Params->State.showing == STATION)
    {
        show_station(Params);
        Params->button[BUTTON_annuler]->state = BUTTON_STATE_default;
        Params->button[BUTTON_acheter]->state = BUTTON_STATE_default;
    }
    else if (Params->State.showing == WATER)
    {
        show_water(Params);
        Params->button[BUTTON_annuler]->state = BUTTON_STATE_default;
        Params->button[BUTTON_acheter]->state = BUTTON_STATE_default;
    }
    show_buttons (Params);

	SDL_UpdateTexture(Params->Surfaces.ecranTex, NULL, Params->Surfaces.ecran->pixels, Params->Surfaces.ecran->pitch);
	SDL_RenderClear(Params->Surfaces.renderer);
	SDL_RenderCopy(Params->Surfaces.renderer, Params->Surfaces.ecranTex, NULL, NULL);
	SDL_RenderPresent(Params->Surfaces.renderer);
}

int substract_money (Param_Joueurs *Joueur, int to_substract)
{
    int paid = 0;
    if (Joueur->money > to_substract)
    {
        paid = to_substract;
        Joueur->money -= to_substract;
    }
    else
    {
        paid = Joueur->money;
        Joueur->money = 0;
        Joueur->perdu = 1;
    }
    return paid;
}

int check_group (Params_ *Params)
{
    //Return -1 if no group or # of the player who own this group
    int current_carte = Params->Joueurs[Params->State.tour].position, i = 0, j = 0, owned = 0;
    int cards_in[3] = {0};

    for (i = (current_carte - 5); i <= (current_carte + 5); i++)
    {
        if (Params->Cartes[i].couleur == Params->Cartes[current_carte].couleur)
        {
            cards_in[j] = i;
            j++;
        }
    }

    if (j == 3)
    {
        if (Params->Cartes[cards_in[0]].owned == Params->Cartes[cards_in[1]].owned
         && Params->Cartes[cards_in[0]].owned == Params->Cartes[cards_in[2]].owned)
        {
            owned = 1;
        }
    }
    else
    {
        if (Params->Cartes[cards_in[0]].owned == Params->Cartes[cards_in[1]].owned)
        {
            owned = 1;
        }
    }

    return owned;
}

void unselect_buttons (Params_ *Params)
{
    int i = 0;

    for (i = 0; i < BUTTON_NUMBER; i++)
    {
        if (Params->button[i]->state == BUTTON_STATE_selected)
        {
            Params->button[i]->state = BUTTON_STATE_default;
        }
    }
}

int main(int argc, char **argv) {
	start();
	return 0;
}
