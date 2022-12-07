#include "car.h"

using namespace SDL2pp;

#define METERS_TO_PIXELS 20
#define CAR_WIDTH 80
#define CAR_HEIGHT 40
#define NITRO_WIDTH 134
#define NITRO_HEIGHT 40

#define INDICATOR_SIZE 15

#define TOTAL_CARS_WIDTH 250
#define TOTAL_CARS_HEIGHT 1000
#define DIFFERENT_MODELS 12

Car::Car(){
    pointing_right = false;
    nitro_flag = false;
}

/*
PARA EL DIBUJADO SE TRANSFORMA LOS METROS RECIBIDOS A PIXELS, 
MULTIPLICANDO POR 20 (METERS_TO_PIXELS) LA POSICION

TAMBIEN SE RESTA LA MITAD DEL TAMANIO DEL SPRITE, PARA CENTRARLO (TANTO EN X COMO EN Y)

PARA LA MAYORIA DE LOS DIBUJADOS EL FORMATO ES:

        METERS_TO_PIXELS * POSITION - CENTERING
*/

void Car::draw(TextureManager& textureManager, SoundManager& soundManager,size_t cant_cars){
    /*
    EL SPRITE CON LOS AUTOS MIDE 250 PIXELES DE ANCHO Y 1000 DE ALTO CON UN TOTAL DE
    12 MODELOS DISTINTOS

    PARA CADA JUGADOR SE CARGA UN SPRITE DE 1000/12 DE ALTO POR EL ANCHO TOTAL, VARIANDO PARA
    CADA ID
    */
    
    int flip;
    textureManager.renderer.Copy(
            textureManager.car_texture,
            Rect(
                0,
                (TOTAL_CARS_HEIGHT/DIFFERENT_MODELS) * id,
                TOTAL_CARS_WIDTH,
                TOTAL_CARS_HEIGHT/DIFFERENT_MODELS), 
            Rect(METERS_TO_PIXELS * x_position - CAR_WIDTH/2,
                (-METERS_TO_PIXELS) * y_position - CAR_HEIGHT/2,
                CAR_WIDTH,
                CAR_HEIGHT)
            ,angle,
            NullOpt,
            flip = (pointing_right == true) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

    show_indicators(textureManager,cant_cars);

    show_nitro(textureManager, soundManager);    

}

void Car::show_indicators(TextureManager& textureManager,size_t cant_cars){
    /*
    SE USAN TRIANGULITOS DE COLORES PARA INDICAR A QUE EQUIPO PERTENECE CADA JUGADOR

    A QUE EQUIPO PERTENECEN DEPENDE DEL ORDEN EN EL QUE SEAN METIDOS A LA PARTIDA EN EL SERVIDOR
    */
    
    if(id < cant_cars / 2){
        textureManager.renderer.Copy(
            textureManager.red_triangle,
            NullOpt,
            Rect(METERS_TO_PIXELS * x_position - 10,   
                (-METERS_TO_PIXELS) * y_position - 40,  //SE CENTRA Y SE DIBUJA POR ENCIMA DEL AUTO
                INDICATOR_SIZE,
                INDICATOR_SIZE),
            0,
            NullOpt,
            SDL_FLIP_VERTICAL);
    } else {
        textureManager.renderer.Copy(
            textureManager.blue_triangle,
            NullOpt,
            Rect(METERS_TO_PIXELS * x_position - 10,
                (-METERS_TO_PIXELS) * y_position - 40,
                INDICATOR_SIZE,
                INDICATOR_SIZE),
            0,
            NullOpt,
            SDL_FLIP_VERTICAL);
    }
}

void Car::show_nitro(TextureManager& textureManager, SoundManager& soundManager){
    int flip;
    int nitro_phase = (SDL_GetTicks()/100)%5;
    
    /*
    PARA EL NITRO SE USO UN SPRITE ESPECIAL, QUE ES DEL TAMANIO 
    DEL AUTO + EL TAMANIO DEL FUEGO QUE EXPULSA HACIA AMBOS LADOS

    CON ESTO SE PUDO SOLUCIONAR EL TEMA DE QUE EL NITRO SIEMPRE APAREZCA DETRAS DEL AUTO
    CUALQUIERA SEA SU ORIENTACION, Y ADEMAS TENGA EL MISMO CENTRO DE ROTACION QUE EL AUTO

            ---------->
    /////////////////////////         
    / nitro // auto //      /
    /////////////////////////


            <----------
    /////////////////////////
    /      // auto // nitro /
    /////////////////////////
    
    */

    if (this->nitro_flag){
    textureManager.renderer.Copy(textureManager.nitro,
                Rect(0,83*nitro_phase,335,83),
                Rect(METERS_TO_PIXELS * x_position - NITRO_WIDTH/2,                
                    -(METERS_TO_PIXELS) * y_position - NITRO_HEIGHT/2,
                    NITRO_WIDTH,
                    NITRO_HEIGHT), 
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