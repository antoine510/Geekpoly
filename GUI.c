#include <SDL.h>
#include <SDL_ttf.h>
#include <string.h>

#include "Button.h"
#include "jeu.h"
#include "GUI.h"

void show_players (Params_ *Params)
{
    int i = 0, current_pos = 0;
    SDL_Rect coord_plateau;
    coord_plateau.x = Params->Surfaces.pos_plateau.x;
    coord_plateau.y = Params->Surfaces.pos_plateau.y;
    coord_plateau.w = (Params->Surfaces.pos_plateau.x + Params->Surfaces.plateau->w);
    coord_plateau.h = (Params->Surfaces.pos_plateau.y + Params->Surfaces.plateau->h);

    for (i = 0; i < Params->State.nbr_joueurs; i++)
    {
        current_pos = Params->Joueurs[i].position;
        if (current_pos >= 1 && current_pos < 11)
        {
            if (current_pos == 1)
            {
                Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.w - (Params->Joueurs[0].pion.ImgPion->w * Params->State.nbr_joueurs + SEPARATION_DE_BORDURE + BORDURE);
            }
            else
            {
                Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.w - ((current_pos - 1) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
            }
            Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.h - (Params->Joueurs[i].pion.ImgPion->h + SEPARATION_DE_BORDURE + BORDURE);
        }
        else if (current_pos >= 11 && current_pos < 21)
        {
            if (current_pos == 11)
            {
                Params->Joueurs[i].pion.Pos_pion.y = 20 + coord_plateau.h - (Params->Joueurs[i].pion.ImgPion->h + SEPARATION_DE_BORDURE + BORDURE);
            }
            else
            {
                Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.h - ((current_pos - 11) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
            }
            Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.x + SEPARATION_DE_BORDURE + BORDURE;
        }
        else if (current_pos >= 21 && current_pos < 31)
        {
            if (current_pos == 21)
            {
                Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.x + SEPARATION_DE_BORDURE + BORDURE;
            }
            else
            {
                Params->Joueurs[i].pion.Pos_pion.x =  coord_plateau.x + (current_pos - 22) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE ;
            }
            Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.y + SEPARATION_DE_BORDURE + BORDURE;
        }
        else
        {
            if (current_pos == 31)
            {
                Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.y + SEPARATION_DE_BORDURE + BORDURE;
            }
            else
            {
                Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.y + (current_pos - 32) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE;
            }
            Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.w - (Params->Joueurs[0].pion.ImgPion->w * Params->State.nbr_joueurs + SEPARATION_DE_BORDURE + BORDURE);
        }
        //  If player is in _jail
        if (Params->Joueurs[i].in_jail != 0)
        {
            Params->Joueurs[i].pion.Pos_pion.x = coord_plateau.x + SEPARATION_DE_BORDURE + BORDURE + 10;
            Params->Joueurs[i].pion.Pos_pion.y = coord_plateau.h - 20 - (Params->Joueurs[i].pion.ImgPion->h + SEPARATION_DE_BORDURE + BORDURE);
        }
        //  Offset beetween players
        Params->Joueurs[i].pion.Pos_pion.x += (Params->Joueurs[i].pion.ImgPion->w * i);

        draw_player(Params->Surfaces.ecran, Params->Joueurs[i].pion.ImgPion, &Params->Joueurs[i].pion.Pos_pion);
    }
}

void show_stats (Params_ *Params)
{
    int i = 0, j = 0, k = 0;
    int r = 200, v = 200, b = 255;
    int xmargin = 20, margin_size = 3;
    int screen_part = (Params->Surfaces.ecran->h / Params->State.nbr_joueurs);
    SDL_Surface *stat_joueur = SDL_CreateRGBSurface(0, Params->Surfaces.pos_plateau.x, Params->Surfaces.ecran->h, 32, 0, 0, 0, 0);

    SDL_FillRect(stat_joueur, NULL, SDL_MapRGB(stat_joueur->format, 240, 240, 255));

    SDL_LockSurface(stat_joueur);
    for (i = 0; i < Params->State.nbr_joueurs; i++)
    {
        for (j = 0; j < (screen_part - xmargin); j++)
        {
            for (k = 0; k < margin_size; k++)
            {
                setPixel(stat_joueur, xmargin + k, (i * screen_part) + j + (xmargin / 2), SDL_MapRGB(stat_joueur->format, r, v, b));
                setPixel(stat_joueur, Params->Surfaces.pos_plateau.x - xmargin + k, (i * screen_part) + j + (xmargin / 2), SDL_MapRGB(stat_joueur->format, r, v, b));
            }
        }
        for (j = xmargin + margin_size; j < Params->Surfaces.pos_plateau.x - xmargin; j++)
        {
            for (k = 0; k < margin_size; k++)
            {
                setPixel(stat_joueur, j, k + (xmargin / 2) + (i * screen_part), SDL_MapRGB(stat_joueur->format, r, v, b));
                setPixel(stat_joueur, j, k - (xmargin / 2) - margin_size + ((i + 1) * screen_part), SDL_MapRGB(stat_joueur->format, r, v, b));
            }
        }
    }
    for (i = 0; i < 140; i++)
    {
        setPixel(stat_joueur, i + xmargin + margin_size + 10, Params->State.tour * screen_part + 18, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, i + xmargin + margin_size + 10, Params->State.tour * screen_part + 19, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, i + xmargin + margin_size + 10, Params->State.tour * screen_part + 57, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, i + xmargin + margin_size + 10, Params->State.tour * screen_part + 58, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
    }
    for (i = 0; i < 41; i++)
    {
        setPixel(stat_joueur, xmargin + margin_size + 10, Params->State.tour * screen_part + 18 + i, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, xmargin + margin_size + 11, Params->State.tour * screen_part + 18 + i, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, xmargin + margin_size + 150, Params->State.tour * screen_part + 18 + i, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
        setPixel(stat_joueur, xmargin + margin_size + 151, Params->State.tour * screen_part + 18 + i, SDL_MapRGB(stat_joueur->format, 0, 0, 0));
    }
    SDL_UnlockSurface(stat_joueur);
    SDL_BlitSurface(stat_joueur, NULL, Params->Surfaces.ecran, NULL);
    for (i = 0; i < Params->State.nbr_joueurs; i++)
    {
        show_text(Params->Joueurs[i].name, 40, i * screen_part + 20, 30, Params, POS_NONE);

        sprintf(Params->Text.temp_text, "%dE", Params->Joueurs[i].money);
        show_text(Params->Text.temp_text, 180, i * screen_part + 20, 30, Params, POS_NONE);
    }
    SDL_FreeSurface(stat_joueur);

    // move the fin button
    move_button(Params->button[BUTTON_fin], 0, Params->State.tour * screen_part + 100);
}

void show_plateau (Params_ *Params)
{
    int i = 0;
    SDL_Rect origin;
    SDL_Rect plateau;
    plateau.x = Params->Surfaces.pos_plateau.x + BORDURE;
    plateau.y = Params->Surfaces.pos_plateau.y + BORDURE;
    plateau.w = plateau.x + Params->Surfaces.plateau->w - (BORDURE * 2);
    plateau.h = plateau.y + Params->Surfaces.plateau->h - (BORDURE * 2);

    //Blit of the main plateau surface
    SDL_BlitSurface(Params->Surfaces.plateau, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_plateau);

    //1st corner
    sprintf(Params->Text.temp_text, "%s", Params->Cartes[1].title);
    show_text(Params->Text.temp_text, plateau.w - (TAILLE_COINS / 2), plateau.h - 120, 25, Params, CENTER_POSITION);

    //2nd corner
    sprintf(Params->Text.temp_text, "%s", Params->Cartes[11].title);
    show_text(Params->Text.temp_text, plateau.x + (TAILLE_COINS / 2) + 21, plateau.h - 100, 22, Params, CENTER_POSITION);

    //3rd corner
    sprintf(Params->Text.temp_text, "%s", Params->Cartes[21].title);
    show_text(Params->Text.temp_text, plateau.x + (TAILLE_COINS / 2), plateau.y + 10, 20, Params, CENTER_POSITION);
    sprintf(Params->Text.temp_text, "%dE", Params->State.money_in_parc_gratuit);
    show_text(Params->Text.temp_text, plateau.x + (TAILLE_COINS / 2), plateau.y + 60, 35, Params, CENTER_POSITION);

    //4th corner
    sprintf(Params->Text.temp_text, "%s", Params->Cartes[31].title);
    show_text(Params->Text.temp_text, plateau.w - (TAILLE_COINS / 2), plateau.y + 10, 25, Params, CENTER_POSITION);

    for (i = 2; i <= 10; i++)
    {
        origin.x = Params->Surfaces.ecran->w - ((i - 1) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
        origin.y = Params->Surfaces.plateau->h - (BORDURE + 100);
    }
    for (i = 12; i <= 20; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + BORDURE + 100 - Params->Surfaces.house->w;
        origin.y = Params->Surfaces.plateau->h - ((i - 11) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
    }
    for (i = 22; i <= 30; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + (i - 22) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE;
        origin.y = BORDURE + 100 - Params->Surfaces.house->h;
    }
    for (i = 32; i <= 40; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + Params->Surfaces.plateau->w - (BORDURE + 100);
        origin.y = (i - 32) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE;
    }
}

void show_carte (Params_ *Params)
{
    int i = 0;
    int current_carte = Params->Joueurs[Params->State.tour].position;
        SDL_BlitSurface (Params->Surfaces.black, NULL, Params->Surfaces.ecran, NULL);
        SDL_BlitSurface(Params->Surfaces.carte, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_carte);

        //  BEGIN card's color managment

        SDL_Surface *couleur_surface = SDL_CreateRGBSurface(0, 243, 85, 32, 0, 0, 0, 0);
        SDL_Rect pos_couleur;
        int r = 0, v = 0, b = 0;
        pos_couleur.x = Params->Surfaces.pos_carte.x + 15;
        pos_couleur.y = Params->Surfaces.pos_carte.y + 15;
        switch (Params->Cartes[current_carte].couleur)
        {
            case MAUVE:
                r = 225;
                v = 11;
                b = 134;
                break;
            case BLEUCLAIR:
                r = 60;
                v = 190;
                b = 255;
                break;
            case VIOLET:
                r = 185;
                v = 88;
                b = 209;
                break;
            case ORANGE:
                r = 255;
                v = 128;
                b = 0;
                break;
            case ROUGE:
                r = 255;
                v = 0;
                b = 0;
                break;
            case JAUNE:
                r = 255;
                v = 255;
                b = 0;
                break;
            case VERT:
                r = 0;
                v = 255;
                b = 0;
                break;
            case BLEU:
                r = 83;
                v = 104;
                b = 253;
                break;
        }
        SDL_FillRect(couleur_surface, NULL, SDL_MapRGB(couleur_surface->format, r, v, b));
        SDL_BlitSurface(couleur_surface, NULL, Params->Surfaces.ecran, &pos_couleur);
        SDL_FreeSurface(couleur_surface);

        // END card's color managment

        // BEGIN card's text managment
        show_text(Params->Cartes[current_carte].title, 0, Params->Surfaces.pos_carte.y + 50, 35, Params, CENTER_CARTE);
        show_text(Params->Messages[MES_titre_de_propriete], 0, Params->Surfaces.pos_carte.y + 20, 18, Params, CENTER_CARTE);
        show_text(Params->Messages[MES_loyer_terrain_nu], 0, Params->Surfaces.pos_carte.y + 110, 15, Params, TEXT_CARTE);

        //Show house and hotel labels
        for (i = 0; i < 4; i++)
        {
            sprintf(Params->Text.temp_text, "       -       %d %s", i + 1, Params->Messages[MES_maison]);
            show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 130 + i * 20, 15, Params, TEXT_CARTE);
        }

        sprintf(Params->Text.temp_text, "       -       %s", Params->Messages[MES_hotel]);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 210, 15, Params, TEXT_CARTE);
        for (i = 0; i <= 5; i++)
        {
            sprintf(Params->Text.temp_text, "%d", Params->Cartes[current_carte].loyer[i]);
            show_text(Params->Text.temp_text, 0, (20 * i + Params->Surfaces.pos_carte.y + 110), 18, Params, NUMERO_CARTE);
        }

        //Show prices
        show_text(Params->Messages[MES_prix_des_maisons], 160, Params->Surfaces.pos_carte.y + 270, 17, Params, TEXT_CARTE);
        sprintf(Params->Text.temp_text, "%d", Params->Cartes[current_carte].tobuild);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 270, 18, Params, NUMERO_CARTE);

        show_text(Params->Messages[MES_prix_a_achat], 160, Params->Surfaces.pos_carte.y + 300, 17, Params, TEXT_CARTE);
        sprintf(Params->Text.temp_text, "%d", Params->Cartes[current_carte].tobuy);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 300, 18, Params, NUMERO_CARTE);

        // END card's text managment

        Params->State.showing = TERRAIN;
}

void show_buffered_text(Params_ *Params)
{
    show_text(Params->T_buffer.status_text, 0, 0, 25,Params, STATUS_MESSAGE);
}

void show_chance(Params_ *Params)
{
    int position = Params->Joueurs[Params->State.tour].position;

    //Paste the semi-alpha background and stats
    SDL_BlitSurface (Params->Surfaces.black, NULL, Params->Surfaces.ecran, NULL);
    show_stats(Params);

    //Paste the card
    SDL_BlitSurface(Params->Surfaces.chance, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_chance);

    show_text(Params->Cartes[position].title, 0, Params->Surfaces.pos_chance.y + 15, 30, Params, CENTER_CARTE);
    show_text(Params->Chances.Chance[Params->Chances.current_item].text, 0, Params->Surfaces.pos_chance.y + 60, 25, Params, CENTER_CARTE);

    Params->State.showing = CHANCE;
}

void show_station (Params_ *Params)
{
    int i = 0, current_carte = Params->Joueurs[Params->State.tour].position;

    SDL_BlitSurface (Params->Surfaces.black, NULL, Params->Surfaces.ecran, NULL);
    SDL_BlitSurface(Params->Surfaces.carte, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_carte);

    show_text(Params->Messages[MES_aeroport], 0, Params->Surfaces.pos_carte.y + 20, 18, Params, CENTER_CARTE);
    show_text(Params->Cartes[current_carte].title, 0, Params->Surfaces.pos_carte.y + 50, 35, Params, CENTER_CARTE);
    show_text(Params->Messages[MES_nbr_aeroport_possede], 0, Params->Surfaces.pos_carte.y + 110, 18, Params, TEXT_CARTE);

    for (i = 0; i < 4; i++)
    {
        sprintf(Params->Text.temp_text, "%d %s", i + 1, Params->Messages[MES_aeroport]);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 130 + i * 25, 22, Params, TEXT_CARTE);
        sprintf(Params->Text.temp_text, "%d", Params->Cartes[6].loyer[i]);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 130 + i * 25, 24, Params, NUMERO_CARTE);
    }

    show_text(Params->Messages[MES_prix_a_achat], 160, Params->Surfaces.pos_carte.y + 270, 17, Params, TEXT_CARTE);
    sprintf(Params->Text.temp_text, "%d", Params->Cartes[current_carte].tobuy);
    show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 270, 18, Params, NUMERO_CARTE);

    Params->State.showing = STATION;
}

