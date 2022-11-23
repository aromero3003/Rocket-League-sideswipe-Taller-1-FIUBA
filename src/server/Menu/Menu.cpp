#include "Menu.h"

Menu::Menu():  gameHandler(),clientsHandler(gameHandler){}

void Menu::conectNewClient(Socket&& sktAccepted,size_t id){
    clientsHandler.conectNewClient(std::move(sktAccepted),id);
}

Menu::~Menu(){
}
