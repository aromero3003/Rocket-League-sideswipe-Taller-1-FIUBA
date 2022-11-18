#ifndef __MENU_H__
#define __MENU_H__

#include "socket.h"
#include "MenuState.h"
#include "MenuCommand/MenuEvent.h"
#include "MenuCommand/MenuEventAddClient.h"
#include "MenuCommand/CommandHandler.h"

#include "BlockingQueue.h"
#include <memory.h>
#include "MenuLogic.h"
//la idea de la clase es que funcione como un monitor 
//pero sin serlo utiliza threads para la ejecucion de metodos
// y utiliza BlockingQueue para ser threadsafe (sus eventos no generan nuevos eventos)
class Menu {
 private:
  BlockingQueue<std::unique_ptr<MenuEvent>> menuEventQueue;
  MenuLogic menuLogic;

 public:
  Menu();
  void run();
  
  void conectNewClient(Socket&& sktAccepted,size_t id);
  
  void pushCommandEvent(std::unique_ptr<MenuEvent> event);
  
  virtual ~Menu() ;
};
#endif
