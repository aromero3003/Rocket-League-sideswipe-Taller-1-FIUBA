#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>
#include "../GameCommand/GameCommandHandler.h"
#include "GameLogic.h"
#include "../Client/GamingClient.h"
#include "ProtectedQueue.h"
#include "thread.h"
#include "socket.h"
#include "liberror.h"

class RunGame : public Thread {
 private:
  GameLogic gameLogic;

  ProtectedQueue<GameCommandHandler> gammingEventQueue;
  std::vector<GamingClient*> players;
 public:
  RunGame();
  ProtectedQueue<GameCommandHandler> & getRefGamingQueue();
  void  addPlayer(GamingClient* gamingClient);
  virtual void run() override;
  virtual ~RunGame() = default;
};
#endif
