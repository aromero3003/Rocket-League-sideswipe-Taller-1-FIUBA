#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <SDL2pp/SDL2pp.hh>
#include "senderThread.h"
#include "receiverThread.h"
#include "socket.h"
#include "blockingQueue.h"
#include "world.h"
#include "menu.h"
#include "texture_manager.h"
#include "sound_manager.h"

#define PRESS_RIGHT 65
#define PRESS_LEFT 66
#define PRESS_SPACE 67
#define PRESS_SHIFT 71
#define RELEASE_RIGHT 68
#define RELEASE_LEFT 69
#define RELEASE_SPACE 70
#define RELEASE_SHIFT 72

#define FRAME_RATE 1000/120

#define QUIT 99

using namespace SDL2pp;

class Client_interface{

    private:
    World* world;
    Socket* socket;
    BlockingQueue<int>* pq;

    public:
        Client_interface(const char *serv, const char *port);

        void run_client();

        bool handle_events(BlockingQueue<int>* pq, bool& going_right, bool& going_left, bool& nitroing, bool& jumping);

        //void render_screen_and_sounds(std::vector<Texture>& car_textures, Texture& ball, Texture& court, Texture& nitro, Chunk& nitro_sound, Chunk& ball_sound);

        void render_screen_and_sounds(TextureManager& textureManager, SoundManager& soundManager);

        ~Client_interface();

};

#endif
