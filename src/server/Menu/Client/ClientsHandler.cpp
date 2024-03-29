#include "ClientsHandler.h"
/*
ClientsHandler::ClientsHandler(BlockingQueue<std::unique_ptr<MenuEvent>>&
queue): gameclients(),menuclients(),menuEventQueueRef(queue) {}
*/
ClientsHandler::ClientsHandler(GameHandler& games)
    : menuclients(), gamesRef(games) {}

void ClientsHandler::conectNewClient(Socket&& skt) {
  std::unique_ptr<MenuClient> client(new MenuClient(std::move(skt), gamesRef));
  menuclients.push_back(std::move(client));
}

// si se deconecta algun cliente lo joineo -esto no esta explicito...- y borro
// ref
void ClientsHandler::cleanDisconectClients() {
  menuclients.erase(
      std::remove_if(menuclients.begin(), menuclients.end(),
                     [&](const std::unique_ptr<MenuClient>& client) {
                       return client.get()->isDisconect();
                     }),
      menuclients.end());
}

void ClientsHandler::disconectAll() { 
  for (auto && menuclient :menuclients) menuclient->disconect();
  menuclients.erase(menuclients.begin(), menuclients.end()); 
}

ClientsHandler::~ClientsHandler() { if (!menuclients.empty()) disconectAll(); }
