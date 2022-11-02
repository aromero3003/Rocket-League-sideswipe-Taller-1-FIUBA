#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../common_src/Socket.h"
#include "../MenuCommand/CommandHandler.h"

class ServerProtocol {
 private:
  Parser receiver;
  Socket& skt;
  bool was_closed;

 public:
  explicit ServerProtocol(Socket& ohterskt);
  ~ServerProtocol()=default;
  bool isOpen();

  bool waitComand(ComandHandler& comandHandler);

  void sendResponse(std::string& response);

  /*
   * No queremos permitir que alguien haga copias
   * */
  ServerProtocol(const ServerProtocol&) = delete;
  ServerProtocol& operator=(const ServerProtocol&) = delete;

  /*
   * Queremos permitir mover a los objetos (move semantics).
   *
   * Como todos nuestros atributos son movibles, la implementación
   * por default de C++ nos alcanza.
   * */
  ServerProtocol(ServerProtocol&&) = default;
  ServerProtocol& operator=(ServerProtocol&&) = default;
};

#endif
