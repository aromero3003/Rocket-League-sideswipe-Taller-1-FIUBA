#include "test.h"
#include "../settings.h"
#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "Constants.h"
#include "car.h"
#include "ball.h"
#include "socket.h"
#include "thread.h"
#include "ProtectedQueue.h"
extern int number_of_bounces;

//#define SOCKET_DEBUG
int commands[] = {GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_F,
                  GLFW_KEY_K, GLFW_KEY_J, GLFW_KEY_L, GLFW_KEY_ENTER};

#ifdef SOCKET_DEBUG
class Receiver : public Thread {
    Socket s;
    ProtectedQueue<int> &q;

 public:
    Receiver(const char *s, ProtectedQueue<int> &q) : s(s), q(q) {
        this->s = std::move(this->s.accept());
    }

    void run() override {
        bool was_closed = false;
        char data = 0;
        while (not was_closed) {
            s.recvall(&data, 1, &was_closed);
            q.push((int)data);
        }
    }

 };
#endif

class CarAndBall : public Test
{
public:

	//CarAndBall() : car(*m_world, b2Vec2(-SCENARIO_HALF_WIDTH / 2.0f, 1.0f)),
    //               car2(*m_world, b2Vec2(SCENARIO_HALF_WIDTH / 2.0f, 1.0f))
	CarAndBall() : car(*m_world, b2Vec2(SCENARIO_HALF_WIDTH * 3.0f /2.0f  + 6.0f, -SCENARIO_HEIGHT + 2.0f)),
                   car2(*m_world, b2Vec2(SCENARIO_HALF_WIDTH /2.0f + 6.0f, -SCENARIO_HEIGHT + 2.0f)),
                   ball(*m_world, SCENARIO_HALF_WIDTH + 6.0f, -SCENARIO_HEIGHT /2.0f)
#ifdef SOCKET_DEBUG
                ,r("8080", this->comms)
#endif
{
        // Scenario
		b2Body* ground = NULL;
        {
            m_world->SetGravity(b2Vec2(0.0f, -10.0f));
            //b2Vec2 scenario_borders[SCENARIO_BORDERS];
            b2Vec2 scenario_borders[8];
            /*
            scenario_borders[0] = scenario_borders[11] = b2Vec2(SCENARIO_HALF_WIDTH, 0.0f);
            scenario_borders[1] = scenario_borders[10] = b2Vec2(SCENARIO_HALF_WIDTH, 11.0f);
            scenario_borders[2] = scenario_borders[9] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 11.0f);
            scenario_borders[3] = scenario_borders[8] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 19.0f);
            scenario_borders[4] = scenario_borders[7] = b2Vec2(SCENARIO_HALF_WIDTH, 19.0f);
            scenario_borders[5] = scenario_borders[6] = b2Vec2(SCENARIO_HALF_WIDTH, SCENARIO_HEIGHT);
            */
            /*
            scenario_borders[0] = scenario_borders[7] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 0.0f);
            scenario_borders[1] = scenario_borders[6] = b2Vec2(SCENARIO_HALF_WIDTH + 6, 8.0f);
            scenario_borders[2] = scenario_borders[5] = b2Vec2(SCENARIO_HALF_WIDTH, 8.0f);
            scenario_borders[3] = scenario_borders[4] = b2Vec2(SCENARIO_HALF_WIDTH, SCENARIO_HEIGHT);
            */
            scenario_borders[0] = b2Vec2(6.0f, 0.0f);
            scenario_borders[1] = b2Vec2(SCENARIO_WIDTH + 6.0f, 0.0f);
            scenario_borders[2] = b2Vec2(SCENARIO_WIDTH + 6.0f, -22.0f);
            scenario_borders[3] = b2Vec2(SCENARIO_WIDTH + 12.0f, -22.0f);
            scenario_borders[4] = b2Vec2(SCENARIO_WIDTH + 12.0f, -SCENARIO_HEIGHT);
            scenario_borders[5] = b2Vec2(0.0f, -SCENARIO_HEIGHT);
            scenario_borders[6] = b2Vec2(0.0f, -SCENARIO_HEIGHT + 8.0f);
            scenario_borders[7] = b2Vec2(6.0f, -SCENARIO_HEIGHT + 8.0f);
            //for(int i = 0; i < 4; i++)
            //for(int i = 0; i < 6; i++)
            //    scenario_borders[i].x *= -1;
            b2ChainShape borders;
            borders.CreateLoop(scenario_borders, 8);
            //borders.CreateLoop(scenario_borders, SCENARIO_BORDERS);

            b2BodyDef bodyDef;
            ground = m_world->CreateBody(&bodyDef);


            b2FixtureDef fixtureDef;
            fixtureDef.shape = &borders;
            fixtureDef.friction = 5.0f;
            fixtureDef.restitutionThreshold = 0.7f;
            fixtureDef.filter.categoryBits = 0x2;
            fixtureDef.filter.maskBits = 0x1 | 0x4;

            ground->CreateFixture(&fixtureDef);
#ifdef SOCKET_DEBUG
            this->r.start();
#endif
        }
	}

