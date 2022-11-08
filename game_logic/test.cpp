#include "car.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/box2d.h>
#include <iostream>
#include "constants.h"
#include <unistd.h>

int main() {
    b2World world(b2Vec2(.0f, -10.0f));
    Car car(world, b2Vec2(.0f, 1.0f));



    b2BodyDef wdbd;
    b2Body *ground = world.CreateBody(&wdbd);
    b2FixtureDef fd;
    fd.shape = &borders;
    ground->CreateFixture(&fd);

    for (int i = 0; i < 60; i++) {
        world.Step(1/60.0f, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        std::cout << car.getPosition().x << " " << car.getPosition().y << std::endl;
        usleep(500 * 1000);
    }
}

