#ifndef __ACCEPTTHREAD_H__
#define __ACCEPTTHREAD_H__

#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

#include "../common_src/Liberror.h"
#include "../common_src/Socket.h"
#include "Menu/ClientsHandler.h"
#include "Thread.h"
class AcceptThread : public Thread {
 private:
  bool& serverIsOpen;
  Socket& soktRef;
  ClientsHandler clientsHandler;

 public:
  AcceptThread(Socket& soktRef, bool& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread() = default;
};
#endif
