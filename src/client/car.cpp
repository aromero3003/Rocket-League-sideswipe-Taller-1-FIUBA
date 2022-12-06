#include "car.h"

using namespace SDL2pp;

Car::Car(){
    pointing_right = false;
    nitro_flag = false;
}

void Car::draw(TextureManager& textureManager, SoundManager& soundManager){
    int flip;
    textureManager.renderer.Copy(
            textureManager.car_texture,
            Rect(
                0,
                (1000/12) * id,
                250,
                1000/12),
            Rect(20 * x_position - 40,
                (-20) * y_position - 20,
                80,
                40)
            ,angle,
            NullOpt,
            flip = (pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    show_indicators(textureManager);

    show_nitro(textureManager, soundManager);    

}

void Car::show_indicators(TextureManager& textureManager){
    if(id % 2 == 0){
        textureManager.renderer.Copy(
            textureManager.red_triangle,
            NullOpt,
            Rect(20 * x_position - 10,
                (-20) * y_position - 40,
                15,
                15),
            0,
            NullOpt,
            SDL_FLIP_VERTICAL);
    } else {
        textureManager.renderer.Copy(
            textureManager.blue_triangle,
            NullOpt,
            Rect(20 * x_position - 10,
                (-20) * y_position - 40,
                15,
                15),
            0,
            NullOpt,
            SDL_FLIP_VERTICAL);
    }
}

void Car::show_nitro(TextureManager& textureManager, SoundManager& soundManager){
    int flip;
    int nitro_phase = (SDL_GetTicks()/100)%5;
    
    if (this->nitro_flag){
    textureManager.renderer.Copy(textureManager.nitro,
                Rect(0,83*nitro_phase,335,83),
                Rect(20*x_position - 67,(-20)*y_position - 20,134,40), 
                angle,
                NullOpt,
                flip = (pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    if(!soundManager.mixer.IsChannelPlaying(id)){
        soundManager.mixer.PlayChannel(id,soundManager.nitro_sound,0);
    }
    } else {
        soundManager.mixer.HaltChannel(id);
    }
}

Car::~Car(){}