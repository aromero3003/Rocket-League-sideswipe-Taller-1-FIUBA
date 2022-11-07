#include "ClientsHandler.h"

ClientsHandler::ClientsHandler() {}

GammingClient& ClientsHandler::addGammingClient(Socket&& soktAccepted,ProtectedQueue<CommandGame> &eventQueue) {
  std::shared_ptr client=
      new GammingClient(std::move(soktAccepted),eventQueue);
  clients.push_back(client);
  return client;
}
//void ClientsHandler::startConect(GammingClient* client) { client->run(); }

GammingClient& ClientsHandler::conectNewGamingClient(Socket&& soktAccepted,ProtectedQueue<CommandGame> &eventQueue) {
  addGammingClient(std::move(soktAccepted),eventQueue);
}
// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](GammingClient* x) { return x->isDisconect(); }),
      clients.end());
}
/// si tengo referencia a algun cliente tengo q joineralo
void ClientsHandler::disconectAll() {
  for (GammingClient* client : clients) {
    client->disconect();
    delete client;
  }
  
  clients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
