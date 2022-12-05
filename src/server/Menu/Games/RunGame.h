#ifndef __RUNGAME_H__
#define __RUNGAME_H__

#include <map>
#include <mutex>
#include <string>
#include <utility>

#include "../Client/GamingClient.h"
#include "../GameCommand/GameCommandHandler.h"
#include "GameLogic.h"
#include "ProtectedQueue.h"
#include "QueueEx.h"
#include <queue>
#include "liberror.h"
#include "thread.h"
#include "GameObjects/Constants.h"

class RunGame : public Thread {
 private:
  GameLogic gameLogic;
  ProtectedQueue<std::shared_ptr<GameCommand> > gammingEventQueue;
  std::vector<std::unique_ptr<GamingClient>> players;
  std::queue<std::shared_ptr<SnapShot> > replayQueue;
  void sendReplay();

 public:
  RunGame(std::size_t cantplayers);
  ProtectedQueue<std::shared_ptr<GameCommand> >& getRefGamingQueue();
  void addPlayer(std::unique_ptr<GamingClient>&& player);
  void endGame();
  void close();
  virtual void run() override;
  virtual ~RunGame() ;
};
#endif
