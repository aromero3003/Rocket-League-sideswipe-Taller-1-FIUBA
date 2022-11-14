#include "ClientsHandler.h"
#include <vector>

ClientsHandler::ClientsHandler() {}

GammingClient* ClientsHandler::conectNewGamingClient(Socket&& soktAccepted, int id){
 GammingClient* client=
      new GammingClient(std::move(soktAccepted),id);
  clients.push_back(client);
  return client;
}


// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](GammingClient* client) { delete client; }),
      clients.end());
}
/// si tengo referencia a algun cliente tengo q joineralo
void ClientsHandler::disconectAll() {
  for (GammingClient* client : clients) {
    client->~GammingClient();
    delete client;
  }
  
  clients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
