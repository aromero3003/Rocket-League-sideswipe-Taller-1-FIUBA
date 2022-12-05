#ifndef __MENUPROTOCOL_H__
#define __MENUPROTOCOL_H__

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



class MenuProtocol
{
private:
    Socket& skt;
    bool was_closed;

    std::stringstream reciveResponse();
    void sendCommand(std::string&& response);
public:
    MenuProtocol(Socket& s);
    void run();

};
#endif