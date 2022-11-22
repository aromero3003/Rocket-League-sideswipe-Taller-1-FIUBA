#include "world.h"
#include <iostream>
#include <string>
#define FC *(float*)

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
    this->goal = (flags && GOAL_FLAG);
    this->nitro = (flags && NITRO_FLAG);
    this->car_ball_collision = (flags && CAR_BALL_COLLISION);
    this->car_terrain_collision = (flags && CAR_TERRAIN_COLLISION);
    this->ball_terrain_collision = (flags && BALL_TERRAIN_COLLISION);

    //UPDATE BALL
    this->ball.x_position = FC(data+1);
    this->ball.y_position = FC(data+5);
    this->ball.angle = FC(data+9);

    //UPDATE ALL CARS
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].y_position = FC(data+((i+1)*13));
        this->cars[i].x_position = FC(data+((i+1)*13 + 4));
        this->cars[i].angle = FC(data+((i+1)*13 + 8));
        this->cars[i].pointing_right = data[(i+1)*13 + 12];
    }
}

void World::draw(std::vector<Texture>& car_textures, Texture& ball, Texture& court, Renderer& renderer){
    std::lock_guard<std::mutex> lock(mutex);
    int flip;

    //Show court, always the same
    renderer.Copy(court,NullOpt,Rect(0,0,renderer.GetOutputWidth(),renderer.GetOutputHeight()));

    //Show all cars
    for(size_t i = 0; i < car_textures.size(); i++){
        renderer.Copy(car_textures[i],
                    Rect(0,(1000/12)*i,250,1000/12),
                    Rect(20*this->cars[i].x_position - 30,
                        (-20)*this->cars[i].y_position - 15,
                        60,
                        30)
                    ,this->cars[i].angle,
                    NullOpt,
                    flip = (this->cars[i].pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    }

    //Show ball
    renderer.Copy(ball, NullOpt, Rect(20*this->ball.x_position -20,(-20)*this->ball.y_position-20, 40, 40));
}


void World::print(){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Ball: (x,y) = (" << this->ball.x_position  << " | " <<  this->ball.y_position << ")" << std::endl;
    std::cout << "Car 1: (x,y) = ("<< this->cars[0].x_position << " | " << this->cars[0].y_position << ")" << std::endl;
    std::cout << "Car 2: (x,y) = ("<< this->cars[1].x_position << " | " << this->cars[1].y_position << ")" << std::endl;

}

World::~World(){}
