#ifndef BALL_H
#define BALL_H

#include <cstdint>

class Ball{
    private:
        float x_position;
        float y_position;
        float angle;
        uint8_t color;

        friend class World;
    public:
        Ball();
        ~Ball();
};

#endif