#include "node.h"

Node::Node(NUM_TYPE new_value)
{
	value = new_value;
}

NUM_TYPE Node::get_value()
{
	return value;
}

Node* Node::get_next()
{
	return next;
}

Node* Node::get_prev()
{
	return prev;
}

void Node::set_next(Node *new_next)
{
	next = new_next;
}

void Node::set_prev(Node *new_prev)
{
	prev = new_prev;
}

unsigned Node::count_zero_bits()
{
	return sizeof(NUM_TYPE)*8 - std::bitset<sizeof(NUM_TYPE)*8>(value).count();
}

unsigned Node::count_one_bits()
{
	return std::bitset<sizeof(NUM_TYPE)*8>(value).count();
}

