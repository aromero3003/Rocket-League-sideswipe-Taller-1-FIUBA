#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include <box2d/b2_math.h>
#include <cstdint>
#include "car.h"
#include "ball.h"
#include <vector>

class SnapShot {
 private:
    //Car &player1;
    //Car &player2;
    //Ball &ball;
    //bool goal;
    std::vector<uint8_t> data;

    void push_in_big_endian(const float &x);

 public:
    SnapShot(Car &player1, Car &player2, Ball &ball, bool goal);
    const uint8_t *getMsg();
};

#endif  //  __SNAPSHOT_H__
