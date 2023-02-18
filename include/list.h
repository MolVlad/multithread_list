#ifndef LIST_H
#define LIST_H

#include "num_type.h"
#include "stdlib.h"
#include "assert.h"
#include "iostream"
#include <bitset>
#include <iomanip>

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
	int size;
} LIST;

LIST * create_list(NUM_TYPE *values, unsigned size);
void delete_list(LIST *list);
void print_list(LIST *list);
void print_list_backward(LIST *list);

#endif // LIST_H
