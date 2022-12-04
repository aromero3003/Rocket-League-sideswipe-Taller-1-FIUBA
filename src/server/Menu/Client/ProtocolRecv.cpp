#include "ProtocolRecv.h"

ProtocolRecv::ProtocolRecv(Socket& o_skt, size_t o_id,
                           ProtectedQueue<GameCommandHandler>& eventQueue)
    : skt(o_skt), was_closed(false), eventQueueRef(eventQueue), id(o_id) {}

int8_t ProtocolRecv::reciveCommand() {
  int8_t oneRequest = 1;
  skt.recvall(&oneRequest, 1, &was_closed);
  return oneRequest;
}

void ProtocolRecv::run() {
  try {
    while (!skt.isClosed()) {
      GameCommandHandler gameCommandHandler(id);
      gameCommandHandler.createCommand(reciveCommand());
      eventQueueRef.push(gameCommandHandler);
      std::cerr<< "recv dont closed";
    }
  } catch (const LibError& err) {

      std::cerr<< "recv closed"<<this->id<<"\n";
     
  }
}
