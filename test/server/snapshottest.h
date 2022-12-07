#include <cstdint>
#include <cxxtest/TestSuite.h>
#include <vector>
#include "../../src/server/Menu/Client/Snap.h"

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
#define TEST_ID 1
#define TEST_POS_X 1.0f
#define TEST_POS_Y -5.0f
#define TEST_ANGLE 3.1415f
#define TEST_ORIENTATION 1
#define TEST_NITRO_ON true
#define TEST_NITRO_AMMOUNT 255

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
        bool orientation;
        bool nitro;
        uint8_t nitro_ammount;
    };

 public:
    void testSnapShot(void) {
        FooFlags someFooFlags{
            TEST_TIME_LEFT,
            TEST_BLUE_SCORE,
            TEST_RED_SCORE,
            TEST_GOAL,
            TEST_BALL_COLLISION,
            TEST_CAR_COLLISION
        };

        FooBall aFooBall{
            TEST_BALL_POSITION_X,
            TEST_BALL_POSITION_Y,
            TEST_BALL_ANGLE,
            TEST_BALL_COLOR
        };

        FooCar aFooCar{
            TEST_ID,
            TEST_POS_X,
            TEST_POS_Y,
            TEST_ANGLE,
            TEST_NITRO_ON,
            TEST_ORIENTATION,
            TEST_NITRO_AMMOUNT
        };

        SnapShot ss;

        // Flags
        ss.add(someFooFlags.remaining_time);
        ss.add(someFooFlags.blue_team_score);
        ss.add(someFooFlags.red_team_score);
        ss.add(someFooFlags.goal);
        ss.add(someFooFlags.ball_collision);

        // Car
        ss.add(aFooCar.id);
        ss.add(aFooCar.position_x);
        ss.add(aFooCar.position_y);
        ss.add(aFooCar.angle);
        ss.add((uint8_t)aFooCar.orientation);
        ss.add((uint8_t)aFooCar.nitro);
        ss.add(aFooCar.nitro_ammount);

        std::vector<uint8_t> &data = ss.getMsg();
    }
};
