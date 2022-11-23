#include "ProtocolSend.h"
#include "Snap.h"
#include <memory>

ProtocolSend::ProtocolSend(Socket&skt,BlockingQueue<std::shared_ptr<SnapShot>> &snapEventQueuePtr):
skt(skt),snapEventQueue(snapEventQueuePtr),was_closed(false){}


void ProtocolSend::sendResponse(std::vector<uint8_t>& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }
}
void ProtocolSend::run() {
  try {
    //sendResponse(numberPlayer);
    while(!was_closed){
    sendResponse(snapEventQueue.pop()->getMsg());
    }
  } catch (const LibError& err) {

  }
  }
  
