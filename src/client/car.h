#ifndef CAR_H
#define CAR_H

#include <cstdint>
#include <SDL2pp/SDL2pp.hh>

#include "texture_manager.h"
#include "sound_manager.h"

class Car{
    private:
        uint8_t id;
        float x_position;
        float y_position;
        float angle;
        bool pointing_right;
        bool nitro_flag;
        uint8_t nitro_quantity;

        friend class World;
    public:  
        Car();

        void draw(TextureManager& textureManager, SoundManager& SoundManager);

        void show_indicators(TextureManager& textureManager);

        void show_nitro(TextureManager& textureManager, SoundManager& soundManager);
        
        ~Car();
};

#endif