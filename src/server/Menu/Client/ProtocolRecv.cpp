#include "ProtocolRecv.h"

ProtocolRecv::ProtocolRecv(Socket &o_skt,ProtectedQueue<GameCommandHandler> & o_eventQueue,size_t o_id):
skt(o_skt),was_closed(false),eventQueueRef(o_eventQueue),id(o_id){}


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

