#include "GammingClient.h"

explicit GammingClient::GammingClient(Socket &&otherSkt,int id):
    id(id),skt(std::move(otherSkt)),snapEventQueue(),protocolSend(skt,snapEventQueue),protocolRecv(skt){}

    void GammingClient::addSnap(SnapShot &snap){
        snapEventQueue.push(snap);
    }
    void GammingClient::start(){
        protocolSend.start();
        protocolRecv.start();
    }
void GammingClient::setup(ProtectedQueue<GameCommandHandler> &eventQueue){
  eventQueueRef=eventQueue;
}
GammingClient::~GammingClient(){
    protocolSend.join();
    protocolRecv.join();
}

    