#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H

#include "../common/socket.h"
#include "../common/thread.h"
#include "world.h"

class ReceiverThread : public Thread {
    private:
    Socket* socket;
    World* world;
    std::thread t;
    bool alive;

    protected:
    void run() override;

    public:
    ReceiverThread(Socket* s, World* world);

    bool is_alive();

    ~ReceiverThread();

};

#endif