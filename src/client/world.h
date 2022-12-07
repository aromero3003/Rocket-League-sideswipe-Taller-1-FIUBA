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
    private:
        uint8_t my_id;

        Ball ball;
        std::mutex mutex;
        std::vector<Car> cars;
        uint8_t remaining_time;
        uint8_t red_team_score;
        uint8_t blue_team_score;
        uint8_t winner;

        bool goal;
        bool ball_collision;
        bool car_collision;

        void show_court(TextureManager& textureManager);

        void show_nitro_bar(TextureManager& textureManager);

        void show_scores_and_time(TextureManager& textureManager);

        void show_cars(TextureManager& textureManager, SoundManager& soundManager);

        void show_ball(TextureManager& textureManager);

        void show_shots(TextureManager& textureManager);

        void sounds(SoundManager& soundManager);

        void replay(TextureManager& textureManager, SoundManager& soundManager);

        void show_statistics(TextureManager& textureManager, SoundManager& soundManager);

        std::string convert_time();

        void update_flags(std::vector<char>& data);

        void update_ball(std::vector<char>& data);

        void update_cars(std::vector<char>& data);

        friend class Protocol_deserializer;



    public:
        World();

        void set_id(uint8_t id);

        //thread-safe
        void update(std::vector<char>& data);

        void finish_match(std::vector<char>& data);

        void create_cars(int n_cars);

        //thread-safe
        void draw(TextureManager& textureManager, SoundManager& soundManager);


        ~World();
};

#endif