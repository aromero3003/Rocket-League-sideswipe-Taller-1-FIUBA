#include "AcceptThread.h"
AcceptThread::AcceptThread(Socket& soktRef, bool& serverStatus)
    : serverIsOpen(serverStatus), soktRef(soktRef) {}

void AcceptThread::disconect() { clientsHandler.disconectAll(); }

void AcceptThread::run() {
  try {
    while (serverIsOpen) {
      Socket sktAccepted = soktRef.accept();
      if (serverIsOpen) clientsHandler.conectNewClient(std::move(sktAccepted));
      clientsHandler.cleanDisconectClients();
    }
  } catch (const LibError& err) {
    clientsHandler.disconectAll();
  }
}
