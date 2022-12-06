#include "ball.h"

#include <box2d/b2_contact.h>

#include <box2d/b2_math.h>
#include <iostream>

#include "Constants.h"

Ball::Ball(b2World& world, float x, float y) {
  b2CircleShape circle;
  circle.m_radius = BALL_RADIUS;

  b2BodyDef ball_def;
  ball_def.type = b2_dynamicBody;
  ball_def.position.Set(x, y);
  initialPosition.x=x;
  initialPosition.y=y;

  b2FixtureDef ball_fd;
  ball_fd.density = 1.0f;
  ball_fd.friction = 0.3f;
  ball_fd.restitution = 0.9f;
  ball_fd.restitutionThreshold = 1.0f;
  ball_fd.filter.categoryBits = BALL_BITS;
  ball_fd.filter.maskBits = SCENARIO_BITS | CAR_BITS | BACK_SENSOR_BITS | FRONT_SENSOR_BITS | DOWN_SENSOR_BITS; 
  ball_fd.shape = &circle;

  this->ball = world.CreateBody(&ball_def);
  this->ball->CreateFixture(&ball_fd);
}

const b2Vec2 Ball::getPosition() { return this->ball->GetPosition(); }

const float Ball::getAngle() { return this->ball->GetAngle(); }

void Ball::reset(){ 
  this->ball->SetTransform(initialPosition,0); 
  this->ball->SetAngularVelocity(0);
  b2Vec2 aux(0,0);
  this->ball->SetLinearVelocity(aux);
}

const bool Ball::isColliding() {
  uint8_t prev_collitions = this->current_collisions;
  current_collisions = 0;
  for (b2ContactEdge* ce = this->ball->GetContactList(); ce;
       ce = ce->next, current_collisions++)
    ;
  // std::cout << (this->current_collisions > prev_collitions) << std::endl;
  return this->current_collisions > prev_collitions;
}

void Ball::applyRedShot(b2Vec2 hitDirection) {
    this->ball->ApplyLinearImpulseToCenter(hitDirection, true);
    this->current_shot_state = RED_SHOT;
    std::cout << "REDSHOT" << std::endl;
}

void Ball::applyPurpleShot(b2Vec2 hitDirection) {
    this->ball->ApplyLinearImpulseToCenter(hitDirection, true);
    this->current_shot_state = PURPLE_SHOT;
    std::cout << "purple" << std::endl;
}

void Ball::applyGoldShot(b2Vec2 hitDirection) {
    this->ball->ApplyLinearImpulseToCenter(hitDirection, true);
    this->current_shot_state = GOLD_SHOT;
    std::cout << "gold" << std::endl;
}

shot_t Ball::getCurrentShot() { return this->current_shot_state; }
