#include "AcceptThread.h"
AcceptThread::AcceptThread(Socket& soktRef, bool& serverStatus)
    : serverIsOpen(serverStatus), soktRef(soktRef) {}

void AcceptThread::disconect() { menu.disconectAll(); }

void AcceptThread::run() {
  try {
    Menu menu;
    int a=0;
    while (serverIsOpen || a!=2) {
      Socket sktAccepted = soktRef.accept();
      if (serverIsOpen) menu.conectNewClient(std::move(sktAccepted),a);
      menu.cleanDisconectClients();
      a++;
    }
    menu.startGame();
  } catch (const LibError& err) {
    menu.disconectAll();
  }
}
