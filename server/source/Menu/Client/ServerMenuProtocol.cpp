#include "ServerMenuProtocol.h"

#include <arpa/inet.h>

#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

ServerProtocol::ServerProtocol(Socket& ohterskt)
    : skt(ohterskt), was_closed(false) {}

bool ServerProtocol::isOpen() { return !was_closed; }

// mientras el skt este abierto y el mensaje no sea completado espera
// mientras el skt este abierto y el mensaje sea completado delego la creación
// del comando retorno true si el socket es cerrado devuelvo false y no delego
// la creación
bool ServerProtocol::waitComand(CommandHandler& comandHandler) {
  while (!was_closed && !receiver.isEndMsg()) {
    std::vector<char> buf(254, 'a');
    int recv = skt.recvsome(buf.data(), buf.size(), &was_closed);
    if (recv > 0) receiver.take(buf, recv);
  }
  if (!was_closed && receiver.isEndMsg())
    comandHandler.createCommand(receiver.getCompleteMsg());
  return !was_closed;
}

void ServerProtocol::sendResponse(std::string& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }
}
