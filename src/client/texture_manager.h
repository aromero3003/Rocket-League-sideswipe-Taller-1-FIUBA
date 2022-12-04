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
    SDL2pp::Texture goal;
    TextureManager(SDL2pp::Window& window);

    ~TextureManager();
};

#endif