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
/*
    std::cout << "          FLAGS:" << std::endl;
    std::cout << "remaining time: " << (int)this->remaining_time << std::endl;
    std::cout << "blue score: " << (int)this->blue_team_score << std::endl;
    std::cout << "red score: " << (int)this->red_team_score << std::endl;
    std::cout << "goal: " << (int)this->goal << std::endl;
    std::cout << "ball collision: " << (int)this->ball_collision << std::endl;
    std::cout << "rcar collision: " << (int)this->car_collision << std::endl << std::endl;
*/
    //UPDATE BALL
    this->ball.x_position = FC(buf+6);
    this->ball.y_position = FC(buf+10);
    this->ball.angle = (-180/PI)*FC(buf+14);
    this->ball.color = data[18];//bytesToInt(data, 18);
/*
    std::cout << "          BALL:" << std::endl;
    std::cout << "x: " << this->ball.x_position << std::endl;
    std::cout << "y: " << this->ball.y_position << std::endl;
    std::cout << "angle: " << this->ball.angle << std::endl;
    std::cout << "color: " << this->ball.color << std::endl << std::endl;

*/
    //UPDATE ALL CARS
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].id = (uint8_t) data[((i) * 16 + 19)];
        this->cars[i].x_position = FC(buf + (i*16 + 20));
        this->cars[i].y_position = FC(buf + (i*16 + 24));
        this->cars[i].angle = (-180/PI)*FC(buf + (i*16 + 28));
        this->cars[i].pointing_right = (uint8_t) data[i*16 + 32];
        this->cars[i].nitro_flag = (uint8_t) data[i*16 + 33];
        this->cars[i].nitro_quantity = FC(buf + (i*16 + 34));
/*
        std::cout << "          CAR " << i << ":" << std::endl;
        std::cout << "x: " << this->cars[i].x_position << std::endl;
        std::cout << "y: " << this->cars[i].y_position << std::endl;
        std::cout << "angle: " << this->cars[i].angle << std::endl;
        std::cout << "orientation: " << this->cars[i].pointing_right << std::endl;
        std::cout << "nitroing: " << this->cars[i].nitro_flag << std::endl;
        std::cout << "nitro restante: " << this->cars[i].nitro_quantity << std::endl << std::endl;
*/
    }
}

void World::draw(TextureManager& textureManager, SoundManager& soundManager){

    std::lock_guard<std::mutex> lock(mutex);

    //Show court, always the same
    show_court(textureManager);

    //Show scores and time
    show_scores_and_time(textureManager);

    //replay
    if (this->goal)
        replay(textureManager, soundManager);

    //Show all cars
    show_cars(textureManager, soundManager);
    
    //Show ball
    show_ball(textureManager);

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

void World::show_cars(TextureManager& textureManager, SoundManager& soundManager){

    int flip;
    int nitro_phase = (SDL_GetTicks()/100)%5;

    for(size_t i = 0; i < this->cars.size(); i++){
        textureManager.renderer.Copy(
            textureManager.car_texture,
            Rect(0,(1000/12)*i,250,1000/12),
            Rect(20*this->cars[i].x_position - 40,
                (-20)*this->cars[i].y_position - 20,
                80,
                40)
            ,this->cars[i].angle,
            NullOpt,
            flip = (this->cars[i].pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
        if(i%2 == 0){
            textureManager.renderer.Copy(
                textureManager.red_triangle,
                NullOpt,
                Rect(20*this->cars[i].x_position - 10,
                    (-20)*this->cars[i].y_position - 40,
                    15,
                    15),
                0,
                NullOpt,
                SDL_FLIP_VERTICAL);
        }
        if(i%2 == 1){
            textureManager.renderer.Copy(
                textureManager.blue_triangle,
                NullOpt,
                Rect(20*this->cars[i].x_position - 10,
                    (-20)*this->cars[i].y_position - 40,
                    15,
                    15),
                0,
                NullOpt,
                SDL_FLIP_VERTICAL);
        }
        
        //show nitro if needed
        if (this->cars[i].nitro_flag){
        textureManager.renderer.Copy(textureManager.nitro,
                    Rect(0,83*nitro_phase,335,83),
                    Rect(20*this->cars[i].x_position - 67,(-20)*this->cars[i].y_position - 20,134,40), 
                    this->cars[i].angle,
                    NullOpt,
                    flip = (this->cars[i].pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
        if(!soundManager.mixer.IsChannelPlaying(i)){
            soundManager.mixer.PlayChannel(i,soundManager.nitro_sound,0);
        }
        } else {soundManager.mixer.HaltChannel(i);}
    }
}

void World::show_ball(TextureManager& textureManager){
    textureManager.renderer.Copy(
        textureManager.ball, 
        NullOpt, 
        Rect(20*this->ball.x_position -20,(-20)*this->ball.y_position-20, 40, 40),
        this->ball.angle); 
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
