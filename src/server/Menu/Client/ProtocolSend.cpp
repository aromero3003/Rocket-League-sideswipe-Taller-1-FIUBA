#include "ProtocolSend.h"

#include <memory>

#include "Snap.h"

ProtocolSend::ProtocolSend(
    Socket& o_skt, BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueuePtr,
    std::size_t cant_players)
    : skt(o_skt), snapEventQueue(snapEventQueuePtr), was_closed(false) {
  sendCantPlayers(cant_players);
}
ProtocolSend::~ProtocolSend(){
      while (!snapEventQueue.size()!=0) snapEventQueue.pop();
}
void ProtocolSend::sendCantPlayers(std::size_t cant_players) {
  uint8_t cant_players_trans = static_cast<uint8_t>(cant_players);
  skt.sendall(&cant_players_trans, sizeof(cant_players_trans), &was_closed);
}

void ProtocolSend::sendResponse(std::vector<uint8_t>& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }
}

void ProtocolSend::run() {
  try {
    while (!skt.isClosed()) {
      sendResponse(snapEventQueue.pop()->getMsg());
    }
  } catch (const LibError& err) {

  }
}
