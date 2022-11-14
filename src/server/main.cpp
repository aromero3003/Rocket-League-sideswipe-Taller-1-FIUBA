#include <iostream>
#include <string>

#include "../client/socket.h"
#include "listener.h"

int main(int argc, char* argv[]) {
    char port[5] = "8080";
    Listener listener(port);
    listener.start();
    std::string input;
    input.clear();
    while (input != "q") {
        std::cin >> input;
    }
    return 0;
}