#include "ProtocolRecv.h"

ProtocolRecv::ProtocolRecv(Socket& o_skt, size_t o_id,
                           ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueue)
    : skt(o_skt), was_closed(false), eventQueueRef(eventQueue), id(o_id) {}

int8_t ProtocolRecv::reciveCommand() {
  int8_t oneRequest = 1;
  skt.recvall(&oneRequest, 1, &was_closed);
  return oneRequest;
}

void ProtocolRecv::run() {
  try {

    GameCommandHandler gameCommandHandler(id);
    while (!skt.isClosed()) {
      std::shared_ptr<GameCommand>  command=gameCommandHandler.createCommand(reciveCommand());
      if(!skt.isClosed())eventQueueRef.push(command);
    }
  } catch (const LibError& err) {
      std::cerr<< "recv closed"<<this->id<<"\n";
      eventQueueRef.close();
  }
}
