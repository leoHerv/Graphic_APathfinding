#ifndef __PATHFINDING__H__
#define __PATHFINDING__H__

	#include <stdbool.h>

	#define TYPE char

	// Grille 2D de type TYPE
	typedef struct grid
	{
		TYPE** tabType;
		int sizeX;
		int sizeY;
	}grid, *pGrid;

	// Node pour l'algorithme A*
	typedef struct node
	{
		struct node* parent;
		int x;
		int y;
		int g;
		int h;
		int f;
	}node, *pNode;

	#include "list_pathfinding.h"

////////////////////////////////////////////////
/*               Allocation :                 */
////////////////////////////////////////////////

	// alloue de la memoire pour une grid.
	void alloueGrid(pGrid* pGrille, int sizeX, int sizeY);

	// alloue de la memoire pour une node.
	pNode alloueNode(pNode parent, int x, int y, int g, int h, int f);

////////////////////////////////////////////////
/*              Calcul distance :             */
////////////////////////////////////////////////

	// fait le calcul pour le H cost.
	int calculHCost(int dX, int dY, int fX, int fY);

	// fait le calcul pour le G cost.
	int calculGCost(int nX, int nY, pNode parentNode);

////////////////////////////////////////////////
/*               Création node :              */
////////////////////////////////////////////////

	// crée la premiere node.
	pNode initFirstNode(int x, int y, int finX, int finY);

	// crée une node voisine.
	pNode InitNeighbourNode(int x, int y, int finX, int finY, pNode parentNode);

////////////////////////////////////////////////
/*      Operation sur liste de node :         */
////////////////////////////////////////////////

	// trouve la node de la liste avec le plus petit F cost.
	pNode findSmallestFCost(List l);

	// regarde si il y a une node avec la même position dans la liste.
	bool nodeInListPos(List l, pNode n);

	// regarde si il y a une node avec la même position dans la liste et retourne la node.
	pNode nodeInListPos_rNode(List l, pNode n);

	// enleve une node d'une liste de node.
	List removeNodeFormList(pNode nodeToRemove, List l);

	// trouve tout les voisins de la node parent et redonne une liste des voisins.
	List findAllNeighbour(grid grille, pNode parentNode, int aX, int aY);

////////////////////////////////////////////////
/*      Comparaison entre deux nodes :        */
////////////////////////////////////////////////

	// regarde si deux nodes sont idendique.
	bool is_nodes_equal(pNode n1, pNode n2);

	// regarde si la position de deux nodes sont egales.
	bool is_posNodes_equal(pNode n1, pNode n2);

////////////////////////////////////////////////
/* Calcul du chemin du depart vers l'arrivé : */
////////////////////////////////////////////////

	// retourne le chemin de l'arrivé vers le depart.
	List returnPath(grid grille, int dX, int dY, int aX, int aY);

////////////////////////////////////////////////
/*         Modification de la grille :        */
////////////////////////////////////////////////

	// affiche le chemin sur la grille.
	void printPath(pGrid grille, pNode arrive);

	// efface le chemin sur la grille.
	void clearPath(pGrid grille, pNode arrive);

////////////////////////////////////////////////
/*          Affichage de la grille :          */
////////////////////////////////////////////////

	// Affiche la grille dans la console.
	void printGrid(pGrid grille);

#endif // __PATHFINDING__H__
