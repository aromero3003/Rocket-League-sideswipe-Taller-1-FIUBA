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
      if(!skt.isClosed())eventQueueRef.push(gameCommandHandler);
    }
  } catch (const LibError& err) {
  }
}
