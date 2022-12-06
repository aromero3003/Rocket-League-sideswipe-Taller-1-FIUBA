#include "world.h"
#include <cstdint>
#include <iostream>
#include <string>

#define FC *(float*)
#define PI 3.14159265
using namespace SDL2pp;

World::World(){}

void World::create_cars(int n_cars){
    for(int i=0; i < n_cars; i++){
        Car new_car;
        this->cars.push_back(new_car);
    }
}

void World::set_id(uint8_t id){
    this->my_id = id;
}

void World::update(std::vector<char>& data){
    std::lock_guard<std::mutex> lock(mutex);
    
    char* buf = reinterpret_cast<char*>(data.data());

    //UPDATE FLAGS
    this->remaining_time = data[0];
    this->blue_team_score = data[1];
    this->red_team_score = data[2];
    this->goal = data[3];
    this->ball_collision = data[4];
    this->car_collision = data[5];

    //UPDATE BALL
    this->ball.x_position = FC(buf+6);
    this->ball.y_position = FC(buf+10);
    this->ball.angle = (-180/PI)*FC(buf+14);
    this->ball.color = data[18];

    std::cout << (int)this->ball.color << std::endl;

    //UPDATE ALL CARS
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].id = (uint8_t) data[((i) * 16 + 19)];
        this->cars[i].x_position = FC(buf + (i*16 + 20));
        this->cars[i].y_position = FC(buf + (i*16 + 24));
        this->cars[i].angle = (-180/PI)*FC(buf + (i*16 + 28));
        this->cars[i].pointing_right = (uint8_t) data[i*16 + 32];
        this->cars[i].nitro_flag = (uint8_t) data[i*16 + 33];
        this->cars[i].nitro_quantity = data[i*16 + 34];
    }
}

void World::draw(TextureManager& textureManager, SoundManager& soundManager){

    std::lock_guard<std::mutex> lock(mutex);

    //Show court, always the same
    show_court(textureManager);

    //nitro_bar
    show_nitro_bar(textureManager);

    //Show scores and time
    show_scores_and_time(textureManager);

    //replay
    if (this->goal)
        replay(textureManager, soundManager);

    //Show all cars
    show_cars(textureManager, soundManager);
    
    //Show ball
    show_ball(textureManager);

    //shots
    show_shots(textureManager);

    //sounds
    sounds(soundManager);

}

void World::show_court(TextureManager& textureManager){
    textureManager.renderer.Copy(
        textureManager.court, 
        NullOpt, 
        Rect(
            0,
            0,
            textureManager.renderer.GetOutputWidth(), 
            textureManager.renderer.GetOutputHeight()));
}

void World::show_nitro_bar(TextureManager& textureManager){
    textureManager.renderer.Copy(
        textureManager.nitro_bar,
        NullOpt,
        Rect(20*this->cars[my_id].x_position - 25,
            (-20)*this->cars[my_id].y_position - 25,
            50,
            10));
    
    textureManager.renderer.Copy(
        textureManager.remaining_nitro,
        NullOpt,
        Rect(20*this->cars[my_id].x_position - 25,
            (-20)*this->cars[my_id].y_position - 25,
            this->cars[my_id].nitro_quantity / 2,
            10));
}

void World::show_cars(TextureManager& textureManager, SoundManager& soundManager){
    
    for(size_t i = 0; i < this->cars.size(); i++){
        cars[i].draw(textureManager, soundManager);
    }
}

void World::show_ball(TextureManager& textureManager){
    ball.draw(textureManager);
}

void World::show_shots(TextureManager& textureManager){   
    ball.draw_shots(textureManager);
}

void World::sounds(SoundManager& soundManager){
    if(this->ball_collision && !soundManager.mixer.IsChannelPlaying(7)){
        soundManager.mixer.PlayChannel(7, soundManager.ball_sound,0);
        this->ball_collision = false;
    }
    if(!this->goal) soundManager.mixer.HaltChannel(6);
}

void World::replay(TextureManager& textureManager, SoundManager& soundManager){
    textureManager.renderer.Copy(
        textureManager.goal_sign,
        NullOpt,
        Rect(textureManager.renderer.GetOutputWidth()/2-200,
            textureManager.renderer.GetOutputHeight()/4-100,
            400,
            200));
    textureManager.renderer.Copy(textureManager.replay_sign,
                                NullOpt,
                                Rect(120,
                                    textureManager.renderer.GetOutputHeight()-225,
                                    150,
                                    100));
    if(!soundManager.mixer.IsChannelPlaying(6))
        soundManager.mixer.PlayChannel(6,soundManager.goal_sound,0);
}

void World::show_scores_and_time(TextureManager& textureManager){
    std::string red_score, blue_score, time;
    red_score = std::to_string(this->red_team_score);
    blue_score = std::to_string(this->blue_team_score);
    time = std::to_string(this->remaining_time);


    Texture red_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended(red_score, SDL_Color{255, 0, 0, 255})
        );
    Texture blue_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended(blue_score, SDL_Color{0, 0, 255, 255})
        );
    Texture time_text_sprite(
            textureManager.renderer,
            textureManager.time_font.RenderText_Blended(time, SDL_Color{255, 255, 255, 255})
        );

    //show scores
    textureManager.renderer.Copy(
        red_text_sprite, 
        NullOpt, 
        Rect(
            375, 
            120, 
            red_text_sprite.GetWidth(), 
            red_text_sprite.GetHeight()));
                                    
    textureManager.renderer.Copy(
        blue_text_sprite, 
        NullOpt, 
        Rect(
            585, 
            120, 
            blue_text_sprite.GetWidth(), 
            blue_text_sprite.GetHeight()));
    
    //show time
    textureManager.renderer.Copy(
        time_text_sprite, 
        NullOpt, 
        Rect(
            475, 
            150, 
            time_text_sprite.GetWidth(), 
            time_text_sprite.GetHeight()));
}

World::~World(){}
