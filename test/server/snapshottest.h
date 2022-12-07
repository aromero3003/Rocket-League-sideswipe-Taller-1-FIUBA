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
    struct FooFlags {
        uint8_t remaining_time;
        uint8_t blue_team_score;
        uint8_t red_team_score;
        uint8_t goal;
        uint8_t ball_collision;
        uint8_t car_collision;
    };

    struct FooBall {
        float position_x;
        float position_y;
        float angle;
        uint8_t color;
    };

    struct FooCar {
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
        FooFlags expectedFooFlags{
            TEST_TIME_LEFT,
            TEST_BLUE_SCORE,
            TEST_RED_SCORE,
            TEST_GOAL,
            TEST_BALL_COLLISION,
            TEST_CAR_COLLISION
        };

        FooBall expectedFooBall{
            TEST_BALL_POSITION_X,
            TEST_BALL_POSITION_Y,
            TEST_BALL_ANGLE,
            TEST_BALL_COLOR
        };

        FooCar expectedFooCar{
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
        ss.add(expectedFooFlags.remaining_time);
        ss.add(expectedFooFlags.blue_team_score);
        ss.add(expectedFooFlags.red_team_score);
        ss.add(expectedFooFlags.goal);
        ss.add(expectedFooFlags.ball_collision);
        ss.add(expectedFooFlags.car_collision);

        // Ball
        ss.add(expectedFooBall.position_x);
        ss.add(expectedFooBall.position_y);
        ss.add(expectedFooBall.angle);
        ss.add(expectedFooBall.color);

        // Car
        ss.add(expectedFooCar.id);
        ss.add(expectedFooCar.position_x);
        ss.add(expectedFooCar.position_y);
        ss.add(expectedFooCar.angle);
        ss.add((uint8_t)expectedFooCar.pointing_right);
        ss.add((uint8_t)expectedFooCar.nitro);
        ss.add(expectedFooCar.nitro_ammount);


        std::vector<uint8_t> &data = ss.getMsg();

        FooFlags gottenFooFlags;
        gottenFooFlags.remaining_time = data[0];
        gottenFooFlags.blue_team_score = data[1];
        gottenFooFlags.red_team_score = data[2];
        gottenFooFlags.goal = data[3];
        gottenFooFlags.ball_collision = data[4];
        gottenFooFlags.car_collision = data[5];

        FooBall gottenFooBall;
        gottenFooBall.position_x = FLOAT_CAST(&data[6]);
        gottenFooBall.position_y = FLOAT_CAST(&data[10]);
        gottenFooBall.angle = FLOAT_CAST(&data[14]);
        gottenFooBall.color = data[18];

        FooCar gottenFooCar;

        gottenFooCar.id = (uint8_t)data[19];
        gottenFooCar.position_x = FLOAT_CAST(&data[20]);
        gottenFooCar.position_y = FLOAT_CAST(&data[24]);
        gottenFooCar.angle = FLOAT_CAST(&data[28]);
        gottenFooCar.pointing_right = (uint8_t) data[32];
        gottenFooCar.nitro = (uint8_t) data[33];
        gottenFooCar.nitro_ammount = data[34];




        TS_ASSERT_EQUALS(TEST_TIME_LEFT, gottenFooFlags.remaining_time);
        TS_ASSERT_EQUALS(TEST_BLUE_SCORE, gottenFooFlags.blue_team_score);
        TS_ASSERT_EQUALS(TEST_RED_SCORE, gottenFooFlags.red_team_score);
        TS_ASSERT_EQUALS(TEST_GOAL, gottenFooFlags.goal);
        TS_ASSERT_EQUALS(TEST_BALL_COLLISION, gottenFooFlags.ball_collision);
        TS_ASSERT_EQUALS(TEST_CAR_COLLISION, gottenFooFlags.car_collision);

        TS_ASSERT_EQUALS(TEST_BALL_POSITION_X, gottenFooBall.position_x);
        TS_ASSERT_EQUALS(TEST_BALL_POSITION_Y, gottenFooBall.position_y);
        TS_ASSERT_EQUALS(TEST_BALL_ANGLE ,gottenFooBall.angle);
        TS_ASSERT_EQUALS(TEST_BALL_COLOR, gottenFooBall.color);

        TS_ASSERT_EQUALS(TEST_CAR_ID, gottenFooCar.id);
        TS_ASSERT_EQUALS(TEST_CAR_POS_X, gottenFooCar.position_x);
        TS_ASSERT_EQUALS(TEST_CAR_POS_Y, gottenFooCar.position_y);
        TS_ASSERT_EQUALS(TEST_CAR_ANGLE, gottenFooCar.angle);
        TS_ASSERT_EQUALS(TEST_CAR_ORIENTATION, gottenFooCar.pointing_right);
        TS_ASSERT_EQUALS(TEST_CAR_NITRO_ON, gottenFooCar.nitro);
        TS_ASSERT_EQUALS(TEST_CAR_NITRO_AMMOUNT, gottenFooCar.nitro_ammount);
    }
};
