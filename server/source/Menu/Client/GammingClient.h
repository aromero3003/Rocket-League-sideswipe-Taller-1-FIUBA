#ifndef __CLIENTTHREAD_H__
#define __CLIENTTHREAD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>

#include "../common/source/liberror.h"
#include "../common/source/socket.h"
#include "../MenuCommand/CommandHandler.h"
#include "../Games/GameHandler.h"
#include "ProtocolSend.h"
#include "../../common/source/protected_queue.h"
#include "../../common/source/blocking_queue.h"
#include "ProtocolRecv.h"
#include "../GameCommand/GameCommand.h"
class GammingClient
{
private:
    int id;
    Socket skt;
    BlockingQueue<Snap>* snapEventQueue;
    ProtocolSend protocolSend;
    ProtocolRecv protocolRecv;

public:
    explicit GammingClient(Socket &&skt,ProtectedQueue<GameCommand> *eventQueue,int id);
    void addSnap(Snap &snap);
    void start();
    ~GammingClient();
};
#endif