void show_water (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position;

    SDL_BlitSurface (Params->Surfaces.black, NULL, Params->Surfaces.ecran, NULL);
    SDL_BlitSurface(Params->Surfaces.carte, NULL, Params->Surfaces.ecran, &Params->Surfaces.pos_carte);

    show_text(Params->Cartes[current_carte].title, 0, Params->Surfaces.pos_carte.y + 30, 35, Params, CENTER_CARTE);

    sprintf(Params->Text.temp_text, Params->Messages[MES_texte_de_carte_eau_et_electricite], Params->Cartes[13].loyer[0], Params->Cartes[13].loyer[1]);
    show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 110, 18, Params, CENTER_CARTE);

    show_text(Params->Messages[MES_prix_a_achat], 0, Params->Surfaces.pos_carte.y + 270, 17, Params, TEXT_CARTE);
    sprintf(Params->Text.temp_text, "%d", Params->Cartes[current_carte].tobuy);
    show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_carte.y + 270, 18, Params, NUMERO_CARTE);

    Params->State.showing = WATER;
}

void show_buildings (Params_ *Params)
{
    int i = 0;
    SDL_Rect origin;

    for (i = 2; i <= 10; i++)
    {
        origin.x = Params->Surfaces.ecran->w - ((i - 1) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
        origin.y = Params->Surfaces.plateau->h - (BORDURE + 125);
        show_building_group(Params->Cartes[i].builded, origin, &Params->Surfaces, HORIZONTAL);
    }
    for (i = 12; i <= 20; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + BORDURE + 125 - Params->Surfaces.house->w;
        origin.y = Params->Surfaces.plateau->h - ((i - 11) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE);
        show_building_group(Params->Cartes[i].builded, origin, &Params->Surfaces, VERTICAL);
    }
    for (i = 22; i <= 30; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + (i - 22) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE;
        origin.y = BORDURE + 125 - Params->Surfaces.house->h;
        show_building_group(Params->Cartes[i].builded, origin, &Params->Surfaces, HORIZONTAL);
    }
    for (i = 32; i <= 40; i++)
    {
        origin.x = Params->Surfaces.pos_plateau.x + Params->Surfaces.plateau->w - (BORDURE + 125);
        origin.y = (i - 32) * ESPACE_ENTRE_CASE + TAILLE_COINS + BORDURE;
        show_building_group(Params->Cartes[i].builded, origin, &Params->Surfaces, VERTICAL);
    }
}

void show_building_group (unsigned int nbr_buildings, SDL_Rect origin, Param_Surfaces *Surfaces, Orientation oriented)
{
    unsigned int i = 0;
    const int offset = 3;       //Space beetween buildings
    int *coordinate_to_change = NULL;
    int *coordinate_to_add = NULL, *coordinate_hotel = NULL;
    SDL_Rect position = origin;

    switch (oriented)
    {
        case VERTICAL:
            coordinate_to_change = &(position.y);
            coordinate_to_add = &Surfaces->house->h;
            coordinate_hotel = &Surfaces->hotel->h;
            break;
        case HORIZONTAL:
            coordinate_to_change = &(position.x);
            coordinate_to_add = &Surfaces->house->w;
            coordinate_hotel = &Surfaces->hotel->w;
            break;
    }

    if (nbr_buildings <= 4)
    {
        for (i = 0; i < nbr_buildings; i++)
        {
            SDL_BlitSurface(Surfaces->house, NULL, Surfaces->ecran, &position);
            (*coordinate_to_change) += *coordinate_to_add + offset;
        }
    }
    else
    {
        *coordinate_to_change += ESPACE_ENTRE_CASE / 2 - (*coordinate_hotel / 2);
        SDL_BlitSurface(Surfaces->hotel, NULL, Surfaces->ecran, &position);
    }
}

void show_text (const char *text, unsigned int posx, unsigned int posy, unsigned int taille_police, Params_ *Params, Positions Position)
{
    if (strchr(text, '\n') != NULL)
    {
        search_lines (text, posx, posy, taille_police, Params, Position);
    }
    else
    {
        TTF_Font *police = TTF_OpenFont("sources/txt.TTF", taille_police);
        Params->Text.text = TTF_RenderText_Blended(police, text, Params->Text.color_text);
        TTF_CloseFont(police);
        Params->Text.pos_text.x = posx;
        Params->Text.pos_text.y = posy;
        switch(Position)
        {
            case CENTER_ECRAN:
                Params->Text.pos_text.x = Params->Surfaces.ecran->w / 2;
                Position = CENTER_POSITION;
                break;
            case CENTER_PLATEAU:
                Params->Text.pos_text.x = Params->Surfaces.pos_plateau.x + Params->Surfaces.plateau->w / 2;
                Position = CENTER_POSITION;
                break;
            case CENTER_CARTE:
                Params->Text.pos_text.x = Params->Surfaces.pos_carte.x  + Params->Surfaces.carte->w / 2;
                Position = CENTER_POSITION;
                break;
            case TEXT_CARTE:
                Params->Text.pos_text.x = Params->Surfaces.pos_carte.x  + 20;
                break;
            case NUMERO_CARTE:
                Params->Text.pos_text.x = Params->Surfaces.pos_carte.x  + 210;
                break;
            case STATUS_MESSAGE:
                Params->Text.pos_text.x = Params->Surfaces.pos_plateau.x + Params->Surfaces.plateau->w / 2;
                Params->Text.pos_text.y = 280 + Params->Surfaces.pos_plateau.y;
                Position = CENTER_POSITION;
                break;
            default:
                break;
        }

        if (Position == CENTER_POSITION)        //Make it accessible from other position
        {
            Params->Text.pos_text.x -= Params->Text.text->w / 2;
        }

        SDL_BlitSurface (Params->Text.text, NULL, Params->Surfaces.ecran, &Params->Text.pos_text);
        SDL_FreeSurface(Params->Text.text);
    }
}

void show_buttons (Params_ *Params)
{
    int i;

    for (i = 0; i < BUTTON_NUMBER; i++)
    {
        blit_button(Params->button[i], Params->Surfaces.ecran);
    }
}

