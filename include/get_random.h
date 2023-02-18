#ifndef GET_RANDOM_H
#define GET_RANDOM_H

#include "iostream"
#include "stdlib.h"
#include "assert.h"
#include "fcntl.h"
#include "unistd.h"
#include "num_type.h"

const char RANDOM_DEV[] = "/dev/random";

void get_random_number(NUM_TYPE *random_value);

#endif // GET_RANDOM_H

