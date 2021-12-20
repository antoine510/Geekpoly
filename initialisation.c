#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include "initialisation.h"

void UpdateEcran(Params_ *Params) {
	SDL_UpdateTexture(Params->Surfaces.ecranTex, NULL, Params->Surfaces.ecran->pixels, Params->Surfaces.ecran->pitch);
	SDL_RenderClear(Params->Surfaces.renderer);
	SDL_RenderCopy(Params->Surfaces.renderer, Params->Surfaces.ecranTex, NULL, NULL);
	SDL_RenderPresent(Params->Surfaces.renderer);
}

void init_surfaces (Param_Surfaces *Surfaces, char *WindowCaption)
{
    //Sufaces
	Surfaces->window = SDL_CreateWindow(WindowCaption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 1024, 0);
	Surfaces->renderer = SDL_CreateRenderer(Surfaces->window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(Surfaces->renderer, 0, 0, 0, 255);
	SDL_RenderSetLogicalSize(Surfaces->renderer, 1280, 1024);

	Surfaces->ecran = SDL_CreateRGBSurface(0, 1280, 1024, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
	Surfaces->ecranTex = SDL_CreateTexture(Surfaces->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, Surfaces->ecran->w, Surfaces->ecran->h);
    Surfaces->black = SDL_CreateRGBSurface(0, Surfaces->ecran->w, Surfaces->ecran->h, 32, 0, 0, 0, 0);
    SDL_FillRect(Surfaces->black, NULL, SDL_MapRGB(Surfaces->black->format, 0, 0, 0));
    SDL_SetSurfaceAlphaMod(Surfaces->black, 120);

    Surfaces->plateau = SDL_LoadBMP("sources/monopoly.bmp");

    Surfaces->des = SDL_LoadBMP("sources/des.bmp");
    SDL_SetColorKey(Surfaces->des, SDL_TRUE, SDL_MapRGB(Surfaces->des->format, 0, 0, 0));

    Surfaces->carte = SDL_LoadBMP("sources/carte.bmp");
    Surfaces->chance = SDL_LoadBMP("sources/chance_cdc.bmp");

    Surfaces->house = SDL_LoadBMP("sources/house.bmp");
    Surfaces->hotel = SDL_LoadBMP("sources/hotel.bmp");

    //Positions

    Surfaces->pos_des.x = 550;
    Surfaces->pos_des.y = 550;

    Surfaces->pos_plateau.x = Surfaces->ecran->w - Surfaces->plateau->w;
    Surfaces->pos_plateau.y = 0;

    Surfaces->pos_carte.x = (Surfaces->plateau->w / 2) - (Surfaces->carte->w / 2) + Surfaces->pos_plateau.x;
    Surfaces->pos_carte.y = (Surfaces->plateau->h / 2) - (Surfaces->carte->h / 2) + Surfaces->pos_plateau.y;

    Surfaces->pos_chance.x = (Surfaces->plateau->w / 2) - (Surfaces->chance->w / 2) + Surfaces->pos_plateau.x;
    Surfaces->pos_chance.y = (Surfaces->plateau->h / 2) - (Surfaces->chance->h / 2) + Surfaces->pos_plateau.y;
}

void init_text (Param_Text *Text)
{
    Text->color_text.r = 0;
    Text->color_text.g = 0;
    Text->color_text.b = 0;
    Text->temp_text[0] = '\0';
}

void init_state (Param_State *State)
{
    State->tour = 0;
    State->quit = 0;
    State->de_already_threw = 0;
    State->money_in_parc_gratuit = 0;
    State->de_result = 0;
    State->showing = NOTHING;
}

void init_joueurs (Params_ *Params)
{
    int i = 0, steps = 0, current_player = 0, current_letter = 0, refresh = 1, ok = 0, nbr_pion = 0, current_x_pion = 300;
    char current_name[21] = "";
    SDL_Surface **pointer_pion;
    SDL_Surface *background = SDL_CreateRGBSurface(0, Params->Surfaces.ecran->w, Params->Surfaces.ecran->h, 32, 0, 0, 0, 0);
    SDL_FillRect (background, NULL, SDL_MapRGB(background->format, 255, 255, 255));
    SDL_Rect *pos_pion;
    SDL_Event event;
    //SDL_EnableKeyRepeat(300,100);

    sprintf(Params->Text.temp_text, "sources/pion1.bmp");
    while(SDL_LoadBMP(Params->Text.temp_text) != NULL)
    {
        i++;
        sprintf(Params->Text.temp_text, "sources/pion%d.bmp", i + 1);
        nbr_pion++;
    }

    pointer_pion = malloc(nbr_pion * sizeof(SDL_Surface*));
    pos_pion = malloc(nbr_pion * sizeof(SDL_Rect));

    for (i = 0; i < nbr_pion; i++)
    {
        sprintf(Params->Text.temp_text, "sources/pion%d.bmp", i + 1);
        pointer_pion[i] = SDL_LoadBMP(Params->Text.temp_text);
        pos_pion[i].x = current_x_pion;
        pos_pion[i].y = 400;
        current_x_pion += pointer_pion[i]->w + 50;
        SDL_SetColorKey(pointer_pion[i], SDL_TRUE, SDL_MapRGB(pointer_pion[i]->format, 0, 0, 0));
    }

    Params->State.nbr_joueurs = 0;

    while (steps <= 2 && !Params->State.quit)
    {
        if (refresh)
        {
            refresh = 0;
            SDL_BlitSurface(background, NULL, Params->Surfaces.ecran, NULL);
            if (!ok)
            {
                switch (steps)
                {
                    case 0:
                        show_text(Params->Messages[MES_combien_de_joueurs], 0, 200, 30, Params, CENTER_ECRAN);
                        if (Params->State.nbr_joueurs != 0)
                        {
                            sprintf(Params->Text.temp_text, "%d", Params->State.nbr_joueurs);
                            show_text(Params->Text.temp_text, 0, 260, 40, Params, CENTER_ECRAN);
                        }
                        break;
                    case 1:
                        sprintf(Params->Text.temp_text, Params->Messages[MES_nom_du_joueur_d], current_player + 1);
                        show_text(Params->Text.temp_text, 0, 200, 30, Params, CENTER_ECRAN);
                        if (current_name[0] != '\0')
                        {
                            show_text(current_name, 0, 260, 40, Params, CENTER_ECRAN);
                        }
                        break;
                    case 2:
                        sprintf(Params->Text.temp_text, Params->Messages[MES_pion_de_s], Params->Joueurs[current_player].name);
                        show_text(Params->Text.temp_text, 0, 200, 30, Params, CENTER_ECRAN);
                        for (i = 0; i < nbr_pion; i++)
                        {
                            SDL_BlitSurface(pointer_pion[i], NULL, Params->Surfaces.ecran, &pos_pion[i]);
                        }
                        break;
                    default:
                        break;
                }
				UpdateEcran(Params);
            }
            else
            {
                show_text(Params->Messages[MES_ok], 0, 300, 60, Params, CENTER_ECRAN);
				UpdateEcran(Params);
                SDL_Delay(300);
                ok = 0;
                refresh = 1;
            }
        }
        else
        {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT:
                    Params->State.quit = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (steps == 2)
                    {
                        for (i = 0; i < nbr_pion; i++)
                        {
                            if (event.button.x >= pos_pion[i].x
                             && event.button.x <= pos_pion[i].x + pointer_pion[i]->w
                             && event.button.y >= pos_pion[i].y
                             && event.button.y <= pos_pion[i].y + pointer_pion[i]->h)
                            {
                                Params->Joueurs[current_player].pion.ImgPion = pointer_pion[i];
                                if (current_player < Params->State.nbr_joueurs - 1)
                                {
                                        current_player++;
                                        ok = 1;
                                        refresh = 1;
                                }
                                else
                                {
                                    steps++;
                                }
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            Params->State.quit = 1;
                            break;
                        case SDLK_BACKSPACE:
                            if (steps == 1 && current_letter >= 1)
                            {
                                current_name[current_letter - 1] = '\0';
                                current_letter--;
                                refresh = 1;
                            }
                            break;
                        case '\r':
                            switch (steps)
                            {
                                case 0:
                                    if (Params->State.nbr_joueurs)
                                    {
                                        Params->Joueurs = malloc(Params->State.nbr_joueurs * sizeof(Param_Joueurs));
                                        current_name[0] = '\0';
                                        ok = 1;
                                        steps++;
                                    }
                                    else
                                    {
                                        show_text(Params->Messages[MES_vous_devez_entrer_un_nombre], 0, 300, 40, Params, CENTER_ECRAN);
										UpdateEcran(Params);
                                        SDL_Delay(700);
                                    }
                                    refresh = 1;
                                    break;
                                case 1:
                                    if (current_name[0] != '\0')
                                    {
                                        int name_lenght = (int)strlen(current_name);

                                        Params->Joueurs[current_player].name = malloc((name_lenght + 1) * sizeof(char));
                                        for (i = 0; i < name_lenght; i++)
                                        {
                                            Params->Joueurs[current_player].name[i] = current_name[i];
                                            current_name[i] = '\0';
                                        }
                                        Params->Joueurs[current_player].name[name_lenght] = '\0';
                                        if (current_player < Params->State.nbr_joueurs - 1)
                                        {
                                            current_letter = 0;
                                            current_player++;
                                        }
                                        else
                                        {
                                            current_player = 0;
                                            steps++;
                                        }
                                        ok = 1;
                                    }
                                    else
                                    {
                                        show_text(Params->Messages[MES_vous_devez_entrer_un_nom], 0, 300, 40, Params, CENTER_ECRAN);
										UpdateEcran(Params);
                                        SDL_Delay(700);
                                    }
                                    refresh = 1;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            if (steps == 0 && event.key.keysym.sym >= SDLK_KP_1 && event.key.keysym.sym <= SDLK_KP_6)
                            {
                                Params->State.nbr_joueurs = event.key.keysym.sym - SDLK_KP_1 + 1;
                            }
                            else if (steps == 1 && current_letter <= 19 && event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
                            {
                                switch (event.key.keysym.sym)       //  Because of french keyboard
                                {
                                    case 'a':
                                        event.key.keysym.sym = 'q';
                                        break;
                                    case 'z':
                                        event.key.keysym.sym = 'w';
                                        break;
                                    case 'q':
                                        event.key.keysym.sym = 'a';
                                        break;
                                    case 'w':
                                        event.key.keysym.sym = 'z';
                                        break;
                                    default:
                                        break;
                                }
                                if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT ||
                                    (event.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT)
                                {
                                    event.key.keysym.sym = SDL_toupper(event.key.keysym.sym);
                                }
                                current_name[current_letter] = event.key.keysym.sym;
                                current_name[current_letter + 1] = '\0';
                                current_letter++;
                            }
                            refresh = 1;
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (!Params->State.quit)
    {
        for(i = 0; i < Params->State.nbr_joueurs; i++)
        {
            Params->Joueurs[i].position = 1;
            Params->Joueurs[i].money = 1000;
            Params->Joueurs[i].perdu = 0;
            Params->Joueurs[i].in_jail = 0;
            Params->Joueurs[i].nbr_station_owned = 0;
            Params->Joueurs[i].nbr_house_owned = 0;
            Params->Joueurs[i].nbr_hotel_owned = 0;
        }
    }

    free(pos_pion);
}

void init_cartes (Param_Cartes *Cartes)
{
    FILE* terrain = NULL;
    int lenght_of_file = 0;
    int i = 0;

    terrain = fopen("sources/terrain.txt", "r");

    if (terrain != NULL)
    {
        lenght_of_file = file_lenght(terrain, 200);
        if (file_lenght(terrain, 200) != 42)
        {
            for (i = 0; i <= 40; i++)
            {
                fscanf (terrain, "%s %d %d %d %d %d %d %d %d", Cartes[i].title, &Cartes[i].loyer[0], &Cartes[i].loyer[1], &Cartes[i].loyer[2], &Cartes[i].loyer[3], &Cartes[i].loyer[4],
                                            &Cartes[i].loyer[5], &Cartes[i].tobuild, &Cartes[i].tobuy);
                replace_letter(Cartes[i].title, '_', ' ');
                replace_letter(Cartes[i].title, '|', '\n');
                Cartes[i].owned = -1;
                Cartes[i].builded = 0;
            }
            Cartes[2].couleur = MAUVE;
            Cartes[4].couleur = MAUVE;
            Cartes[7].couleur = BLEUCLAIR;
            Cartes[9].couleur = BLEUCLAIR;
            Cartes[10].couleur = BLEUCLAIR;
            Cartes[12].couleur = VIOLET;
            Cartes[14].couleur = VIOLET;
            Cartes[15].couleur = VIOLET;
            Cartes[17].couleur = ORANGE;
            Cartes[19].couleur = ORANGE;
            Cartes[20].couleur = ORANGE;
            Cartes[22].couleur = ROUGE;
            Cartes[24].couleur = ROUGE;
            Cartes[25].couleur = ROUGE;
            Cartes[27].couleur = JAUNE;
            Cartes[28].couleur = JAUNE;
            Cartes[30].couleur = JAUNE;
            Cartes[32].couleur = VERT;
            Cartes[33].couleur = VERT;
            Cartes[35].couleur = VERT;
            Cartes[38].couleur = BLEU;
            Cartes[40].couleur = BLEU;
        }
        else
        {
            fputs("Fichier de terrain corrompu, il doit contenir 42 definitions de carte", stderr);
            exit(0);
        }
        fclose(terrain);
    }
    else
    {
        fputs("Fichier de terrain manquant", stderr);
        exit(0);
    }
}

void init_chances (Param_Chances *Chances)
{
    FILE *chances_file = NULL;

    chances_file = fopen("sources/chances.txt", "r");

    if (chances_file != NULL)
    {
        Chances->nbr_items = file_lenght(chances_file, 200);
        if (Chances->nbr_items > 0)
        {
            int i = 0;

            Chances->Chance = malloc(Chances->nbr_items * sizeof(Param_Chance));        //Allow the chance cards place in memory
            for (i = 0; i < Chances->nbr_items; i++)
            {
                fscanf (chances_file, "%d %d %s", &Chances->Chance[i].type, &Chances->Chance[i].action, Chances->Chance[i].text);
                replace_letter (Chances->Chance[i].text, '_', ' ');
                replace_letter (Chances->Chance[i].text, '|', '\n');
            }
            Chances->current_item = rand() % Chances->nbr_items;        //Select one of the card to begin with
        }
        else
        {
            fputs("fichier de carte chance vide", stderr);
            exit(0);
        }
        fclose(chances_file);
    }
    else
    {
        fputs("fichier de carte chance manquant", stderr);
        exit(0);
    }
}

void init_messages (Params_ *Params)
{
    FILE *messages_file = NULL;

    messages_file = fopen("sources/messages.txt", "r");

    if (messages_file != NULL)
    {
        int lenght_of_file = 0;

        lenght_of_file = file_lenght(messages_file, 200);
        if (lenght_of_file != 0)
        {
            int i = 0, lenght_of_line = 0;
            char temp_line[100] = "";

            Params->Messages = malloc(lenght_of_file * sizeof(char*));        //Allow the place in memory
            for (i = 0; i < lenght_of_file; i++)
            {
                lenght_of_line = line_lenght(messages_file);                    //It requires a memory optimization
                Params->Messages[i] = malloc(lenght_of_line * sizeof(char));
                fscanf (messages_file, "%s = %s", temp_line, Params->Messages[i]);
                fgetc(messages_file);           //Because the scanf does not pick the final '\n'
                // it retturn -1 when eof but not a problem
                replace_letter (Params->Messages[i], '_', ' ');
                replace_letter (Params->Messages[i], '|', '\n');
            }
        }
        else
        {
            fputs("fichier de langue corrompu", stderr);
            exit(0);
        }
        fclose(messages_file);
    }
    else
    {
        fputs("fichier de langue manquant", stderr);
        exit(0);
    }
}

void init_buttons (Param_Button** button, Param_Surfaces* surfaces)
{
    ButtonStyle bstyle;                                 //Only one style for now but maybe more lately
    setcolor(&bstyle.fontcolor[0], 255, 0, 0);
    setcolor(&bstyle.fontcolor[1], 0, 0, 255);
    setcolor(&bstyle.backcolor[0], 255, 255, 0);
    setcolor(&bstyle.backcolor[1], 255, 0, 255);
    setcolor(&bstyle.bordercolor[0], 0, 0, 0);
    setcolor(&bstyle.bordercolor[1], 0, 0, 0);
    bstyle.fontsize = 23;
    bstyle.bordersize = 2;

    button[BUTTON_acheter] = create_button("Acheter", bstyle);
    move_button(button[BUTTON_acheter],
                surfaces->pos_carte.x + 20,
                surfaces->pos_carte.y + surfaces->carte->h - button[BUTTON_acheter]->position.h - 20);

    button[BUTTON_annuler] = create_button("Annuler", bstyle);
    move_button(button[BUTTON_annuler],
                surfaces->pos_carte.x + surfaces->carte->w - button[BUTTON_annuler]->position.w - 20,
                surfaces->pos_carte.y + surfaces->carte->h - button[BUTTON_annuler]->position.h - 20);

    button[BUTTON_construire] = create_button("Construire", bstyle);
    move_button(button[BUTTON_construire], surfaces->pos_plateau.x, surfaces->pos_plateau.y + surfaces->plateau->h);

    button[BUTTON_fin] = create_button("Fin du tour", bstyle);
    move_button(button[BUTTON_fin], 40, 0);

    button[BUTTON_ok] = create_button("OK", bstyle);
    move_button(button[BUTTON_ok],
                surfaces->pos_chance.x + (surfaces->chance->w / 2) - (button[BUTTON_ok]->position.w / 2),
                surfaces->pos_chance.y + surfaces->chance->h - 40);
}

void create_plateau (SDL_Surface *plateau, int side)
{

}
