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
#include <atomic>
class AcceptThread : public Thread {
 private:
  std::atomic<bool> &serverIsOpen;
  Socket soktRef;
  Menu menu;
 public:
  AcceptThread(Socket& soktRef, std::atomic<bool>& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread() {};
};
#endif
