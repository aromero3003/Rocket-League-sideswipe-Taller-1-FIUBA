#include "ball.h"

#include <box2d/b2_contact.h>

#include <box2d/b2_math.h>
#include <iostream>

#include "Constants.h"

Ball::Ball(b2World& world, b2Vec2 position):rest_current_time_effect(MAXSHOTTIME) {
  b2CircleShape circle;
  circle.m_radius = BALL_RADIUS;

  b2BodyDef ball_def;
  ball_def.type = b2_dynamicBody;
  ball_def.position = position;
  this->initialPosition = position;

  b2FixtureDef ball_fd;
  ball_fd.density = 1.0f;
  ball_fd.friction = 0.3f;
  ball_fd.restitution = 0.9f;
  ball_fd.restitutionThreshold = 1.0f;
  ball_fd.filter.categoryBits = BALL_BITS;
  ball_fd.filter.maskBits = SCENARIO_BITS | CAR_BITS | BACK_SENSOR_BITS | FRONT_SENSOR_BITS | DOWN_SENSOR_BITS; 
  ball_fd.userData.pointer = reinterpret_cast<uintptr_t>(this);
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
  this->shot_state_counter = 0;
  this->current_shot_state = NO_SHOT;
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

void Ball::applyShot(Car &hitter, shot_t shot) {
    b2Vec2 hitDirection = this->getPosition() - hitter.getPosition();
    hitDirection.Normalize();
    hitDirection *= shot == PURPLE_SHOT ? 20.0f : 40.0f;

    this->ball->ApplyLinearImpulseToCenter(hitDirection, true);
    this->current_shot_state = shot;

    //this->registerHit(&hitter);
}

void Ball::applyRedShot(Car &hitter) {
    this->applyShot(hitter, RED_SHOT);
    std::cout << "REDSHOT" << std::endl;
}

void Ball::applyPurpleShot(Car &hitter) {
    this->applyShot(hitter, PURPLE_SHOT);
    std::cout << "purple" << std::endl;
}

void Ball::applyGoldShot(Car &hitter) {
    this->applyShot(hitter, GOLD_SHOT);
    std::cout << "gold" << std::endl;
}

shot_t Ball::getCurrentShot() { return this->current_shot_state; }

void Ball::registerHit(Car *new_hitter) {
    if (this->last_hitter == nullptr)
        this->last_hitter = new_hitter;

    if (this->last_hitter == new_hitter)
        return;

    bool isNewHitterRed = new_hitter->isTeamRed();
    bool iAmRed = this->last_hitter->isTeamRed();
    
    if (iAmRed != isNewHitterRed) {
        this->blue_assistance = nullptr;
        this->red_assistance = nullptr;
    } else {
        if (iAmRed && (last_hitter != this->red_assistance)) {
            this->red_assistance=this->last_hitter;
        } else 
        if (!iAmRed && (last_hitter != this->blue_assistance)) {
            this->blue_assistance=this->last_hitter;
        } 
    }
    this->last_hitter = new_hitter;
}

void Ball::update() {
    if (this->current_shot_state !=NO_SHOT){
        this->rest_current_time_effect--;
    } else {
        this->rest_current_time_effect=MAXSHOTTIME;
    }
    if (this->rest_current_time_effect==0){
        this->current_shot_state=NO_SHOT;
    }

}

void Ball::getGoalAndAssistant(Car **goaler, Car **assistant) {
    *goaler = this->last_hitter;
    if (this->last_hitter == nullptr)
        *assistant = nullptr;
    else
     *assistant = this->last_hitter->isTeamRed() ? this->red_assistance : this->blue_assistance;
}
