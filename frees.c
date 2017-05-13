#include "frees.h"
#include <stdio.h>

void free_joueurs (Param_Joueurs *Joueurs, int nbr_joueurs)        //Complete
{
    int i = 0, j = 0;

    for (i = 0; i < nbr_joueurs; i++)
    {
        free(Joueurs[i].name);
        for (j = 0; j < nbr_joueurs; j++)
        {
            if (Joueurs[i].pion.ImgPion == Joueurs[j].pion.ImgPion && i != j)
            {
                Joueurs[i].pion.ImgPion = NULL;
            }
        }
        if (Joueurs[i].pion.ImgPion != NULL)
        {
            SDL_FreeSurface(Joueurs[i].pion.ImgPion);
        }
    }
    free(Joueurs);
}

void free_messages (char **Messages)
{
    int i = 0;
    for (i = 0; i < 41; i++)
    {
        free(Messages[i]);
    }
}

void empty_buffer (Text_Buffer *T_buffer)
{
    sprintf(T_buffer->status_text, " ");
}

void make_button_state (Param_Button **button, int state)
{
    int i;

    for (i = 0; i < BUTTON_NUMBER; i++)
    {
        button[i]->state = state;
    }
}
