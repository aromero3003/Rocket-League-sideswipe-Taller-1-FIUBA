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

    this->ball.x_position = FC(data+1);
    this->ball.y_position = FC(data+5);

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
    renderer.Copy(court,NullOpt,Rect(0,0,renderer.GetOutputWidth(),renderer.GetOutputHeight()));
    for(size_t i = 0; i < car_textures.size(); i++){
        renderer.Copy(car_textures[i],
                    Rect(0,50*i,120,50),
                    Rect(renderer.GetOutputWidth()/2 + 20*this->cars[i].x_position - 30,
                        renderer.GetOutputHeight()/2 + 280  + (-20)*this->cars[i].y_position - 18,
                        60,
                        36),
                this->cars[i].angle, 
                NullOpt,
                flip = (this->cars[i].pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
                );
    }
    renderer.Copy(ball, 
                NullOpt, 
                Rect(renderer.GetOutputWidth()/2 + 20*this->ball.x_position - 20,
                    renderer.GetOutputHeight() + (-20)*this->ball.y_position - 20, 
                    40, 40));
}


void World::print(){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Ball: (x,y) = (" << this->ball.x_position  << " | " <<  this->ball.y_position << ")" << std::endl;
    std::cout << "Car 1: (x,y) = ("<< this->cars[0].x_position << " | " << this->cars[0].y_position << ")" << std::endl;
    std::cout << "Car 2: (x,y) = ("<< this->cars[1].x_position << " | " << this->cars[1].y_position << ")" << std::endl;

}

World::~World(){}
