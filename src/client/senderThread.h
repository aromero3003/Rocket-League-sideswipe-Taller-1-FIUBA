#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H

#include "socket.h"
#include "thread.h"
#include "blockingQueue.h"

class SenderThread : public Thread {
    private:
    Socket& socket;
    BlockingQueue<int>& pq;
    std::thread t;
    bool alive;

    protected:
    void run() override;

    public:
    SenderThread(Socket& s, BlockingQueue<int>& pq);

    bool is_alive();

    ~SenderThread();
};

#endif