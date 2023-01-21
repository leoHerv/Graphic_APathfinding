#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "listeDouble.h"

typedef enum typeCase{mur, mob, arriver, route} typeDeCase;

typedef struct unite
{
    typeDeCase type; // Type de l'unité.
    pTpos pos;  // Position de l'unité.
    List_P chemin;  // Chemin que doit prendre l'unité si elle peut bouger.
    bool deplacement; // Si l'unité ce deplace ou pas.
    int deplacementCap; // Combien de tick doit attendre l'unité avant de bouger.
    int deplacementActual; // Combien de tick l'unité à attendu jusqu'ici.
}*pTunite;

typedef struct T_cell
{
    struct T_cell *suiv;
    pTunite pUnite;
}ListeTunite, *pListeTunite;

typedef pTunite** TplateauJeu;


#endif // TYPES_H_INCLUDED
