#ifndef WORLD_H
#define WORLD_H

#include <mutex>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include "car.h"
#include "ball.h"

#define GOAL_FLAG 0x01
#define NITRO_FLAG 0x02
#define CAR_BALL_COLLISION 0x04
#define CAR_TERRAIN_COLLISION 0x08
#define BALL_TERRAIN_COLLISION 0x10

class World{
    public:
        Ball ball;
        std::mutex mutex;
        std::vector<Car> cars;
        bool goal;
        bool nitro;
        bool car_ball_collision;
        bool car_terrain_collision;
        bool ball_terrain_collision;

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