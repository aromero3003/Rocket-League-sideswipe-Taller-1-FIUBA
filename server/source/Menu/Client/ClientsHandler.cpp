#include "ClientsHandler.h"

ClientsHandler::ClientsHandler() {}

GammingClient* ClientsHandler::conectNewGamingClient(Socket&& soktAccepted,ProtectedQueue<GameCommand> *eventQueue, int id){
 GammingClient* client=
      new GammingClient(std::move(soktAccepted),eventQueue,id);
  clients.push_back(client);
  return client;
}


// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  clients.erase(
      std::remove_if(clients.begin(), clients.end(),
                     [](GammingClient* x) { return x->~GammingClient(); }),
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