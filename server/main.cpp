#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>

#include "../common_src/socket.h"
#include "AcceptThread.h"
#include "Server.h"
#define ERROR 1
#define SUCCESS 0
#define SERVPORT argv[1]

int main(int argc, char* argv[]) {
    try {
        Socket skt(SERVPORT);
        Server server(skt);
        server.run();
        server.waitToClose();
        return SUCCESS;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: "
                  << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
