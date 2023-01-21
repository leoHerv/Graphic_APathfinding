#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listeDouble.h"

/*///////////////////////////////////////////////////////////////*/

List_P empty_List_P(void)
{
	return NULL;
}

/*///////////////////////////////////////////////////////////////*/

bool is_empty_List_P(List_P l)
{
	return l == NULL;
}

/*///////////////////////////////////////////////////////////////*/

int len_List_P(List_P l)
{
	if(is_empty_List_P(l))
    {
        return 0;
    }
	return l->len;
}

/*///////////////////////////////////////////////////////////////*/

TYPE_P fst_List_P(List_P l)
{
	if(is_empty_List_P(l))
	{
		fprintf(stderr, "Erreur fst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	return l->begin->value;
}

/*///////////////////////////////////////////////////////////////*/

TYPE_P lst_List_P(List_P l)
{
	if(is_empty_List_P(l))
	{
		fprintf(stderr, "Erreur lst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}
	return l->end->value;
}

/*///////////////////////////////////////////////////////////////*/

List_P add_fst_List_P(List_P l, TYPE_P pos)
{
	ListNode_P* node;

	node = (ListNode_P *)malloc(sizeof(ListNode_P));

	if(node == NULL)
	{
		fprintf(stderr, "Erreur add_fst_List : allocation memoire (1).\n");
		exit(EXIT_FAILURE);
	}

	node->value = pos;
	node->back = NULL;
	node->next = NULL;

	if(is_empty_List_P(l))
	{
		l = (List_P)malloc(sizeof(struct List_P));

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

List_P add_lst_List_P(List_P l, TYPE_P pos)
{
	ListNode_P* node;

	node = (ListNode_P *)malloc(sizeof(ListNode_P));

	if(node == NULL)
	{
		fprintf(stderr, "Erreur add_lst_List : allocation memoire (1).\n");
		exit(EXIT_FAILURE);
	}

	node->value = pos;
	node->back = NULL;
	node->next = NULL;

	if(is_empty_List_P(l))
	{
		l = (List_P)malloc(sizeof(struct List_P));

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

List_P rem_fst_List_P(List_P l)
{
	if(is_empty_List_P(l))
	{
		fprintf(stderr, "Erreur rem_fst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}

	if(l->begin == l->end)
	{
		free(l);
		l->end = NULL;
		l = NULL;

		return empty_List_P();
	}

	ListNode_P *tmp = l->begin;

	l->begin = l->begin->next;
	l->begin->back = NULL;
	tmp->next = NULL;
	tmp->back = NULL;

	free(tmp);
	tmp = NULL;

	l->len--;

	return l;
}

/*///////////////////////////////////////////////////////////////*/

List_P rem_lst_List_P(List_P l)
{
	if(is_empty_List_P(l))
	{
		fprintf(stderr, "Erreur rem_lst_List : la liste est vide.\n");
		exit(EXIT_FAILURE);
	}

	if(l->begin == l->end)
	{
		free(l);
		l->begin = NULL;
		l = NULL;

		return empty_List_P();
	}

	ListNode_P *tmp = l->end;

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

List_P clear_List_P(List_P l)
{
	while(!(is_empty_List_P(l)))
	{
	    free(l->end->value);
		l = rem_lst_List_P(l);
	}
	return l;
}

/*///////////////////////////////////////////////////////////////*/

void print_List_P(List_P l)
{
    if(l != NULL)
    {
        for(ListNode_P* tmp = l->begin; tmp != NULL; tmp = tmp->next)
        {
            printf("Pos = X: %d Y: %d\n", tmp->value->posX, tmp->value->posY);
        }
    }
    else
    {
        printf("La liste de pos est vide.\n");
    }

}

/*///////////////////////////////////////////////////////////////*/
