#include "GamingClient.h"

GamingClient::GamingClient(Socket &&otherSkt,size_t o_id,ProtectedQueue<GameCommandHandler> &eventQueue):
    id(o_id),skt(std::move(otherSkt)),snapEventQueue(),protocolSend(skt,snapEventQueue),protocolRecv(skt,eventQueue,id){}

    void GamingClient::addSnap(SnapShot &snap){
        snapEventQueue.push(snap);
    }
    void GamingClient::start(){
        protocolSend.start();
        protocolRecv.start();
    }
    bool GamingClient::isDisconect(){
        return false;// refactor
    }

GamingClient::~GamingClient(){
    protocolSend.join();
    protocolRecv.join();
}

    