#include "receiverThread.h"
#include <string>

#define FC *(float*)

ReceiverThread::ReceiverThread(Socket* s, World* world) {
 this->socket = s;
 this->world = world;
}

void ReceiverThread::run(){
    char data[39];
    bool closed = false;
    while(!closed){
        this->socket->recvall(data, 39, &closed);
        std::cout << "Flag: " << (int)data[0] << std::endl;
        std::cout << "Ball: (x,y) = (" << FC(data + 1)  << " | " <<  FC(data + 5) << ") angle: " << FC (data+9) << std::endl;
        std::cout << "car1: (x,y) = ("<< FC(data + 17) << " | " << FC(data + 13) << ") angle: " << FC (data+21) << " orientation: " << (int)data[25] << std::endl;
        std::cout << "car1: (x,y) = ("<< FC(data + 30) << " | " << FC(data + 26) << ") angle: " << FC (data+34) << " orientation: " << (int)data[38] << std::endl;
        //std::cout << "car2: (x,y) = "<< FC(data + 26) << FC(data + 30) << "angle: " << FC (data+34) << "orientation: " << (int)data[38] << std::endl;
        std::cout << "Termina iteración\n" << std::endl;
    }

}

bool ReceiverThread::is_alive(){
    return this->alive;
}

ReceiverThread::~ReceiverThread(){
    this->join();
}