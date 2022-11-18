#include "Menu.h"

Menu::Menu():
    menuEventQueue (BlockingQueue<std::unique_ptr<MenuEvent>>),
    menuLogic(menuEventQueue,){
        menuLogic.start();
    }
void Menu::conectNewClient(Socket&& sktAccepted,size_t id){
    std::unique_ptr<MenuEventAddClient> event(new MenuEventAddClient(std::move(sktAccepted),id));
    menuEventQueue.push(event);
}
  
void Menu::pushCommandEvent(std::unique_ptr<MenuEvent> event){
    menuEventQueue.push(event);
}
Menu::~Menu():{
        menuLogic.join();
    }