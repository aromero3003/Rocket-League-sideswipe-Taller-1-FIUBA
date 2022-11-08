#include "GammingClient.h"

explicit GammingClient::GammingClient(Socket &&otherSkt,ProtectedQueue<GameCommand> *eventQueue,int id):
    id(id),skt(std::move(otherSkt)),snapEventQueue(),protocolSend(skt),protocolRecv(skt,eventQueue){
        snapEventQueue = protocolSend.getSnapQueue();
    }

    void GammingClient::addSnap(Snap &snap){
        snapEventQueue->push(snap);
    }
    void GammingClient::start(){
        protocolSend.start();
        protocolRecv.start();
    }

GammingClient::~GammingClient(){
    protocolSend.join();
    protocolRecv.join();
}

    