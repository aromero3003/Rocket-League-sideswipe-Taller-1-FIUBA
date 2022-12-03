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
#include "liberror.h"
#include "thread.h"
class RunGame : public Thread {
 private:
  GameLogic gameLogic;
  ProtectedQueue<GameCommandHandler> gammingEventQueue;
  std::vector<std::unique_ptr<GamingClient>> players;

 public:
  RunGame(std::size_t cantplayers);
  ProtectedQueue<GameCommandHandler>& getRefGamingQueue();
  void addPlayer(std::unique_ptr<GamingClient>&& player);
  void close();
  virtual void run() override;
  virtual ~RunGame() = default;
};
#endif
