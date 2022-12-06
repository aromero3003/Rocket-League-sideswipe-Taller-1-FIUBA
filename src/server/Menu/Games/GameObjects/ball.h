#ifndef __BALL_H__
#define __BALL_H__

#include "Constants.h"
#include <box2d/box2d.h>
#include <queue>
#include "car.h"

typedef enum {NO_SHOT, GOLD_SHOT, RED_SHOT, PURPLE_SHOT} shot_t;

class Ball {
 private:
  b2Body *ball;
  uint8_t current_collisions;
  b2Vec2 initialPosition;
  shot_t current_shot_state;
  float shot_state_counter;

  void applyShot(Car &hitter, shot_t shot);

 public:
  Ball(b2World &world, float x, float y);
  const b2Vec2 getPosition();
  const float getAngle();
  const bool isColliding();
  void reset();
  Car *last_hitter;
  Car *blue_assistance;
  Car *red_assistance;

  void applyRedShot(Car &hitter);
  void applyGoldShot(Car &hitter);
  void applyPurpleShot(Car &hitter);

  shot_t getCurrentShot();
  void transform(b2Vec2 position, float angle);
  void update();

  void registerHit(Car *hitter);
  void getGoalAndAssistant(Car **goaler, Car **assistant);
};

#endif
