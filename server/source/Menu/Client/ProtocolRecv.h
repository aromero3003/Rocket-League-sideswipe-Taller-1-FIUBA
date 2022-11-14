#ifndef __PROTOCOLRECV_H__
#define __PROTOCOLRECV_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>
#include "../../../../common/source/Socket/Socket.h"
#include "../../../../common/source/Socket/Liberror.h"

#include "../../../../common/source/Queue/protected_queue.h"
#include "../../../../common/source/Queue/blocking_queue.h"
#include "../GameCommand/GameCommandHandler.h"

#include "../../../../common/source/Thread/Thread.h"


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
