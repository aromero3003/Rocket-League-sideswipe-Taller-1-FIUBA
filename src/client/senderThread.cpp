#include "senderThread.h"
#include <cstdint>
#include <string>

SenderThread::SenderThread(Socket& s, BlockingQueue<int>& pq):
                            socket(s),
                            pq(pq) {
}

void SenderThread::run() {
    int8_t action = 0;
    bool closed = false;
    while (1){
        action = pq.pop();
        if (action == 99) break;
        this->socket.sendall(&action,1, &closed);
    }
}

bool SenderThread::is_alive(){
    return this->alive;
}

SenderThread::~SenderThread(){
    std::cout << "cerrando sender" << std::endl;
    this->join();
    std::cout << "sender CERRADO" << std::endl;
}
