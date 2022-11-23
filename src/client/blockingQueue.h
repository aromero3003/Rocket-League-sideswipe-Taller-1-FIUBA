#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T> class BlockingQueue {

private:
    std::queue<T> internal;
    std::mutex mutex;
    std::condition_variable cv;

public:
    BlockingQueue(){}

    void push(T element) {
        std::unique_lock<std::mutex> lock(mutex);
        internal.push(element);
        cv.notify_all();
    }

    T pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while (internal.empty()) {
        cv.wait(lock);
    }
    T element = internal.front();
    internal.pop();
    return element;
    }

    ~BlockingQueue(){}
};

#endif