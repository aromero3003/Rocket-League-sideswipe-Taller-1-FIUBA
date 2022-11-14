#ifndef __SERVER_MENU_PROTOCOL_H__
#define __SERVER_MENU_PROTOCOL_H__

#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../../../../common/source/Socket/Socket.h"
#include "../MenuCommand/CommandHandler.h"



class ServerProtocol {
  /*
 private:
  Socket& skt;
  bool was_closed;

 public:
  explicit ServerProtocol(Socket& ohterskt);
  ~ServerProtocol()=default;
  bool isOpen();

  bool waitComand(CommandHandler& comandHandler);

  void sendResponse(std::string& response);
*/
  /*
   * No queremos permitir que alguien haga copias
   * *//*
  ServerProtocol(const ServerProtocol&) = delete;
  ServerProtocol& operator=(const ServerProtocol&) = delete;
*/
  /*
   * Queremos permitir mover a los objetos (move semantics).
   *
   * Como todos nuestros atributos son movibles, la implementación
   * por default de C++ nos alcanza.
   * *//*
  ServerProtocol(ServerProtocol&&) = default;
  ServerProtocol& operator=(ServerProtocol&&); // std::move está por default deleteado
*/
};

#endif
