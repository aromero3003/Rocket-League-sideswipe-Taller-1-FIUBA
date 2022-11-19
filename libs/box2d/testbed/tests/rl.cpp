#include "test.h"
//#include "game_logic/car.h"
#include <box2d/box2d.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <iostream>
#include "car.h"
#include "Constants.h"
#include "ball.h"
#include "../../../../src/common/socket.h"
#include "../../../../src/common/thread.h"
#include <thread>



//#define TESTCAR

class CarAndBall : public Test
{
public:

#ifndef TESTCAR
	CarAndBall() : car(*m_world, b2Vec2(-SCENARIO_HALF_WIDTH / 2.0f, 1.0f)),
                  car2(*m_world, b2Vec2(-SCENARIO_HALF_WIDTH / 2.0f, 1.0f)),
                   skt("8085") {
#else
    CarAndBall() {
		m_speed = 10000.0f;
#endif
        // Scenario
		b2Body* ground = NULL;
        {
            m_world->SetGravity(b2Vec2(0.0f, -10.0f));
            b2Vec2 scenario_borders[SCENARIO_BORDERS];
            scenario_borders[0] = scenario_borders[11] = b2Vec2(SCENARIO_HALF_WIDTH, 0.0f);
            scenario_borders[1] = scenario_borders[10] = b2Vec2(SCENARIO_HALF_WIDTH, 11.0f);
            scenario_borders[2] = scenario_borders[9] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 11.0f);
            scenario_borders[3] = scenario_borders[8] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 19.0f);
            scenario_borders[4] = scenario_borders[7] = b2Vec2(SCENARIO_HALF_WIDTH, 19.0f);
            scenario_borders[5] = scenario_borders[6] = b2Vec2(SCENARIO_HALF_WIDTH, SCENARIO_HEIGHT);
            for(int i = 0; i < 6; i++)
                scenario_borders[i].x *= -1;
            b2ChainShape borders;
            borders.CreateLoop(scenario_borders, SCENARIO_BORDERS);

            b2BodyDef bodyDef;
            ground = m_world->CreateBody(&bodyDef);


            b2FixtureDef fixtureDef;
            fixtureDef.shape = &borders;
            fixtureDef.restitutionThreshold = 1.0f;
            fixtureDef.filter.categoryBits = 0x2;
            fixtureDef.filter.maskBits = 0x1 | 0x4;

            ground->CreateFixture(&fixtureDef);

        }

        // Ball
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(0.0f, 10.0f);
            m_ball = m_world->CreateBody(&bodyDef);

            b2CircleShape shape;
            shape.m_radius = 1.0f;

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(1.0f, 1.0f);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = 0.05f;
            fixtureDef.restitution = 0.75f;
            fixtureDef.restitutionThreshold = 1.0f;
            fixtureDef.filter.categoryBits = 0x4;
            fixtureDef.filter.maskBits = 0x1 | 0x2;
            //fixtureDef.friction = 0.3f;

            m_ball->CreateFixture(&fixtureDef);
        }

		// Car
#ifdef TESTCAR
#define CAR_BITS 0x1
		{
			b2PolygonShape chassis;
			b2Vec2 vertices[6];
			vertices[0].Set(1.5f, -0.5f);
			vertices[1].Set(1.5f, 0.2f);
			vertices[2].Set(0.5f, 0.9f);
			vertices[3].Set(-0.5f, 0.9f);
			vertices[4].Set(-1.5f, 0.2f);
			vertices[5].Set(-1.5f, -0.5f);
			chassis.Set(vertices, 6);

            b2FixtureDef chassis_fd;
            chassis_fd.shape = &chassis;
            chassis_fd.density = 1.0f;
            chassis_fd.filter.categoryBits = CAR_BITS;
            //chassis_fd.filter.groupIndex = -1;
            chassis_fd.filter.maskBits = 0x2 | 0x4;

			b2CircleShape circle;
			circle.m_radius = 0.4f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.0f, 1.0f);
			m_car = m_world->CreateBody(&bd);
			// m_car->CreateFixture(&chassis, 1.0f);
            m_car->CreateFixture(&chassis_fd);

            bd.position.Set(10.0f, 1.0f);
            m_car2 = m_world->CreateBody(&bd);
            // m_car2->CreateFixture(&chassis, 1.0f);
            m_car2->CreateFixture(&chassis_fd);

			b2FixtureDef fd;
            //fd.filter.groupIndex = -1;
			fd.shape = &circle;
			fd.density = 1.0f;
			fd.friction = 0.9f;
            fd.filter.categoryBits = CAR_BITS;
            fd.filter.maskBits = 0x2 | 0x4;

			bd.position.Set(-1.0f, 0.35f);
			m_wheel1 = m_world->CreateBody(&bd);
			m_wheel1->CreateFixture(&fd);

			bd.position.Set(1.0f, 0.4f);
			m_wheel2 = m_world->CreateBody(&bd);
			m_wheel2->CreateFixture(&fd);

            bd.position.Set(9.0f, 0.35f);
			m_wheel3 = m_world->CreateBody(&bd);
			m_wheel3->CreateFixture(&fd);

            bd.position.Set(11.0f, 0.4f);
			m_wheel4 = m_world->CreateBody(&bd);
			m_wheel4->CreateFixture(&fd);

			b2WheelJointDef jd;
			b2Vec2 axis(0.0f, 1.0f);

			float mass1 = m_wheel1->GetMass();
			float mass2 = m_wheel2->GetMass();

			float hertz = 54.0f;
			float dampingRatio = 1.7f;
			float omega = 4.0f * b2_pi * hertz;

