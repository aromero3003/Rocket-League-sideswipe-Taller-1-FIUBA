#include "MenuClient.h"

MenuClient::MenuClient(Socket&& otherSkt, GameHandler& game)
    : menuProtocol(std::move(otherSkt), game),
      skt(this->menuProtocol.getSocketRef()) {
  menuProtocol.start();
}

bool MenuClient::isDisconect() { return menuProtocol.isClosed(); }
void MenuClient::disconect() {
  if (!isDisconect()){
  this->skt.shutdown(SHUT_RDWR);
  }
}

MenuClient::~MenuClient() {
   disconect(); 
  this->menuProtocol.join();
}
