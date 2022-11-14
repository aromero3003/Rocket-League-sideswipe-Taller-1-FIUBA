#include "ProtocolRecv.h"

explicit ProtocolRecv::ProtocolRecv(Socket &otherSkt):
skt(otherSkt),was_closed(false){}
void ProtocolRecv::setup(ProtectedQueue<GameCommandHandler> &eventQueue, size_t id_o){
  eventQueueRef=eventQueue;
  id=id_o;
}

int ProtocolRecv::reciveCommand(){
  int oneRequest = 1;
  while (!was_closed && oneRequest != 0) {
    skt.recvall(&oneRequest, sizeof(oneRequest), &was_closed);
  }
  return oneRequest;
}
void ProtocolRecv::run() {
  try {
   
    while(!was_closed){
      GameCommandHandler gameCommandHandler(id);
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

