#ifndef WORLD_H
#define WORLD_H

#include <mutex>

#include "car.h"
#include "ball.h"

class World{
    public:
        Car car1;
        Car car2;
        Ball ball;
        std::mutex mutex;
    
        World();

        //thread-safe
        void update(char* data);

        void print();

        //thread-safe
        void draw();

        ~World();
};

#endif