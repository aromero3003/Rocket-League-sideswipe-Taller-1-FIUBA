#include "MenuClient.h"

MenuClient::MenuClient(Socket&& otherSkt,GameHandler& game):
    menuProtocol(std::move(otherSkt),game),skt(this->menuProtocol.getSocketRef())
{
    menuProtocol.start();
}

bool MenuClient::isDisconect(){
    return menuProtocol.isClosed();
}
void MenuClient::disconect(){
    this->skt.shutdown(SHUT_RDWR);
    this->menuProtocol.join();
}

MenuClient::~MenuClient(){
    disconect();
}
