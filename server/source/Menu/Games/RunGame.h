#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>


class RunGame : public Thread {
 private:
    QueueP

 public:
  AcceptThread(Socket& soktRef, bool& serverStatus);
  virtual void run() override;
  void disconect();
  virtual ~AcceptThread() = default;
};
#endif
