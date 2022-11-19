#include "world.h"
#include <iostream>
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
    this->ball.x_position = FC(data+1);
    this->ball.y_position = FC(data+5);

    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].y_position = FC(data+(i*13));
        this->cars[i].x_position = FC(data+(i*13 + 4));
        this->cars[i].angle = FC(data+(i*13 + 8));
        this->cars[i].pointing_right = data+(i*13 + 12);
    }
/*
    this->car1.x_position = FC(data+17);
    this->car1.y_position = FC(data+13);
    this->car1.angle = FC(data+21);
    this->car1.pointing_right = data[25];

    this->car2.x_position = FC(data+30);
    this->car2.y_position = FC(data+26);
    this->car2.angle = FC(data+34);
    this->car2.pointing_right = data+38;
*/
}

void World::print(){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Ball: (x,y) = (" << this->ball.x_position  << " | " <<  this->ball.y_position << ")" << std::endl;
    //std::cout << "Ball: (x,y) = (" << this->ball.x_position  << " | " <<  this->ball.y_position << ")" << std::endl;
    std::cout << "Car 1: (x,y) = ("<< this->cars[0].x_position << " | " << this->cars[0].y_position << ")" << std::endl;
    std::cout << "Car 2: (x,y) = ("<< this->cars[1].x_position << " | " << this->cars[1].y_position << ")" << std::endl;
    //std::cout << "Car 2: (x,y) = ("<< this->car2.x_position << " | " << this->car2.y_position << ")" << std::endl;
}

void World::draw(std::vector<Texture>& car_textures, Texture& ball, Texture& court, Renderer& renderer){

    std::lock_guard<std::mutex> lock(mutex);
    renderer.Copy(court,NullOpt,Rect(0,0,renderer.GetOutputWidth(),renderer.GetOutputHeight()));

    for(size_t i = 0; i < car_textures.size(); i++){
        renderer.Copy(car_textures[i],
                    Rect(0,50*i,120,50),
                    Rect(renderer.GetOutputWidth()/2 + 20* this->cars[i].x_position,
                        renderer.GetOutputHeight()/2  + (20)*this->cars[i].y_position,
                        120,
                        50),
                this->cars[i].angle, 
                NullOpt, 
                SDL_FLIP_NONE
                );
    }
    /*
    renderer.Copy(car,
                Rect(120,110,120,50),
                Rect(renderer.GetOutputWidth()/2 + 10* this->car1.x_position,
                    renderer.GetOutputHeight()/2 + 120 + (-5)*this->car1.y_position,
                    120,
                    50),
                this->car1.angle, 
                NullOpt, 
                SDL_FLIP_NONE
                );
    renderer.Copy(car,
                Rect(250,220,120,50), 
                Rect(renderer.GetOutputWidth()/2 + 10*this->car2.x_position,
                    renderer.GetOutputHeight()/2 + 120 + (-5)*this->car2.y_position,
                    120,
                    50),
                this->car2.angle,
                NullOpt,
                SDL_FLIP_HORIZONTAL);
    */
    renderer.Copy(ball, 
                NullOpt, 
                Rect(renderer.GetOutputWidth()/2 + this->ball.x_position,
                    renderer.GetOutputHeight()/2 + (-1)*this->ball.y_position, 
                    50, 50));
}
World::~World(){}
