#include "RLContactListener.h"
#include <cstdint>
#include <iostream>
#include <box2d/box2d.h>
#include "GameObjects/Constants.h"
#include "GameObjects/car.h"
#include "GameObjects/ball.h"

void RLContactListener::BeginContact(b2Contact *c) {
    b2Fixture *a = c->GetFixtureA(), *b = c->GetFixtureB();
    uint16_t cat_A = a->GetFilterData().categoryBits;
    uint16_t cat_B = b->GetFilterData().categoryBits;

    if (cat_A == BALL_BITS or cat_B == BALL_BITS) {
        b2Fixture *not_ball_fd = cat_A == BALL_BITS ? b : a;
        uint16_t not_ball_cat = not_ball_fd->GetFilterData().categoryBits;
        Car *player = reinterpret_cast<Car*>(not_ball_fd->GetUserData().pointer);
        if (not_ball_cat == FRONT_SENSOR_BITS)
            player->setActiveSensor(FRONT_SENSOR);
        else if (not_ball_cat == DOWN_SENSOR_BITS)
            player->setActiveSensor(DOWN_SENSOR);
        else if (not_ball_cat == BACK_SENSOR_BITS)
            player->setActiveSensor(BACK_SENSOR);
        else if (not_ball_cat == CAR_BITS) {
            (reinterpret_cast<Ball *>((cat_A == BALL_BITS ? a : b)->GetUserData().pointer))->registerHit(player);
        }
    }
}

void RLContactListener::EndContact(b2Contact *c) {
    uint16_t mask_A = c->GetFixtureA()->GetFilterData().categoryBits;
    uint16_t mask_B = c->GetFixtureB()->GetFilterData().categoryBits;

    if (mask_A == BALL_BITS or mask_B == BALL_BITS) {
        b2Fixture *other_fixture = (mask_A == BALL_BITS ? c->GetFixtureB() : c->GetFixtureA());
        uint16_t other_mask = other_fixture->GetFilterData().categoryBits;
        if (other_mask == FRONT_SENSOR_BITS or other_mask == BACK_SENSOR_BITS or other_mask == DOWN_SENSOR_BITS)
            (reinterpret_cast<Car *>(other_fixture->GetUserData().pointer))->setActiveSensor(NO_SENSOR);
    }
}
