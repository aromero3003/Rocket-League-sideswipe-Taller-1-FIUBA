#include "ProtocolSend.h"

ProtocolSend::ProtocolSend(Socket&skt,BlockingQueue<SnapShot>& snapEventQueueRef):
skt(skt),snapEventQueue(snapEventQueueRef),was_closed(false){}


void ProtocolSend::sendResponse(std::vector<uint8_t>& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }
}
void ProtocolSend::run() {
  try {
    //sendResponse(numberPlayer);
    while(!was_closed){
    sendResponse(snapEventQueue.pop().getMsg());
    }
  } catch (const LibError& err) {

  }
  }
  