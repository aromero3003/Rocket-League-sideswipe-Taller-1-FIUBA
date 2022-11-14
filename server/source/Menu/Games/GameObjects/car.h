#ifndef __CAR_H__
#define __CAR_H__

#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <box2d/b2_wheel_joint.h>
#include <box2d/b2_world.h>
#include <cstdint>

enum {LEFT, RIGHT};

class Car {
 private:
    b2Body *chassis;
    b2Body *wheel1;
    b2Body *wheel2;
    b2WheelJoint *damper1;
    b2WheelJoint *damper2;
    bool orientation;

 public:
    Car(b2World &world, const b2Vec2 &position);
    void moveLeft();
    void moveRight();
    void brake();
    void jump();
    const b2Vec2 getPosition();
    const float getAngle();
    const uint8_t getOrientation();

};

#endif  // __CAR_H__