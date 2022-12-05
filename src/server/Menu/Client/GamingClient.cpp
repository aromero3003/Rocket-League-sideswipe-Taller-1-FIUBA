#include "GamingClient.h"

#include "Snap.h"

GamingClient::GamingClient(Socket&& otherSkt, size_t o_id,
                           ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueue,
                           std::size_t cant_players)
    : id(o_id),
      skt(std::move(otherSkt)),
      snapEventQueue(),
      protocolSend(skt, snapEventQueue, cant_players,id),
      protocolRecv(skt, id, eventQueue) {}

void GamingClient::addSnap(std::shared_ptr<SnapShot> snap) {
  snapEventQueue.push(snap);
}

void GamingClient::start() {
  protocolSend.start();
  protocolRecv.start();
}

bool GamingClient::isDisconect() {

  return skt.isClosed();  // refactor
}
void GamingClient::disconect() {
  this->skt.shutdown(2);


}
GamingClient::~GamingClient() { 
  if (!isDisconect()) disconect(); 
  protocolSend.join();
  protocolRecv.join(); 
  std::cerr<< "se limpio los hilos\n";

}
