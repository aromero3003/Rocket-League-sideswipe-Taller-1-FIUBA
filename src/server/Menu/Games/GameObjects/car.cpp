#include "car.h"
#include <cstdint>
#include <iostream>

#include <box2d/b2_common.h>
#include <box2d/b2_math.h>

#include <cmath>

#include "Constants.h"

Car::Car(b2World &world, const b2Vec2 &position, bool orientation, size_t id) :
    initialPosition(position),
    orientation(orientation),
    direction_pressed(NO_PRESSED),
    active_sensor(NO_SENSOR),
    jump_ammount(0),
    current_jump(NO_FLIP),
    nitro_cant(MAXNITRO),
    id(id),
    isRedTeam(orientation),
    goals(0),
    assistances(0),
    tackles(0) {
  float x = position.x, y = position.y;
  initialPosition.y += 1.0f;
  {
    b2BodyDef chassis_def;
    chassis_def.type = b2_dynamicBody;
    chassis_def.position.Set(x, y + 1.0f);
    // chassis_def.fixedRotation = false;

    b2PolygonShape chassis_shape;
    b2Vec2 vertices[6];
    vertices[0].Set(1.5f, -0.5f);
    vertices[1].Set(1.5f, 0.2f);
    vertices[2].Set(0.5f, 0.9f);
    vertices[3].Set(-0.5f, 0.9f);
    vertices[4].Set(-1.5f, 0.2f);
    vertices[5].Set(-1.5f, -0.5f);
    chassis_shape.Set(vertices, 6);

    b2FixtureDef chassis_fd;
    chassis_fd.density = 10.0f;
    chassis_fd.friction = 0.3f;
    chassis_fd.shape = &chassis_shape;
    chassis_fd.filter.categoryBits = CAR_BITS;
    chassis_fd.filter.maskBits = SCENARIO_BITS | BALL_BITS;
    chassis_fd.userData.pointer = reinterpret_cast<uintptr_t>(this);

    this->chassis = world.CreateBody(&chassis_def);
    this->chassis->CreateFixture(&chassis_fd);
  }

    // Sensor
  {
      b2BodyDef sensordef;
      sensordef.type = b2_dynamicBody;
      sensordef.position.Set(position.x + 2.0f, position.y + 1.0f);
      this->front_sensor = world.CreateBody(&sensordef);
      sensordef.position.Set(position.x - 2.0f, position.y + 1.0f);
      this->back_sensor = world.CreateBody(&sensordef);

      sensordef.position.Set(position.x, position.y - 0.2f);
      this->down_sensor = world.CreateBody(&sensordef);

      b2PolygonShape square;
      square.SetAsBox(0.2, 0.5f);

      b2FixtureDef sensorfd;
      sensorfd.shape = &square;
      sensorfd.density = 0.001f;
      sensorfd.isSensor = true;
      sensorfd.filter.categoryBits = FRONT_SENSOR_BITS;
      sensorfd.userData.pointer = reinterpret_cast<uintptr_t>(this);

      this->front_sensor->CreateFixture(&sensorfd);

      sensorfd.filter.categoryBits = BACK_SENSOR_BITS;
      sensorfd.userData.pointer = reinterpret_cast<uintptr_t>(this);
      this->back_sensor->CreateFixture(&sensorfd);

      square.SetAsBox(1.5, 0.2f);
      sensorfd.userData.pointer = reinterpret_cast<uintptr_t>(this);
      sensorfd.filter.categoryBits = DOWN_SENSOR_BITS;
      this->down_sensor->CreateFixture(&sensorfd);

      b2PrismaticJointDef joint_def;
      b2Vec2 axis(0.0f, 1.0f);
      joint_def.Initialize(chassis, this->front_sensor, chassis->GetPosition(), b2Vec2(1.0f, 0.0f));
      joint_def.motorSpeed = 0.0f;
      joint_def.enableMotor = false;
      joint_def.enableLimit = true;
      joint_def.lowerTranslation = 0.0f;
      joint_def.upperTranslation = 0.0f;
      world.CreateJoint(&joint_def);

      joint_def.Initialize(chassis, this->back_sensor, chassis->GetPosition(), b2Vec2(-1.0f, 0.0f));
      joint_def.motorSpeed = 0.0f;
      joint_def.enableMotor = false;
      joint_def.enableLimit = true;
      joint_def.lowerTranslation = 0.0f;
      joint_def.upperTranslation = 0.0f;
      world.CreateJoint(&joint_def);

      joint_def.Initialize(chassis, this->down_sensor, chassis->GetPosition(), b2Vec2(0.0f, -0.5f));
      joint_def.motorSpeed = 0.0f;
      joint_def.enableMotor = false;
      joint_def.enableLimit = true;
      joint_def.lowerTranslation = 0.0f;
      joint_def.upperTranslation = 0.0f;
      world.CreateJoint(&joint_def);
  }

  {
    b2CircleShape circle;
    circle.m_radius = 0.4f;

    b2FixtureDef wheel_fd;
    wheel_fd.shape = &circle;
    wheel_fd.density = 1.0f;
    wheel_fd.friction = 0.9f;
    wheel_fd.filter.categoryBits = CAR_BITS;
    wheel_fd.filter.maskBits = BALL_BITS | SCENARIO_BITS;
    wheel_fd.restitution = 0.0f;
    wheel_fd.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2BodyDef wheel_def;
    wheel_def.type = b2_dynamicBody;
    wheel_def.position.Set(x - 1.0f, y + 0.4f);

    wheel1 = world.CreateBody(&wheel_def);
    wheel1->CreateFixture(&wheel_fd);

    wheel_def.position.Set(x + 1.0f, y + 0.4f);
    wheel2 = world.CreateBody(&wheel_def);
    wheel2->CreateFixture(&wheel_fd);
  }

  {
    b2WheelJointDef joint_def;
    b2Vec2 axis(0.0f, 1.0f);

    float mass1 = this->wheel1->GetMass();
    float mass2 = this->wheel2->GetMass();

    float hertz = 4.0f;
    float damping_ratio = 0.7f;
    float omega = 2.0f * b2_pi * hertz;

#define TRANSLATION 0.25f

    joint_def.Initialize(this->chassis, this->wheel1,
                         this->wheel1->GetPosition(), axis);
    joint_def.motorSpeed = 0.0f;
    joint_def.maxMotorTorque = 20.0f;
    joint_def.enableMotor = true;
    joint_def.stiffness = mass1 * omega * omega;
    joint_def.damping = 2.0f * mass1 * damping_ratio * omega;
    joint_def.lowerTranslation = -TRANSLATION;
    joint_def.upperTranslation = TRANSLATION;
    joint_def.enableLimit = true;
    this->damper1 = (b2WheelJoint *)world.CreateJoint(&joint_def);
    joint_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    joint_def.Initialize(this->chassis, this->wheel2,
                         this->wheel2->GetPosition(), axis);
    joint_def.motorSpeed = 0.0f;
    joint_def.maxMotorTorque = 20.0f;
    joint_def.enableMotor = true;
    joint_def.stiffness = mass2 * omega * omega;
    joint_def.damping = 2.0f * mass1 * damping_ratio * omega;
    joint_def.lowerTranslation = -TRANSLATION;
    joint_def.upperTranslation = TRANSLATION;
    joint_def.enableLimit = true;
    this->damper2 = (b2WheelJoint *)world.CreateJoint(&joint_def);
    joint_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  }

  this->nitro = false;
}
/*
void Car::buildChassis() {
    
}
void Car::buildWheels();
void Car::buildMotor();
void Car::buildSensors();
*/

