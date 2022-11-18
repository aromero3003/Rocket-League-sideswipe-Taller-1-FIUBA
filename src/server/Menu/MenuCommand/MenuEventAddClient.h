#ifndef __MENUEVENTADDCLIENT_H__
#define __MENUEVENTADDCLIENT_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include "MenuEvent.h"
#include "socket.h"

class MenuEventAddClient: public MenuEvent {
 protected:
    Socket skt;
    size_t id;
    
 public:
  MenuEventAddClient(Socket&& sktAccepted,size_t id);
  virtual void run();
  virtual ~MenuEventAddClient() {}
};

#endif
