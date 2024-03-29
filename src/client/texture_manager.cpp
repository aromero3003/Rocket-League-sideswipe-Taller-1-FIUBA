#include "texture_manager.h"

using namespace SDL2pp;

TextureManager::TextureManager(Window& window):renderer(window, -1, SDL_RENDERER_ACCELERATED),
                                car_texture(renderer, "../data/cars.png"),
                                ball(renderer, "../data/ball.png"),
                                court(renderer, "../data/court.png"),
                                nitro(renderer, "../data/complete_nitro.png"),
                                goal_sign(renderer, "../data/goal_sign.png"),
                                replay_sign(renderer, "../data/replay_sign.png"),
                                blue_triangle(renderer,SDL2pp::Surface("../data/triangle.png").SetColorMod(0,0,255)),
                                red_triangle(renderer,SDL2pp::Surface("../data/triangle.png").SetColorMod(255,0,0)),
                                nitro_bar(renderer,SDL2pp::Surface("../data/nitro_bar.png").SetColorMod(255,0,0)),
                                remaining_nitro(renderer,SDL2pp::Surface("../data/nitro_bar.png").SetColorMod(0,255,0)),
                                red_shot(renderer,"../data/red_shot.png"),
                                purple_shot(renderer,"../data/purple_shot.png"),
                                gold_shot(renderer,"../data/gold_shot.png"),
                                time_font("../data/Vera.ttf", 30),
                                score_font("../data/Vera.ttf",80),
                                statistics_score("../data/Vera.ttf", 120){

}

TextureManager::~TextureManager(){}
