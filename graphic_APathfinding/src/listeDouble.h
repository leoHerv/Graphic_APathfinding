#ifndef __LISTEDOUBLE__H__
#define __LISTEDOUBLE__H__

#include <stdbool.h>

typedef struct pos
{
    int posX;
    int posY;
}*pTpos;

#define TYPE_P pTpos

	// Definition d'une case de la liste.
	typedef struct ListNode_P
	{
		TYPE_P value;
		struct ListNode_P* back;
		struct ListNode_P* next;
	}ListNode_P;

	// Definition d'une liste.
	typedef struct List_P
	{
		int len;
		struct ListNode_P* begin;
		struct ListNode_P* end;
	}*List_P;

	// Prototypes :

	// Crée une liste vide.
	List_P empty_List_P(void);

	// Regarde si la liste est vide (true oui / false non).
	bool is_empty_List_P(List_P l);

	// Donne la longueur de la liste.
	int len_List_P(List_P l);

	// Donne la première valeur de la liste.
	TYPE_P fst_List_P(List_P l);

	// Donne la dernière valeur de la liste.
	TYPE_P lst_List_P(List_P l);

	// Ajoute "pos" au debut de la liste.
	List_P add_fst_List_P(List_P l, TYPE_P pos);

	// Ajoute "pos" à la fin de la liste.
	List_P add_lst_List_P(List_P l, TYPE_P pos);

	// Enleve le debut de la liste.
	List_P rem_fst_List_P(List_P l);

	// Enleve la fin de la liste.
	List_P rem_lst_List_P(List_P l);

	// Remet la liste à 0 élément et supprime tout les elements contenu dans la liste.
	List_P clear_List_P(List_P l);

	// Affiche la liste.
	void print_List_P(List_P l);

#endif // __LISTEDOUBLE__H__
