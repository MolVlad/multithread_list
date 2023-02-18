#include "list.h"

LIST * create_list(NUM_TYPE *values, unsigned size)
{
	assert(size);

	LIST *list = (LIST *) malloc(sizeof(LIST));
	assert(list);

	list->initial_size = size;
	list->mutex_arr = (std::mutex **) malloc(sizeof(std::mutex*) * size);
	assert(list->mutex_arr);

	for (int i = 0; i < size; i++)
	{
		list->mutex_arr[i] = new std::mutex;
		assert(list->mutex_arr[i]);
	}

	NODE *prev_node = NULL;
	NODE *node;
	for (int i = 0; i < size; i++)
	{
		node = (NODE*) malloc(sizeof(NODE));
		assert(node);

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
	
	return list;
}

void delete_list(LIST *list)
{
	for (int i = 0; i < list->initial_size; i++)
	{
		delete list->mutex_arr[i];
	}
	free(list->mutex_arr);
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

void process_list_forward(LIST *list)
{
	unsigned zero_bit_count = 0;
	unsigned block_count = 0;
	unsigned block_idx = 0;

	while (list->head != NULL)
	{
		bool locked = list->mutex_arr[block_idx]->try_lock();
		if (!locked)
		{
			#ifdef DEBUG
			std::cout << "Forward locked at " << block_idx << std::endl;
			#endif // DEBUG

			break;
		}

		NODE *node = list->head;
		zero_bit_count += count_zero_bits(node->value);
		block_count++;
		block_idx++;

		list->head = node->next;

		free(node);
	}

	std::cout << "Zero bits were counted from the head: " << block_count << " blocks, " << zero_bit_count << " zero bits" << std::endl;
}

void process_list_backward(LIST *list)
{
	unsigned one_bit_count = 0;
	unsigned block_count = 0;
	unsigned block_idx = list->initial_size - 1;

	while (list->tail != NULL)
	{
		bool locked = list->mutex_arr[block_idx]->try_lock();
		if (locked == false)
		{
			#ifdef DEBUG
			std::cout << "Backward locked at " << block_idx << std::endl;
			#endif // DEBUG

			break;
		}

		NODE *node = list->tail;
		one_bit_count += count_one_bits(node->value);
		block_count++;
		block_idx--;

		list->tail = node->prev;

		free(node);
	}

	std::cout << "One bits were counted from the tail: " << block_count << " blocks, " << one_bit_count << " one bits" << std::endl;
}

unsigned count_zero_bits(NUM_TYPE value)
{
	return sizeof(NUM_TYPE)*8 - std::bitset<sizeof(NUM_TYPE)*8>(value).count();
}

unsigned count_one_bits(NUM_TYPE value)
{
	return std::bitset<sizeof(NUM_TYPE)*8>(value).count();
}


