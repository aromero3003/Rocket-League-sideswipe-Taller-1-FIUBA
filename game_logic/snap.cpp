#include <box2d/b2_math.h>
#include "car.h"
#include "ball.h"
#include "snap.h"
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <vector>

void SnapShot::push_in_big_endian(const float &x) {
    uint32_t *float_addr_as_int_addr = (uint32_t *)&x;

    uint32_t float_converted = htonl(*float_addr_as_int_addr);
    for(int i = 0; i < 4; i++)
        this->data.push_back(((uint8_t *)&float_converted)[i]);
}

//SnapShot::SnapShot(Car &player1, Car &player2, Ball &ball, bool goal) : player1(player1), player2(player2), ball(ball), goal(goal) {
SnapShot::SnapShot(Car &player1, Car &player2, Ball &ball, bool goal) {
    this->data.push_back(goal);
    float xb = ball.getPosition().x, yb = ball.getPosition().y;
    float x1 = player1.getPosition().x, y1 = player1.getPosition().y;
    float x2 = player2.getPosition().x, y2 = player2.getPosition().y;

    this->data.push_back(goal);

    this->push_in_big_endian(xb);
    this->push_in_big_endian(yb);
    this->push_in_big_endian(ball.getAngle());

    this->push_in_big_endian(x1);
    this->push_in_big_endian(y1);
    this->push_in_big_endian(player1.getAngle());
    this->data.push_back(player1.getOrientation());

    this->push_in_big_endian(x2);
    this->push_in_big_endian(y2);
    this->push_in_big_endian(player2.getAngle());
    this->data.push_back(player1.getOrientation());
}

const uint8_t *SnapShot::getMsg() {
    // 1 byte flag de gol
    //
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
    return this->data.data();
}
