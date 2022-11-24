#include "receiverThread.h"
#include <string>

#define FC *(int*)

ReceiverThread::ReceiverThread(Socket* s, World* world, int n) {
 this->socket = s;
 this->world = world;
 this->n_cars = n;
}

void ReceiverThread::run(){
    char data[39];
    bool closed = false;
    while(!closed){
        this->socket->recvall(data, BALL_AND_FLAGS + n_cars*BYTES_PER_CAR, &closed);
        this->world->update(data);
        //this->world->print();
    }

}

bool ReceiverThread::is_alive(){
    return this->alive;
}

ReceiverThread::~ReceiverThread(){
    std::cout << "cerrando receiver" << std::endl;
    this->join();
    std::cout << "receiver CERRADO" << std::endl;
}