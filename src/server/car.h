#ifndef CAR_H
#define CAR_H

#include <SDL2pp/SDL2pp.hh>

class Car {
public:
    Car();
    ~Car();
    void update(float dt);
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    bool facingLeft;
    bool moving;
    int speed;
    int animation;
    int x;
    int y;
};

#endif