#include "menuProtocol.h"
#include "menu.h"
#include <QApplication>

MenuProtocol::MenuProtocol(Socket& s): skt(s){
 this->was_closed = false;
}
void MenuProtocol::sendCommand(std::string&& response) {
  int8_t lenght=response.size();
  skt.sendall(&lenght,1, &was_closed);
  skt.sendall(response.data(),lenght, &was_closed);
}

std::stringstream  MenuProtocol::reciveResponse(){
  uint8_t lenght = 0;
  skt.recvall(&lenght, sizeof(lenght), &this->was_closed);
  std::vector<char> buff;
  buff.resize(lenght);
  skt.recvall(buff.data(), lenght, &this->was_closed);
  std::string sresp(buff.data(), buff.size());
  std::stringstream ssresp(sresp);
  return ssresp;
}


void MenuProtocol::run() {
    int argc = 0;
    char** argv = nullptr;
    QApplication a(argc,argv);
    Menu menu(this->skt);
    menu.show();
    a.exec();

}  