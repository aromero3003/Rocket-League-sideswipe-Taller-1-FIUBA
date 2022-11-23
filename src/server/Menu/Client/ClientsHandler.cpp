#include "ClientsHandler.h"
#include <vector>

ClientsHandler::ClientsHandler() {}

GamingClient* ClientsHandler::conectNewGamingClient(Socket&& soktAccepted, size_t id,ProtectedQueue<GameCommandHandler> &eventQueue){
 GamingClient* client=
      new GamingClient(std::move(soktAccepted),id,eventQueue);
  clients.push_back(client);
  return client;
}


// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](GamingClient* client) { return client->isDisconect(); }),
      clients.end());
}
/// si tengo referencia a algun cliente tengo q joineralo
void ClientsHandler::disconectAll() {
  for (GamingClient* client : clients) {
    delete client;
  }
  
  clients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
