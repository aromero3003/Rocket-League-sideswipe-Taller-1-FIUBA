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
      this->snapEventQueue.clean();
      std::cerr<< "send limpio\n";
}

void ProtocolSend::sendCantPlayers(std::size_t cant_players) {
  uint8_t cant_players_trans = static_cast<uint8_t>(cant_players);
  skt.sendall(&cant_players_trans, sizeof(cant_players_trans), &was_closed);
}

void ProtocolSend::sendResponse(std::vector<uint8_t>& response) {
  
  if (response.empty()) {
    skt.sendall(response.data(), response.size(), &was_closed);
  } else {throw QueueEx();}
}

void ProtocolSend::run() {
  try {
    while (!skt.isClosed()) {
      sendResponse(snapEventQueue.pop()->getMsg());
    }
  }catch (const QueueEx) {

      std::cerr<< "queue closed";

  } catch (const LibError& err) {

      std::cerr<< "send closed";

  }
}
