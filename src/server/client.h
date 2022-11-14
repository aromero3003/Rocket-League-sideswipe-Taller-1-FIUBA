#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "../client/socket.h"
#include "thread.h"
#include "mapMonitor.h"
#include "blockingQueue.h"
#include "command.h"

class Client : public Thread {
    private:
    Socket peer;
    MapMonitor* carmap;
    BlockingQueue<Command>* bq;
    int id;
    std::thread t;
    bool alive;

    protected:
    void run() override;

    public:
    Client(Socket &p,int id, MapMonitor* m, BlockingQueue<Command>* bq);

    bool is_alive();

    ~Client();
};

#endif
