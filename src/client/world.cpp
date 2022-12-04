#include "world.h"
#include <iostream>
#include <string>

#define FC *(uint32_t*)
#define PI 3.14159265
using namespace SDL2pp;

World::World(){}

void World::create_cars(int n_cars){
    for(int i=0; i < n_cars; i++){
        Car new_car;
        this->cars.push_back(new_car);
    }
}

uint32_t World::bytesToInt(std::vector<char>& data, int pos){
    uint32_t value = 0;
    for (size_t i = 0; i < 4; ++i) {
        value |= static_cast<int>(data[i + pos]) << (i * 8);
    }
    return value;
}

void World::update(std::vector<char>& data){
    std::lock_guard<std::mutex> lock(mutex);
    
    //UPDATE FLAGS
    this->remaining_time = data[0];
    this->blue_team_score = data[1];
    this->red_team_score = data[2];
    this->goal = data[3];
    this->ball_collision = data[4];
    this->car_collision = data[5];

    std::cout << "          FLAGS:" << std::endl;
    std::cout << "remaining time: " << (int)this->remaining_time << std::endl;
    std::cout << "blue score: " << (int)this->blue_team_score << std::endl;
    std::cout << "red score: " << (int)this->red_team_score << std::endl;
    std::cout << "goal: " << (int)this->goal << std::endl;
    std::cout << "ball collision: " << (int)this->ball_collision << std::endl;
    std::cout << "rcar collision: " << (int)this->car_collision << std::endl << std::endl;

    //UPDATE BALL
    this->ball.x_position = bytesToInt(data, 6);
    this->ball.y_position = bytesToInt(data, 10);
    this->ball.angle = bytesToInt(data, 14);
    this->ball.color = bytesToInt(data, 18);

    std::cout << "          BALL:" << std::endl;
    std::cout << "x: " << (int)this->ball.x_position << std::endl;
    std::cout << "y: " << (int)this->ball.y_position << std::endl;
    std::cout << "angle: " << (int)this->ball.angle << std::endl;
    std::cout << "color: " << (int)this->ball.color << std::endl << std::endl;


    //UPDATE ALL CARS
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].id = data[((i+1)*19)];
        this->cars[i].x_position = bytesToInt(data, (i+1)*19 + 1);
        this->cars[i].y_position = bytesToInt(data, (i+1)*19 + 5);
        this->cars[i].angle = bytesToInt(data, (i+1)*19 + 9);
        this->cars[i].pointing_right = data[(i+1)*19 + 14];
        this->cars[i].nitro_flag = data[(i+1)*19 + 15];
        this->cars[i].nitro_quantity = bytesToInt(data, (i+1)*19 + 16);

    std::cout << "          CAR " << i << ":" << std::endl;
    std::cout << "x: " << (int)this->cars[i].x_position << std::endl;
    std::cout << "y: " << (int)this->cars[i].y_position << std::endl;
    std::cout << "angle: " << (int)this->cars[i].angle << std::endl;
    std::cout << "orientation: " << (int)this->cars[i].pointing_right << std::endl;
    std::cout << "nitroing: " << (int)this->cars[i].nitro_flag << std::endl;
    std::cout << "nitro restante: " << (int)this->cars[i].nitro_quantity << std::endl << std::endl;
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
    //Show ball
    textureManager.renderer.Copy(textureManager.ball, NullOpt, Rect(20*this->ball.x_position -20,(-20)*this->ball.y_position-20, 40, 40),this->ball.angle);

    if(this->ball_collision && !soundManager.mixer.IsChannelPlaying(7)){
        soundManager.mixer.PlayChannel(7, soundManager.ball_sound,0);
        this->ball_collision = false;
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
