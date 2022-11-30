#include "world.h"
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

void World::update(char* data){
    std::lock_guard<std::mutex> lock(mutex);
    
    //UPDATE FLAGS
    char flags = data[0];
    this->goal = (flags & (RED_GOAL_FLAG | BLUE_GOAL_FLAG)) > 0;

    //UPDATE BALL
    this->ball.x_position = FC(data+1);
    this->ball.y_position = FC(data+5);
    this->ball.angle = (-180/PI)*FC(data+9);

    this->ball.collision = (flags & BALL_COLLISION);

    //UPDATE ALL CARS
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].y_position = FC(data+((i+1)*13));
        this->cars[i].x_position = FC(data+((i+1)*13 + 4));
        this->cars[i].angle = (-180/PI)*FC(data+((i+1)*13 + 8));

        this->cars[i].pointing_right = (data[(i+1)*13 + 12] & POINTING_RIGHT);
        this->cars[i].nitro = (data[(i+1)*13 + 12] & NITRO);
    }
}

void World::draw(TextureManager& textureManager, SoundManager& soundManager){

    std::lock_guard<std::mutex> lock(mutex);
    int flip;
    int nitro_phase = (SDL_GetTicks()/100)%5;

    //Show court, always the same
    textureManager.renderer.Copy(textureManager.court, NullOpt, Rect(0,0,textureManager.renderer.GetOutputWidth(), textureManager.renderer.GetOutputHeight()));

    //Show all cars
    for(size_t i = 0; i < this->cars.size(); i++){
        textureManager.renderer.Copy(textureManager.car_texture,
                    Rect(0,(1000/12)*i,250,1000/12),
                    Rect(20*this->cars[i].x_position - 40,
                        (-20)*this->cars[i].y_position - 20,
                        80,
                        40)
                    ,this->cars[i].angle,
                    NullOpt,
                    flip = (this->cars[i].pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
        
        //show nitro if needed
        if (this->cars[i].nitro){
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
    //Show ball
    textureManager.renderer.Copy(textureManager.ball, NullOpt, Rect(20*this->ball.x_position -20,(-20)*this->ball.y_position-20, 40, 40),this->ball.angle);

    if(this->ball.collision && !soundManager.mixer.IsChannelPlaying(7)){
        soundManager.mixer.PlayChannel(7, soundManager.ball_sound,0);
        this->ball.collision = false;
    }

    if(this->goal){
        this->goal = false;
    }
}

void World::print(char *data){
    std::cout << "Flag: " << (int)data[0] << std::endl;
    std::cout << "Ball: (x,y) = (" << FC(data + 1)  << " | " <<  FC(data + 5) << ") angle: " << FC (data+9) << std::endl;
    std::cout << "car1: (x,y) = ("<< FC(data + 17) << " | " << FC(data + 13) << ") angle: " << FC (data+21) << " orientation: " << (int)data[25] << std::endl;
    std::cout << "car2: (x,y) = ("<< FC(data + 30) << " | " << FC(data + 26) << ") angle: " << FC (data+34) << " orientation: " << (int)data[38] << std::endl;
    std::cout << "Termina iteración\n" << std::endl;
}

World::~World(){}
