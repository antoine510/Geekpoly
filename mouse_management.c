#include "mouse_management.h"
#include "initialisation.h"

void mouse_management (int posx, int posy, int type, Params_ *Params)
{
    int selected_button = -1;

    if (posx >= Params->Surfaces.pos_des.x
    && posx <= (Params->Surfaces.pos_des.x + Params->Surfaces.des->w)
    && posy >= Params->Surfaces.pos_des.y
    && posy <= (Params->Surfaces.pos_des.y + Params->Surfaces.des->h)
    && Params->State.showing == NOTHING)
    {
        if (type == 1)
        {
            de_clicked (Params);
        }
    }
    else if (posx >= Params->button[BUTTON_acheter]->position.x
    && posx <= Params->button[BUTTON_acheter]->position.x + Params->button[BUTTON_acheter]->position.w
    && posy >= Params->button[BUTTON_acheter]->position.y
    && posy <= Params->button[BUTTON_acheter]->position.y + Params->button[BUTTON_acheter]->position.h)
    {
        if (type == 1)
        {
            if (Params->State.showing == TERRAIN)
            {
                buy_terrain_clicked (Params);
            }
            else if (Params->State.showing == STATION)
            {
                buy_station_clicked (Params);
            }
            else if (Params->State.showing == WATER)
            {
                buy_water_clicked (Params);
            }
        }
        else if (Params->State.showing == TERRAIN || Params->State.showing == STATION || Params->State.showing == WATER)
        {
            selected_button = BUTTON_acheter;
        }
    }
    else if (posx >= Params->button[BUTTON_annuler]->position.x
    && posx <= Params->button[BUTTON_annuler]->position.x + Params->button[BUTTON_annuler]->position.w
    && posy >= Params->button[BUTTON_annuler]->position.y
    && posy <= Params->button[BUTTON_annuler]->position.y + Params->button[BUTTON_annuler]->position.h)
    {
        if (Params->State.showing == TERRAIN || Params->State.showing == STATION || Params->State.showing == WATER)
        {
            if (type == 1)
            {
                cancel_clicked (Params);
            }
            else
            {
                selected_button = BUTTON_annuler;
            }
        }
    }
    else if (posx >= Params->button[BUTTON_construire]->position.x
    && posx <= Params->button[BUTTON_construire]->position.x + Params->button[BUTTON_construire]->position.w
    && posy >= Params->button[BUTTON_construire]->position.y
    && posy <= Params->button[BUTTON_construire]->position.y + Params->button[BUTTON_construire]->position.h
    && Params->State.showing == NOTHING)
    {
        if (type == 1)
        {
            build_clicked (Params);
        }
        else
        {
            selected_button = BUTTON_construire;
        }
    }
    else if (posx >= Params->button[BUTTON_fin]->position.x
    && posx <= Params->button[BUTTON_fin]->position.x + Params->button[BUTTON_fin]->position.w
    && posy >= Params->button[BUTTON_fin]->position.y
    && posy <= Params->button[BUTTON_fin]->position.y + Params->button[BUTTON_fin]->position.h
    && Params->State.showing == NOTHING)
    {
        if (type == 1)
        {
            fin_clicked (Params);
        }
        else
        {
            selected_button = BUTTON_fin;
        }
    }
    else if (posx >= Params->button[BUTTON_ok]->position.x
    && posx <= Params->button[BUTTON_ok]->position.x + Params->button[BUTTON_ok]->position.w
    && posy >= Params->button[BUTTON_ok]->position.y
    && posy <= Params->button[BUTTON_ok]->position.y + Params->button[BUTTON_ok]->position.h
    && Params->State.showing == CHANCE)
    {
        if (type == 1)
        {
            ok_chance_clicked(Params);
        }
        else
        {
            selected_button = BUTTON_ok;
        }
    }
        //  Here is the refresh function
    if (type == 1)
    {
        refresh(Params);
    }
    else
    {
        unselect_buttons(Params);
        if (selected_button != -1)
        {
            Params->button[selected_button]->state = BUTTON_STATE_selected;
        }
        show_buttons (Params);
		UpdateEcran(Params);
    }
}


void de_clicked (Params_ *Params)
{
    if (Params->State.de_already_threw == 0)
    {
        Params->State.de_result = (rand() % 11) + 2;

        Params->Joueurs[Params->State.tour].position += Params->State.de_result;
        Params->State.de_already_threw = 1;

        if (Params->Joueurs[Params->State.tour].position >= 41)
        {
            Params->Joueurs[Params->State.tour].position -= 40;
            Params->Joueurs[Params->State.tour].money += Params->Cartes[1].loyer[1];
        }

        sprintf(Params->Text.temp_text, "%d", Params->State.de_result);
        show_text(Params->Text.temp_text, 0, Params->Surfaces.pos_plateau.y + 150, 120, Params, CENTER_PLATEAU);
		UpdateEcran(Params);
        SDL_Delay(500);

        boxes_managment(Params);
    }
    else
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_avez_deja_lance_les_des]);
    }

    refresh(Params);
}

void cancel_clicked (Params_ *Params)
{
    Params->State.showing = NOTHING;
}

void buy_terrain_clicked (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position;

    Params->Cartes[current_carte].owned = Params->State.tour;
    Params->Joueurs[Params->State.tour].money -= Params->Cartes[current_carte].tobuy;

    sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_achete_s], Params->Joueurs[Params->State.tour].name, Params->Cartes[current_carte].title);
    Params->State.showing = NOTHING;
}

