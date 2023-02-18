#include "get_random.h"

void get_random_number(NUM_TYPE *random_value)
{
	assert(random_value);

	static int dev_random_fd = -1;

	if (dev_random_fd == -1)
	{
		dev_random_fd = open(RANDOM_DEV, O_RDONLY);
  		assert(dev_random_fd != -1);
		#ifdef DEBUG
		std::cout << "Device " << RANDOM_DEV << " is opened" << std::endl;
		#endif // DEBUG
	}

	char* next_random_byte = (char*) random_value;

	int bytes_to_read = sizeof(*random_value);
	#ifdef DEBUG
	std::cout << bytes_to_read << " bytes to read" << std::endl;
	#endif // DEBUG

	while (bytes_to_read > 0)
	{
		int bytes_read = read(dev_random_fd, next_random_byte, bytes_to_read);
		#ifdef DEBUG
		std::cout << bytes_read << " bytes read" << std::endl;
		#endif // DEBUG
		bytes_to_read -= bytes_read;
		next_random_byte += bytes_read;
	}
}

NUM_TYPE* get_random_array(unsigned size)
{
	NUM_TYPE *random_values = (NUM_TYPE*) malloc(size * sizeof(NUM_TYPE));
	assert(random_values);

	std::cout << "Generate random numbers from linux kernel (" << RANDOM_DEV << ")..." << std::endl;
	std::cout << "(In case of stuck, take random actions to add entropy)" << std::endl;
	for (int i = 0; i < size; i++)
	{
		get_random_number(random_values + i);
	}

	#ifdef DEBUG
	for (int i = 0; i < size; i++)
	{
		std::cout << "Generated: b" << std::bitset<sizeof(NUM_TYPE)*8>(random_values[i]) << " (" << random_values[i] << ", " << sizeof(NUM_TYPE) << " bytes)" << std::endl;
	}
	#endif // DEBUG

	return random_values;
}

