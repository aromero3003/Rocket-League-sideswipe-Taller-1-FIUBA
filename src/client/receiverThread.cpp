#include "receiverThread.h"
#include <string>

ReceiverThread::ReceiverThread(Socket* s, World* world) {
 this->socket = s;
 this->world = world;
}

void ReceiverThread::run(){
    //receive from socket
    //update world
}

bool ReceiverThread::is_alive(){
    return this->alive;
}

ReceiverThread::~ReceiverThread(){
    this->join();
}