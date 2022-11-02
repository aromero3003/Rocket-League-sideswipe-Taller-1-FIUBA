#include "ClientHandler.h"
ClientThread::ClientThread(Socket& skt, GameHandler& gameHandler)
    : Thread(), protocol(skt), gameHandler(gameHandler) {}

void ClientThread::run() {
  try {
    while (protocol.isOpen()) {
      ComandHandler comandHandler;
      if (protocol.waitComand(comandHandler)) {
        comandHandler.run(gameHandler);
        protocol.sendResponse(comandHandler.getResponse());
      }
    }
  } catch (const LibError& err) {
  }
}

