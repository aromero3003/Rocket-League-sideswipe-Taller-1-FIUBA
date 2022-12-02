#include "Menu.h"

Menu::Menu():  gameHandler(),clientsHandler(gameHandler){}

void Menu::conectNewClient(Socket&& sktAccepted){
    clientsHandler.conectNewClient(std::move(sktAccepted));
}

Menu::~Menu(){
}
