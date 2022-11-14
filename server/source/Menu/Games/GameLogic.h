
#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__

#include <box2d/b2_world.h>
#include <vector>
#include <cstdint>
#include "GameObjects/ball.h"
#include "GameObjects/car.h"
#include "../Client/Snap.h"

class GameLogic {
 private:
    b2World world;
    Ball ball;
    std::vector<Car> players;
    void setPlayer(SnapShot& snap,Car& player);
    void setBall(SnapShot& snap);
    void setGoal(SnapShot& snap);
   void setSnap(Snap& snap);
 public:
    GameLogic(size_t cant_players);

    bool rotate_player(size_t id, float angle);

    void jump_player (size_t id);
    void move_player_up (size_t id);
    void move_player_down (size_t id);
    void move_player_left (size_t id);
    void move_player_right (size_t id);

    void step();
   SnapShot getSnap();

};

#endif  // __GAME_LOGIC__