#include "ball.h"
#include "constants.h"
#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>

Ball::Ball(b2World &world, float x, float y) {
    b2CircleShape circle;
    circle.m_radius = BALL_RADIUS;

    b2BodyDef ball_def;
    ball_def.type = b2_dynamicBody;
    ball_def.position.Set(x, y);

    b2FixtureDef ball_fd;
    ball_fd.density = 1.0f;
    ball_fd.friction = 0.3f;
    ball_fd.restitution = 0.9f;
    ball_fd.restitutionThreshold = 1.0f;
    ball_fd.filter.categoryBits = CAR_CATEGORY_BITS;

    this->ball = world. CreateBody(&ball_def);
    this->ball->CreateFixture(&ball_fd);
}

b2Vec2 Ball::getPosition() {
    return this->ball->GetPosition();
}
