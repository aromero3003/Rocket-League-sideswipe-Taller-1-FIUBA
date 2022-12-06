#include "ball.h"

using namespace SDL2pp;

Ball::Ball(){
}

void Ball::draw(TextureManager& textureManager){
    textureManager.renderer.Copy(
        textureManager.ball, 
        NullOpt, 
        Rect(20 * x_position -20, 
            (-20) * y_position-20, 
            40, 
            40),
        angle); 
}

void Ball::draw_shots(TextureManager& textureManager){
    int shot_phase = SDL_GetTicks() % 360;

    if(color == 1){
    textureManager.renderer.Copy(
        textureManager.gold_shot,
        NullOpt,
        Rect(20 * x_position -33,
            (-20) * y_position - 33, 
            66, 
            66),
        shot_phase,
        NullOpt);
    }
    if(color == 2){
        textureManager.renderer.Copy(
            textureManager.purple_shot,
            NullOpt,
            Rect(20 * x_position -30,
                (-20) * y_position - 30, 
                60, 
                60),
            shot_phase,
            NullOpt);
    }
    if(color == 3){
        textureManager.renderer.Copy(
            textureManager.red_shot,
            NullOpt,
            Rect(20 * x_position -30,
                (-20) * y_position - 30, 
                60, 
                60),
            shot_phase,
            NullOpt);
    }
}

Ball::~Ball(){}