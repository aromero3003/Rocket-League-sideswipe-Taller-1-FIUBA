#ifndef __SERVER_H__
#define __SERVER_H__

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>

#include "../../common/source/Socket/Socket.h"
#include "AcceptThread.h"
class Server {
 private:
  AcceptThread acceptThread;
  bool serverStatus;
  void shutdown();

 public:
  explicit Server(Socket& skt);
  void run();
  void waitToClose();
};
#endif
