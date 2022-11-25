#ifndef __GAMMINGCLIENT_H__
#define __GAMMINGCLIENT_H__

#include <istream>
#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "socket.h"
#include "liberror.h"

#include "ProtectedQueue.h"
#include "BlockingQueue.h"

#include "../GameCommand/GameCommandHandler.h"

#include "ProtocolRecv.h"
#include "ProtocolSend.h"
#include "Snap.h"
class GamingClient
{
private:
    size_t id;
    Socket skt;
    BlockingQueue<std::shared_ptr<SnapShot>>snapEventQueue;
    ProtocolSend protocolSend;
    ProtocolRecv protocolRecv;

public:
    GamingClient(Socket&& skt,size_t id,ProtectedQueue<GameCommandHandler>& eventQueue,std::size_t cant_players);
    bool isDisconect();
    void addSnap(std::shared_ptr<SnapShot> snap);
    void start();
    ~GamingClient();
};
#endif
