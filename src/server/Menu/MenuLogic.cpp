#include "MenuLogic.h"



MenuLogic::MenuLogic(BlockingQueue<std::unique_ptr<MenuEvent>>& menuEventQueue,Menu &menuRef):
   menuEventQueueRef(menuEventQueue),menuState(menuRef){}
   
void MenuLogic::run() {
  try {
    menuEventQueueRef.pop()->run();
    clientsHandlerRef.cleanDisconectClients();

  } catch (const LibError& err) {
    /*
    recordar 
    cosas que pueden pasar  
el cliente a responder no exista
(paso a ser gaming no hay forma de retornar el mensaje)
lazar y agarrar error notClient Found  

el comandoAdd.run() lanze error
lanzar y agarrar  commandError 
reponder Con BadReques al cliente



    */
  }
}