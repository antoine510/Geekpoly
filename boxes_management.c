#include <SDL.h>
#include "GUI.h"
#include "jeu.h"
#include "boxes_management.h"

void boxes_managment (Params_ *Params)
{
    switch (Params->Joueurs[Params->State.tour].position)
    {
        case 1:
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_recoit_dE], Params->Joueurs[Params->State.tour].name, Params->Cartes[1].loyer[0]);
            //  Because of the pre-allowed money
            Params->Joueurs[Params->State.tour].money += (Params->Cartes[1].loyer[0] - Params->Cartes[1].loyer[1]);
            break;
        case 2:
            terrain_manager(Params);
            break;
        case 3:
            show_chance(Params);
            break;
        case 4:
            terrain_manager(Params);
            break;
        case 5:
            tax_manager(Params);
            break;
        case 6:
            station_manager(Params);
            break;
        case 7:
            terrain_manager(Params);
            break;
        case 8:
            show_chance(Params);
            break;
        case 9:
            terrain_manager(Params);
            break;
        case 10:
            terrain_manager(Params);
            break;
        //11 = Prison
        case 12:
            terrain_manager(Params);
            break;
        case 13:
            water_manager(Params);
            break;
        case 14:
            terrain_manager(Params);
            break;
        case 15:
            terrain_manager(Params);
            break;
        case 16:
            station_manager(Params);
            break;
        case 17:
            terrain_manager(Params);
            break;
        case 18:
            show_chance(Params);
            break;
        case 19:
            terrain_manager(Params);
            break;
        case 20:
            terrain_manager(Params);
            break;
        case 21:
            Params->Joueurs[Params->State.tour].money += Params->State.money_in_parc_gratuit;
            Params->State.money_in_parc_gratuit = 0;
            break;
        case 22:
            terrain_manager(Params);
            break;
        case 23:
            show_chance(Params);
            break;
        case 24:
            terrain_manager(Params);
            break;
        case 25:
            terrain_manager(Params);
            break;
        case 26:
            station_manager(Params);
            break;
        case 27:
            terrain_manager(Params);
            break;
        case 28:
            terrain_manager(Params);
            break;
        case 29:
            water_manager(Params);
            break;
        case 30:
            terrain_manager(Params);
            break;
        case 31:
            sprintf(Params->T_buffer.status_text, Params->Messages[MES_s_va_en_prison], Params->Joueurs[Params->State.tour].name);
            Params->Joueurs[Params->State.tour].in_jail = Params->Cartes[31].loyer[0];  //It is equal to the number of turn in jail
            Params->Joueurs[Params->State.tour].position = 11;
            break;
        case 32:
            terrain_manager(Params);
            break;
        case 33:
            terrain_manager(Params);
            break;
        case 34:
            show_chance(Params);
            break;
        case 35:
            show_carte(Params);
            break;
        case 36:
            station_manager(Params);
            break;
        case 37:
            show_chance(Params);
            break;
        case 38:
            terrain_manager(Params);
            break;
        case 39:
            tax_manager(Params);
            break;
        case 40:
            terrain_manager(Params);
            break;
        default:
            break;
    }
}


void terrain_manager (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position;

    if (Params->Cartes[current_carte].owned == Params->State.tour)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_ce_terrain_vous_appartient]);
    }
    else if (Params->Cartes[current_carte].owned != -1)
    {
        int current_loyer = Params->Cartes[current_carte].loyer[Params->Cartes[current_carte].builded], paid = 0;

        if (Params->Cartes[current_carte].builded == 0)
        {
            int owned = 0;
            owned = check_group(Params);
            if (owned == 1)
            {
                current_loyer *= 3;
            }
        }

        paid = substract_money(&Params->Joueurs[Params->State.tour], current_loyer);
        Params->Joueurs[Params->Cartes[current_carte].owned].money += paid;
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_payez_dE_a_s], paid, Params->Joueurs[Params->Cartes[current_carte].owned].name);
    }
    else if (Params->Joueurs[Params->State.tour].money < Params->Cartes[current_carte].tobuy)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_il_vous_manque_dE_pour_acheter_ce_terrain], (Params->Cartes[current_carte].tobuy - Params->Joueurs[Params->State.tour].money));
    }
    else
    {
        Params->State.showing = TERRAIN;
    }
}

void station_manager (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position, paid = 0;

    if (Params->Cartes[current_carte].owned == Params->State.tour)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_cette_gare_vous_appartient]);
    }
    else if (Params->Cartes[current_carte].owned != -1)
    {
        int current_loyer = Params->Cartes[6].loyer[(Params->Joueurs[Params->Cartes[current_carte].owned].nbr_station_owned) - 1];

        paid = substract_money(&Params->Joueurs[Params->State.tour], current_loyer);
        Params->Joueurs[Params->Cartes[current_carte].owned].money += paid;
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_payez_dE_a_s], paid, Params->Joueurs[Params->Cartes[current_carte].owned].name);
    }
    else if (Params->Joueurs[Params->State.tour].money < Params->Cartes[6].tobuy)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_il_vous_manque_dE_pour_acheter_cette_gare], (Params->Cartes[6].tobuy - Params->Joueurs[Params->State.tour].money));
    }
    else
    {
        Params->State.showing = STATION;
    }
}

void water_manager (Params_ *Params)
{
    int current_carte = Params->Joueurs[Params->State.tour].position, times_he_pay = 0;

    if (Params->Cartes[current_carte].owned == Params->State.tour)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_ce_terrain_vous_appartient]);
    }
    if (Params->Cartes[current_carte].owned != -1)
    {
        int current_loyer = 0, paid = 0;
        times_he_pay = Params->Cartes[13].loyer[0];

        if (Params->Cartes[13].owned == Params->Cartes[29].owned && Params->Cartes[13].owned != -1)
        {
            times_he_pay = Params->Cartes[13].loyer[1];
        }
        current_loyer = times_he_pay * Params->State.de_result;

        paid = substract_money(&Params->Joueurs[Params->State.tour], current_loyer);
        Params->Joueurs[Params->Cartes[current_carte].owned].money += paid;
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_voud_payez_d_fois_les_des_soit_dE], times_he_pay, paid);
    }
    else if (Params->Joueurs[Params->State.tour].money < Params->Cartes[current_carte].tobuy)
    {
        sprintf(Params->T_buffer.status_text, Params->Messages[MES_il_vous_manque_dE_pour_acheter_ce_terrain], (Params->Cartes[current_carte].tobuy - Params->Joueurs[Params->State.tour].money));
    }
    else
    {
        Params->State.showing = WATER;
    }
}

void tax_manager (Params_ *Params)
{
    int current_card = Params->Joueurs[Params->State.tour].position, paid = 0;
    paid = substract_money(&Params->Joueurs[Params->State.tour], Params->Cartes[current_card].loyer[0]);
    Params->State.money_in_parc_gratuit += paid;
    sprintf(Params->T_buffer.status_text, Params->Messages[MES_vous_payez_des_taxes_a_hauteur_de_dE], paid);
}
