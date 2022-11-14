#include "car.h"

Car::Car(){
    this->facingLeft = false;
    this->x = 320;
    this->y = 480;
    this->animation = 0;
}


void Car::update(float dt) {
    if (moving) {
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}


void Car::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Car::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Car::stopMoving() {
    moving = false;
}

Car::~Car(){
    
}