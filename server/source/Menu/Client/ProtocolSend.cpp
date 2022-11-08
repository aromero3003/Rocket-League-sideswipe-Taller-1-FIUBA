#include "ProtocolSend.h"

explicit ProtocolSend::ProtocolSend(Socket&skt):skt(skt),was_closed(false){
    snapEventQueue= new BlockingQueue<Snap>;
}
BlockingQueue<Snap>*  ProtocolSend::getSnapQueue(){
    return snapEventQueue;
}
  ProtocolSend::~ProtocolSend(){
    delete snapEventQueue;
}
void ProtocolSend::sendResponse(std::string& response) {
  if (response.size() != 0) {
    skt.sendall(response.data(), response.size(), &was_closed);
  }
}
void ProtocolSend::run() {
  try {
    while(was_closed){
    sendResponse(snapEventQueue->pop().getMsg());
    }
  } catch (const LibError& err) {

  }
  }