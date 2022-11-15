#include "Menu.h"

Menu::Menu():
clientsHandler(ClientsHandler()),
   gameHandler(GameHandler()),
    runGame(gameHandler.addRunGame()){}

void Menu::conectNewClient(Socket&& sktAccepted,size_t id){
    runGame.addPlayer(
        clientsHandler.conectNewGamingClient(std::move(sktAccepted),id,runGame.getRefGamingQueue())
                    );
}

void Menu::cleanDisconectClients(){
    clientsHandler.cleanDisconectClients();
}
void Menu::disconectAll(){
  clientsHandler.disconectAll();
}
void Menu::startGame(){
    runGame.start();
}