void Car::jump() {
    if (this->jump_ammount > 1)
        return;

    else if (this->jump_ammount == 0) {
        this->chassis->ApplyLinearImpulseToCenter(b2Vec2(0.0f,100.0f), true);
        this->wheel1->ApplyLinearImpulseToCenter(b2Vec2(0.0f,75.0f), true);
        this->wheel2->ApplyLinearImpulseToCenter(b2Vec2(0.0f,75.0f), true);
        (this->jump_ammount)++;
    } else if (this->jump_ammount == 1) {
        if (this->direction_pressed == LEFT_PRESSED) std::cout << "LEFT FLIP" << std::endl;
        else if (this->direction_pressed == NO_PRESSED) std::cout << "DOUBLE JUMP" << std::endl;
        else std::cout << "RIGHT FLIP" << std::endl;
        (this->jump_ammount)++;

        float angle = this->chassis->GetAngle();
        b2Vec2 jump_direction(this->direction_pressed == LEFT_PRESSED ? -300.0f : 300.0f, 0.0f);
        if (this->direction_pressed == NO_PRESSED) {
            jump_direction.x = 200.0f * std::cos(angle + b2_pi * 0.5f);
            jump_direction.y = 200.0f * std::sin(angle + b2_pi * 0.5f);
            this->chassis->ApplyLinearImpulseToCenter(jump_direction,true);
            jump_direction *= 0.5f;
            this->wheel1->ApplyLinearImpulseToCenter(jump_direction,true);
            this->wheel2->ApplyLinearImpulseToCenter(jump_direction,true);
            this->current_jump = DOUBLE_JUMP;
        } else {
            this->wheel2->ApplyLinearImpulseToCenter(jump_direction,true);
            this->chassis->ApplyAngularImpulse(this->direction_pressed == LEFT_PRESSED ? 500.0f : -500.0f, true);
            this->current_jump = FLIP;
        }
    }
    std::cout << (int)this->jump_ammount << std::endl;
}

void Car::moveLeft() {
  this->direction_pressed = LEFT_PRESSED;
  this->damper1->SetMotorSpeed(50000.0f);
  this->damper2->SetMotorSpeed(50000.0f);
  if (this->onSurface(true)) {
    this->orientation = LEFT;
    if (this->active_sensor == BACK_SENSOR)
      this->active_sensor = FRONT_SENSOR;
    else if (this->active_sensor == FRONT_SENSOR)
      this->active_sensor = BACK_SENSOR;
  }
}

