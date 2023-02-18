#ifndef GET_RANDOM_H
#define GET_RANDOM_H

#include "iostream"
#include "stdlib.h"
#include "assert.h"
#include "fcntl.h"
#include "unistd.h"
#include "num_type.h"

#ifdef REAL_RANDOM
const char RANDOM_DEV[] = "/dev/random";
#else
const char RANDOM_DEV[] = "/dev/urandom";
#endif // REAL_RANDOM

void get_random_number(NUM_TYPE *random_value);

#endif // GET_RANDOM_H

