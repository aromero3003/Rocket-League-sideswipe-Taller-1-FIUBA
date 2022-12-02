#include "AcceptThread.h"
AcceptThread::AcceptThread(Socket& soktRef, bool& serverStatus)
    : serverIsOpen(serverStatus), soktRef(std::move(soktRef)) {}


void AcceptThread::run() {
  try {
    Menu menu;
    while (serverIsOpen ) {
      Socket sktAccepted = soktRef.accept();
      if (serverIsOpen) menu.conectNewClient(std::move(sktAccepted));
  
    }
  } catch (const LibError& err) {
   
  }
}
  void AcceptThread::disconect(){
    this->soktRef.shutdown(2);
  }