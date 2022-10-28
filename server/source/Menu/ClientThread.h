#ifndef __CLIENTTHREAD_H__
#define __CLIENTTHREAD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../common_src/liberror.h"
#include "../MenuCommand/ComandHandler.h"
#include "../Game/GameHandler.h"
#include "ServerMenuProtocol.h"
#include "../Thread.h"
class ClientThread : public Thread {
 private:
  ServerProtocol protocol;
  GameHandler& gameHandler;

 public:
  ClientThread(Socket& skt, GameHandler& gameHandler);
  void run() override;
  virtual ~ClientThread()=default;
};
#endif
