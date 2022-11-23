#ifndef WORLD_H
#define WORLD_H

#include <mutex>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include "car.h"
#include "ball.h"

#define RED_GOAL_FLAG 0x01
#define BLUE_GOAL_FLAG 0x02
#define BALL_COLLISION 0x04

#define POINTING_RIGHT 0x01
#define NITRO 0x02

class World{
    public:
        Ball ball;
        std::mutex mutex;
        std::vector<Car> cars;
        bool goal;
        bool ball_collision;
        //bool car_terrain_collision;
        //bool ball_terrain_collision;

        World();

        //thread-safe
        void update(char* data);

        void create_cars(int n_cars);

        //thread-safe
        void draw(std::vector<SDL2pp::Texture>& car_textures,
                 SDL2pp::Texture& ball, 
                 SDL2pp::Texture& court, 
                 SDL2pp::Renderer& renderer,
                 SDL2pp::Chunk& ball_sound, 
                 SDL2pp::Mixer& mixer);


        ~World();
};

#endif