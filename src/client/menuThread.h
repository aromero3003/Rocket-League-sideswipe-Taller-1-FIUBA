#ifndef __MENUTHREAD_H__
#define __MENUTHREAD_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>
#include <sstream>
#include <vector>
#include "thread.h"
#include "socket.h"
#include "liberror.h"
#include <arpa/inet.h>
class MenuThread: public Thread 
{
private:
    Socket* skt;
    bool was_closed;
    int& n_cars;

    std::stringstream reciveResponse();
    void sendCommand(std::string&& response);
public:
    MenuThread(Socket* s,  int& n);
    virtual void run() override;
    virtual ~MenuThread()= default;
};
#endif