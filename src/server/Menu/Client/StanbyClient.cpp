#include "StandbyClient.h"

StandbyClient::StandbyClient(Socket&& otherSkt):skt(std::move(otherSkt)){
    //send ok in add Game
    bool was_closed=false;
    std::string response("OK");
    int8_t lenght=response.size();
    skt.sendall(&lenght,1, &was_closed);
    skt.sendall(response.data(),response.size(), &was_closed);
}

std::unique_ptr<GamingClient> StandbyClient::getGamingClient(
    ProtectedQueue<GameCommandHandler>& eventQueue,
    size_t a,
    std::size_t cant_players){
    std::unique_ptr<GamingClient> gameCli (new GamingClient(
                                            std::move(this->skt),a,eventQueue,cant_players));
    return gameCli;
}

StandbyClient::~StandbyClient()=default;


    
    
