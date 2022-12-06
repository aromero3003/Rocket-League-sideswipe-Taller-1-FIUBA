#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2pp/SDL2pp.hh>

class TextureManager {
    public:
    SDL2pp::Renderer renderer;

    SDL2pp::Texture car_texture;
    SDL2pp::Texture ball;
    SDL2pp::Texture court; 
    SDL2pp::Texture nitro;
    SDL2pp::Texture goal_sign;
    SDL2pp::Texture replay_sign;
    SDL2pp::Texture blue_triangle;
    SDL2pp::Texture red_triangle;
    SDL2pp::Texture nitro_bar;
    SDL2pp::Texture remaining_nitro;
    SDL2pp::Texture red_shot;
    SDL2pp::Texture purple_shot;
    SDL2pp::Texture gold_shot;

    SDL2pp::Font time_font;
    SDL2pp::Font score_font;

    TextureManager(SDL2pp::Window& window);

    ~TextureManager();
};

#endif