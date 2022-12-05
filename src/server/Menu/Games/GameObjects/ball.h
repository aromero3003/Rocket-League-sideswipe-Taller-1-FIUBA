#ifndef __BALL_H__
#define __BALL_H__

#include "Constants.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

typedef enum {NO_SHOT, GOLD_SHOT, RED_SHOT, PURPLE_SHOT} shot_t;

class Ball {
 private:
  b2Body *ball;
  uint8_t current_collisions;
  b2Vec2 initialPosition;
  shot_t current_shot_state;

 public:
  Ball(b2World &world, float x, float y);
  const b2Vec2 getPosition();
  const float getAngle();
  const bool isColliding();
  void setInitialPos();
  // getSnapshotData

  void applyRedShot(b2Vec2 hitDirection);
  void applyGoldShot(b2Vec2 hitDirection);
  void applyPurpleShot(b2Vec2 hitDirection);

  uint8_t getCurrentShot();
  void transform(b2Vec2 position, float angle);
};

#endif
