#include "get_random.h"
#include "list.h"
#include "thread"

#ifndef LIST_SIZE
#define LIST_SIZE 3000
#endif

int main() {
	NUM_TYPE *random_values = get_random_array(LIST_SIZE);
	
	List list(random_values, LIST_SIZE);
	free(random_values);

	std::cout << "List is generated:" << std::endl;

	#ifndef NOPRINT
	list.print();
	#endif // NOPRINT
	
	std::cout << "Run processing..." << std::endl;

	std::thread thread2(&List::process, &list);
	std::thread thread1(&List::process, &list);

	thread1.join();
	thread2.join();

	return 0;
}

