#include "SDL.h"
#include "SDL_image.h" // Pour les images en .png
#include "maSDL.h"
#include "mobDeplacement.h"
#include "pathfinding.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[])
{
    // Initialise la randomisation.
    initRandom();

    SDL_Event event;

    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "-A* Demo-",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*11 + 1,
        HAUTEURJEU*11 + 1,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran

    SDL_Surface* pSpriteMur = IMG_Load("./data/mur.png");
    SDL_Surface* pSpriteMob = IMG_Load("./data/mob.png");
    SDL_Surface* pSpriteArriver = IMG_Load("./data/arriver.png");
    SDL_Surface* pSpriteRoute = IMG_Load("./data/route.png");
    SDL_Surface* pSpriteCadreBlanc = IMG_Load("./data/cadreBlanc.png");

    SDL_Surface* TabSprite[5]={pSpriteMur, pSpriteMob, pSpriteArriver, pSpriteRoute, pSpriteCadreBlanc};

    if(pSpriteMur && pSpriteMob && pSpriteArriver && pSpriteRoute && pSpriteCadreBlanc)
    {

        ///*****************************************************************************///
        ///**DEBUT VARIABLE**///

        // Boucle qui fait tourner le jeu.
        bool boucleJeu = true;

        int time = 0;
        bool timeChange = false;

        int typeUnite = 0;

        unsigned int valeurAvantLaBouclePlusLimit = 0;

        bool boutonGaucheInput = false;

        pListeTunite lArriver = creerListeVide();
        pListeTunite lMob = creerListeVide();

        pGrid grid;


        ///**FIN VARIABLE**///
        ///*****************************************************************************///

        ///*****************************************************************************///
        ///**DEBUT INITIALISATION**///

        TplateauJeu plateau = AlloueTab2D(LARGEURJEU, HAUTEURJEU);
        initPlateauAvecNULL(plateau, LARGEURJEU, HAUTEURJEU);
        for(int y = 0; y < HAUTEURJEU; y++)
        {
            for(int x = 0; x < LARGEURJEU; x++)
            {
                //plateau[x][y] = creeMur(x, y);
                plateau[x][y] = NULL;
            }
        }

        alloueGrid(&grid, LARGEURJEU, HAUTEURJEU);
        initGridAvecPlateau(plateau, grid);

        affichePlateauConsole(plateau, LARGEURJEU, HAUTEURJEU);

        prepareAllSpriteDuJeu(plateau,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);


        ///**FIN INITIALISATION**///
        ///*****************************************************************************///


        message("Differentes action du jeu",
                "Clic gauche pour placer un bloc\nClic droit pour changer de bloc\n ECHAP pour quitte le jeu");

        // boucle principale du jeu
        while (boucleJeu)
        {
                limitFps(&valeurAvantLaBouclePlusLimit, &time, &timeChange);

                ///*****************************************************************************///
                ///**DEBUT DU JEU**///
                if(timeChange)
                {
                    if(lArriver != NULL)
                    {
                        deplacementDeToutLesMobs(plateau, &lMob, lArriver);
                    }
                    incrementTickMobs(lMob);


                    //Affichage du plateau à chaque tour.
                    efface_fenetre(pWinSurf);
                    prepareAllSpriteDuJeu(plateau,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                    maj_fenetre(pWindow);
                    timeChange = false;
                }

                ///**FIN DU JEU**///
                ///*****************************************************************************///

                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                boucleJeu = false;
                            }
                            if(event.key.keysym.sym == SDLK_r)
                            {
                                //printf("touche R\n");
                            }
                            continue;

                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                lookMouse(event.button.x, event.button.y, plateau, &typeUnite, &lArriver, &lMob, grid);
                                boutonGaucheInput = true;
                            }
                            if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                addToInt(&typeUnite, -1, 2);
                            }
                            continue;

                        case SDL_MOUSEBUTTONUP:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                boutonGaucheInput = false;
                            }
                            continue;

                        case SDL_QUIT:
                            boucleJeu = false;
                            break;

                        default:
                            break;
                    }
                    if(boutonGaucheInput)
                    {
                        lookMouse(event.button.x, event.button.y, plateau, &typeUnite, &lArriver, &lMob, grid);
                    }
                }

        }
        //fin boucle du jeu

        // Free des surfaces.
        SDL_FreeSurface(pWinSurf);

        SDL_FreeSurface(pSpriteMur);
        SDL_FreeSurface(pSpriteMob);
        SDL_FreeSurface(pSpriteArriver);
        SDL_FreeSurface(pSpriteRoute);
        SDL_FreeSurface(pSpriteCadreBlanc);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
