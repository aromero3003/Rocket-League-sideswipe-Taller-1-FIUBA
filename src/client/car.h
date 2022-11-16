#ifndef CAR_H
#define CAR_H

class Car{
    public:
        friend class World;
        float x_position;
        float y_position;
        float angle;
        bool pointing_right;
        Car();

        ~Car();
};

#endif