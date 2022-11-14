#include <iostream>
#include <exception>

#include "client_interface.h"

using namespace SDL2pp;

int main() try {
	Client_interface interface;
	interface.run_client();
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
