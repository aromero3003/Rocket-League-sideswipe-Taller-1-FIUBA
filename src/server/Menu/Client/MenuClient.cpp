#include "MenuClient.h"

MenuClient::MenuClient(Socket&& otherSkt,GameHandler& game):
    menuProtocol(std::move(otherSkt),game),skt(this->menuProtocol.getSocketRef())
{
    menuProtocol.start();
}

bool MenuClient::isDisconect(){
    return menuProtocol.isClosed();// refactor
}

MenuClient::~MenuClient(){
    this->menuProtocol.join();
}
