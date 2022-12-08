#ifndef DESERIALIZER_H
#define DESERIALIZER_H

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

class Deserializer {
 private:
    std::vector<uint8_t> deserialized_data;

    void deserialize(uint32_t &x) {
        uint32_t float_value_as_int = x * PRESITION_SENDED;
        float_value_as_int = htonl(float_value_as_int);
        uint8_t *float_bytes = reinterpret_cast<uint8_t*>(&float_value_as_int);
        for (uint8_t i = 0; i < sizeof(uint32_t); i++)
            this->deserialized_data.push_back(float_bytes[i]);
    }

    void deserialize(MatchDataObject &matchData) {
        this->deserialized_data.push_back(matchData.remaining_time);
        this->deserialized_data.push_back(matchData.blue_team_score);
        this->deserialized_data.push_back(matchData.red_team_score);
        this->deserialized_data.push_back(matchData.goal);
        this->deserialized_data.push_back(matchData.car_collision);
        this->deserialized_data.push_back(matchData.ball_collision);
    }

    void deserialize(BallDataObject &ballData) {
        this->deserialize(ballData.position_x);
        this->deserialize(ballData.position_y);
        this->deserialize(ballData.angle);
        deserialized_data.push_back(ballData.color);
    }

    void deserialize(CarDataObject &carData) {
        this->deserialized_data.push_back(carData.id);
        this->deserialize(carData.position_x);
        this->deserialize(carData.position_y);
        this->deserialize(carData.angle);
        this->deserialized_data.push_back(carData.pointing_right);
        this->deserialized_data.push_back(carData.nitro_status);
        this->deserialized_data.push_back(carData.nitro_ammount);
    }

 public:

    Snap deserializeGameData(std::vector<uint8_t> &data) {
        this->deserializeMatchData();
        this->deserializeBallData(data);
        for (CarDataObject &carData : s.carsData)
            this->deserialize(carData);
    }
};


#endif /* DESERIALIZER_H*/
