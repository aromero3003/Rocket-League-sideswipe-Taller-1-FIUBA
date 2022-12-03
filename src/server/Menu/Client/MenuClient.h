#ifndef __MENUCLIENT_H__
#define __MENUCLIENT_H__

#include <list>
#include <memory>
#include <ostream>
#include <string>

#include "socket.h"
#include "liberror.h"

#include "BlockingQueue.h"
#include "../MenuCommand/Command.h"
#include "MenuProtocol.h"
#include <memory>
#include "../Games/GameHandler.h"

class MenuClient
{
private:
    MenuProtocol menuProtocol;
    Socket& skt;


public:
    MenuClient(Socket&& skt,GameHandler& game);

    bool isDisconect();

    void disconect();
    ~MenuClient();
};
#endif
