#ifndef PROTOCOL_DESERIALIZER_H
#define PROTOCOL_DESERIALIZER_H

#include <cstdint>
#include "ball.h"
#include "car.h"

#define FC *(float*)
#define PI 3.14159265

class ProtocolDeserializer{
    public:

    static uint8_t deserialize_time(char* data);

    static uint8_t deserialize_blue_team_score(char* data);

    static uint8_t deserialize_red_team_score(char* data);

    static uint8_t deserialize_goal_flag(char* data);

    static uint8_t deserialize_ball_collision_flag(char* data);

    static uint8_t deserialize_car_collision_flag(char* data);

    static void deserialize_ball(Ball& ball, char* data);

    static void deserialize_cars(std::vector<Car>& cars, char* data);

};

#endif