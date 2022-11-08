#include "game_logic.h"
#include "constants.h"
#include <box2d/b2_body.h>
#include <box2d/b2_collision.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_world.h>
#include <cstddef>
#include "constants.h"
#include "car.h"
#include "ball.h"

GameLogic::GameLogic(size_t cant_players) :
    world(b2Vec2(0.0f, -GRAVITY)),
    ball(this->world, 0.0f, SCENARIO_HEIGHT / 2.0f) {

    // WORLD
    b2FixtureDef scn_fd;
    b2Vec2 scenario_borders[SCENARIO_BORDERS];
    scenario_borders[0] = scenario_borders[6]  = b2Vec2(SCENARIO_HALF_WIDTH, 0.0f);
    scenario_borders[1] = scenario_borders[7]  = b2Vec2(SCENARIO_HALF_WIDTH, 11.0f);
    scenario_borders[2] = scenario_borders[8]  = b2Vec2(SCENARIO_HALF_WIDTH + 6, 11.0f);
    scenario_borders[3] = scenario_borders[9]  = b2Vec2(SCENARIO_HALF_WIDTH + 6, 19.0f);
    scenario_borders[4] = scenario_borders[10] = b2Vec2(SCENARIO_HALF_WIDTH, 19.0f);
    scenario_borders[5] = scenario_borders[11] = b2Vec2(SCENARIO_HALF_WIDTH, SCENARIO_HEIGHT);
    for(int i = 6; i < 12; i++)
        scenario_borders[i].x *= -1;
    b2ChainShape borders;
    borders.CreateLoop(scenario_borders, SCENARIO_BORDERS);


    //  PLAYERS
    for (size_t i = 0; i < cant_players / 2; i++) {
        this->players.emplace_back()
    }
    for (float x = -SCENARIO_HALF_WIDTH + 2.5f; x < SCENARIO_HALF_WIDTH - 2.5f; x += (SCENARIO_HALF_WIDTH - 5.0f) / (cant_players + 1)) {
        this->players.push_back() 
    }
}

bool GameLogic::jump_player(size_t id) {
    this->players[id];
}


void GameLogic::step() {
    this->world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}
