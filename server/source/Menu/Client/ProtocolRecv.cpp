#include "ProtocolRecv.h"

explicit ProtocolRecv::ProtocolRecv(Socket &otherSkt,ProtectedQueue<GameCommand> *eventQueue):
skt(otherSkt),eventQueueRef(eventQueue),was_closed(false){}



void ProtocolRecv::run() {
  try {
    GameCommandHandler gameCommandHandler;
    while(was_closed){
      gameCommandHandler.createCommand(reciveCommand());
      eventQueueRef->push(gameCommandHandler.getCommand());
    }
  } catch (const LibError& err) {

  }
  }   
