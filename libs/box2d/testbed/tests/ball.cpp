#include "ball.h"
#include "Constants.h"
#include "box2d/b2_contact.h"
#include "contact_listener.h"
#include <iostream>

Ball::Ball(b2World &world, float x, float y) {
    b2CircleShape circle;
    circle.m_radius = BALL_RADIUS;

    b2BodyDef ball_def;
    ball_def.type = b2_dynamicBody;
    ball_def.position.Set(x, y);
    //ball_def.linearDamping = 0.5f;

    b2FixtureDef ball_fd;
    ball_fd.shape = &circle;
    ball_fd.density = 0.1f;
    ball_fd.friction = 0.3f;
    ball_fd.restitution = 0.3f;
    ball_fd.restitutionThreshold = 0.1f;
    ball_fd.filter.categoryBits = BALL_BITS;
    ball_fd.filter.maskBits = CAR_BITS | SCENARIO_BITS;

    this->ball = world.CreateBody(&ball_def);
    this->ball->CreateFixture(&ball_fd);
    //this->ball->SetGravityScale(0.80f);
}

const b2Vec2 Ball::getPosition() {
    return this->ball->GetPosition();
}

const float Ball::getAngle() {
    return this->ball->GetAngle();
}

const bool Ball::is_bouncing() {
    for (b2ContactEdge* ce = this->ball->GetContactList(); ce; ce = ce->next) {
        //if (not ce->contact->IsTouching()) continue; recibe contactos de más
        uint8_t mask_A = ce->contact->GetFixtureA()->GetFilterData().categoryBits;
        uint8_t mask_B = ce->contact->GetFixtureB()->GetFilterData().categoryBits;
        if ((mask_A == BALL_BITS and mask_B == SCENARIO_BITS)
                or (mask_B == BALL_BITS and mask_A == SCENARIO_BITS)) {
            if (not this->bouncing)
                return this->bouncing = true;
            return false;
        }
    }
    return this->bouncing = false;
}
