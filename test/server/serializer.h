#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <netinet/in.h>
#include <vector>


struct MatchDataObject {
    uint8_t remaining_time;
    uint8_t blue_team_score;
    uint8_t red_team_score;
    uint8_t goal;
    uint8_t ball_collision;
    uint8_t car_collision;
};

struct BallDataObject {
    float position_x;
    float position_y;
    float angle;
    uint8_t color;
};

struct CarDataObject {
    uint8_t id;
    float position_x;
    float position_y;
    float angle;
    bool pointing_right;
    bool nitro_status;
    uint8_t nitro_ammount;
};


struct Snap {
    MatchDataObject matchData;
    BallDataObject ballData;
    std::vector<CarDataObject> carsData;
};

#define PRESITION_SENDED 10000

class Serializer {
 private:
    std::vector<uint8_t> serialized_data;

    void serialize(float &x) {
        uint32_t float_value_as_int = x * PRESITION_SENDED;
        float_value_as_int = htonl(float_value_as_int);
        uint8_t *float_bytes = reinterpret_cast<uint8_t*>(&float_value_as_int);
        for (uint8_t i = 0; i < sizeof(uint32_t); i++)
            this->serialized_data.push_back(float_bytes[i]);
    }

    void serialize(MatchDataObject &matchData) {
        this->serialized_data.push_back(matchData.remaining_time);
        this->serialized_data.push_back(matchData.blue_team_score);
        this->serialized_data.push_back(matchData.red_team_score);
        this->serialized_data.push_back(matchData.goal);
        this->serialized_data.push_back(matchData.car_collision);
        this->serialized_data.push_back(matchData.ball_collision);
    }

    void serialize(BallDataObject &ballData) {
        this->serialize(ballData.position_x);
        this->serialize(ballData.position_y);
        this->serialize(ballData.angle);
        serialized_data.push_back(ballData.color);
    }

    void serialize(CarDataObject &carData) {
        this->serialized_data.push_back(carData.id);
        this->serialize(carData.position_x);
        this->serialize(carData.position_y);
        this->serialize(carData.angle);
        this->serialized_data.push_back(carData.pointing_right);
        this->serialized_data.push_back(carData.nitro_status);
        this->serialized_data.push_back(carData.nitro_ammount);
    }

 public:

    std::vector<uint8_t> serializeGameData(SnapShot &s) {
        this->serialize(s.matchData);
        this->serialize(s.ballData);
        for (CarDataObject &carData : s.carsData)
            this->serialize(carData);
    }
};


#endif /* SERIALIZER_H*/
