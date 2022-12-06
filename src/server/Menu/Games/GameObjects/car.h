#ifndef __CAR_H__
#define __CAR_H__

#include <cstdint>

#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_common.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_wheel_joint.h"
#include "box2d/b2_world.h"
#include "box2d/box2d.h"

enum { LEFT, RIGHT };
typedef enum {NO_SENSOR, BACK_SENSOR, DOWN_SENSOR, FRONT_SENSOR} sensor_t;
typedef enum {NO_FLIP, DOUBLE_JUMP, FLIP} jump_t;
typedef enum {NO_PRESSED, LEFT_PRESSED, RIGHT_PRESSED} direction_t;


class Car {
 private:
  b2Vec2 initialPosition;

  b2Body *chassis;
  b2Body *wheel1;
  b2Body *wheel2;
  b2WheelJoint *damper1;
  b2WheelJoint *damper2;

  b2Body *front_sensor;
  b2Body *back_sensor;
  b2Body *down_sensor;

  bool orientation;
  direction_t direction_pressed;

  sensor_t active_sensor;

  uint8_t jump_ammount;
  jump_t current_jump;

  uint16_t nitro_cant;

  size_t id;
  bool isRedTeam;

  uint8_t goals;
  uint8_t assistances;
  uint8_t tackles;

  bool onSurface(bool strictly_touching);


 public:
  Car(b2World &world, const b2Vec2 &position, bool orientation, size_t id);
  void moveLeft();
  void moveRight();
  void brake();
  void jump();
  void boost();
  void activate_nitro();
  void deactivate_nitro();
  void update();
  const b2Vec2 getPosition();
  const float getAngle();
  const uint8_t getOrientation();
  const uint16_t getNitroAmmount();
  const bool isTeamRed();
  void setActiveSensor(sensor_t active);
  sensor_t getActiveSensor();
  jump_t getSecondJumpMade();
  void reset();

  void registerGoal();
  void registerAssistance();
  void registerTackle();
  uint8_t getGoals();
  uint8_t getAssistances();
  uint8_t getTackles();


  bool has_jumped;
  double time_elapsed;
  bool nitro;
  bool go_up;
};

#endif  // __CAR_H__
