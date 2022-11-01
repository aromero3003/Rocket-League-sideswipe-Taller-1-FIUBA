#ifndef __BALL_H__
#define __BALL_H__

#include <box2d/b2_body.h>

class Ball {
 private:
    b2Body *ball;

 public:
    Ball(b2World &world, float x, float y);
    // getSnapshotData
};

#endif
