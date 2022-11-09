#include <box2d/b2_math.h>
#include "car.h"
#include "ball.h"
#include "snap.h"

SnapShot::SnapShot(Car &player1, Car &player2, Ball &ball, bool goal) :
    player1(player1), player2(player2), ball(ball), goal(goal) {}

char *SnapShot::getMsg() {
    float x1 = player1.getPosition().x, y1 = player1.getPosition().y;
    float x2 = player2.getPosition().x, y2 = player2.getPosition().y;
    char msg[20];  // número inventado
    msg[0] = goal;
    *(int *)(msg + 1) = x1;
    // 4 bytes pelota angulo (float)
    // 4 bytes pelota x (float)
    // 4 bytes pelota y (float)
    //
    // 4 bytes auto1 angulo (float)
    // 4 bytes auto1 x (float)
    // 4 bytes auto1 y (float)
    // 1 byte orientación
    //
    // 4 bytes auto2 angulo (float)
    // 4 bytes auto2 x (float)
    // 4 bytes auto2 y (float)
    // 1 byte orientación
    return msg;
}
