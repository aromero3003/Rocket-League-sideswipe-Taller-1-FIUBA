#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>

#include "../GameCommand/GameCommandHandler.h"
#include "../../common/source/liberror.h"
#include "../../common/source/socket.h"
#include "../common/source/Thread.h"
#include "../../common/source/protected_queue.h"

class ProtocolRecv: public Thread 
{
private:
    Socket& skt;
    bool was_closed;
    std::istream& reciveCommand();
    ProtectedQueue<GameCommandHandler> &eventQueueRef;
    size_t id;
public:
    explicit ProtocolRecv(Socket &skt);
    void setup(ProtectedQueue<GameCommandHandler> &eventQueue);
    virtual void run() override;
};
#endif
