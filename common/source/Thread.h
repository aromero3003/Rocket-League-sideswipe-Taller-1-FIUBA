#ifndef __THREAD_H__
#define __THREAD_H__
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

class Thread {
 private:
  std::thread thread;

 public:
  Thread() {}

  void start() {
    try {
      thread = std::thread(&Thread::run, this);
    } catch (const std::exception& err) {
      std::cerr << "Something went wrong and an exception was caught: "
                << err.what() << "\n";
    } catch (...) {
      std::cerr
          << "Something went wrong and an unknown exception was caught.\n";
    }
  }

  void join() { thread.join(); }

  virtual void run() = 0;
  virtual ~Thread() {}

  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  Thread(Thread&& other) { this->thread = std::move(other.thread); }

  Thread& operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
  }
};
#endif