void Car::moveRight() {
  this->direction_pressed = RIGHT_PRESSED;
  this->damper1->SetMotorSpeed(-50000.0f);
  this->damper2->SetMotorSpeed(-50000.0f);
  if (this->onSurface(true)) {
    this->orientation = RIGHT;
    if (this->active_sensor == BACK_SENSOR)
      this->active_sensor = FRONT_SENSOR;
    else if (this->active_sensor == FRONT_SENSOR)
      this->active_sensor = BACK_SENSOR;
  }
}

void Car::brake() {
  this->direction_pressed = NO_PRESSED;
  this->damper1->SetMotorSpeed(0.0f);
  this->damper2->SetMotorSpeed(0.0f);
  if (not this->onSurface(false)) return;
  b2Vec2 opossite_vector = this->chassis->GetLinearVelocity();
  opossite_vector.y = 0;
  opossite_vector.x *= -4.0f;
  this->chassis->ApplyLinearImpulseToCenter(opossite_vector, true);
}

void Car::activate_nitro() {
  if (nitro_cant>0){
    this->nitro = true;
  }
}

void Car::deactivate_nitro() { this->nitro = false; }

bool Car::onSurface(bool strictly_touching) {
  b2ContactEdge *ce1 = this->wheel1->GetContactList();
  b2ContactEdge *ce2 = this->wheel2->GetContactList();
  bool is_near = ce1 != nullptr and ce2 != nullptr;
  return is_near and
      (strictly_touching ?
       ce1->contact->IsTouching() and ce2->contact->IsTouching() :
       true);
}

void Car::boost() {
  // b2Vec2 current_vel(this->chassis->GetLinearVelocity());
  // if (current_vel.x * current_vel.x + current_vel.y * current_vel.y > 100.0f)
  // return;
  float angle = this->chassis->GetAngle();
  b2Vec2 boost_vec(200 * cos(angle), 500 * sin(angle));
  if (this->orientation == LEFT) boost_vec *= -1;
  this->chassis->ApplyForceToCenter(boost_vec, true);
}

void Car::update() {
  if (nitro && nitro_cant>0)
    nitro_cant--;

  if (!nitro && nitro_cant<MAXNITRO)
    nitro_cant++;
  if (nitro_cant==0) nitro=false;

  b2Vec2 position(this->chassis->GetPosition());
  float angle = this->chassis->GetAngle();
  bool is_near_surface = this->onSurface(false);
  if (position.y < -SCENARIO_HEIGHT + 1.4f) {
    if (not is_near_surface and this->chassis->GetLinearVelocity().y < 0.0f)
      if (std::cos(angle) < 0.0f) {
        this->orientation = not this->orientation;
        this->chassis->SetTransform(position, angle - b2_pi);
      }
  }

  b2Filter new_filter;
  new_filter.categoryBits = this->orientation == RIGHT ? FRONT_SENSOR_BITS : BACK_SENSOR_BITS;
  this->front_sensor->GetFixtureList()->SetFilterData(new_filter);

  new_filter.categoryBits = this->orientation == RIGHT ? BACK_SENSOR_BITS : FRONT_SENSOR_BITS;
  this->back_sensor->GetFixtureList()->SetFilterData(new_filter);


  if (this->onSurface(true)) {
      this->jump_ammount = 0;
  }

  this->current_jump = NO_FLIP; // Esta línea desactiva el reseteo del FLIP
                                // Comentarla para probar los shots sin saltar de nuevo
                                // Luego del segundo salto cualquier acercamiento
                                // activa visualmente el shot de la pelota
}
void Car::reset(){
  this->chassis->SetTransform(initialPosition,0);
  this->chassis->SetSleepingAllowed(false);
  this->chassis->SetAngularVelocity(0);
  this->chassis->SetLinearVelocity(b2Vec2_zero);

  this->wheel1->SetLinearVelocity(b2Vec2_zero);
  this->wheel2->SetLinearVelocity(b2Vec2_zero);

  this->direction_pressed = NO_PRESSED;
  this->damper1->SetMotorSpeed(0.0f);
  this->damper2->SetMotorSpeed(0.0f);

  this->nitro_cant = 0xff;
  this->nitro = false;
}

const uint8_t Car::getOrientation() { return this->orientation; }

const b2Vec2 Car::getPosition() { return chassis->GetPosition(); }

const float Car::getAngle() { return chassis->GetAngle(); }

const uint16_t Car::getNitroAmmount() { return this->nitro_cant; }

void Car::setActiveSensor(sensor_t active) { this->active_sensor = active; }

sensor_t Car::getActiveSensor() { return this->active_sensor; }

jump_t Car::getSecondJumpMade() { return this->current_jump; }

const bool Car::isTeamRed() { return this->isRedTeam; }

void Car::registerGoal() {
    std::cout << "gol de " <<   (int)id << std::endl;
    (this->goals)++;
}

void Car::registerAssistance() {
    (this->assistances)++;
}

void Car::registerTackle() {
    (this->tackles)++;
}

uint8_t Car::getGoals() {
    return this->goals;
}

uint8_t Car::getAssistances() {
    return this->assistances;
}

uint8_t Car::getTackles() {
    return this->tackles;
}
