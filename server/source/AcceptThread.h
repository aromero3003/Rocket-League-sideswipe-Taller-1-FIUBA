#ifndef __ACCEPTTHREAD_H__
#define __ACCEPTTHREAD_H__

#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

#include "../../common/source/Socket/Liberror.h"
#include "../../common/source/Socket/Socket.h"
#include "Menu/Menu.h"
#include "../../common/source/Thread/Thread.h"
class AcceptThread : public Thread {
 private:
  bool& serverIsOpen;
  Socket soktRef;
  Menu menu;

 public:
  AcceptThread(Socket& soktRef, bool& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread() = default;
};
#endif
