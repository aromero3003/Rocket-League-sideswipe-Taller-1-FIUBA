#ifndef __MENULOGIC_H__
#define __MENULOGIC_H__

#include "socket.h"
#include "Menu.h"
#include "MenuState.h"
#include "MenuCommand/MenuEvent.h"
#include "BlockingQueue.h"
#include <memory.h>

class MenuLogic : public Thread  {
 private:
  BlockingQueue<std::unique_ptr<MenuEvent>>& menuEventQueueRef;
  MenuState menuState;

 public:
  MenuLogic(BlockingQueue<std::unique_ptr<MenuEvent>>& menuEventQueue,Menu &menu);
  virtual void run() override;
  virtual ~MenuLogic() = default;
};
#endif