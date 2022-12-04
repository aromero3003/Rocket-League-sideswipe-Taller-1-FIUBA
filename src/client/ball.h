#ifndef BALL_H
#define BALL_H

#include <cstdint>

class Ball{
    private:
        uint32_t x_position;
        uint32_t y_position;
        uint32_t angle;
        uint8_t color;

        friend class World;
    public:
        Ball();
        ~Ball();
};

#endif