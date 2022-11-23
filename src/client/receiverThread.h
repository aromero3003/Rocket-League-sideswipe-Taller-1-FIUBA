#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#define BYTES_PER_CAR 13
#define BALL_AND_FLAGS 13
#include "socket.h"
#include "thread.h"
#include "world.h"

class ReceiverThread : public Thread {
    private:
    Socket* socket;
    World* world;
    std::thread t;
    bool alive;
    int n_cars;

    protected:
    void run() override;

    public:
    ReceiverThread(Socket* s, World* world, int n);

    bool is_alive();

    ~ReceiverThread();

};

#endif