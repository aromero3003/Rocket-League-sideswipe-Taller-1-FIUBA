#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>


class RunGame : public Thread {
 private:
   

 public:
  RunGame();
  virtual void run() override;
  void disconect();
  virtual ~RunGame() = default;
};
#endif
