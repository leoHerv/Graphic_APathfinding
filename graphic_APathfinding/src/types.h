#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "listeDouble.h"

typedef enum typeCase{mur, mob, arriver, route} typeDeCase;

typedef struct unite
{
    typeDeCase type; // Type de l'unit�.
    pTpos pos;  // Position de l'unit�.
    List_P chemin;  // Chemin que doit prendre l'unit� si elle peut bouger.
    bool deplacement; // Si l'unit� ce deplace ou pas.
    int deplacementCap; // Combien de tick doit attendre l'unit� avant de bouger.
    int deplacementActual; // Combien de tick l'unit� � attendu jusqu'ici.
}*pTunite;

typedef struct T_cell
{
    struct T_cell *suiv;
    pTunite pUnite;
}ListeTunite, *pListeTunite;

typedef pTunite** TplateauJeu;


#endif // TYPES_H_INCLUDED
