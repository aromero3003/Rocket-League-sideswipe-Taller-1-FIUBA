#ifndef __PROTECTED_QUEUE__
#define __PROTECTED_QUEUE__

#include <queue>
#include <mutex>
#include "QueueEx.h"

template <class T> class ProtectedQueue {
 private:
    std::mutex mutex;
    std::queue<T> queue;
    bool isClosed = false;

 public:
    void push(T& item) {
        std::lock_guard<std::mutex> lock(this->mutex);
        if(!isClosed)this->queue.push(item);
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(this->mutex);
        return this->queue.size();
    }

    bool is_empty() {
        std::lock_guard<std::mutex> lock(this->mutex);
        return this->queue.size() == 0;
    }
    void close() {
        std::lock_guard<std::mutex> lock(this->mutex);
        this->isClosed = true; 
    }

    T pop() {
        std::lock_guard<std::mutex> lock(this->mutex);
        if (isClosed) throw QueueEx();
        T item = this->queue.front();
        this->queue.pop();
        return item;
    }
    void clean() {
        std::lock_guard<std::mutex> lock(this->mutex);
        if (this->queue.size() != 0) this->queue.pop();
    }
};

#endif  //  __PROTECTED_QUEUE__
