#include "world.h"

World::World(){}

void World::update(){
    std::lock_guard<std::mutex> lock(mutex);
}

void World::draw(){
    std::lock_guard<std::mutex> lock(mutex);
}
World::~World(){}