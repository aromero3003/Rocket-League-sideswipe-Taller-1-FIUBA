#include "MenuEventAddClient.h"
MenuEventAddClient::MenuEventAddClient(Socket&& sktAccepted,size_t oid) :
    skt(std::move(sktAccepted)),id(oid){}

void MenuEventAddClient::run() {
/*

*/

}