void buy_station_clicked (Params_ *Params)
{
    int current_card = Params->Joueurs[Params->State.tour].position;

    Params->Cartes[current_card].owned = Params->State.tour;
    Params->Joueurs[Params->State.tour].money -= Params->Cartes[6].tobuy;

    sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_achete_aeroport_de_s], Params->Joueurs[Params->State.tour].name, Params->Cartes[current_card].title);
    (Params->Joueurs[Params->State.tour].nbr_station_owned)++;
    Params->State.showing = NOTHING;
}

void buy_water_clicked (Params_ *Params)
{
    int current_card = Params->Joueurs[Params->State.tour].position;

    Params->Cartes[current_card].owned = Params->State.tour;
    Params->Joueurs[Params->State.tour].money -= Params->Cartes[current_card].tobuy;

    if (current_card == 13) //So it's the parliament
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_achete_le_parlement], Params->Joueurs[Params->State.tour].name);
    }
    else
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_achete_la_cour_de_justice], Params->Joueurs[Params->State.tour].name);
    }
    Params->State.showing = NOTHING;
}

void build_clicked (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position;
    int current_money = Params->Joueurs[Params->State.tour].money;

    if (Params->Cartes[current_carte].owned == Params->State.tour)
    {
        if (Params->Cartes[current_carte].builded < 4 && current_money >= Params->Cartes[current_carte].tobuild)
        {
            (Params->Cartes[current_carte].builded)++;
            Params->Joueurs[Params->State.tour].nbr_house_owned++;
            Params->Joueurs[Params->State.tour].money -= Params->Cartes[current_carte].tobuild;
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_avez_batie_une_maison_sur_s_pour_dE], Params->Cartes[current_carte].title, Params->Cartes[current_carte].tobuild);
        }
        else if (Params->Cartes[current_carte].builded == 4 && current_money >= Params->Cartes[current_carte].tobuild)
        {
            (Params->Cartes[current_carte].builded)++;
            Params->Joueurs[Params->State.tour].nbr_hotel_owned++;
            Params->Joueurs[Params->State.tour].money -= Params->Cartes[current_carte].tobuild;
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_avez_batie_un_hotel_sur_s_pour_dE], Params->Cartes[current_carte].title, Params->Cartes[current_carte].tobuild);
        }
        else if (Params->Cartes[current_carte].builded >= 5)
        {
            Params->Cartes[current_carte].builded = 5;
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_avez_deja_un_hotel_sur_s], Params->Cartes[current_carte].title);
        }
        else
        {
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_il_vous_manque_dE_pour_batir_ici], Params->Cartes[current_carte].tobuild - current_money);
        }
    }
    else if (Params->Cartes[current_carte].owned == -1)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_ceci_est_pas_constructible]);
    }
    else
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_ce_terrain_appartient_a_s], Params->Joueurs[Params->Cartes[current_carte].owned].name);
    }
}

void fin_clicked (Params_ *Params)
{
    if (Params->State.de_already_threw == 1)
    {
        Params->State.de_already_threw = 0;
        tour_suivant(Params);
        empty_buffer(&Params->T_buffer);
        while (Params->Joueurs[Params->State.tour].in_jail > 0)
        {
            (Params->Joueurs[Params->State.tour].in_jail)--;
            if (Params->Joueurs[Params->State.tour].in_jail > 1)
            {
                sprintf(Params->Text.temp_text, "%s\n%s",   Params->Messages[MES_s_passe_son_tour], Params->Messages[MES_encore_d_tour_en_prison]);
                sprintf(Params->T_buffer.status_text, Params->Text.temp_text,   Params->Joueurs[Params->State.tour].name, Params->Joueurs[Params->State.tour].in_jail);
            }
            else
            {
                sprintf(Params->Text.temp_text, "%s\n%s",   Params->Messages[MES_s_passe_son_tour], Params->Messages[MES_dernier_tour_en_prison]);
                sprintf(Params->T_buffer.status_text, Params->Text.temp_text, Params->Joueurs[Params->State.tour].name);
            }
            refresh(Params);
            SDL_Delay(2000);
            empty_buffer(&Params->T_buffer);
            Params->State.de_result = 0;
            tour_suivant(Params);
        }
    }
    else
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_avez_pas_encore_lance_les_des]);
    }

     refresh(Params);
}

void ok_chance_clicked (Params_ *Params)
{
    int current_action = Params->Chances.Chance[Params->Chances.current_item].action, paid = 0, to_substract = 0;
    switch (Params->Chances.Chance[Params->Chances.current_item].type)
    {
        case 1: //equals win money
            Params->Joueurs[Params->State.tour].money += current_action;
            break;
        case 2: //equals loose money
            paid = substract_money(&Params->Joueurs[Params->State.tour], current_action);
            Params->State.money_in_parc_gratuit += paid;
            break;
        case 3: //equals moove
            Params->Joueurs[Params->State.tour].position += current_action;
            break;
        case 4: //equals go to
            Params->Joueurs[Params->State.tour].position = current_action;
            break;
        case 5: //equals go to jail for x turns
            Params->Joueurs[Params->State.tour].in_jail = current_action;
            break;
        case 6: //equals repair your houses and hotels
            to_substract += Params->Joueurs[Params->State.tour].nbr_house_owned * ((current_action - (current_action % 1000)) / 1000);
            to_substract += Params->Joueurs[Params->State.tour].nbr_hotel_owned * (current_action % 1000);
            //  Because it is xxxyyy formated
            paid = substract_money(&Params->Joueurs[Params->State.tour], to_substract);
            Params->State.money_in_parc_gratuit += paid;
            break;
    }

    if (Params->Chances.current_item < Params->Chances.nbr_items - 1)
    {
        Params->Chances.current_item++;
    }
    else
    {
        Params->Chances.current_item = 0;
    }
    Params->State.showing = NOTHING;
}
