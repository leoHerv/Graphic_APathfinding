#include "SDL.h"
#include "maSDL.h"
#include "mobDeplacement.h"
//#include "types.h"

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
    /*
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    */
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void clear_surface(SDL_Surface *psurf){
        Uint32 color = SDL_MapRGB(psurf->format,0,0,0);
        SDL_FillRect(psurf,NULL, color);
}

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    apply_surface( x, y, source, destination );
}

void efface_fenetre(SDL_Surface *psurf){
    clear_surface(psurf);
}

void maj_fenetre(SDL_Window *pWindow){
    SDL_UpdateWindowSurface(pWindow);
}

// Affichage graphique :

void prepareWhiteGrid(SDL_Surface* cadreBlanc, SDL_Surface* destination, int largeur, int hauteur)
{
    for(int x = 0; x < largeur; x++)
    {
       for(int y = 0; y < hauteur; y++)
       {
           prepare_sprite(x * 11, y * 11, cadreBlanc, destination);
       }
    }
}

void prepareAllSpriteDuJeu(TplateauJeu plateau, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination)
{

    prepareWhiteGrid(TabSprite[4], destination, largeur, hauteur);
    for (int j=0;j<hauteur;j++)
    {
        for (int i=0;i<largeur;i++)
        {
            if (plateau[i][j] != NULL)
            {
                prepare_sprite(i * 11 + 1,j * 11 + 1, TabSprite[plateau[i][j]->type], destination);
            }
        }
    }
}



