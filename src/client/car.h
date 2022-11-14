#ifndef CAR_H
#define CAR_H

class Car{
    private:
        friend class World;
        float x_position;
        float y_position;
        bool pointing_right;
    public:
        Car();

        ~Car();
};

#endif