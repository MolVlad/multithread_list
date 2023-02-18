#include "list.h"

List::List(NUM_TYPE *values, unsigned size)
{
	assert(size);

	initial_size = size;
	mutex_arr = (std::mutex **) malloc(sizeof(std::mutex*) * size);
	assert(mutex_arr);

	for (int i = 0; i < size; i++)
	{
		mutex_arr[i] = new std::mutex;
		assert(mutex_arr[i]);
	}

	print_mutex = new std::mutex;
	assert(print_mutex);

	head_mutex = new std::mutex;
	assert(head_mutex);

	Node *prev_node = NULL;
	Node *node;
	for (int i = 0; i < size; i++)
	{
		node = new Node(values[i]);

		node->set_next(NULL);
		node->set_prev(prev_node);

		if (i == 0)
		{
			head = node;
		}
		else
		{
			prev_node->set_next(node);
		}
		prev_node = node;
	}

	tail = node;
}

List::~List()
{
	for (int i = 0; i < initial_size; i++)
	{
		delete mutex_arr[i];
	}
	free(mutex_arr);

	delete print_mutex;
	delete head_mutex;
}

void List::print()
{
	int counter = 0;
	std::cout << std::endl << "\t\t\t\t\t\t\t<<<<< LIST from head >>>>>" << std::endl;
	std::cout << std::setw(10) << "Size: " << initial_size << "\t\tHead: " << head << "\t\tTail: " << tail << std::endl;
	Node *node = head;
	while (node != NULL)
	{
		std::cout << std::setw (10) << "Node: " << counter;
		std::cout << "\t\tThis: " << node;

		Node *next = node->get_next();
		std::cout << "\t\tNext: " << next;
		if (next == NULL)
		{
			std::cout << "\t";
		}

		Node *prev = node->get_prev();
		std::cout << "\t\tPrev: " << prev;
		if (prev == NULL)
		{
			std::cout << "\t";
		}

		NUM_TYPE value = node->get_value();
		std::cout << "\t\tValue: b" << std::bitset<sizeof(NUM_TYPE)*8>(value) << " (" << value << ", " << sizeof(NUM_TYPE) << " bytes)" << std::endl;
		
		counter += 1;
		node = next;
	}
}

void List::process()
{
	bool locked = head_mutex->try_lock();

	if (locked)
	{
		process_forward();
	}
	else
	{
		process_backward();
	}
}

void List::process_forward()
{
	unsigned zero_bit_count = 0;
	unsigned block_count = 0;
	unsigned block_idx = 0;

	while (head != NULL)
	{
		bool locked = mutex_arr[block_idx]->try_lock();
		if (!locked)
		{
			#ifdef DEBUG
			std::cout << "Forward locked at " << block_idx << std::endl;
			#endif // DEBUG

			break;
		}

		Node *node = head;
		zero_bit_count += node->count_zero_bits();
		block_count++;
		block_idx++;

		head = node->get_next();

		delete node;
	}

	print_mutex->lock();
	std::cout << "Zero bits were counted from the head: " << block_count << " blocks, " << zero_bit_count << " zero bits" << std::endl;
	print_mutex->unlock();
}

void List::process_backward()
{
	unsigned one_bit_count = 0;
	unsigned block_count = 0;
	unsigned block_idx = initial_size - 1;

	while (tail != NULL)
	{
		bool locked = mutex_arr[block_idx]->try_lock();
		if (locked == false)
		{
			#ifdef DEBUG
			std::cout << "Backward locked at " << block_idx << std::endl;
			#endif // DEBUG

			break;
		}

		Node *node = tail;
		one_bit_count += node->count_one_bits();
		block_count++;
		block_idx--;

		tail = node->get_prev();

		delete node;
	}

	print_mutex->lock();
	std::cout << "One bits were counted from the tail: " << block_count << " blocks, " << one_bit_count << " one bits" << std::endl;
	print_mutex->unlock();
}

