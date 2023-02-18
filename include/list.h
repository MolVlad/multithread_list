#ifndef LIST_H
#define LIST_H

#include "num_type.h"
#include "node.h"
#include "assert.h"
#include "iostream"
#include <iomanip>
#include "mutex"

class List
{
	public:
		List(NUM_TYPE *values, unsigned size);
		~List();

		void print();
		void process();

	private:
		void process_forward();
		void process_backward();

		Node *head;
		Node *tail;
		int initial_size;
		std::mutex **mutex_arr;
		std::mutex *print_mutex;
		std::mutex *head_mutex;
};

#endif // LIST_H
