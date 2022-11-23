#include "MenuClient.h"

MenuClient::MenuClient(Socket&& otherSkt,size_t o_id, GameHandler& game):
    id(o_id),menuProtocol(std::move(otherSkt),id,game),skt(this->menuProtocol.getSocketRef())
{
    menuProtocol.start();
}

bool MenuClient::isDisconect(){
    return false;// refactor
}
/*
size_t MenuClient::getId(){
    return this->id;
}
*/
MenuClient::~MenuClient(){
    this->menuProtocol.join();
 
}
