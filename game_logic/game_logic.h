#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__

#include <box2d/b2_world.h>
#include <vector>
#include <cstdint>
#include "ball.h"
#include "car.h"

class GameLogic {
 private:
    b2World world;
    Ball ball;
    std::vector<Car> players;

 public:
    GameLogic(size_t cant_players);

    bool rotate_player(size_t id, float angle);
    bool move_player  (size_t id, bool right);
    bool jump_player  (size_t id);

    void step();
};

#endif  // __GAME_LOGIC__
