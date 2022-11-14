#include "ProtocolRecv.h"

explicit ProtocolRecv::ProtocolRecv(Socket &otherSkt):
skt(otherSkt),was_closed(false){}
void ProtocolRecv::setup(ProtectedQueue<GameCommandHandler> &eventQueue){
  eventQueueRef=eventQueue;
}
void ProtocolRecv::run() {
  try {
   
    while(!was_closed){
      GameCommandHandler gameCommandHandler;
      gameCommandHandler.createCommand(reciveCommand());
      if (!gameCommandHandler.isEnd()){
      eventQueueRef.push(gameCommandHandler);
      } else {
        was_closed= true;
      }
    }
  } catch (const LibError& err) {

  }
  }   
