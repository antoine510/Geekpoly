#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "Button.h"

Param_Button* create_button (char* text,ButtonStyle bstyle)
{
    Param_Button *button = malloc(sizeof(Param_Button));
    SDL_Surface *Text_surface;
    SDL_Rect TextPosition;
    int i, j;

    TextPosition.x = bstyle.bordersize + 2;  //To prevent the text to touch the border
    TextPosition.y = bstyle.bordersize + 2;

    for (i = 0; i < 2; i++)
    {
        //Button text
        TTF_Font *font = TTF_OpenFont("sources/txt.TTF", bstyle.fontsize);
        Text_surface = TTF_RenderText_Blended(font, text, bstyle.fontcolor[i]);
        TTF_CloseFont(font);

        //Button back
        button->surface[i] = SDL_CreateRGBSurface(0, (Text_surface->w + 2 * bstyle.bordersize + 4), (Text_surface->h + 2 * bstyle.bordersize + 4), 32, 0, 0, 0, 0);
        SDL_FillRect(button->surface[i], NULL, SDL_MapRGB(button->surface[i]->format, bstyle.backcolor[i].r, bstyle.backcolor[i].g, bstyle.backcolor[i].b));

        //Button border
        for (j = 0; j < bstyle.bordersize; j++)
        {
            draw_rectangle (
                button->surface[i], j, j, button->surface[i]->w - 2 * j, button->surface[i]->h - 2 * j,
                SDL_MapRGB(button->surface[i]->format, bstyle.bordercolor[i].r, bstyle.bordercolor[i].g, bstyle.bordercolor[i].b));
        }

        //Button text blit
        SDL_BlitSurface(Text_surface, NULL, button->surface[i], &TextPosition);

        SDL_FreeSurface(Text_surface);
    }

    //Final button structure filling
    button->text = text;
    button->state = 0;
    button->position.w = button->surface[0]->w;
    button->position.h = button->surface[0]->h;


    return button;
}

void blit_button (Param_Button* button, SDL_Surface* surface)
{
    if (button->state != BUTTON_STATE_hiden)
    {
        SDL_BlitSurface(button->surface[button->state], NULL, surface, &button->position);
    }
}

void move_button (Param_Button* button, unsigned int x, unsigned int y)
{
    if (x != 0)
    {
        button->position.x = x;
    }
    if (y != 0)
    {
        button->position.y = y;
    }
}

void free_button (Param_Button *button)
{
    free(button->text);
    SDL_FreeSurface(button->surface[0]);
    SDL_FreeSurface(button->surface[1]);
    free(button);
}
