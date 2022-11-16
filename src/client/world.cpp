#include "world.h"
#include <iostream>
#define FC *(float*)

World::World(){}

void World::update(char* data){
    std::lock_guard<std::mutex> lock(mutex);
    this->ball.x_position = FC(data+1);
    this->ball.y_position = FC(data+5);

    this->car1.x_position = FC(data+17);
    this->car1.y_position = FC(data+13);
    this->car1.angle = FC(data+21);
    this->car1.pointing_right = data+25;

    this->car2.x_position = FC(data+30);
    this->car2.y_position = FC(data+26);
    this->car2.angle = FC(data+34);
    this->car2.pointing_right = data+38;
}

void World::print(){
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Ball: (x,y) = (" << this->ball.x_position  << " | " <<  this->ball.y_position << ")" << std::endl;
    std::cout << "Car 1: (x,y) = ("<< this->car1.x_position << " | " << this->car1.y_position << ")" << std::endl;
    std::cout << "Car 2: (x,y) = ("<< this->car2.x_position << " | " << this->car2.y_position << ")" << std::endl;
}

void World::draw(){
    std::lock_guard<std::mutex> lock(mutex);
}
World::~World(){}