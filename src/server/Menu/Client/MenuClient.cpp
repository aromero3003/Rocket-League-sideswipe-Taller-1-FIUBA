#include "MenuClient.h"

MenuClient::MenuClient(Socket&& otherSkt,size_t o_id, GameHandler& game):
    id(o_id),menuProtocol(std::move(otherSkt),id,game),skt(this->menuProtocol.getSocketRef())
{
    menuProtocol.start();
}

bool MenuClient::isDisconect(){
    return menuProtocol.isClosed();// refactor
}

MenuClient::~MenuClient(){
    this->menuProtocol.join();
 
}
