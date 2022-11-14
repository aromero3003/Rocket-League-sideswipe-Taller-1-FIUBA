#include "ClientsHandler.h"
#include "GammingClient.h"
#include <vector>

ClientsHandler::ClientsHandler() : gameHandler() {}

GammingClient * ClientsHandler::addClient(Socket&& soktAccepted) {
  GammingClient* client =
      new GammingClient(std::move(soktAccepted), gameHandler);
  clients.push_back(client);
  return client;
}
void ClientsHandler::startConect(ClientsHandler* client) { client->run(); }

void ClientsHandler::conectNewClient(Socket&& soktAccepted) {
  startConect(addClient(std::move(soktAccepted)));
}
// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](ClientsHandler* x) { return x->isDisconect(); }),
      clients.end());
}
/// si tengo referencia a algun cliente tengo q joineralo
void ClientsHandler::disconectAll() {
  for (ClientsHandler* client : clients) {
    client->disconect();
    delete client;
  }
  
  clients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
