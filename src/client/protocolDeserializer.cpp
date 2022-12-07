#include "protocolDeserializer.h"

uint8_t ProtocolDeserializer::deserialize_time(char* data){
    return data[0];
}

uint8_t ProtocolDeserializer::deserialize_blue_team_score(char* data){
    return data[1];
}

uint8_t ProtocolDeserializer::deserialize_red_team_score(char* data){
    return data[2];
}

uint8_t ProtocolDeserializer::deserialize_goal_flag(char* data){
    return data[3];
}

uint8_t ProtocolDeserializer::deserialize_ball_collision_flag(char* data){
    return data[4];
}

uint8_t ProtocolDeserializer::deserialize_car_collision_flag(char* data){
    return data[5];
}

void ProtocolDeserializer::deserialize_ball(Ball& ball, char* data){
    ball.x_position = FC(data + 6);
    ball.y_position = FC(data + 10);
    ball.angle = (-180/PI)*FC(data + 14);
    ball.color = data[18];
}

void ProtocolDeserializer::deserialize_cars(std::vector<Car>& cars, char* data){
    for(size_t i=0; i < cars.size(); i++){
        cars[i].id = (uint8_t) data[((i) * 16 + 19)];
        cars[i].x_position = FC(data + (i*16 + 20));
        cars[i].y_position = FC(data + (i*16 + 24));
        cars[i].angle = (-180/PI)*FC(data + (i*16 + 28));
        cars[i].pointing_right = (uint8_t) data[i*16 + 32];
        cars[i].nitro_flag = (uint8_t) data[i*16 + 33];
        cars[i].nitro_quantity = data[i*16 + 34];
    }
}