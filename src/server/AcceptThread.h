#ifndef __ACCEPTTHREAD_H__
#define __ACCEPTTHREAD_H__

#include <memory.h>

#include <atomic>
#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

#include "BlockingQueue.h"
#include "Menu/Menu.h"
#include "liberror.h"
#include "socket.h"
#include "thread.h"
class AcceptThread : public Thread {
 private:
  std::atomic<bool>& serverIsOpen;
  Socket soktRef;
  Menu menu;

 public:
  AcceptThread(Socket& soktRef, std::atomic<bool>& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread(){};
};
#endif
