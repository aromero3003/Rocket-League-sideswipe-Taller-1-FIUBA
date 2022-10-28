#include "ClientHandler.h"

ClientHandler::ClientHandler(Socket&& skt, GameHandler& gameHandler)
    : sktRefOfClient(std::move(skt)),
      clientThread(sktRefOfClient, gameHandler) {}

void ClientHandler::run() { clientThread.start(); }

bool ClientHandler::isDisconect() {
  if (sktRefOfClient.isClose()) {
    clientThread.join();
    return true;
  }
  return false;
}

void ClientHandler::disconect() {
  sktRefOfClient.shutdown(SHUT_RDWR);
  clientThread.join();
}

