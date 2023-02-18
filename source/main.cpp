#include "get_random.h"
#include "list.h"

#ifndef LIST_SIZE
#define LIST_SIZE 3
#endif

int main() {
	NUM_TYPE *random_values = (NUM_TYPE*) malloc(LIST_SIZE * sizeof(NUM_TYPE));
	assert(random_values);

	std::cout << "Generate random numbers from linux kernel..." << std::endl;
	std::cout << "(In case of stuck, take random actions to add entropy)" << std::endl;
	for (int i = 0; i < LIST_SIZE; i++)
	{
		get_random_number(random_values + i);
	}

	#ifdef DEBUG
	for (int i = 0; i < LIST_SIZE; i++)
	{
		std::cout << "Generated: b" << std::bitset<sizeof(NUM_TYPE)*8>(random_values[i]) << " (" << random_values[i] << ", " << sizeof(NUM_TYPE) << " bytes)" << std::endl;
	}
	#endif // DEBUG

	LIST *list = create_list(random_values, LIST_SIZE);
	free(random_values);

	std::cout << "List is generated:" << std::endl;
	print_list(list);
	
	process_list_forward(list);
	//process_list_backward(list);

	delete_list(list);

	return 0;
}

