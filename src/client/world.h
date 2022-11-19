#ifndef WORLD_H
#define WORLD_H

#include <mutex>
#include <SDL2pp/SDL2pp.hh>

#include "car.h"
#include "ball.h"

class World{
    public:
        Ball caca;
        Ball ball;
        std::mutex mutex;
        std::vector<Car> cars;

        World();

        //thread-safe
        void update(char* data);

        void create_cars(int n_cars);

        void print();

        //thread-safe
        void draw(std::vector<SDL2pp::Texture>& car_textures, SDL2pp::Texture& ball, SDL2pp::Texture& court, SDL2pp::Renderer& renderer);

        ~World();
};

#endif