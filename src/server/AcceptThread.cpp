#include "AcceptThread.h"
AcceptThread::AcceptThread(Socket& soktRef, std::atomic<bool>& serverStatus)
    : serverIsOpen(serverStatus), soktRef(std::move(soktRef)),menu() {}


void AcceptThread::run() {
  try {
    while (this->serverIsOpen.load(std::memory_order_acquire)) {
      Socket sktAccepted = soktRef.accept();
      if (this->serverIsOpen.load(std::memory_order_acquire)) this->menu.conectNewClient(std::move(sktAccepted));
  
    }
  } catch (const LibError& err) {
   
  }
}
  void AcceptThread::disconect(){
    this->menu.disconect();
    this->serverIsOpen.store(false,std::memory_order_acquire);
    this->soktRef.shutdown(SHUT_RDWR);

  }
