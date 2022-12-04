#ifndef WORLD_H
#define WORLD_H

#include <mutex>
#include <vector>
#include <SDL2pp/SDL2pp.hh>
#include "car.h"
#include "ball.h"
#include "texture_manager.h"
#include "sound_manager.h"

class World{
    public:
        Ball ball;
        std::mutex mutex;
        std::vector<Car> cars;
        uint8_t remaining_time;
        uint8_t red_team_score;
        uint8_t blue_team_score;
        bool goal;
        bool ball_collision;
        bool car_collision;

        World();

        uint32_t bytesToInt(std::vector<char>& data, int pos);

        //thread-safe
        void update(std::vector<char>& data);

        void create_cars(int n_cars);

        //thread-safe
        void draw(TextureManager& textureManager, SoundManager& soundManager);

        void print(char* data);

        ~World();
};

#endif