#include <iostream>
#include <thread>

class Thread {
private:
    std::thread t;

    void runExpecting();
protected:
    virtual void run() = 0;

public:
    void start();

    void join();

    virtual ~Thread();
};
