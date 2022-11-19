
#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_chain_shape.h"
#include <vector>
#include <cstdint>
#include "GameObjects/ball.h"
#include "GameObjects/car.h"
#include "../Client/Snap.h"
#include <memory>
#include "GameObjects/Constants.h"
#include <cstddef>
#include <cstdint>
#include "../Client/Snap.h"
class GameLogic {
 private:
    b2World world;
    Ball ball;
    std::vector<Car> players;
    uint8_t goal;
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

    void jump_player (size_t id);
    void move_player_up (size_t id);
    void move_player_down (size_t id);
    void move_player_left (size_t id);
    void move_player_right (size_t id);
    void brake_player(size_t id);
    //void jump_release_player (size_t id);
    //void move_release_player_up (size_t id);
    //void move_release_player_down (size_t id);
    //void move_release_player_left (size_t id);
    //void move_release_player_right (size_t id);

    void step();
    std::shared_ptr<SnapShot> getSnap();

};

#endif  // __GAME_LOGIC__
