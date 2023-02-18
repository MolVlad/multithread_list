#ifndef LIST_H
#define LIST_H

#include "num_type.h"
#include "stdlib.h"
#include "assert.h"
#include "iostream"
#include <bitset>
#include <iomanip>
#include "mutex"

typedef struct NODE
{
	struct NODE * next;
	struct NODE * prev;
	NUM_TYPE value;
} NODE;

typedef struct LIST
{
	struct NODE * head;
	struct NODE * tail;
	int initial_size;
	std::mutex **mutex_arr;
} LIST;

LIST * create_list(NUM_TYPE *values, unsigned size);
void delete_list(LIST *list);
void print_list(LIST *list);
void process_list_forward(LIST *list);
void process_list_backward(LIST *list);
unsigned count_zero_bits(NUM_TYPE value);
unsigned count_one_bits(NUM_TYPE value);

#endif // LIST_H
