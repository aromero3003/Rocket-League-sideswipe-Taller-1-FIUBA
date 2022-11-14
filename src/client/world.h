#ifndef WORLD_H
#define WORLD_H

#include <mutex>

#include "car.h"
#include "ball.h"

class World{
    private:
        Car car1;
        Car car2;
        Ball ball;
        std::mutex mutex;
    public:
        World();

        //thread-safe
        void update();

        //thread-safe
        void draw();

        ~World();
};

#endif