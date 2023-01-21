#ifndef __LIST__H__
#define __LIST__H__

	#include <stdbool.h>
	#include "pathfinding.h"

	#define TYPE_LIST pNode

	// Definition d'une case de la liste.
	typedef struct ListNode
	{
		TYPE_LIST value;
		struct ListNode* back;
		struct ListNode* next;
	}ListNode;

	// Definition d'une liste.
	typedef struct List
	{
		int len;
		struct ListNode* begin;
		struct ListNode* end;
	}*List;

	// Prototypes :

	// Crée une liste vide.
	List empty_List(void);

	// Regarde si la liste est vide (true oui / false non).
	bool is_empty_List(List l);

	// Donne la longueur de la liste.
	int len_List(List l);

	// Donne la première valeur de la liste.
	TYPE_LIST fst_List(List l);

	// Donne la dernière valeur de la liste.
	TYPE_LIST lst_List(List l);

	// Affiche toute la liste.
	void print_List(List l);

	// Ajoute "number" au debut de la liste.
	List add_fst_List(List l, TYPE_LIST number);

	// Ajoute "number" à la fin de la liste.
	List add_lst_List(List l, TYPE_LIST number);

	// Enleve le debut de la liste.
	List rem_fst_List(List l);

	// Enleve la fin de la liste.
	List rem_lst_List(List l);

	// Remet la liste à 0 élément.
	List clear_List(List l);

#endif // __LIST__H__
