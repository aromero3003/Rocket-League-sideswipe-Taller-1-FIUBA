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

        uint8_t goals;
        uint8_t assists;

        friend class World;
        friend class ProtocolDeserializer;
    public:  
        Car();

        void draw(TextureManager& textureManager, SoundManager& SoundManager,size_t cant_cars);

        void show_indicators(TextureManager& textureManager,size_t cant_cars);

        void show_nitro(TextureManager& textureManager, SoundManager& soundManager);
        
        ~Car();
};

#endif