#include "ServerMenuProtocol.h"
/*
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


bool ServerProtocol::waitComand(CommandHandler& comandHandler) {

  while (!was_closed ) {
    std::vector<char> buf(254, 'a');
    int recv = skt.recvsome(buf.data(), buf.size(), &was_closed);
    if (recv > 0) receiver.take(buf, recv);
  }

}

void ServerProtocol::sendResponse(std::string& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }*/
