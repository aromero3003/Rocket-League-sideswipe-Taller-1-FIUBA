#include "client.h"
#include <string>

Client::Client(Socket &p, int id, MapMonitor* carmap, BlockingQueue<Command>* bq): peer(std::move(p)) {
    this->bq = bq;
    this->alive = true;
    this->id = id;
    this->carmap = carmap;
}

void Client::run() {
    try {
    std::cout << "soy cliente:" << this->id << std::endl;

    bool closed = false;
    int command_received = 0;
    while(1){
        this->peer.recvall(&command_received, 4, &closed);
        Command command(this->id, command_received);
        if (closed) return;
        bq->push(command);
        std::cout << command.get_command() << std::endl;
    }
    } catch(...) {
        this->alive = false;
        return;
    }
}

bool Client::is_alive(){
    return this->alive;
}

Client::~Client(){
    this->peer.shutdown(2);
    this->peer.close();
    this->join();
}
