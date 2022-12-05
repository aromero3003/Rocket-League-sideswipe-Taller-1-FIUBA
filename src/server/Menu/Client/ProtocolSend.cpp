#include "ProtocolSend.h"

#include <memory>

#include "Snap.h"

ProtocolSend::ProtocolSend(
    Socket& o_skt, BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueuePtr,
    std::size_t cant_players, size_t o_id)
    : skt(o_skt), snapEventQueue(snapEventQueuePtr), was_closed(false),id(o_id) {
  sendInfo(cant_players);
  //sendInfo(o_id);
}

ProtocolSend::~ProtocolSend(){
      this->snapEventQueue.clean();
      std::cerr<< "snapEventQueue"<<id<<" limpio\n";
}
void ProtocolSend::sendInfo(size_t id) {
  uint8_t id_trans = static_cast<uint8_t>(id);
  skt.sendall(&id_trans, sizeof(id_trans), &was_closed);
}

//en el caso de snap vacio cierro el bucle run
void ProtocolSend::sendResponse(std::vector<uint8_t>& response) {

  if (response.size()>0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  } else {throw QueueEx();}
}

void ProtocolSend::run() {
  try {
    while (!skt.isClosed()) {
      sendResponse(snapEventQueue.pop()->getMsg());
    }
  }catch (const QueueEx) {

      std::cerr<< "queue closed\n";

  } catch (const LibError& err) {

      std::cerr<< "send closed\n";

  }
}
