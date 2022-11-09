#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include <box2d/b2_math.h>
#include "car.h"
#include "ball.h"

class SnapShot {
 private:
    Car &player1;
    Car &player2;
    Ball &ball;
    bool goal;

 public:
    SnapShot(Car &player1, Car &player2, Ball &ball, bool goal);
    char *getMsg();
};

#endif  //  __SNAPSHOT_H__
