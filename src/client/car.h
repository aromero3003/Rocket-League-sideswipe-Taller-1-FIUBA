#ifndef CAR_H
#define CAR_H

#include <cstdint>

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
        ~Car();
};

#endif