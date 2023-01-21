#include "mobDeplacement.h"
#ifndef MASDL_H_INCLUDED
#define MASDL_H_INCLUDED

void message(char *myTitle, char *myMessage);


//void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//void clear_surface(SDL_Surface *psurf);

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void efface_fenetre(SDL_Surface *psurf);
void maj_fenetre(SDL_Window *pWindow);

void prepareWhiteGrid(SDL_Surface* cadreBlanc, SDL_Surface* destination, int largeur, int hauteur);

void prepareAllSpriteDuJeu(TplateauJeu plateau, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination);




#endif // MASDL_H_INCLUDED
