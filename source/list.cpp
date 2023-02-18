#include "list.h"

LIST * create_list(NUM_TYPE *values, unsigned size)
{
	LIST *list = (LIST *) malloc(sizeof(LIST));
	list->initial_size = size;

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
	std::cout << std::setw(10) << "Size: " << list->initial_size << "\t\tHead: " << list->head << "\t\tTail: " << list->tail << std::endl;
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
	int counter = list->initial_size-1;
	std::cout << std::endl << "\t\t\t\t\t\t\t<<<<< LIST from tail >>>>>" << std::endl;
	std::cout << std::setw(10) << "Size: " << list->initial_size << "\t\tHead: " << list->head << "\t\tTail: " << list->tail << std::endl;
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

void process_list(LIST *list)
{
	unsigned zero_bit_count = 0;
	unsigned block_count = 0;

	while (list->head != NULL)
	{
		if (list->head == list->tail)
		{
			list->tail = NULL;
		}

		NODE *node = list->head;

		zero_bit_count += sizeof(NUM_TYPE)*8 - std::bitset<sizeof(NUM_TYPE)*8>(node->value).count();
		block_count++;

		list->head = node->next;
		if (list->head != NULL)
		{
			list->head->prev = NULL;
		}
		free(node);
	}

	std::cout << "Zero bits were counted from the head: " << block_count << " blocks, " << zero_bit_count << " zero bits" << std::endl;
}

void process_list_backward(LIST *list)
{
	unsigned one_bit_count = 0;
	unsigned block_count = 0;

	while (list->tail != NULL)
	{
		if (list->head == list->tail)
		{
			list->head = NULL;
		}

		NODE *node = list->tail;

		one_bit_count += std::bitset<sizeof(NUM_TYPE)*8>(node->value).count();
		block_count++;

		list->tail = node->prev;
		if (list->tail != NULL)
		{
			list->tail->next = NULL;
		}
		free(node);
	}

	std::cout << "One bits were counted from the tail: " << block_count << " blocks, " << one_bit_count << " one bits" << std::endl;
}