#define TRANSLATION 0.25f

			jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = true;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -TRANSLATION;
			jd.upperTranslation = TRANSLATION;
			jd.enableLimit = true;
			m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -TRANSLATION;
			jd.upperTranslation = TRANSLATION;
			jd.enableLimit = true;
            m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);


			jd.Initialize(m_car2, m_wheel3, m_wheel3->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = true;
			jd.stiffness = mass1 * omega * omega;
			jd.damping = 2.0f * mass1 * dampingRatio * omega;
			jd.lowerTranslation = -TRANSLATION;
			jd.upperTranslation = TRANSLATION;
			jd.enableLimit = true;
			m_spring3 = (b2WheelJoint*)m_world->CreateJoint(&jd);

			jd.Initialize(m_car2, m_wheel4, m_wheel4->GetPosition(), axis);
			jd.motorSpeed = 0.0f;
			jd.maxMotorTorque = 20.0f;
			jd.enableMotor = false;
			jd.stiffness = mass2 * omega * omega;
			jd.damping = 2.0f * mass2 * dampingRatio * omega;
			jd.lowerTranslation = -TRANSLATION;
			jd.upperTranslation = TRANSLATION;
			jd.enableLimit = true;
            m_spring4 = (b2WheelJoint*)m_world->CreateJoint(&jd);

		}
#endif

	}

	void Keyboard(int key) override
	{
		switch (key)
		{
#ifdef TESTCAR
		case GLFW_KEY_A:
			m_spring1->SetMotorSpeed(m_speed);
			m_spring2->SetMotorSpeed(m_speed);
			break;

		case GLFW_KEY_S:
			m_spring1->SetMotorSpeed(0.0f);
			m_spring2->SetMotorSpeed(0.0f);
			break;

		case GLFW_KEY_D:
			m_spring1->SetMotorSpeed(-m_speed);
			m_spring2->SetMotorSpeed(-m_speed);
			break;
        case GLFW_KEY_F:
            //m_wheel1->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 20.0f), true);
            //m_wheel2->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 20.0f), true);
            m_car->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 40.0f), true);
            //m_car->ApplyLinearImpulseToCenter(b2Vec2(10.0f, 0.0f), true);
            break;
        //case GLFW_KEY_W:
            //m_car->ApplyTorque(1000.0f, true);

		case GLFW_KEY_L:
			m_spring3->SetMotorSpeed(-m_speed);
			m_spring4->SetMotorSpeed(-m_speed);
			break;

		case GLFW_KEY_K:
			m_spring3->SetMotorSpeed(0.0f);
			m_spring4->SetMotorSpeed(0.0f);
			break;

		case GLFW_KEY_J:
			m_spring3->SetMotorSpeed(m_speed);
			m_spring4->SetMotorSpeed(m_speed);
			break;
        case GLFW_KEY_ENTER:
            //m_wheel1->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 20.0f), true);
            //m_wheel2->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 20.0f), true);
            m_car2->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 40.0f), true);
            break;

#else
		case GLFW_KEY_A:
            car.moveLeft();
			break;

		case GLFW_KEY_S:
            car.brake();
			break;

		case GLFW_KEY_D:
            car.moveRight();
			break;
        case GLFW_KEY_F:
            car.jump();
            break;
        //case GLFW_KEY_W:
            //m_car->ApplyTorque(1000.0f, true);
#endif
		}
	}

	void Step(Settings& settings) override
	{
		g_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
		m_textLine += m_textIncrement;

		//g_camera.m_center.x = m_car->GetPosition().x;
        if (m_ball->GetPosition().x > SCENARIO_HALF_WIDTH + BALL_RADIUS
                || m_ball->GetPosition().x < -SCENARIO_HALF_WIDTH - BALL_RADIUS)
            std::cout << "GOAL" << std::endl;
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new CarAndBall;
	}

    void recv_and_execute() {
        bool was_closed = false;
        char data = 0;
        do {
            this->skt.recvall(&data, 1, &was_closed);
            switch (data) {
                case 1:
                    this->car.brake();
                    break;
                case 2:
                    this->car.moveLeft();
                    break;
                case 3:
                    this->car.moveRight();
                    break;
                case 4:
                    this->car.jump();
                    break;


            }

        } while(not was_closed);
    }
#ifndef TESTCAR
    Car car;
    Car car2;
#else
	b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;

	float m_speed;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;

	b2Body* m_car2;
	b2Body* m_wheel3;
	b2Body* m_wheel4;


	float m_speed2;
	b2WheelJoint* m_spring3;
	b2WheelJoint* m_spring4;
    

#endif
    Socket skt;
    b2Body *m_ball;
};

static int testIndex = RegisterTest("Local Test", "Rocket League", CarAndBall::Create);
