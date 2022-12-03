#ifndef __MENUPROTOCOL_H__
#define __MENUPROTOCOL_H__

#include <atomic>
#include <istream>
#include <list>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "../MenuCommand/Command.h"
#include "../MenuCommand/CommandHandler.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
class MenuProtocol : public Thread {
 private:
  Socket skt;
  bool was_closed;
  GameHandler& games;
  std::stringstream reciveCommand();
  void sendResponse(std::string&& response);

 public:
  MenuProtocol(Socket&& skt, GameHandler& game);
  Socket& getSocketRef();
  bool isClosed();
  virtual void run() override;
  virtual ~MenuProtocol() = default;
};
#endif
