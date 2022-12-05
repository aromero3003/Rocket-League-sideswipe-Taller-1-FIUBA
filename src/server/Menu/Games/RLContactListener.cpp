#include "RLContactListener.h"
#include <iostream>
#include <box2d/box2d.h>
#include "GameObjects/car.h"

void RLContactListener::BeginContact(b2Contact *c) {
    std::cout << "inicio" << std::endl;
}

void RLContactListener::EndContact(b2Contact *c) {
    std::cout << "fin" << std::endl;
}
