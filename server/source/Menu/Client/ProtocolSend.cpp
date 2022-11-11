#include "ProtocolSend.h"

explicit ProtocolSend::ProtocolSend(Socket&skt,BlockingQueue<SnapShot>& snapEventQueueRef):
skt(skt),was_closed(false),snapEventQueue(snapEventQueueRef){}

  ProtocolSend::~ProtocolSend(){}

void ProtocolSend::sendResponse(std::string& response) {
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