#ifndef MOBDEPLACEMENT_H_INCLUDED
#define MOBDEPLACEMENT_H_INCLUDED

#include "types.h"
#include "pathfinding.h"

//////////////////////////////////////////
/*          Types et defines            */
//////////////////////////////////////////

    #define LARGEURJEU 100
    #define HAUTEURJEU 70

    #define FPS 120
    #define FPS_LIMIT (1000 / FPS) // 120 fps (33 = 30 fps -> 1000 ms / 30 = 33)

///////////////////////////////////////
/*               Liste               */
///////////////////////////////////////

    // Retourne une pListeTunite vide.
    pListeTunite creerListeVide(void);

     // Retourne vrai ou faux si la pListeTunite est vide ou pas.
    bool PlayerEstVide(pListeTunite L);

    // Ajoute une valeur devant la pListeTunite.
    pListeTunite add_fst(pListeTunite L, pTunite u);

    // Ajoute une valeur derière la pListeTunite.
    pListeTunite add_lst(pListeTunite L, pTunite u);

    // Retire le premier element de la pListeTunite.
    pListeTunite rem_fst(pListeTunite L);

    // Donne le premier element de la pListeTunite.
    pTunite fst(pListeTunite L);

    // Donne le nombre d'elements qu'il y a dans la liste.
    int len(pListeTunite L);

    // Vide une pListeTunite.
    pListeTunite clearList(pListeTunite L);

    // Fait une copie d'une pListeTunite.
    pListeTunite copieList(pListeTunite L);

//////////////////////////////////////////
/*                Random                */
//////////////////////////////////////////

    // Initialise la randomisation.
    void initRandom(void);

    // Donne un nombre random entre min et max.
    int random_int(int min, int max);

//////////////////////////////////////////
/*             Allocations              */
//////////////////////////////////////////

    // Alloue un tableau 2D de pointeurs sur des unités du jeu.
    TplateauJeu AlloueTab2D(int largeur, int hauteur);

    // Alloue une unité.
    pTunite creeUnite(typeDeCase typeDeCase, int posX, int posY, List_P chemin, bool deplacement, int deplacementCap, int deplacementActual);

    // Alloue une unité "mur".
    pTunite creeMur(int posX, int posY);

    // Alloue une unité "mob".
    pTunite creeMob(int posX, int posY);

    // Alloue une unité "arriver".
    pTunite creeArriver(int posX, int posY);

    // Alloue une unité "route".
    pTunite creeRoute(int posX, int posY);

    // Transforme une liste de node en liste de pos.
    void createListPosAvecListNode(List* lDepartVersArriver, List_P* listPos);

//////////////////////////////////////////
/*         Ajout / Initialisation       */
//////////////////////////////////////////

    // Initialise le tableau en début de partie.
    void initPlateauAvecNULL(TplateauJeu plateau, int largeur, int hauteur);

    // Ajoute 1 à un nombre si ce n'est pas son max.
    void addToInt(int* nbAModifier, int minV, int maxV);

    // Rempli une grid avec les données du plateau.
    void initGridAvecPlateau(TplateauJeu plateau, pGrid grid);

//////////////////////////////////////////
/*            Modification              */
//////////////////////////////////////////

    // Regarde si une touche est utilisé et fait des actions en consequence.
    void lookAction(SDL_Event* event, bool* boucleJeu, TplateauJeu plateau, bool* boutonGaucheInput, int* typeUnite,
                    pListeTunite* lArriver, pListeTunite* lMob, pGrid grid);

    // Regarde les actions possible avec le clic gauche.
    void lookMouse(int x, int y, TplateauJeu plateau, int* typeUnite, pListeTunite* lArriver, pListeTunite* lMob, pGrid grid);

    // Donne une fonction de création d'unité en fonction du type donner.
    pTunite(*fonctionDeCreationUnites(typeDeCase type))(int posX, int posY);

    // Calcul le chemin de l'unité vers l'arriver.
    void calculCheminMob(TplateauJeu plateau, pListeTunite lArriver, pTunite mob, pGrid grid);

    // Calcul le chemin de toutes les unités vers l'arriver.
    void calculCheminDeToutLesMob(TplateauJeu plateau, pListeTunite lArriver, pListeTunite lMob, pGrid grid);

    // Affiche une route sur le plateau.
    void afficheRouteMob(TplateauJeu plateau, pTunite mob);

    // Affiche toutes les routes des Mobs de la liste.
    void afficheRouteDeToutLesMob(TplateauJeu plateau, pListeTunite lMob);

    // Permet de deplacer un mob selon le chemin qu'il doit suivre.
    void deplacementMob(TplateauJeu plateau, pTunite mob, pListeTunite* lMob, pListeTunite lArriver);

    // Permet de deplacer tout les mobs de la liste.
    void deplacementDeToutLesMobs(TplateauJeu plateau, pListeTunite* lMob, pListeTunite lArriver);

    // Modifie à chaque tick le champs "deplacementActual" de toutes les mobs de la liste.
    void incrementTickMobs(pListeTunite lMob);


//////////////////////////////////////////
/*             Suppression              */
//////////////////////////////////////////

    // Supprime une unité de la liste d'unités d'une listUnite.
    void supprimerUniteInList(pListeTunite* listUnite, pTunite UniteDetruite);

    // Supprime une unité.
    void supprimerUnite(pTunite* UniteADetruite);

//////////////////////////////////////////
/*             Verification             */
//////////////////////////////////////////

    // Permet de savoir si une position X Y est (largeur, hauteur) est dans la map du jeu ou pas.
    bool posInMap(int x, int y, int largeur, int hauteur);

//////////////////////////////////////////
/*           Affichage Console          */
//////////////////////////////////////////

    // Affiche le plateau dans la console avec les noms des unités et rien s'il n'y en a pas.
    void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

    // Affiche une unité.
    void afficheUneUnite(pTunite unite);

    // Affiche une liste d'unites.
    void afficheListeUnites(pListeTunite liste, const char* nomListe);

//////////////////////////////////////////
/*               Limite FPS             */
//////////////////////////////////////////

    // Permet de faire une regulation d'FPS (selon FPS_LIMIT).
    void limitFps(unsigned int* valeurAvantLaBouclePlusLimit, int* tick, bool* tickChange);

//////////////////////////////////////////

#endif // MOBDEPLACEMENT_H_INCLUDED
