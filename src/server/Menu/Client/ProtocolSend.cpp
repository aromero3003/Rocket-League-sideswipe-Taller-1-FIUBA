#include "ProtocolSend.h"

#include <memory>

#include "Snap.h"

ProtocolSend::ProtocolSend(
    Socket& o_skt, BlockingQueue<std::shared_ptr<SnapShot>>& snapEventQueuePtr,
    std::size_t cant_players, size_t o_id)
    : skt(o_skt), snapEventQueue(snapEventQueuePtr), was_closed(false),id(o_id) {
  sendInfo(cant_players);
  sendInfo(o_id);
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
    if(was_closed) skt.shutdown(2);
  } else {throw QueueEx();}


}

void ProtocolSend::run() {
  try {
    //el primer pop es basura nose por q, 
    //si comento la siguiente line valgrid chilla pero el juego no explota
    //mas detalle comentario final
    snapEventQueue.pop();
    while (!skt.isClosed()) {
      sendResponse(snapEventQueue.pop()->getMsg());
    }
  }catch (const LibError& err) {

      std::cerr<< "send closed\n";

  }catch (const QueueEx &e) {

      std::cerr<< "queue closed\n";

  } 
}
//mensaje si comento la linea 40
//==23630== Syscall param socketcall.sendto(msg) points to uninitialised byte(s)
//==23630==    at 0x4CC4AAE: __libc_send (send.c:28)
//==23630==    by 0x4CC4AAE: send (send.c:23)
//==23630==    by 0x11095D: Socket::sendsome(void const*, unsigned int, bool*) (socket.cpp:258)
//==23630==    by 0x110B5D: Socket::sendall(void const*, unsigned int, bool*) (socket.cpp:344)
//==23630==    by 0x118DB6: ProtocolSend::sendResponse(std::vector<unsigned char, std::allocator<unsigned char> >&) (ProtocolSend.cpp:28)
//==23630==    by 0x118E78: ProtocolSend::run() (ProtocolSend.cpp:41)
//==23630==    by 0x110DF5: Thread::runExpecting() (thread.cpp:5)
