#include "Menu.h"

Menu::Menu():
clientsHandler(ClientsHandler()),
   gameHandler(GameHandler()),
    runGame(gameHandler.addRunGame()){}

void Menu::conectNewClient(Socket&& sktAccepted,int id){
    runGame.addPlayer(
        clientsHandler.conectNewGamingClient(std::move(sktAccepted),
                    runGame.getRefGammingQueue(),id)
                    );
}

void Menu::cleanDisconectClients(){
    clientsHandler.cleanDisconectClients();
}
void Menu::disconectAll(){
  clientsHandler.disconectAll();
}
void Menu::startGame(){
    runGame.setupStart();
    runGame.start();
}
