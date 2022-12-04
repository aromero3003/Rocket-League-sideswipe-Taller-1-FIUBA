#include "receiverThread.h"

#define FC *(int*)

ReceiverThread::ReceiverThread(Socket* s, World* world, int n) {
 this->socket = s;
 this->world = world;
 this->n_cars = n;
}

void ReceiverThread::run(){
    std::vector<char> buff;
    int vec_size = BYTES_BALL+ FLAGS + n_cars*BYTES_PER_CAR;
    buff.resize(vec_size);
    bool closed = false;
    while(!closed) {
        this->socket->recvall(&(buff[0]), vec_size, &closed);
        this->world->update(buff);
        this->world->print(buff);
    }
}

bool ReceiverThread::is_alive(){
    return this->alive;
}

ReceiverThread::~ReceiverThread(){
    //std::cout << "cerrando receiver" << std::endl;
    this->join();
    //std::cout << "receiver CERRADO" << std::endl;
}