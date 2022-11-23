#ifndef __MENUPROTOCOL_H__
#define __MENUPROTOCOL_H__

#include <istream>
#include <list>
#include <ostream>
#include <string>
#include <utility>

#include <sstream>
#include "thread.h"
#include "socket.h"
#include "liberror.h"
#include "../MenuCommand/CommandHandler.h"
#include "../MenuCommand/Command.h"
#include "../MenuCommand/CommandAdd.h"
#include "../MenuCommand/IncompleteCommandAdd.h"
class MenuProtocol: public Thread 
{
private:
    Socket skt;
    bool was_closed;
    size_t id;
    GameHandler& games;
    std::stringstream reciveCommand();
    void sendResponse(std::string&& response);
public:
    MenuProtocol(Socket&& skt, size_t id,GameHandler& game);
    Socket& getSocketRef();
    virtual void run() override;
    virtual ~MenuProtocol()= default;
};
#endif
