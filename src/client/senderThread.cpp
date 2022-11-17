#include "senderThread.h"
#include <cstdint>
#include <string>

SenderThread::SenderThread(Socket* s, BlockingQueue<int>* pq) {
 this->socket = s;
 this->pq = pq;
}

void SenderThread::run() {
    int8_t action = 0;
    bool closed = false;
    while (1){
        action = pq->pop();
        if (action == 99) break;
        this->socket->sendall(&action,1, &closed);
    }
}

bool SenderThread::is_alive(){
    return this->alive;
}

SenderThread::~SenderThread(){
    this->join();
}
