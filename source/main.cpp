#include "get_random.h"
#include "list.h"
#include "thread"

#ifndef LIST_SIZE
#define LIST_SIZE 3000
#endif

int main() {
	NUM_TYPE *random_values = (NUM_TYPE*) malloc(LIST_SIZE * sizeof(NUM_TYPE));
	assert(random_values);

	std::cout << "Generate random numbers from linux kernel (" << RANDOM_DEV << ")..." << std::endl;
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

	#ifndef NOPRINT
	print_list(list);
	#endif // NOPRINT
	
	std::cout << "Run processing..." << std::endl;

	std::thread thread2(process_list, list);
	std::thread thread1(process_list, list);

	thread1.join();
	thread2.join();

	delete_list(list);

	return 0;
}

