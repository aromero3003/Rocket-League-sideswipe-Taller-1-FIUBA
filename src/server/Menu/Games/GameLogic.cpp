#include "GameLogic.h"

#include <box2d/b2_body.h>
#include <box2d/b2_math.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "GameObjects/Constants.h"
#include "GameObjects/car.h"

GameLogic::GameLogic(size_t cant_players)
    : world(b2Vec2(0.0f, -GRAVITY)),
      ball(this->world, SCENARIO_HALF_WIDTH + 6.0f, -SCENARIO_HEIGHT / 2.0f),
      goal(false),
      time_left(180.0f),
      red_score(0),
      blue_score(0){
  // WORLD
  this->world.SetContactListener(&(this->contact_listener));
  b2Vec2 scenario_borders[SCENARIO_BORDERS];

  scenario_borders[0] = b2Vec2(6.0f, 0.0f);
  scenario_borders[1] = b2Vec2(SCENARIO_WIDTH + 6.0f, 0.0f);
  scenario_borders[2] = b2Vec2(SCENARIO_WIDTH + 6.0f, -22.0f);
  scenario_borders[3] = b2Vec2(SCENARIO_WIDTH + 12.0f, -22.0f);
  scenario_borders[4] = b2Vec2(SCENARIO_WIDTH + 12.0f, -SCENARIO_HEIGHT);
  scenario_borders[5] = b2Vec2(0.0f, -SCENARIO_HEIGHT);
  scenario_borders[6] = b2Vec2(0.0f, -SCENARIO_HEIGHT + 8.0f);
  scenario_borders[7] = b2Vec2(6.0f, -SCENARIO_HEIGHT + 8.0f);

  // for(int i = 0; i < 6; i++)
  // for(int i = 0; i < 6; i++)
  //     scenario_borders[i].x *= -1;
  b2ChainShape borders;
  // borders.CreateLoop(scenario_borders, SCENARIO_BORDERS);
  borders.CreateLoop(scenario_borders, 8);

  b2FixtureDef scn_fd;
  scn_fd.restitutionThreshold = 1.0f;
  scn_fd.shape = &borders;
  scn_fd.filter.categoryBits = SCENARIO_BITS;
  scn_fd.filter.maskBits = CAR_BITS | BALL_BITS;

  b2BodyDef scn_bd;
  b2Body *scenario = world.CreateBody(&scn_bd);
  scenario->CreateFixture(&scn_fd);

  float delta_x = (SCENARIO_WIDTH ) / (float)(cant_players+1);
  for (size_t i = 1; i <= cant_players; i++) {
    this->players.emplace_back(
        this->world, b2Vec2(6.0f+delta_x * i, -SCENARIO_HEIGHT),
        i <= cant_players / 2);
  }
}
void GameLogic::reset(){
  for (auto car : this->players) car.reset();
  ball.reset();
}

void GameLogic::jump_player(size_t id) { this->players[id].jump(); }

void GameLogic::move_player_left(size_t id) { this->players[id].moveLeft(); }

void GameLogic::move_player_right(size_t id) { this->players[id].moveRight(); }

void GameLogic::move_player_up(size_t id) {}

void GameLogic::brake_player(size_t id) { this->players[id].brake(); }

void GameLogic::activate_nitro_player(size_t id) {
  this->players[id].activate_nitro();
}

void GameLogic::deactivate_nitro_player(size_t id) {
  this->players[id].deactivate_nitro();
}

void GameLogic::step() {

    for (Car &player : this->players) {
        if (player.nitro == true) player.boost();
        sensor_t active_sensor = player.getActiveSensor();
        jump_t second_jump = player.getSecondJumpMade();
        b2Vec2 hitDirection = ball.getPosition() - player.getPosition();
        hitDirection.Normalize();
        if (second_jump == DOUBLE_JUMP and active_sensor == DOWN_SENSOR) {
            hitDirection *= 20.0f;
            ball.applyPurpleShot(hitDirection);
        } else if (second_jump == FLIP) {
            hitDirection *= 40.0f;
            if (active_sensor == BACK_SENSOR)
                ball.applyGoldShot(hitDirection);
            else if (active_sensor == FRONT_SENSOR)
                ball.applyRedShot(hitDirection);
        }
        player.update();
    }

    if (ball.getPosition().x < 6.0f - BALL_RADIUS) {
        goal = true;
        red_score++;
    } else if (ball.getPosition().x > SCENARIO_WIDTH + 6.0f + BALL_RADIUS) {
        goal = true;
        blue_score++;
    } else {
      goal = false;
    }
    this->world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    this->time_left -= TIME_STEP;
    ball.update();
}

std::shared_ptr<SnapShot> GameLogic::getSnap() {

    std::shared_ptr<SnapShot> snap(new SnapShot);

    snap->add((uint8_t)this->time_left);                      // 1 byte
    snap->add(this->red_score);                               // 2 byte
    snap->add(this->blue_score);                              // 3 byte
    snap->add(this->goal);
    snap->add((uint8_t)this->ball.isColliding());
    snap->add((uint8_t)false);

    snap->add(this->ball.getPosition().x);
    snap->add(this->ball.getPosition().y);
    snap->add(this->ball.getAngle());
    snap->add((uint8_t)(this->ball.getCurrentShot()));
    if (this->ball.getCurrentShot() != 0)
        std::cout << (int)this->ball.getCurrentShot() << std::endl;

    //std::vector<uint8_t> &values = snap->getMsg();
    //for (Car &player : this->players) {
    for (uint8_t id = 0; id < this->players.size(); id++) {
        Car &player = this->players[id];
        snap->add((uint8_t)id);
        snap->add(player.getPosition().x);
        snap->add(player.getPosition().y);
        snap->add(player.getAngle() );
        snap->add(player.getOrientation());
        snap->add((uint8_t)(player.nitro));// isNitroOn());
        //std::cerr<< "nitro :"<<(int) ((uint8)(player.getNitroAmmount()*100/MAXNITRO))<<"\n";
        snap->add( (uint8)( (player.getNitroAmmount()*100)/MAXNITRO));
    }
    return snap;
}
