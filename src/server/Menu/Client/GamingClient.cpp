#include "GamingClient.h"

#include "Snap.h"

GamingClient::GamingClient(Socket&& otherSkt, size_t o_id,
                           ProtectedQueue<GameCommandHandler>& eventQueue,
                           std::size_t cant_players)
    : id(o_id),
      skt(std::move(otherSkt)),
      snapEventQueue(),
      protocolSend(skt, snapEventQueue, cant_players),
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
  protocolSend.join();
  protocolRecv.join();
}
GamingClient::~GamingClient() { disconect(); }
