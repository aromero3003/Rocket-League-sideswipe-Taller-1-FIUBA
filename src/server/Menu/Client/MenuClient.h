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
    size_t id;
    MenuProtocol menuProtocol;
    Socket& skt;


public:
    MenuClient(Socket&& skt, size_t id,GameHandler& game);

    bool isDisconect();

    ~MenuClient();
};
#endif
