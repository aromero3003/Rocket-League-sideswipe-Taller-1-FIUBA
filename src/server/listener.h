#ifndef LISTENER_H
#define LISTENER_H

#include <list>

#include "../client/socket.h"
#include "client.h"

class Listener : public Thread {
    private:
    Socket accepter;
    std::list<Client *> clients;

    protected:
    void run() override;

    public:
    explicit Listener(char* port);

    void kill_dead_clients();

    ~Listener();
};

#endif
