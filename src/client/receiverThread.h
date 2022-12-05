#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#define BYTES_PER_CAR 16
#define BYTES_BALL 13
#define FLAGS 6
#include "socket.h"
#include "thread.h"
#include "world.h"

#include <string>
#include <vector>
#include <cstdint>

class ReceiverThread : public Thread {
    private:
    Socket& socket;
    World& world;
    std::thread t;
    bool alive;
    int n_cars;

    protected:
    void run() override;

    public:
    ReceiverThread(Socket& s, World& w);

    bool is_alive();

    ~ReceiverThread();

};

#endif