#ifndef BALL_H
#define BALL_H

#include <cstdint>
#include "texture_manager.h"
#include <SDL2pp/SDL2pp.hh>

class Ball{
    private:
        float x_position;
        float y_position;
        float angle;
        uint8_t color;

        friend class World;
        friend class ProtocolDeserializer;
    public:
        Ball();

        void draw(TextureManager& textureManager);

        void draw_shots(TextureManager& textureManager);


        ~Ball();
};

#endif