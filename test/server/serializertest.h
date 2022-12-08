
#include <cxxtest/TestSuite.h>
#include <vector>
#include "../../src/server/Menu/Client/Snap.h"

#define FLOAT_CAST(n) (*(float*)(n))

// TEST FLAGS
#define TEST_TIME_LEFT 180
#define TEST_RED_SCORE 4
#define TEST_BLUE_SCORE 4
#define TEST_GOAL true
#define TEST_BALL_COLLISION false
#define TEST_CAR_COLLISION false

// TEST BALL
#define TEST_BALL_POSITION_X 20.0f
#define TEST_BALL_POSITION_Y 10.0f
#define TEST_BALL_ANGLE 6.2830f
#define TEST_BALL_COLOR 0

// TEST CAR
#define TEST_CAR_ID 1
#define TEST_CAR_POS_X 1.0f
#define TEST_CAR_POS_Y -5.0f
#define TEST_CAR_ANGLE 3.1415f
#define TEST_CAR_ORIENTATION 1
#define TEST_CAR_NITRO_ON true
#define TEST_CAR_NITRO_AMMOUNT 255

typedef enum {NO_SHOT, GOLD_SHOT, PURPLE_SHOT, RED_SHOT} test_shot_t;

class SnapshotTest : public CxxTest::TestSuite {
 private:
    struct FlagsDataObject {
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
        bool nitro;
        uint8_t nitro_ammount;
    };

 public:
    void testSnapShot(void) {
        FlagsDataObject expectedFlags{
            TEST_TIME_LEFT,
            TEST_BLUE_SCORE,
            TEST_RED_SCORE,
            TEST_GOAL,
            TEST_BALL_COLLISION,
            TEST_CAR_COLLISION
        };

        BallDataObject expectedBall{
            TEST_BALL_POSITION_X,
            TEST_BALL_POSITION_Y,
            TEST_BALL_ANGLE,
            TEST_BALL_COLOR
        };

        CarDataObject expectedCar{
            TEST_CAR_ID,
            TEST_CAR_POS_X,
            TEST_CAR_POS_Y,
            TEST_CAR_ANGLE,
            TEST_CAR_NITRO_ON,
            TEST_CAR_ORIENTATION,
            TEST_CAR_NITRO_AMMOUNT
        };


        SnapShot ss;

        // Flags
        ss.add(expectedFlags.remaining_time);
        ss.add(expectedFlags.blue_team_score);
        ss.add(expectedFlags.red_team_score);
        ss.add(expectedFlags.goal);
        ss.add(expectedFlags.ball_collision);
        ss.add(expectedFlags.car_collision);

        // Ball
        ss.add(expectedBall.position_x);
        ss.add(expectedBall.position_y);
        ss.add(expectedBall.angle);
        ss.add(expectedBall.color);

        // Car
        ss.add(expectedCar.id);
        ss.add(expectedCar.position_x);
        ss.add(expectedCar.position_y);
        ss.add(expectedCar.angle);
        ss.add((uint8_t)expectedCar.pointing_right);
        ss.add((uint8_t)expectedCar.nitro);
        ss.add(expectedCar.nitro_ammount);


        std::vector<uint8_t> &data = ss.getMsg();

        FlagsDataObject gottenFlags;
        gottenFlags.remaining_time = data[0];
        gottenFlags.blue_team_score = data[1];
        gottenFlags.red_team_score = data[2];
        gottenFlags.goal = data[3];
        gottenFlags.ball_collision = data[4];
        gottenFlags.car_collision = data[5];

        BallDataObject gottenBall;
        gottenBall.position_x = FLOAT_CAST(&data[6]);
        gottenBall.position_y = FLOAT_CAST(&data[10]);
        gottenBall.angle = FLOAT_CAST(&data[14]);
        gottenBall.color = data[18];

        CarDataObject gottenCar;

        gottenCar.id = (uint8_t)data[19];
        gottenCar.position_x = FLOAT_CAST(&data[20]);
        gottenCar.position_y = FLOAT_CAST(&data[24]);
        gottenCar.angle = FLOAT_CAST(&data[28]);
        gottenCar.pointing_right = (uint8_t) data[32];
        gottenCar.nitro = (uint8_t) data[33];
        gottenCar.nitro_ammount = data[34];




        TS_ASSERT_EQUALS(TEST_TIME_LEFT, gottenFlags.remaining_time);
        TS_ASSERT_EQUALS(TEST_BLUE_SCORE, gottenFlags.blue_team_score);
        TS_ASSERT_EQUALS(TEST_RED_SCORE, gottenFlags.red_team_score);
        TS_ASSERT_EQUALS(TEST_GOAL, gottenFlags.goal);
        TS_ASSERT_EQUALS(TEST_BALL_COLLISION, gottenFlags.ball_collision);
        TS_ASSERT_EQUALS(TEST_CAR_COLLISION, gottenFlags.car_collision);

        TS_ASSERT_EQUALS(TEST_BALL_POSITION_X, gottenBall.position_x);
        TS_ASSERT_EQUALS(TEST_BALL_POSITION_Y, gottenBall.position_y);
        TS_ASSERT_EQUALS(TEST_BALL_ANGLE ,gottenBall.angle);
        TS_ASSERT_EQUALS(TEST_BALL_COLOR, gottenBall.color);

        TS_ASSERT_EQUALS(TEST_CAR_ID, gottenCar.id);
        TS_ASSERT_EQUALS(TEST_CAR_POS_X, gottenCar.position_x);
        TS_ASSERT_EQUALS(TEST_CAR_POS_Y, gottenCar.position_y);
        TS_ASSERT_EQUALS(TEST_CAR_ANGLE, gottenCar.angle);
        TS_ASSERT_EQUALS(TEST_CAR_ORIENTATION, gottenCar.pointing_right);
        TS_ASSERT_EQUALS(TEST_CAR_NITRO_ON, gottenCar.nitro);
        TS_ASSERT_EQUALS(TEST_CAR_NITRO_AMMOUNT, gottenCar.nitro_ammount);
    }
};
