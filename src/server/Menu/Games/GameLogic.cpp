#include "GameLogic.h"
#include "GameObjects/Constants.h"
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <cstdint>
#include <iostream>
#include <memory>


GameLogic::GameLogic(size_t cant_players) :
    world(b2Vec2(0.0f, -GRAVITY)),
    ball(this->world, SCENARIO_HALF_WIDTH + 6.0f, -SCENARIO_HEIGHT / 2.0f),
    goal(0) {

    // WORLD

    b2Vec2 scenario_borders[SCENARIO_BORDERS];
    /*
    scenario_borders[0] = scenario_borders[11]  = b2Vec2(SCENARIO_HALF_WIDTH, 0.0f);
    scenario_borders[1] = scenario_borders[10]  = b2Vec2(SCENARIO_HALF_WIDTH, 11.0f);
    scenario_borders[2] = scenario_borders[9]  = b2Vec2(SCENARIO_HALF_WIDTH + 6, 11.0f);
    scenario_borders[3] = scenario_borders[8]  = b2Vec2(SCENARIO_HALF_WIDTH + 6, 19.0f);
    scenario_borders[4] = scenario_borders[7] = b2Vec2(SCENARIO_HALF_WIDTH, 19.0f);
    scenario_borders[5] = scenario_borders[6] = b2Vec2(SCENARIO_HALF_WIDTH, SCENARIO_HEIGHT);
    */

    scenario_borders[0] = b2Vec2(6.0f, 0.0f);
    scenario_borders[1] = b2Vec2(SCENARIO_WIDTH + 6.0f, 0.0f);
    scenario_borders[2] = b2Vec2(SCENARIO_WIDTH + 6.0f, -22.0f);
    scenario_borders[3] = b2Vec2(SCENARIO_WIDTH + 12.0f, -22.0f);
    scenario_borders[4] = b2Vec2(SCENARIO_WIDTH + 12.0f, -SCENARIO_HEIGHT);
    scenario_borders[5] = b2Vec2(0.0f, -SCENARIO_HEIGHT);
    scenario_borders[6] = b2Vec2(0.0f, -SCENARIO_HEIGHT + 8.0f);
    scenario_borders[7] = b2Vec2(6.0f, -SCENARIO_HEIGHT + 8.0f);


    //for(int i = 0; i < 6; i++)
    //for(int i = 0; i < 6; i++)
    //    scenario_borders[i].x *= -1;
    b2ChainShape borders;
    //borders.CreateLoop(scenario_borders, SCENARIO_BORDERS);
    borders.CreateLoop(scenario_borders, 8);

    b2FixtureDef scn_fd;
    scn_fd.restitutionThreshold = 1.0f;
    scn_fd.shape = &borders;
    scn_fd.filter.categoryBits = SCENARIO_BITS;
    scn_fd.filter.maskBits = CAR_BITS | BALL_BITS;

    b2BodyDef scn_bd;
    b2Body *scenario = world.CreateBody(&scn_bd);
    scenario->CreateFixture(&scn_fd);




    //  PLAYERS
    /*size_t mid = cant_players / 2;
    float delta_x = (SCENARIO_WIDTH - 5.0f) / (cant_players + 1);
    for (ssize_t i = -1; i > -mid; i--)
        this->players.emplace_back(this->world, b2Vec2((float)i * delta_x, 1.0f));
    for (size_t i = 0; i > -mid; i--)
        this->players.emplace_back(this->world, b2Vec2((float)i * delta_x, 1.0f));
        */
    // creo solo dos jugadores
    this->players.emplace_back(this->world, b2Vec2(SCENARIO_HALF_WIDTH /2.0f + 6.0f, -SCENARIO_HEIGHT + 2.0f));
    this->players.emplace_back(this->world, b2Vec2(SCENARIO_HALF_WIDTH * 3.0f / 2.0f, -SCENARIO_HEIGHT + 2.0f));
}

void GameLogic::jump_player(size_t id) {
    this->players[id].jump();
}

void GameLogic::move_player_left(size_t id) {
    this->players[id].moveLeft();
}

void GameLogic::move_player_right(size_t id) {
    this->players[id].moveRight();
}

void GameLogic::move_player_up(size_t id) {
//    this->players[id].moveRight();
}

void GameLogic::brake_player(size_t id) {
    this->players[id].brake();
}

void GameLogic::activate_nitro_player(size_t id) {
    this->players[id].activate_nitro();
}

void GameLogic::deactivate_nitro_player(size_t id) {
    this->players[id].deactivate_nitro();
}

void GameLogic::step() {
    for (Car &player : this->players) {
        if (player.nitro == true)
            player.boost();
    }
    if(ball.getPosition().x < 6.0f - BALL_RADIUS){
        goal = 2;
    } else if (ball.getPosition().x > SCENARIO_WIDTH + 6.0f + BALL_RADIUS) {
        goal = 1;
    } else {
        goal = 0;
    }
    
    this->world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    //setSnap();
}

std::shared_ptr<SnapShot> GameLogic::getSnap(){
    std::shared_ptr<SnapShot> snap(new SnapShot);
    uint8_t match_flags = this->goal;  // 2 BITS // 0 NONE | 1 RED | 2 BLUE
    match_flags |= this->ball.isColliding() << 2; // 0 FALSE | 1 TRUE  xxxx x1xx
    snap->add(match_flags);

    snap->add(this->ball.getPosition().x);
    snap->add(this->ball.getPosition().y);
    snap->add(this->ball.getAngle());

    for (Car &player : this->players) {
        snap->add(player.getPosition().y);
        snap->add(player.getPosition().x);
        snap->add(player.getAngle());
        uint8_t flags = player.getOrientation();  // 0 LEFT | 1 RIGHT   xxxx xxx1
        flags |= player.nitro << 1;               // 0 OFF | 1 ON       xxxx xx1x
        //flags |= player.nitro << 2;  IMPACT     // 0 FALSE | 1 TRUE   xxxx x1xx
        snap->add(flags);
    }
    return snap;
}
/*
void GameLogic::setSnap(){
    std::shared_ptr<SnapShot> snap(new SnapShot);
    //setBall();
    for (Car& player : players){
        setPlayer(player);
    }
}

void GameLogic::setPlayer(Car& player){
       snap->add(player.getPosition().y);
       snap->add(player.getPosition().x);
       snap->add(player.getAngle());
       snap->add(player.getOrientation());
}

void GameLogic::setBall(){
       //snap->add(ball.getPosition().y);
       //snap->add(ball.getPosition().x);
       //snap->add(ball.getAngle());
       snap->add(10.0f);
       snap->add(20.0f);
       snap->add(0.0f);
}
*/
