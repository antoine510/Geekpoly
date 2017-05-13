#include "option.h"
#include <stdio.h>

void select_options (Params_ *Params)
{
    SDL_Event event;
    Options options;
    int finished = 0, refresh = 1;

    read_options(&options);
    change_res(Params->Surfaces.ecran, options.def_x, options.def_y, options.is_fullscreen);

    SDL_Surface *background = SDL_CreateRGBSurface(0, Params->Surfaces.ecran->w, Params->Surfaces.ecran->h, 32, 0, 0, 0, 0);
    SDL_FillRect (background, NULL, SDL_MapRGB(background->format, 255, 255, 255));

    while (!finished)
    {
        if (refresh)
        {
			SDL_UpdateTexture(Params->Surfaces.ecranTex, NULL, Params->Surfaces.ecran->pixels, Params->Surfaces.ecran->pitch);
			SDL_RenderClear(Params->Surfaces.renderer);
			SDL_RenderCopy(Params->Surfaces.renderer, Params->Surfaces.ecranTex, NULL, NULL);
			SDL_RenderPresent(Params->Surfaces.renderer);
        }
        else
        {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
                case SDL_MOUSEBUTTONUP:

                    break;
            }
        }
    }
}

void write_options (Options *options)
{
    FILE *option_file = NULL;
    char temp_text[10] = "";

    option_file = fopen("sources/options.txt", "w");

    sprintf(temp_text, "%d %d %d", options->def_x, options->def_y, options->is_fullscreen);
                                    //It will be changed to binary values on 32bits
    fputs (temp_text, option_file);
}

void read_options (Options *options)
{
    FILE *option_file = NULL;

    option_file = fopen("sources/options.txt", "r");

    if (option_file != NULL)
    {
        fscanf (option_file, "%d %d %d", &options->def_x, &options->def_y, &options->is_fullscreen);

        fclose (option_file);
    }
    else
    {
        fputs("fichier d'options manquant", stderr);
        exit(0);
    }
}

void change_res (SDL_Surface *ecran, unsigned int width, unsigned int height, int is_fullscreen)
{
    /*SDL_FreeSurface(ecran);
    if (is_fullscreen)
    {
        ecran = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    }
    else
    {
        ecran = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    }*/
}
