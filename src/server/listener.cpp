#include "listener.h"
#include "mapMonitor.h"
#include "blockingQueue.h"
#include "car.h"
#include "command.h"

Listener::Listener(char* port) : accepter(port){
}

void Listener::run(){
    int i = 0;
    MapMonitor* carmap = new MapMonitor;
    BlockingQueue<Command>* bq = new BlockingQueue<Command>;

    while (true){
        try{
        Socket new_peer = accepter.accept();
        carmap->new_car(i);
        Client* client = new Client(new_peer, i, carmap, bq);
        i++;
        this->clients.push_back(client);
        client->start();
        kill_dead_clients();
        } 
        catch(...)
        {
        break;
        }
    }
    delete carmap;
}

void Listener::kill_dead_clients() {
    std::list<Client *>::iterator it = clients.begin();
    while (it != clients.end()) {
        if (!(*it)->is_alive()) {
            delete *it;
            it = clients.erase(it);
        } else {
            it++;
        }
    }
}

Listener::~Listener(){
    for (Client *c : clients) {
        delete c;
    }
    this->accepter.shutdown(2);
    this->accepter.close();
    this->join();
}
