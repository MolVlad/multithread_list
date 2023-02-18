#ifndef NODE_H
#define NODE_H

#include "num_type.h"
#include "assert.h"
#include "iostream"
#include <bitset>

class Node
{
	public:
		Node(NUM_TYPE new_value);

		NUM_TYPE get_value();
		Node* get_next();
		Node* get_prev();
		void set_next(Node *new_next);
		void set_prev(Node *new_prev);

		unsigned count_zero_bits();
		unsigned count_one_bits();

	private:
		Node *next;
		Node *prev;
		NUM_TYPE value;
};

#endif // NODE_H
