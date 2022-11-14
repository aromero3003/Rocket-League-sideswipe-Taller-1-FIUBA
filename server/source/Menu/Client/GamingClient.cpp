#include "GamingClient.h"

explicit GammingClient::GammingClient(Socket &&otherSkt,size_t id):
    id(id),skt(std::move(otherSkt)),snapEventQueue(),protocolSend(skt,snapEventQueue),protocolRecv(skt){}

    void GammingClient::addSnap(SnapShot &snap){
        snapEventQueue.push(snap);
    }
    void GammingClient::start(){
        protocolSend.start();
        protocolRecv.start();
    }
    bool GammingClient::isDisconect(){
        return false;// refactor
    }
void GammingClient::setup(ProtectedQueue<GameCommandHandler> &eventQueue){
  protocolRecv.setup(eventQueue,id);
}
GammingClient::~GammingClient(){
    protocolSend.join();
    protocolRecv.join();
}

    