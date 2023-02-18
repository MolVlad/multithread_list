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

