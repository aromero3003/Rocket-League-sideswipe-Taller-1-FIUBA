#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <SDL2pp/SDL2pp.hh>
#include "senderThread.h"
#include "receiverThread.h"
#include "socket.h"
#include "blockingQueue.h"
#include "world.h"

using namespace SDL2pp;

class Client_interface{

    private:
    SDL2pp::SDL sdl;
	SDL2pp::Window window;
	SDL2pp::Renderer renderer;
    World* world;

    public:
        Client_interface();

        void run_client(const char *serv, const char *port);

        bool handle_events(BlockingQueue<int>* pq, bool& going_right, bool& going_left, bool& nitroing, bool& jumping);

        //void render_screen(Texture& car, Texture& road, Texture& ball, Texture& court);

        void render_screen(std::vector<Texture>& car_textures, Texture& ball, Texture& court);

        ~Client_interface();

};

#endif
