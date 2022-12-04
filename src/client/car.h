#ifndef CAR_H
#define CAR_H

#include <cstdint>

class Car{
    private:
        uint8_t id;
        uint32_t x_position;
        uint32_t y_position;
        uint32_t angle;
        bool pointing_right;
        bool nitro_flag;
        uint8_t nitro_quantity;

        friend class World;
    public:  
        Car();
        ~Car();
};

#endif