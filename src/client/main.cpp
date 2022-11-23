#include <iostream>
#include <exception>

#include "client_interface.h"

using namespace SDL2pp;

int main(int argc, const char *argv[]) try {
	Client_interface interface(argv[1], argv[2]);
	interface.run_client();
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
