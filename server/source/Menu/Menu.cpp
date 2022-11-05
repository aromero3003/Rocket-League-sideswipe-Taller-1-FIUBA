#include "Menu.h"

Menu::Menu():
    runGame(gameHandler.addRunGame()){}

void Menu::conectNewClient(Socket&& sktAccepted){
    runGame.addPlayer(clientsHandler.conectNewClient(std::move(sktAccepted)));
}

void Menu::cleanDisconectClients(){
    clientsHandler.cleanDisconectClients();
}
void Menu::disconectAll(){
  clientsHandler.disconectAll();
}
void Menu::starGame(){
    runGame.setupStart();
    runGame.start();
}
