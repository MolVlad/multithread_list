#include "list.h"

LIST * create_list(NUM_TYPE *values, unsigned size)
{
	LIST *list = (LIST *) malloc(sizeof(LIST));
	list->size = size;

	if (size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		NODE *prev_node = NULL;
		NODE *node;
		for (int i = 0; i < size; i++)
		{
			node = (NODE*) malloc(sizeof(NODE));
			node->value = values[i];
			node->next = NULL;
			node->prev = prev_node;
			if (i == 0)
			{
				list->head = node;
			}
			else
			{
				prev_node->next = node;
			}
			prev_node = node;
		}

		list->tail = node;
	}
	
	return list;
}

void delete_list(LIST *list)
{
	while (list->head != NULL)
	{
		NODE *new_head = list->head->next;
		free(list->head);
		list->head = new_head;
	}

	free(list);
}

void print_list(LIST *list)
{
	int counter = 0;
	std::cout << std::endl << "\t\t\t\t\t\t\t<<<<< LIST from head >>>>>" << std::endl;
	std::cout << std::setw(10) << "Size: " << list->size << "\t\tHead: " << list->head << "\t\tTail: " << list->tail << std::endl;
	NODE *node = list->head;
	while (node != NULL)
	{
		std::cout << std::setw (10) << "Node: " << counter;
		std::cout << "\t\tThis: " << node;
		std::cout << "\t\tNext: " << node->next;
		if (node->next == NULL)
		{
			std::cout << "\t";
		}
		std::cout << "\t\tPrev: " << node->prev;
		if (node->prev == NULL)
		{
			std::cout << "\t";
		}
		std::cout << "\t\tValue: b" << std::bitset<sizeof(NUM_TYPE)*8>(node->value) << " (" << node->value << ", " << sizeof(NUM_TYPE) << " bytes)" << std::endl;
		
		counter += 1;
		node = node->next;
	}
}

void print_list_backward(LIST *list)
{
	int counter = list->size-1;
	std::cout << std::endl << "\t\t\t\t\t\t\t<<<<< LIST from tail >>>>>" << std::endl;
	std::cout << std::setw(10) << "Size: " << list->size << "\t\tHead: " << list->head << "\t\tTail: " << list->tail << std::endl;
	NODE *node = list->tail;
	while (node != NULL)
	{
		std::cout << std::setw (10) << "Node: " << counter;
		std::cout << "\t\tThis: " << node;
		std::cout << "\t\tNext: " << node->next;
		if (node->next == NULL)
		{
			std::cout << "\t";
		}
		std::cout << "\t\tPrev: " << node->prev;
		if (node->prev == NULL)
		{
			std::cout << "\t";
		}
		std::cout << "\t\tValue: b" << std::bitset<sizeof(NUM_TYPE)*8>(node->value) << " (" << node->value << ", " << sizeof(NUM_TYPE) << " bytes)" << std::endl;
		
		counter -= 1;
		node = node->prev;
	}
}
