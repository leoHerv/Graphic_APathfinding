#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pathfinding.h"
#include "list_pathfinding.h"

/*///////////////////////////////////////////////////////////////*/

List empty_List(void)
{
	return NULL;
}

/*///////////////////////////////////////////////////////////////*/

bool is_empty_List(List l)
{
	if(l == NULL)
		return true;
	return false;
}

/*///////////////////////////////////////////////////////////////*/

int len_List(List l)
{
	if(is_empty_List(l))
		return 0;
	return l->len;
}

/*///////////////////////////////////////////////////////////////*/

TYPE_LIST fst_List(List l)
{
	if(is_empty_List(l))
	{
		fprintf(stderr, "Erreur fst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	return l->begin->value;
}

/*///////////////////////////////////////////////////////////////*/

TYPE_LIST lst_List(List l)
{
	if(is_empty_List(l))
	{
		fprintf(stderr, "Erreur lst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	return l->end->value;
}

/*///////////////////////////////////////////////////////////////*/

void print_List(List l)
{
	if(is_empty_List(l))
	{
		printf("La liste est vide.\n");
		return;
	}

	ListNode* tmp = l->begin;

	for(int i = 0; i < l->len; i++)
	{
		printf("x: %d, y: %d, g: %d, h: %d, f: %d ", tmp->value->x, tmp->value->y, tmp->value->g, tmp->value->h, tmp->value->f);
		if(tmp->value->parent != NULL)
		{
			printf("[parent: x: %d, y: %d, g: %d, h: %d, f: %d]", tmp->value->parent->x, tmp->value->parent->y, tmp->value->parent->g, tmp->value->parent->h, tmp->value->parent->f);
		}
		if(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		printf("\n");
	}
}

/*///////////////////////////////////////////////////////////////*/

List add_fst_List(List l, TYPE_LIST number)
{
	ListNode* node;

	node = (ListNode *)malloc(sizeof(ListNode));

	if(node == NULL)
	{
		fprintf(stderr, "Erreur add_fst_List : allocation memoire (1).\n");
		exit(EXIT_FAILURE);
	}

	node->value = number;
	node->back = NULL;
	node->next = NULL;

	if(is_empty_List(l))
	{
		l = (List)malloc(sizeof(struct List));

		if(l == NULL)
		{
			fprintf(stderr, "Erreur add_fst_List : allocation memoire (2).\n");
			exit(EXIT_FAILURE);
		}
		l->len = 0;
		l->begin = node;
		l->end = node;
	}
	else
	{
		l->begin->back = node;
		node->next = l->begin;
		l->begin = node;
	}

	l->len++;

	return l;
}

/*///////////////////////////////////////////////////////////////*/

List add_lst_List(List l, TYPE_LIST number)
{
	ListNode* node;

	node = (ListNode *)malloc(sizeof(ListNode));

	if(node == NULL)
	{
		fprintf(stderr, "Erreur add_lst_List : allocation memoire (1).\n");
		exit(EXIT_FAILURE);
	}

	node->value = number;
	node->back = NULL;
	node->next = NULL;

	if(is_empty_List(l))
	{
		l = (List)malloc(sizeof(struct List));

		if(l == NULL)
		{
			fprintf(stderr, "Erreur add_lst_List : allocation memoire (2).\n");
			exit(EXIT_FAILURE);
		}
		l->len = 0;
		l->begin = node;
		l->end = node;
	}
	else
	{
		l->end->next = node;
		node->back = l->end;
		l->end = node;
	}

	l->len++;

	return l;
}

/*///////////////////////////////////////////////////////////////*/

List rem_fst_List(List l)
{
	if(is_empty_List(l))
	{
		fprintf(stderr, "Erreur rem_fst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}

	if(l->begin == l->end)
	{
	    free(l->begin);
	    l->end = NULL;
		free(l);
		l = NULL;
		return l;
	}

	ListNode* tmp = l->begin;

	l->begin = tmp->next;
	l->begin->back = NULL;
	tmp->next = NULL;
	tmp->back = NULL;

	free(tmp);
	tmp = NULL;

	l->len--;

	return l;
}

/*///////////////////////////////////////////////////////////////*/

List rem_lst_List(List l)
{
	if(is_empty_List(l))
	{
		fprintf(stderr, "Erreur rem_lst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}

	if(l->begin == l->end)
	{
	    free(l->end);
	    l->begin = NULL;
		free(l);
		l = NULL;
		return l;
	}

	ListNode* tmp = l->end;

	l->end = l->end->back;
	l->end->next = NULL;
	tmp->next = NULL;
	tmp->back = NULL;

	free(tmp);
	tmp = NULL;

	l->len--;

	return l;
}

/*///////////////////////////////////////////////////////////////*/

List clear_List(List l)
{
	while(!(is_empty_List(l)))
	{
	    free(l->end->value);
	    l->end->value = NULL;
		l = rem_lst_List(l);
	}
	return l;
}

/*///////////////////////////////////////////////////////////////*/
