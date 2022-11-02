#include "ClientsHandler.h"

ClientsHandler::ClientsHandler() : gameHandler() {}

ClientHandler* ClientsHandler::addClient(Socket&& soktAccepted) {
  ClientHandler* client =
      new ClientHandler(std::move(soktAccepted), gameHandler);
  clients.push_back(client);
  return client;
}
void ClientsHandler::startConect(ClientHandler* client) { client->run(); }

void ClientsHandler::conectNewClient(Socket&& soktAccepted) {
  startConect(addClient(std::move(soktAccepted)));
}
// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](ClientHandler* x) { return x->isDisconect(); }),
      clients.end());
}
/// si tengo referencia a algun cliente tengo q joineralo
void ClientsHandler::disconectAll() {
  for (ClientHandler* client : clients) {
    client->disconect();
    delete client;
  }
  
  clients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
