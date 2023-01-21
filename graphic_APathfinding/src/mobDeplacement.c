#include "SDL.h"
#include "mobDeplacement.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "types.h"

//////////////////////////////////////////////////////////////////
/*                           Liste                              */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    pListeTunite creerListeVide(void)
    {
        return NULL;
    }

    /*----------------------------------------------------------*/

    bool PlayerEstVide(pListeTunite L)
    {
        return L == NULL;
    }

    /*----------------------------------------------------------*/

    pListeTunite add_fst(pListeTunite L, pTunite u)
    {
        pListeTunite fst = (pListeTunite) malloc(sizeof(ListeTunite)); //struct T_cell = ListePlayer

        fst->pUnite = u;
        fst->suiv = L;
        return fst;
    }

    /*----------------------------------------------------------*/

    pListeTunite add_lst(pListeTunite L, pTunite u)
    {
        pListeTunite lst = (pListeTunite) malloc(sizeof(ListeTunite)); //struct T_cell = ListePlayer

        lst->pUnite = u;
        lst->suiv = NULL;
        if(PlayerEstVide(L)) // Si la liste est vide alors L = lst.
        {
            return lst;
        }
        else // Sinon on va à la fin de la liste et on met lst.
        {
            pListeTunite tmp = L;
            while(tmp->suiv != NULL)
            {
                tmp = tmp->suiv;
            }
            tmp->suiv = lst;
            return L;
        }
    }

    /*----------------------------------------------------------*/

    pListeTunite rem_fst(pListeTunite L)
    {
        if(PlayerEstVide(L)) //Si la liste est vide alors elle reste vide.
        {
            return NULL;
        }
        else // Sinon on enlève et libère le premier element.
        {
            pListeTunite suiv = L->suiv;
            free(L);
            L = NULL;
            return suiv;
        }
    }

    /*----------------------------------------------------------*/

    pTunite fst(pListeTunite L)
    {
        return L->pUnite;
    }

    /*----------------------------------------------------------*/

    int len(pListeTunite L)
    {
        int len = 0;
        pListeTunite tmp = L;
        while(!PlayerEstVide(tmp))
        {
            len++;
            tmp = tmp->suiv;
        }
        return len;
    }

    /*----------------------------------------------------------*/

    pListeTunite clearList(pListeTunite L)
    {
        while(!PlayerEstVide(L)) // Tant que la liste n'est pas vide on enleve le premier element.
        {
             L = rem_fst(L);
        }
        return L;
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                           Random                             */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void initRandom(void)
    {
        srand(time(NULL));
    }

    /*----------------------------------------------------------*/

    int random_int(int min, int max)
    {
        return min + rand() % (max+1 - min);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                           Allocations                        */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    TplateauJeu AlloueTab2D(int largeur, int hauteur)
    {
        TplateauJeu jeu;
        jeu = (pTunite**)malloc(sizeof(pTunite*)*largeur);
        for (int i=0;i<largeur;i++)
        {
            jeu[i] = (pTunite*)malloc(sizeof(pTunite)*hauteur);
        }
        return jeu;
    }

    /*----------------------------------------------------------*/

    pTunite creeUnite(typeDeCase type, int posX, int posY, List_P chemin, bool deplacement, int deplacementCap, int deplacementActual)
    {
        pTunite nouv = (pTunite)malloc(sizeof(struct unite));
        nouv->type = type;
        pTpos nouvPos = (pTpos)malloc(sizeof(struct pos));
        nouvPos->posX = posX;
        nouvPos->posY = posY;
        nouv->pos = nouvPos;
        nouv->chemin = chemin;
        nouv->deplacement = deplacement;
        nouv->deplacementCap = deplacementCap;
        nouv->deplacementActual = deplacementActual;
        return nouv;
    }

    /*----------------------------------------------------------*/

    pTunite creeMur(int posX, int posY)
    {
        // typeDeCase /pos /chemin
        return creeUnite(mur, posX, posY, NULL, false, 0, 0);
    }

    /*----------------------------------------------------------*/

    pTunite creeMob(int posX, int posY)
    {
        return creeUnite(mob, posX, posY, NULL, true, 20, 1);
    }

    /*----------------------------------------------------------*/

    pTunite creeArriver(int posX, int posY)
    {
        return creeUnite(arriver, posX, posY, NULL, false, 0, 0);
    }

    /*----------------------------------------------------------*/

    pTunite creeRoute(int posX, int posY)
    {
        return creeUnite(route, posX, posY, NULL, false, 0, 0);
    }

    /*----------------------------------------------------------*/

    void createListPosAvecListNode(List* lDepartVersArriver, List_P* listPos)
    {
        if(lDepartVersArriver != NULL)
        {
            // On supprime le premier element.
            free((*lDepartVersArriver)->begin->value);
            (*lDepartVersArriver)->begin->value = NULL;
            *lDepartVersArriver = rem_fst_List(*lDepartVersArriver);
            while(*lDepartVersArriver != NULL)
            {
                // On crée un pTpos avec les info de la node.
                pTpos newPos = (pTpos)malloc(sizeof(struct pos));
                pNode fNode = fst_List(*lDepartVersArriver);
                newPos->posX = fNode->x;
                newPos->posY = fNode->y;
                // On ajoute la pos à la liste finale.
                *listPos = add_lst_List_P(*listPos, newPos);
                // Et on supprime la node qui ne sert plus à rien.
                free(fNode);
                fNode = NULL;
                *lDepartVersArriver = rem_fst_List(*lDepartVersArriver);
            }
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                    Ajout / Initialisation                    */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void initPlateauAvecNULL(TplateauJeu plateau, int largeur, int hauteur)
    {
        for (int i=0;i<largeur;i++)
        {
            for (int j=0;j<hauteur;j++)
            {
                plateau[i][j] = NULL;
            }
        }
    }

    /*----------------------------------------------------------*/

    void addToInt(int* nbAModifier, int minV, int maxV)
    {
        if(*nbAModifier == maxV)
        {
            *nbAModifier = minV;
        }
        else
        {
            (*nbAModifier)++;
        }
    }

    /*----------------------------------------------------------*/

    void initGridAvecPlateau(TplateauJeu plateau, pGrid grid)
    {
        for (int x = 0; x < LARGEURJEU; x++)
        {
            for (int y = 0; y < HAUTEURJEU; y++)
            {
                char c;
                int type;
                if(plateau[x][y] != NULL)
                {
                    type = plateau[x][y]->type;
                }
                else
                {
                    type = -1;
                }
                switch(type)
                {
                    case mur:
                        c = 'M';
                        break;
                    case mob:
                        c = 'U';
                        break;
                    case arriver:
                        c = 'A';
                        break;
                    default:
                        c = ' ';
                        break;
                }
                grid->tabType[x][y] = c;
            }
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                         Modification                         */
//////////////////////////////////////////////////////////////////

   /*----------------------------------------------------------*/

   void lookMouse(int x, int y, TplateauJeu plateau, int* typeUnite, pListeTunite* lArriver, pListeTunite* lMob, pGrid grid)
   {
       if(x > 0 && x < LARGEURJEU * 11 && y > 0 && y < HAUTEURJEU * 11)
       {
            pTunite unite = plateau[x / 11][y / 11];
            bool changementDeCase = true;
            if(unite == NULL)
            {
                if(*typeUnite == -1) // Si la case est vide et que on veut mettre NULL dans la case alors on ne change pas.
                {
                    changementDeCase = false;
                }
            }
            else
            {
                if(unite->type == *typeUnite) // Si la case est la même que celle que l'on veut mettre alors on ne change pas.
                {
                    changementDeCase = false;
                }
            }
            if(changementDeCase)
            {
                // Si la case n'est pas vide, on supprime l'unité qui est sur la case.
                if(unite != NULL)
                {
                    if(unite->type == arriver)
                    {
                        supprimerUniteInList(lArriver, unite);
                    }
                    else if(unite->type == mob)
                    {
                        supprimerUniteInList(lMob, unite);
                    }
                    else
                    {
                        supprimerUnite(&unite);
                    }
                }
                if(*typeUnite != -1)
                {
                    pTunite (*fDeCreation)(int posX, int posY) = fonctionDeCreationUnites(*typeUnite);
                    pTunite newUnite = fDeCreation(x /11, y / 11);
                    if(*typeUnite == mob)
                    {
                        *lMob = add_fst(*lMob, newUnite);
                    }
                    else if(*typeUnite == arriver)
                    {
                        if(!PlayerEstVide(*lArriver))
                        {
                            pTunite uniteADetruire = fst(*lArriver);
                            plateau[uniteADetruire->pos->posX][uniteADetruire->pos->posY] = NULL;
                            supprimerUniteInList(lArriver, uniteADetruire);
                        }
                        *lArriver = add_fst(*lArriver, newUnite);
                    }
                    plateau[x / 11][y / 11] = newUnite;
                }
                if(*typeUnite == -1)
                {
                    plateau[x / 11][y / 11] = NULL;
                }
                afficheListeUnites(*lArriver, "Arriver");
                afficheListeUnites(*lMob, "Mob");

                // On fait calcul des chemin pour aller vers l'arriver si c'est possible.
                initGridAvecPlateau(plateau, grid);
                calculCheminDeToutLesMob(plateau, *lArriver, *lMob, grid);
            }
        }
   }

   /*----------------------------------------------------------*/

   pTunite(*fonctionDeCreationUnites(typeDeCase type))(int posX, int posY)
   {
       switch(type)
       {
            case mur:
                return creeMur;

            case mob:
                return creeMob;

            case arriver:
                return creeArriver;

            case route:
                return creeRoute;

            default:
                printf("Erreur fonctionDeCreationUnites : mauvais type\n");
                return NULL;
       }
   }

   /*----------------------------------------------------------*/

   void calculCheminMob(TplateauJeu plateau, pListeTunite lArriver, pTunite mob, pGrid grid)
   {
       pTunite arriver = fst(lArriver);
       //printf("debut returnPath\n");
       //SDL_Delay(7000);
       List lDepartVersArriver = returnPath(*grid, mob->pos->posX, mob->pos->posY, arriver->pos->posX, arriver->pos->posY);
       //printf("fin returnPath\n");
       //SDL_Delay(7000);
       List_P listPos = empty_List_P();
       createListPosAvecListNode(&lDepartVersArriver, &listPos);
       mob->chemin = clear_List_P(mob->chemin);
       mob->chemin = listPos;
   }

   /*----------------------------------------------------------*/

   void calculCheminDeToutLesMob(TplateauJeu plateau, pListeTunite lArriver, pListeTunite lMob, pGrid grid)
   {
       if(lArriver != NULL)
       {
            initGridAvecPlateau(plateau, grid);
            for(pListeTunite tmp = lMob; tmp != NULL; tmp = tmp->suiv)
            {
                calculCheminMob(plateau, lArriver, tmp->pUnite, grid);
            }
       }
   }

   /*----------------------------------------------------------*/

   void afficheRouteMob(TplateauJeu plateau, pTunite mob)
   {
       if(mob->chemin != NULL)
       {
           for(ListNode_P* tmp = mob->chemin->begin; tmp != NULL; tmp = tmp->next)
           {
               int tmpX = tmp->value->posX;
               int tmpY = tmp->value->posY;
               if(plateau[tmpX][tmpY] == NULL)
               {
                   plateau[tmpX][tmpY] = creeRoute(tmpX, tmpY);
               }
           }
       }
   }

   /*----------------------------------------------------------*/

   void afficheRouteDeToutLesMob(TplateauJeu plateau, pListeTunite lMob)
   {
        for(pListeTunite tmp = lMob; tmp != NULL; tmp = tmp->suiv)
        {
            afficheRouteMob(plateau, tmp->pUnite);
        }
   }

   /*----------------------------------------------------------*/

   void deplacementMob(TplateauJeu plateau, pTunite mob, pListeTunite* lMob, pListeTunite lArriver)
   {
       if(mob->deplacementCap == mob->deplacementActual)
       {
           int nextX = mob->chemin->begin->value->posX;
           int nextY = mob->chemin->begin->value->posY;
           if(plateau[nextX][nextY] == NULL)
           {
                int oldX = mob->pos->posX;
                int oldY = mob->pos->posY;
                mob->pos->posX = nextX;
                mob->pos->posY = nextY;
                plateau[nextX][nextY] = mob;
                plateau[oldX][oldY] = NULL;
                free(mob->chemin->begin->value);
                mob->chemin->begin->value = NULL;
                mob->chemin = rem_fst_List_P(mob->chemin);
           }
           else if(plateau[nextX][nextY] == fst(lArriver))
           {
                plateau[mob->pos->posX][mob->pos->posY] = NULL;
                supprimerUniteInList(lMob, mob);
           }
       }
   }

   /*----------------------------------------------------------*/

   void deplacementDeToutLesMobs(TplateauJeu plateau, pListeTunite* lMob, pListeTunite lArriver)
   {
        for(pListeTunite tmp = *lMob; tmp != NULL; tmp = tmp->suiv)
        {
            if(tmp->pUnite->deplacement == true && tmp->pUnite->chemin != NULL)
            {
                deplacementMob(plateau, tmp->pUnite, lMob, lArriver);
            }
        }
   }

   /*----------------------------------------------------------*/

   void incrementTickMobs(pListeTunite lMob)
   {
        for(pListeTunite tmp = lMob; tmp != NULL; tmp = tmp->suiv)
        {
            if(tmp->pUnite->deplacement) // Si deplacement = true
            {
                if(tmp->pUnite->deplacementActual == tmp->pUnite->deplacementCap)
                {
                    tmp->pUnite->deplacementActual = 1;
                }
                else
                {
                    tmp->pUnite->deplacementActual += 1;
                }
            }
        }
   }

   /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                        Suppression                           */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void supprimerUniteInList(pListeTunite* listUnite, pTunite UniteDetruite)
    {
        bool finSuppression = false;
        pListeTunite precUnit = NULL;
        pListeTunite Unit = *listUnite;
        while(!finSuppression && Unit != NULL)
        {
            if(Unit->pUnite == UniteDetruite)
            {
                if(precUnit != NULL)
                {
                    precUnit->suiv = Unit->suiv;
                }
                else
                {
                    *listUnite = Unit->suiv;
                }
                // Suppresion de l'unité.
                supprimerUnite(&(Unit->pUnite));
                finSuppression = true;
            }
            else
            {
                precUnit = Unit;
                Unit = Unit->suiv;
            }
        }
        if(Unit == NULL)
        {
            printf("Erreur supprimerUnite : la liste est vide ou ne contient pas l\'unite a detruitre.\n");
        }
    }

    /*----------------------------------------------------------*/

    void supprimerUnite(pTunite* UniteADetruite)
    {
        pTunite unite = *UniteADetruite;
        free(unite->pos);
        // Supprime tout les pTpos de la liste.
        unite->chemin = clear_List_P(unite->chemin);
        free(unite);
        *UniteADetruite = NULL;
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                      Verification                            */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    bool posInMap(int x, int y, int largeur, int hauteur)
    {
        return (x >= 0 && x < largeur) && (y >= 0 && y < hauteur);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                   Affichage Console                          */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
        const char* InitialeUnite[4]={"M", "o", "a", "r"};

        printf("\n");
        for (int i=0;i < largeur+2; i++)
        {
            printf("/");
        }
        printf("\n");
        for (int j=0;j<hauteur;j++)
        {
            printf("/");
            for (int i=0;i<largeur;i++)
            {
                if (jeu[i][j] != NULL)
                {
                        printf("%s",InitialeUnite[jeu[i][j]->type]);
                }
                else // Pas d'unité sur cette case.
                {
                    printf(".");
                }
            }
            printf("/\n");
        }
        for (int i=0;i < largeur+2; i++)
        {
            printf("/");
        }
        printf("\n");
    }

    /*----------------------------------------------------------*/

    void afficheUneUnite(pTunite unite)
    {
        const char* nomUnites[4] = {"Mur", "Mob", "Arriver", "Route"};
        printf("%s = posX: %d, posY: %d, dCap: %d, dActual: %d\n", nomUnites[unite->type], unite->pos->posX, unite->pos->posY, unite->deplacementCap, unite->deplacementActual);
        //print_List_P(unite->chemin);
    }

    /*----------------------------------------------------------*/

    void afficheListeUnites(pListeTunite liste, const char* nomListe)
    {
        printf("\nAffichage de la liste de \"%s\" :\n", nomListe);
        printf("----------------------------------------------------------------------\n");
        if(PlayerEstVide(liste))
        {
            printf("La liste est vide.\n");
        }
        else
        {
            pListeTunite tmp = liste;
            while(!PlayerEstVide(tmp)) // Affiche toutes les unités.
            {
                afficheUneUnite(tmp->pUnite);
                tmp = tmp->suiv;
            }
        }
        printf("----------------------------------------------------------------------\n");
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                        Limite FPS                            */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    // limite le nombre de FPS selon les FPS voulu
    void limitFps(unsigned int* valeurAvantLaBouclePlusLimit, int* tick, bool* tickChange)
    {
        unsigned int currentTime = SDL_GetTicks();
        if(*valeurAvantLaBouclePlusLimit <= currentTime)
        {
            if(*tick == FPS)
            {
                *tick = 0;
            }
            else
            {
              (*tick)++;
            }
            *valeurAvantLaBouclePlusLimit = SDL_GetTicks() + FPS_LIMIT;
            *tickChange = true;
        }
        else
        {
            SDL_Delay(2); // 1000 / 120 = 8
            *tickChange = false;
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////




