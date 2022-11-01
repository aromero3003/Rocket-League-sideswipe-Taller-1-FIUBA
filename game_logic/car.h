#ifndef __CAR_H__
#define __CAR_H__

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>

class Car {
 private:
    b2Body *chassis;
    b2Body *wheel1;
    b2Body *wheel2;
    b2Body *damper1;
    b2Body *damper2;
 public:
    Car(b2World &world);


};

#endif  // __CAR_H__
