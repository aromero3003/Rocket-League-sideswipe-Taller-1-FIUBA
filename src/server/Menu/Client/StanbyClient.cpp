#include "StandbyClient.h"

StandbyClient::StandbyClient(Socket&& otherSkt,size_t o_id):
    id(o_id),skt(std::move(otherSkt)){}

std::unique_ptr<GamingClient> StandbyClient::getGamingClient(ProtectedQueue<GameCommandHandler>& eventQueue){
    std::unique_ptr<GamingClient> gameCli (new GamingClient(std::move(this->skt),this->id,eventQueue));
    return gameCli;
}

StandbyClient::~StandbyClient()=default;


    
    
