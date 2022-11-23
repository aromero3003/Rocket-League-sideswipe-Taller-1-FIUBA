#include "ClientsHandler.h"
/*
ClientsHandler::ClientsHandler(BlockingQueue<std::unique_ptr<MenuEvent>>& queue):
  gameclients(),menuclients(),menuEventQueueRef(queue) {}
*/
ClientsHandler::ClientsHandler(GameHandler& games):
  menuclients(), gamesRef(games){}
  
void ClientsHandler::conectNewClient(Socket &&skt,size_t id){
  std::shared_ptr<MenuClient> client(new MenuClient(std::move(skt),id,gamesRef));
  menuclients.push_back(client);
}

// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  menuclients.erase(
      std::remove_if(menuclients.begin(), menuclients.end(),
                     [&](const std::shared_ptr<MenuClient> & client) { return client.get()->isDisconect(); }),
      menuclients.end());

}

void ClientsHandler::disconectAll() {
  menuclients.clear();
}

ClientsHandler::~ClientsHandler() { disconectAll(); }
