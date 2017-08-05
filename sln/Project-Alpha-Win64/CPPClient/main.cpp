#include <iostream>
#include "../Engine/core.hpp"

int main() {
	Core core;
	core.init();

	std::cout << "Exiting Main" << std::endl;

	return 0;
}