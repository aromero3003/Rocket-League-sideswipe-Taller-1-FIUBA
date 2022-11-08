#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_common.h>
#include <box2d/b2_math.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_wheel_joint.h>
#include <box2d/box2d.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include "car.h"

Car::Car(b2World &world, const b2Vec2 &position) {
    float x = position.x, y = position.y;
    {
        b2BodyDef chassis_def;
        chassis_def.type = b2_dynamicBody;
        chassis_def.position.Set(x, y + 1.0f);

        b2PolygonShape chassis_box;
        chassis_box.SetAsBox(x + 1.5f, y + 1.0f);

        b2FixtureDef chassis_fd;
        chassis_fd.density = 10.0f;
        chassis_fd.friction = 0.3f;
        chassis_fd.shape = &chassis_box;

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

        b2BodyDef wheel_def;
        wheel_def.type = b2_dynamicBody;
        wheel_def.position.Set(x - 1.0f, y + 0.35f);

        wheel1 = world.CreateBody(&wheel_def);
        wheel1->CreateFixture(&wheel_fd);

        wheel_def.position.Set(1.0f, 0.4f);
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
    }
}

b2Vec2 Car::getPosition() {
    return chassis->GetPosition();
}
