#include "GammingClient.h"

explicit GammingClient::GammingClient(Socket &&otherSkt,ProtectedQueue<GameCommand> &eventQueue):
    skt(std::move(otherSkt)),snapEventQueue(),protocolSend(skt,snapEventQueue),protocolRecv(skt,eventQueue){}
    