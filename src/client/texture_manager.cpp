#include "texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Window& window):renderer(window, -1, SDL_RENDERER_ACCELERATED),
                                car_texture(renderer, "../data/cars.png"),
                                ball(renderer, "../data/ball.png"),
                                court(renderer, "../data/court.png"),
                                nitro(renderer, "../data/complete_nitro.png"),
                                goal_sign(renderer, "../data/goal_sign.png"),
                                replay_sign(renderer, "../data/replay_sign.png"),
                                time_font("../data/Vera.ttf", 30),
                                score_font("../data/Vera.ttf",80){

}

TextureManager::~TextureManager(){}
