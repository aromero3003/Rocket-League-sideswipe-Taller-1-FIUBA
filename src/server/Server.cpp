#include "Server.h"


Server::Server(Socket& skt)
    : serverStatus(true), acceptThread(skt,serverStatus) {}

void Server::run() { acceptThread.start(); }

void Server::shutdown() {
  serverStatus.store(false,std::memory_order_relaxed);
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
