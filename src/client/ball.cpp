#include "ball.h"

using namespace SDL2pp;

#define METERS_TO_PIXELS 20
#define BALL_WIDTH 40
#define BALL_HEIGHT 40
#define SHOT_WIDTH 60
#define SHOT_HEIGHT 60

Ball::Ball(){
}

void Ball::draw(TextureManager& textureManager){

    /*
    EL DIBUJADO DE LA PELOTA ES MUY DIRECTO. AL IGUAL QUE EL AUTO EL FORMATO ES:

    METERS_TO_PIXELS * POSICION DEL AUTO - CENTERING
    */

    textureManager.renderer.Copy(
        textureManager.ball, 
        NullOpt, 
        Rect(METERS_TO_PIXELS * x_position - BALL_WIDTH/2, 
            (-METERS_TO_PIXELS) * y_position- BALL_HEIGHT/2, 
            BALL_WIDTH, 
            BALL_HEIGHT),
        angle); 
}

void Ball::draw_shots(TextureManager& textureManager){
    int shot_phase = SDL_GetTicks() % 360;

    /*
    PARA LOS TIROS SE TIENEN SPRITES CIRCULARES EN FORMA DE ANILLO, CON EL CENTRO VACIO.

    DEPENDIENDO DEL TIRO SE USA UNA TEXTURA DIFERENTE Y SE LE AGREGA UNA ANIMACION QUE GIRE PARA
    EFECTOS VISUALES. SHOT_PHASE SE USA COMO ANGULO DE DIBUJO Y VA VARIANDO ENTRE 0 Y 360
    */

    if(color == 1){
    textureManager.renderer.Copy(
        textureManager.gold_shot,
        NullOpt,
        Rect(METERS_TO_PIXELS * x_position - SHOT_WIDTH/2,
            (-METERS_TO_PIXELS) * y_position - SHOT_HEIGHT/2, 
            SHOT_WIDTH, 
            SHOT_HEIGHT),
        shot_phase,
        NullOpt);
    }    
    if(color == 2){
        textureManager.renderer.Copy(
            textureManager.red_shot,
            NullOpt,
            Rect(METERS_TO_PIXELS * x_position - SHOT_WIDTH/2,
                (-METERS_TO_PIXELS) * y_position - SHOT_HEIGHT/2, 
                SHOT_WIDTH, 
                SHOT_HEIGHT),
            shot_phase,
            NullOpt);
    }
    if(color == 3){
        textureManager.renderer.Copy(
            textureManager.purple_shot,
            NullOpt,
            Rect(METERS_TO_PIXELS * x_position - SHOT_WIDTH/2,
                (-METERS_TO_PIXELS) * y_position - SHOT_HEIGHT/2, 
                SHOT_WIDTH, 
                SHOT_HEIGHT),
            shot_phase,
            NullOpt);
    }

}

Ball::~Ball(){}