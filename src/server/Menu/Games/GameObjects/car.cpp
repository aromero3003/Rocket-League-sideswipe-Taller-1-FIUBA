#include "Constants.h"
#include "car.h"
#include <box2d/b2_common.h>
#include <box2d/b2_math.h>
#include <cmath>

Car::Car(b2World &world, const b2Vec2 &position, bool orientation) :
    orientation(orientation) {
    float x = position.x, y = position.y;
    {
        b2BodyDef chassis_def;
        chassis_def.type = b2_dynamicBody;
        chassis_def.position.Set(x, y + 1.0f);
        //chassis_def.fixedRotation = false;

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

        this->chassis = world.CreateBody(&chassis_def);
        this->chassis->CreateFixture(&chassis_fd);
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

        b2BodyDef wheel_def;
        wheel_def.type = b2_dynamicBody;
        wheel_def.position.Set(x - 1.0f, y + 0.35f);

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

        joint_def.Initialize(this->chassis, this->wheel1, this->wheel1->GetPosition(), axis);
        joint_def.motorSpeed = 0.0f;
        joint_def.maxMotorTorque = 20.0f;
        joint_def.enableMotor = true;
        joint_def.stiffness = mass1 * omega * omega;
        joint_def.damping = 2.0f * mass1 * damping_ratio * omega;
        joint_def.lowerTranslation = -TRANSLATION;
        joint_def.upperTranslation = TRANSLATION;
        joint_def.enableLimit = true;
        this->damper1 = (b2WheelJoint *)world.CreateJoint(&joint_def);

        joint_def.Initialize(this->chassis, this->wheel2, this->wheel2->GetPosition(), axis);
        joint_def.motorSpeed = 0.0f;
        joint_def.maxMotorTorque = 20.0f;
        joint_def.enableMotor = true;
        joint_def.stiffness = mass2 * omega * omega;
        joint_def.damping = 2.0f * mass1 * damping_ratio * omega;
        joint_def.lowerTranslation = -TRANSLATION;
        joint_def.upperTranslation = TRANSLATION;
        joint_def.enableLimit = true;
        this->damper2 = (b2WheelJoint *)world.CreateJoint(&joint_def);
    }

    this->nitro = false;
}

void Car::jump() {
    this->wheel1->ApplyLinearImpulseToCenter(b2Vec2(0.0f,100.0f), true);
    this->wheel2->ApplyLinearImpulseToCenter(b2Vec2(0.0f,100.0f), true);
}

void Car::moveLeft() {
    this->damper1->SetMotorSpeed(50000.0f);
    this->damper2->SetMotorSpeed(50000.0f);
    if (this->onSurface(true))
        this->orientation = LEFT;
}

void Car::moveRight() {
    this->damper1->SetMotorSpeed(-50000.0f);
    this->damper2->SetMotorSpeed(-50000.0f);
    if (this->onSurface(true))
        this->orientation = RIGHT;
}

void Car::brake() {
    this->damper1->SetMotorSpeed(0.0f);
    this->damper2->SetMotorSpeed(0.0f);
    if(this->has_jumped)
        return;
    b2Vec2 opossite_vector = this->chassis->GetLinearVelocity();
    opossite_vector.y = 0;
    opossite_vector.x *= -1.0f * 4;
    this->chassis->ApplyLinearImpulseToCenter(opossite_vector, true);
}

void Car::activate_nitro() {
    this->nitro = true;
}

void Car::deactivate_nitro() {
    this->nitro = false;
}

bool Car::onSurface(bool strictly_touching) {
    b2ContactEdge *ce1 = this->wheel1->GetContactList();
    b2ContactEdge *ce2 = this->wheel2->GetContactList();
    bool is_near = ce1 != nullptr and ce2 != nullptr;
    return is_near and (strictly_touching ? ce1->contact->IsTouching()
        and ce2->contact->IsTouching() : true);
}

void Car::boost() {
    //b2Vec2 current_vel(this->chassis->GetLinearVelocity());
    //if (current_vel.x * current_vel.x + current_vel.y * current_vel.y > 100.0f) return;
    float angle = this->chassis->GetAngle();
    b2Vec2 boost_vec(200 * cos(angle) , 500 * sin(angle));
    if (this->orientation == LEFT) boost_vec *= -1;
    this->chassis->ApplyForceToCenter(boost_vec ,true);
}

void Car::update() {
    b2Vec2 position(this->chassis->GetPosition());
    float angle = this->chassis->GetAngle();
    if (position.y < -SCENARIO_HEIGHT + 1.4f) {
        if (not this->onSurface(false) and this->chassis->GetLinearVelocity().y < 0.0f)
            if (std::cos(angle) < 0.0f) {
                this->orientation = not this->orientation;
                this->chassis->SetTransform(position, angle - b2_pi);
            }
    }
}

const uint8_t Car::getOrientation() {
    return this->orientation;
}

const b2Vec2 Car::getPosition() {
    return chassis->GetPosition();
}

const float Car::getAngle() {
    return chassis->GetAngle();
}
