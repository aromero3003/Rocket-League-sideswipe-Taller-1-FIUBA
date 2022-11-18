#ifndef __MENUEVENT_H__
#define __MENUEVENT_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

class MenuEvent {
 protected:

 public:
  MenuEvent();
  virtual void run() = 0;
  virtual ~MenuEvent() {}
};

#endif