	void Keyboard(int key) override
	{
		switch (key)
		{
	case GLFW_KEY_A:
            car.moveLeft();
			break;

		case GLFW_KEY_S:
            car.brake();
			break;

		case GLFW_KEY_D:
            car.moveRight();
			break;

        case GLFW_KEY_ENTER:
            car.jump();
            break;

        case GLFW_KEY_LEFT_SHIFT:
            car.set_nitro(true);
            break;

        case GLFW_KEY_W:
            car.go_up = true;
		}
	}
    void KeyboardUp(int key) override {
        switch (key) {
            case GLFW_KEY_A:
            case GLFW_KEY_D:
                car.brake();
                break;

            case GLFW_KEY_LEFT_SHIFT:
                car.set_nitro(false);
                break;

            case GLFW_KEY_W:
                car.go_up = false;
                break;
        }


    }

/*
    uint8_t updateCollitions() {
        uint8_t collitions = 0;
        for(b2ContactEdge *ce = m_world->GetContactList() ; ce ;ce = ce->next) {
            b2Contact *c = ce->contact;
            uint8_t cat_A = c->GetFixtureA()->GetFilterData().categoryBits;
            uint8_t cat_B = c->GetFixtureB()->GetFilterData().categoryBits;

            if ((cat_A == BALL_BITS and cat_B == SCENARIO_BITS) or (cat_A == SCENARIO_BITS and cat_B == BALL_BITS)) {
                if (not ground_ball_contact) {
                    collitions |= 0x1;
                    this->ground_ball_contact = true;
                }
                continue;
            }


        }

    }
*/

	void Step(Settings& settings) override
	{
		//g_debugDraw.DrawString(5, m_textLine, "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
		g_debugDraw.DrawString(5, m_textLine, car.getOrientation() ? "Der" : "left");
		m_textLine += m_textIncrement;

//        car.time_elapsed += settings.m_hertz;

        car.update();

        if(car.nitro == true) {
            car.boost();
        }
        if(car.go_up == true)
            car.up();
        float angle = car.getAngle();
        //std::cout << angle << ": sin " << std::sin(angle) << "   cos " << std::cos(angle) << std::endl;
        //std::cout << (number_of_bounces == 1 ? "CANT JUMP" : "JUMP CAN") << std::endl;
        //ball.is_bouncing();
        //if (ball.is_bouncing()) std::cout << "BOUNCE: " /*<< number_of_bounces*/ << std::endl;
        //if (car.isHittingBall()) std::cout << "HIT: " /*<< number_of_bounces*/ << std::endl;
        //if (car.isHittingBall()) std::cout << "HIT: " /*<< number_of_bounces*/ << std::endl;
        //std::cout << car.getAngle() << std::endl;
		//g_camera.m_center.x = m_car->GetPosition().x;
        //if (ball.getPosition().x > SCENARIO_WIDTH + 6.0f + BALL_RADIUS
        //        || ball.getPosition().x < 6.0f - BALL_RADIUS)
        //    std::cout << "GOAL" << std::endl;
#ifdef SOCKET_DEBUG
        while (not comms.is_empty()) {
            int c = comms.pop();
            this->Keyboard(commands[c]);
        }
#endif
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new CarAndBall;
	}

#ifdef SOCKET_DEBUG
    ~CarAndBall() {
        this->r.join();
    }
#endif

    Car car;
    Car car2;
    Ball ball;
#ifdef SOCKET_DEBUG
    ProtectedQueue<int>comms;
    Receiver r;
#endif
    bool ground_ball_contact;
};

static int testIndex = RegisterTest("Local Test", "Rocket League", CarAndBall::Create);
