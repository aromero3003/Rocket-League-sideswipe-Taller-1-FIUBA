#include "MenuProtocol.h"

MenuProtocol::MenuProtocol(Socket&& o_skt,GameHandler& gameRef):
    skt(std::move(o_skt)),
     was_closed(false),
     games(gameRef){}

Socket& MenuProtocol::getSocketRef(){
  return this->skt;
}
void MenuProtocol::sendResponse(std::string&& response) {
  int8_t lenght=response.size();
  skt.sendall(&lenght,1, &was_closed);
  skt.sendall(response.data(),response.size(), &was_closed);
}

std::stringstream  MenuProtocol::reciveCommand(){
  uint8_t lenght = 0;
  skt.recvall(&lenght, sizeof(lenght), &was_closed);
  std::vector<char> buff;
  buff.resize(lenght);
  skt.recvall(buff.data(), lenght, &was_closed);
  std::string sresp(buff.data(), buff.size());
  std::stringstream ssresp(sresp);
  return ssresp;
}

bool MenuProtocol::isClosed() { return was_closed;}

void MenuProtocol::run() {
  try{
    while(!was_closed){
      CommandHandler commandHandler;
      std::unique_ptr<Command> command(commandHandler.createCommand(reciveCommand(),skt));
      command->execut(games);
      sendResponse(std::move(command->getResponse()));
    }
  } catch (const LibError& err) {
      
  }
}  


