#ifndef __ACCEPTTHREAD_H__
#define __ACCEPTTHREAD_H__

#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

#include "liberror.h"
#include "socket.h"
#include "Menu/Menu.h"
#include "thread.h"
#include "BlockingQueue.h"
#include <memory.h>

class AcceptThread : public Thread {
 private:
  bool& serverIsOpen;
  Socket soktRef;
  
 public:
  AcceptThread(Socket& soktRef, bool& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread() = default;
};
#endif
