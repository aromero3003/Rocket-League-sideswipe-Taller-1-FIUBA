#include "RLContactListener.h"
#include <iostream>
#include <box2d/box2d.h>
#include "GameObjects/car.h"
void RLContactListener::BeginContact(b2Contact *c) {
    uint16_t mask_A = c->GetFixtureA()->GetFilterData().categoryBits;

    b2Fixture *other_fixture = (mask_A == BALL_BITS ? c->GetFixtureB() : c->GetFixtureA());
    uint16_t other_mask = other_fixture->GetFilterData().categoryBits;
    std::string s = "no";
    if (other_mask == FRONT_SENSOR_BITS) {
        ((Car *)other_fixture->GetUserData().pointer)->setActiveSensor(FRONT_SENSOR);
        s = "FRONT";
    }else if (other_mask == BACK_SENSOR_BITS) {
        ((Car *)other_fixture->GetUserData().pointer)->setActiveSensor(BACK_SENSOR);
        s = "BACK";
    }else if (other_mask == DOWN_SENSOR_BITS) {
        ((Car *)other_fixture->GetUserData().pointer)->setActiveSensor(DOWN_SENSOR);
        s = "DOWN_SENSOR";
    }
    std::cout << s << std::endl;
}

void RLContactListener::EndContact(b2Contact *c) {
    uint16_t mask_A = c->GetFixtureA()->GetFilterData().categoryBits;
    uint16_t mask_B = c->GetFixtureB()->GetFilterData().categoryBits;

    if (mask_A == BALL_BITS or mask_B == BALL_BITS) {
        b2Fixture *other_fixture = (mask_A == BALL_BITS ? c->GetFixtureB() : c->GetFixtureA());
        uint16_t other_mask = other_fixture->GetFilterData().categoryBits;
        if (other_mask == FRONT_SENSOR_BITS or other_mask == BACK_SENSOR_BITS or other_mask == DOWN_SENSOR_BITS)
            ((Car *)other_fixture->GetUserData().pointer)->setActiveSensor(NO_SENSOR);
    }
}
