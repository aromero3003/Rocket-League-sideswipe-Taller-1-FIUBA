
#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "../Client/Snap.h"
#include "RLContactListener.h"
#include "GameObjects/Constants.h"
#include "GameObjects/ball.h"
#include "GameObjects/car.h"
#include <box2d/box2d.h>
#include "box2d/b2_body.h"
#include "box2d/b2_chain_shape.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"

class GameLogic {
 private:
  b2World world;
  RLContactListener contact_listener;
  Ball ball;
  std::vector<Car> players;
  uint8_t goal;
  float time_left;
  uint8_t red_score;
  uint8_t blue_score;
  /*
  SnapShot* snap;
  void setPlayer(Car& player);
  void setBall();
  void setGoal();
  void setSnap();
  */
 public:
  GameLogic(size_t cant_players);

  bool rotate_player(size_t id, float angle);

  void jump_player(size_t id);
  void move_player_up(size_t id);
  void move_player_down(size_t id);
  void move_player_left(size_t id);
  void move_player_right(size_t id);
  void brake_player(size_t id);
  void activate_nitro_player(size_t id);
  void deactivate_nitro_player(size_t id);
  // void jump_release_player (size_t id);
  // void move_release_player_up (size_t id);
  // void move_release_player_down (size_t id);
  // void move_release_player_left (size_t id);
  // void move_release_player_right (size_t id);
  void reset();
  void step();
  std::shared_ptr<SnapShot> getSnap();
};

#endif  // __GAME_LOGIC__
