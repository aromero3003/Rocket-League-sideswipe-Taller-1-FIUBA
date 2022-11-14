#include "Server.h"

#include <sys/socket.h>

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
Server::Server(Socket& skt)
    : skt(skt), acceptThread(skt, serverStatus), serverStatus(true) {}

void Server::run() { acceptThread.start(); }

void Server::shutdown() {
  serverStatus = false;
  acceptThread.disconect();
  skt.shutdown(SHUT_RDWR);
  acceptThread.join();
}

void Server::waitToClose() {
  std::string serverStdin;
  do {
    std::cin >> serverStdin;
  } while (serverStdin.compare("q"));
  shutdown();
}
