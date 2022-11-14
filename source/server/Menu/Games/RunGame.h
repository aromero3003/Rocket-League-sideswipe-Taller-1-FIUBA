#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>
#include "../GameCommand/GameCommandHandler.h"
#include "GameLogic.h"
#include "../Client/GamingClient.h"
#include "../../../../common/source/Thread/Thread.h"
#include "../../../../common/source/Queue/protected_queue.h"

class RunGame : public Thread {
 private:
   ProtectedQueue<GameCommandHandler> gammingEventQueue;
   GameLogic gameLogic;
   std::vector<GammingClient*> players;
 public:
  RunGame();
  ProtectedQueue<GameCommandHandler> & getRefGammingQueue();
  void  addPlayer(GammingClient* gamingClient);
  void setupStart();
  virtual void run() override;
  virtual ~RunGame() = default;
};
#endif
