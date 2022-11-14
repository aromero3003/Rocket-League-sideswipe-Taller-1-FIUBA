#ifndef __BALL_H__
#define __BALL_H__

#include <box2d/b2_body.h>
#include <box2d/b2_math.h>

class Ball {
 private:
    b2Body *ball;

 public:
    Ball(b2World &world, float x, float y);
    const b2Vec2 getPosition();
    const float getAngle();
    // getSnapshotData
};

#endif
