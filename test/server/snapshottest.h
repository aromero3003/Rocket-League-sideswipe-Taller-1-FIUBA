#include <cstdint>
#include <cxxtest/TestSuite.h>
#include <vector>
#include "../../src/server/Menu/Client/Snap.h"


#define ID 1
#define POS_X 1.0f
#define POS_Y -5.0f
#define ANGLE 3.1415f
#define ORIENTATION 1
#define NITRO_ON true
#define NITRO_AMMOUNT 255

typedef enum {NO_SHOT, GOLD_SHOT, PURPLE_SHOT, RED_SHOT} test_shot_t;

class SnapshotTest : public CxxTest::TestSuite {
 private:
    struct FooCar {
        uint8_t id;
        float position_x;
        float position_y;
        float angle;
        bool orientation;
        bool nitro;
        uint8_t nitro_ammount;
    };

    struct FooBall {
        float position_x;
        float position_y;
        float angle;
        uint8_t color;
    };

 public:
    void testSnapShot(void) {
        FooCar aFooCar = {ID, POS_X, POS_Y, ANGLE, NITRO_ON, ORIENTATION, NITRO_AMMOUNT};
        SnapShot ss;
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
