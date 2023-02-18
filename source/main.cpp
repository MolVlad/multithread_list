#include "get_random.h"
#include "iostream"

int main() {
	NUM_TYPE random_value;

	get_random_number(&random_value);
	std::cout << "Generated: " << random_value << std::endl;
	get_random_number(&random_value);
	std::cout << "Generated: " << random_value << std::endl;
	get_random_number(&random_value);
	std::cout << "Generated: " << random_value << std::endl;

	return 0;
}



