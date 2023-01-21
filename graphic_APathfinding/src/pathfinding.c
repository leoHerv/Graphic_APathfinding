#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"
#include "pathfinding.h"
#include "list_pathfinding.h"

////////////////////////////////////////////////////////////////
/*                       Allocation :                         */
////////////////////////////////////////////////////////////////

	/**--------------------------------------------------------*/

	void alloueGrid(pGrid* pGrille, int sizeX, int sizeY)
	{
		*pGrille = (pGrid) malloc(sizeof(grid));

		(*pGrille)->sizeX = sizeX;
		(*pGrille)->sizeY = sizeY;

		(*pGrille)->tabType = (TYPE**) malloc(sizeof(TYPE*) * sizeX);

		for(int i = 0; i < sizeX; i++)
		{
            (*pGrille)->tabType[i] = (TYPE*) malloc(sizeof(TYPE) * sizeY);
		}
	}

	/**--------------------------------------------------------*/

	pNode alloueNode(pNode parent, int x, int y, int g, int h, int f)
	{
		pNode newNode = (pNode) malloc(sizeof(node));

		newNode->parent = parent;
		newNode->x = x;
		newNode->y = y;
		newNode->g = g;
		newNode->h = h;
		newNode->f = f;
		return newNode;
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*                   Calcul distance :                        */
////////////////////////////////////////////////////////////////

	/**--------------------------------------------------------*/

	int calculHCost(int dX, int dY, int fX, int fY)
	{
		return 10 * (abs(dX - fX) + abs(dY - fY));
	}

	/**--------------------------------------------------------*/

	int calculGCost(int nX, int nY, pNode parentNode)
	{
		if((nX != parentNode->x && nY == parentNode->y) || (nX == parentNode->x && nY != parentNode->y))
		{
			return parentNode->g + 10;
		}
		else
		{
			return parentNode->g + 14;
		}
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*                    Création node :                         */
////////////////////////////////////////////////////////////////

	/**--------------------------------------------------------*/

	pNode initFirstNode(int x, int y, int finX, int finY)
	{
		int hCost = calculHCost(x, y, finX, finY);
		return alloueNode(NULL, x, y, 0, hCost, hCost);
	}

	/**--------------------------------------------------------*/

	pNode InitNeighbourNode(int x, int y, int finX, int finY, pNode parentNode)
	{
		int gCost = calculGCost(x, y, parentNode);
		int hCost = calculHCost(x, y, finX, finY);
		return alloueNode(parentNode, x, y, gCost, hCost, gCost + hCost);
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*                Operation sur liste de node :               */
////////////////////////////////////////////////////////////////

	/**--------------------------------------------------------*/

	pNode findSmallestFCost(List l)
	{
		if(is_empty_List(l))
		{
			fprintf(stderr, "Erreur findSmallestFCost: la liste est vide.\n");
			exit(EXIT_FAILURE);
		}
		else if(len_List(l) == 1)
        {
            return l->begin->value;
        }
		else
		{
			pNode smallestFCostNode = l->begin->value;
			for(ListNode* tmp = l->begin->next; tmp != NULL; tmp = tmp->next)
            {
                if(smallestFCostNode->f > tmp->value->f)
				{
					smallestFCostNode = tmp->value;
				}
            }
			return smallestFCostNode;
		}
	}

	/**--------------------------------------------------------*/

	bool nodeInListPos(List l, pNode n)
	{
		if(is_empty_List(l))
		{
			return false;
		}
		else
		{
			for(ListNode* tmp = l->begin; tmp != NULL; tmp = tmp->next)
            {
                if(is_posNodes_equal(tmp->value, n))
				{
					return true;
				}
            }
			return false;
		}
	}

	/**--------------------------------------------------------*/

	pNode nodeInListPos_rNode(List l, pNode n)
	{
		for(ListNode* tmp = l->begin; tmp != NULL; tmp = tmp->next)
        {
            if(is_posNodes_equal(tmp->value, n))
            {
                return tmp->value;
            }
        }
		fprintf(stderr, "Erreur nodeInListPos_rNode: la node n'est pas dans la liste.\n");
		exit(EXIT_FAILURE);
	}

	/**--------------------------------------------------------*/

	List removeNodeFormList(pNode nodeToRemove, List l)
	{
		if(is_empty_List(l))
		{
			fprintf(stderr, "Erreur removeNodeFormList: la liste est vide.\n");
			exit(EXIT_FAILURE);
		}
		else if(len_List(l) == 1 && is_nodes_equal(nodeToRemove, l->begin->value))
        {
            if(is_nodes_equal(nodeToRemove, l->begin->value))
            {
                l = rem_fst_List(l);
                return l;
            }
            else
            {
                fprintf(stderr, "Erreur removeNodeFormList: la node a detruire n\'est pas dans la liste.\n");
                exit(EXIT_FAILURE);
            }
        }
		else
		{
			for(ListNode* tmp = l->begin; tmp != NULL; tmp = tmp->next)
            {
                if(is_nodes_equal(tmp->value, nodeToRemove))
				{
					ListNode* aDetruire = tmp;
					ListNode* back = aDetruire->back;
					ListNode* next = aDetruire->next;

                    //Si la node arriere est differente de NULL alors on met son next au next de aDetruire
					if(back != NULL)
                    {
                        back->next = next;
                    }
                    //Si la node suivante est differente de NULL alors on met son back au back de aDetruire
					if(next != NULL)
                    {
                        next->back = back;
                    }
                    //Si aDetruire est premier de la liste alors on met begin au next de aDetruire
                    if(aDetruire == l->begin)
                    {
                        l->begin = next;
                    }
                    //Si aDetruire est dernier de la liste alors on met end au back de aDetruire
                    if(aDetruire == l->end)
                    {
                        l->end = back;
                    }
                    (l->len)--;
					free(aDetruire);
					aDetruire = NULL;
					return l;
				}
            }
			return l;
		}
	}

	/**--------------------------------------------------------*/

	List findAllNeighbour(grid grille, pNode parentNode, int aX, int aY)
	{
		List neighbourList = empty_List();

		for(int x = -1; x <= 1; x++)
		{
			for(int y = -1; y <= 1; y++)
			{
				if(!(x == 0 && y == 0))
				{
					int newX = parentNode->x + x;
					int newY = parentNode->y + y;
					// Si la position est dans la grille.
					if(newX < grille.sizeX && newY < grille.sizeY && newX > 0 && newY > 0)
					{
                        char posChar = grille.tabType[newX][newY];
                        if(posChar== ' ' || posChar == 'R' || posChar == 'U' || posChar == 'A')
                        {
                            neighbourList = add_fst_List(neighbourList, InitNeighbourNode(newX, newY, aX, aY, parentNode));
                        }
					}
				}
			}
		}
		return neighbourList;
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*              Comparaison entre deux nodes :                */
////////////////////////////////////////////////////////////////

	/*--------------------------------------------------------*/

	bool is_nodes_equal(pNode n1, pNode n2)
	{
		return n1 == n2;
	}

	/*--------------------------------------------------------*/

	bool is_posNodes_equal(pNode n1, pNode n2)
	{
			return ((n1->x == n2->x) && (n1->y == n2->y));
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*           Calcul du chemin du depart vers l'arrivé :       */
////////////////////////////////////////////////////////////////

	/*--------------------------------------------------------*/

	List returnPath(grid grille, int dX, int dY, int aX, int aY)
	{
	    // Initialise les listes ouverte et fermer.
		List open = empty_List();
		List closed = empty_List();

		// On crée la première node.
		pNode fstNode = initFirstNode(dX, dY, aX, aY);
		open = add_fst_List(open, fstNode);

		pNode actuel = NULL;

		//printf("Debut recherche\n");
        //SDL_Delay(2000);
        int nb = 0;

		do
		{
		    //printf("Delay %d\n", nb);
		    nb++;
		    //SDL_Delay(2);

		    // On trouve le plus petit F cost de la liste ouverte.
			actuel = findSmallestFCost(open);

			open = removeNodeFormList(actuel, open);

			closed = add_fst_List(closed, actuel);

            // Si nous sommes à l'arriver alors on retoure la liste des nodes, du point de depart vers l'arriver.
			if(actuel->x == aX && actuel->y == aY)
			{
			    List listeDeRetour = empty_List();
			    for(pNode tmp = actuel; tmp != NULL; tmp = tmp->parent)
                {
                    closed = removeNodeFormList(tmp, closed);
                    listeDeRetour = add_fst_List(listeDeRetour, tmp);
                }
                //printf("debut clear_List\n");
                //SDL_Delay(5000);
                closed = clear_List(closed);
                open = clear_List(open);
                //printf("fin clear_List\n");
                //SDL_Delay(5000);
				return listeDeRetour;
			}
			//printf("start findAllNeighbour\n");
			List neighbourList = findAllNeighbour(grille, actuel, aX, aY);

			while(!is_empty_List(neighbourList))
			{
				pNode neighbour = fst_List(neighbourList);
                // Si le voisin n'est pas dans la liste fermer.
				if(!(nodeInListPos(closed, neighbour)))
				{
				    // Si le voisin n'est pas dans la liste fermer et n'est pas dans la liste ouverte on l'ajoute à la liste ouverte.
					if(!(nodeInListPos(open, neighbour)))
					{
						open = add_lst_List(open, neighbour);
					}
					else
					{
					    // Si le voisin est dans la liste ouverte on l'enleve de la liste ouverte.
						pNode neighbourInOpen = nodeInListPos_rNode(open, neighbour);
						// Si le nouveau voisin a un meilleur F cost alors on supprime l'ancien.
						if(neighbourInOpen->f > neighbour->f)
						{
						    pNode oldNeighbourNode = neighbourInOpen;
							open = removeNodeFormList(oldNeighbourNode, open);
							free(oldNeighbourNode);
							oldNeighbourNode = NULL;
							open = add_lst_List(open, neighbour);
						}
						else
                        {
                            free(neighbour);
                            neighbour = NULL;
                        }
					}
				}
				neighbourList = rem_fst_List(neighbourList);
			}
			//printf("end findAllNeighbour\n");
			//SDL_Delay(200);

		}while(!is_empty_List(open));

		closed = clear_List(closed);
		open = clear_List(open);

		return empty_List();
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*                Modification de la grille :                 */
////////////////////////////////////////////////////////////////

	/*--------------------------------------------------------*/

	void printPath(pGrid grille, pNode arrive)
	{
		if(arrive != NULL)
		{
			pNode newArrive = arrive->parent;

			while(newArrive->parent != NULL)
			{
			    grille->tabType[newArrive->x][newArrive->y] = '.';
				newArrive = newArrive->parent;
			}
		}
		else
		{
			fprintf(stderr, "Erreur printPath: chemin impossible entre A et B.\n");
			exit(EXIT_FAILURE);
		}
	}

	/*--------------------------------------------------------*/

	void clearPath(pGrid grille, pNode arrive)
	{
		if(arrive != NULL)
		{
			pNode newArrive = arrive->parent;

			while(newArrive->parent != NULL)
			{
			    grille->tabType[newArrive->x][newArrive->y] = ' ';
				newArrive = newArrive->parent;
			}
		}
		else
		{
			fprintf(stderr, "Erreur clearPath: chemin impossible entre A et B.\n");
			exit(EXIT_FAILURE);
		}
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////
/*                 Affichage de la grille :                   */
////////////////////////////////////////////////////////////////

    /*--------------------------------------------------------*/

    void printGrid(pGrid grille)
	{
		for(int y = grille->sizeY-1; y >= 0; y--)
		{
			for(int x = 0; x < grille->sizeX; x++)
			{
				printf("%c", grille->tabType[x][y]);
			}
			printf("\n");
		}
	}

	/*--------------------------------------------------------*/

////////////////////////////////////////////////////////////////


