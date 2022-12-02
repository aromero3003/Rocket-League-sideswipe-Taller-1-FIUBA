#ifndef __STANDBYCLIENT_H__
#define __STANDBYCLIENT_H__

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "socket.h"
#include "liberror.h"
#include "GamingClient.h"
#include "../GameCommand/GameCommandHandler.h"
#include "ProtectedQueue.h"
class StandbyClient
{
private:
    Socket skt;

public:
    StandbyClient(Socket&& skt);
    
    std::unique_ptr<GamingClient> getGamingClient(ProtectedQueue<GameCommandHandler>& eventQueue,size_t a,std::size_t cant_players);
    ~StandbyClient();
};
#endif
