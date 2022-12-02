#include "StandbyClient.h"

StandbyClient::StandbyClient(Socket&& otherSkt):skt(std::move(otherSkt)){}

std::unique_ptr<GamingClient> StandbyClient::getGamingClient(
    ProtectedQueue<GameCommandHandler>& eventQueue,
    size_t a,
    std::size_t cant_players){
    std::unique_ptr<GamingClient> gameCli (new GamingClient(
                                            std::move(this->skt),a,eventQueue,cant_players));
    return gameCli;
}

StandbyClient::~StandbyClient()=default;


    
    
