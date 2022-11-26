#include "MenuProtocol.h"

MenuProtocol::MenuProtocol(Socket&& o_skt, size_t o_id,GameHandler& gameRef):
    skt(std::move(o_skt)),
     was_closed(false),
     id(o_id),
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

void MenuProtocol::run() {
  try{
    while(!was_closed){
      CommandHandler commandHandler;
      std::unique_ptr<Command> command(commandHandler.createCommand(reciveCommand(),skt,id));
      command->execut(games);
      if (command->getResponse()=="Added In Game"){
        this->was_closed=true;
      } else {
         sendResponse(std::move(command->getResponse()));

      }

    }
  } catch (const LibError& err) {
      
  }
}  


