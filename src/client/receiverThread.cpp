#include "receiverThread.h"

#define FC *(int*)

ReceiverThread::ReceiverThread(Socket& s, World& w): socket(s), world(w) {
    uint8_t cars;
    bool closed = false;
    s.recvall(&cars,1,&closed);
    this->n_cars = cars;
    this->world.create_cars(cars);

    uint8_t my_id;
    s.recvall(&my_id,1,&closed);
    this->world.set_id(my_id);
}

void ReceiverThread::run(){
    std::vector<char> buff;
    int vec_size = BYTES_BALL+ FLAGS + n_cars*BYTES_PER_CAR;
    buff.resize(vec_size);
    bool closed = false;
    while(!closed) {
        this->socket.recvall(&(buff[0]), vec_size, &closed);
        this->world.update(buff);
        if(buff[0] == 0) {
            vec_size = 1 + n_cars * 2;
            std::cout << "entro aca?" << std::endl;
            this->socket.recvall(&(buff[0]), vec_size, &closed);
            this->world.finish_match(buff);
            std::cout << "SI" << std::endl;
        }
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