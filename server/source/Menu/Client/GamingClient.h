#ifndef __GAMMINGCLIENT_H__
#define __GAMMINGCLIENT_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../../../../common/source/Socket/Socket.h"
#include "../../../../common/source/Socket/Liberror.h"

#include "../../../../common/source/Queue/protected_queue.h"
#include "../../../../common/source/Queue/blocking_queue.h"

#include "../GameCommand/GameCommandHandler.h"

#include "ProtocolRecv.h"
#include "ProtocolSend.h"
#include "Snap.h"
class GammingClient
{
private:
    size_t id;
    Socket skt;
    BlockingQueue<SnapShot> snapEventQueue;
    ProtocolSend protocolSend;
    ProtocolRecv protocolRecv;

public:
    explicit GammingClient(Socket &&skt,size_t id);
    void setup(ProtectedQueue<GameCommandHandler> &eventQueue);
    void addSnap(SnapShot &snap);
    void start();
    ~GammingClient();
};
#endif
