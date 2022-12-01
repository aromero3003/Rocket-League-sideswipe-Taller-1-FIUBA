#include "menuThread.h"

MenuThread::MenuThread(Socket* s, int &n):n_cars(n){
 this->skt = s;
 this->was_closed=false;
}
void MenuThread::sendCommand(std::string&& response) {
  int8_t lenght=response.size();
  skt->sendall(&lenght,1, &was_closed);
  skt->sendall(response.data(),lenght, &was_closed);
}

std::stringstream  MenuThread::reciveResponse(){
  uint8_t lenght = 0;
  skt->recvall(&lenght, sizeof(lenght), &this->was_closed);
  std::vector<char> buff;
  buff.resize(lenght);
  skt->recvall(buff.data(), lenght, &this->was_closed);
  std::string sresp(buff.data(), buff.size());
  std::stringstream ssresp(sresp);
  return ssresp;
}


void MenuThread::run() {
    try{
        //while(!this->was_closed){
            std::string s1("LISTAR");
            sendCommand(std::move(s1));
            if (reciveResponse().str() == "OK\n"){
              std::string s2 ("CREAR 3 tomako");
              sendCommand(std::move(s2));
            } else {
              std::string s2("UNIR tomako");
              sendCommand(std::move(s2)); 
            }
    }
    catch (const LibError& err) {
      std::cerr << err.what();
      
    }    
}  