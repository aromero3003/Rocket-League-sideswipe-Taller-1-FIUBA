#include "AcceptThread.h"
AcceptThread::AcceptThread(Socket& soktRef, bool& serverStatus)
    : serverIsOpen(serverStatus), soktRef(std::move(soktRef)) {}


void AcceptThread::run() {
  try {
    Menu menu;
    size_t a=0;
    while (serverIsOpen ) {
      Socket sktAccepted = soktRef.accept();
      if (serverIsOpen) menu.conectNewClient(std::move(sktAccepted),a);
    
    }
  } catch (const LibError& err) {
   
  }
}
