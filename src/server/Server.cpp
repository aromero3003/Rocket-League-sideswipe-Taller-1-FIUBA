#include "Server.h"


Server::Server(Socket& skt)
    : serverStatus(true), acceptThread(skt,serverStatus) {}

void Server::run() { acceptThread.start(); }

void Server::shutdown() {
  acceptThread.disconect();

  acceptThread.join();
}

void Server::waitToClose() {
  std::string serverStdin;
  do {
    std::cin >> serverStdin;
  } while (serverStdin.compare("q"));
  shutdown();

}
