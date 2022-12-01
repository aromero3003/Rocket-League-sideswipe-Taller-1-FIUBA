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
class Menu
{
private:
    Socket* skt;
    bool was_closed;
    int& n_cars;

    std::stringstream reciveResponse();
    void sendCommand(std::string&& response);
public:
    Menu(Socket* s,  int& n);
    void run();

};
#endif