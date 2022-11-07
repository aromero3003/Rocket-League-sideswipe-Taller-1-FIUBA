#include "ProtocolSend.h"

explicit ProtocolSend::ProtocolSend(Socket&skt,BlockingQueue<Snap>& snap):skt(skt),snapEventQueue(BlockingQueue<Snap>& snap){}