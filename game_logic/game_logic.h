#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__

#include <box2d/b2_world.h>
#include <vector>
#include <cstdint>
#include "ball.h"
#include "car.h"
#include "snap.h"

class GameLogic {
 private:
    b2World world;
    Ball ball;
    std::vector<Car> players;

 public:
    GameLogic(size_t cant_players);

    bool rotate_player(size_t id, float angle);

    void jump_player (size_t id);
    void move_player_up (size_t id);
    void move_player_down (size_t id);
    void move_player_left (size_t id);
    void move_player_right (size_t id);

    void step();
    SnapShot get_snap();

};

#endif  // __GAME_LOGIC__
