#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>
#include "../GameCommand/GameCommand.h"

#include "../../common/source/protected_queue.h"

class RunGame : public Thread {
 private:
   ProtectedQueue<GameCommand>* gammingEventQueue;
 public:
  RunGame();
  ProtectedQueue<GameCommand> * getRefGammingQueue();
  void  addPlayer(GammingClient* gamingClient);
  void setupStart();
  virtual void run() override;
  virtual ~RunGame() = default;
};
#endif
