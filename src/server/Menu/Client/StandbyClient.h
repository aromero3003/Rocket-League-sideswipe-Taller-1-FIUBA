#ifndef __STANDBYCLIENT_H__
#define __STANDBYCLIENT_H__

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "../GameCommand/GameCommandHandler.h"
#include "GamingClient.h"
#include "ProtectedQueue.h"
#include "liberror.h"
#include "socket.h"
class StandbyClient {
 private:
  Socket skt;

 public:
  StandbyClient(Socket&& skt);

  std::unique_ptr<GamingClient> getGamingClient(
      ProtectedQueue<std::shared_ptr<GameCommand> >& eventQueue, size_t a,
      std::size_t cant_players);
  ~StandbyClient();
};
#endif
