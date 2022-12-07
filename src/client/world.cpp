#include "world.h"
#include "protocolDeserializer.h"
#include <cstdint>
#include <iostream>
#include <string>

#define FC *(float*)
#define PI 3.14159265
#define METERS_TO_PIXELS 20
using namespace SDL2pp;

World::World(){}

void World::create_cars(int n_cars){
    for(int i=0; i < n_cars; i++){
        Car new_car;
        this->cars.push_back(new_car);
    }
}

void World::set_id(uint8_t id) {
    this->my_id = id;
}

void World::finish_match(std::vector<char>& data){
    std::lock_guard<std::mutex> lock(mutex);

    this->winner = data[0];
    for(size_t i=0; i < this->cars.size(); i++){
        this->cars[i].goals = data[i*2 + 1];
        this->cars[i].assists = data[i*2 + 2];
    }
}

void World::update(std::vector<char>& data){
    
    std::lock_guard<std::mutex> lock(mutex);
    
    //UPDATE FLAGS
    update_flags(data);

    //UPDATE BALL
    update_ball(data);

    //UPDATE ALL CARS
    update_cars(data);

}

void World::draw(TextureManager& textureManager, SoundManager& soundManager){

    std::lock_guard<std::mutex> lock(mutex);

    /*
    CUANDO EL TIEMPO LLEGA A 0, SE CAMBIA EL PROTOCOLO PARA RECIBIR (VER RECEIVER_THREAD),
    Y SE DEJA DE DIBUJAR TODO
    */

    if(remaining_time > 0){

    //Show court, always the same
    show_court(textureManager);

    //nitro_bar
    show_nitro_bar(textureManager);

    //Show scores and time
    show_scores_and_time(textureManager);

    //replay
    if (this->goal)
        replay(textureManager, soundManager);

    //Show all cars
    show_cars(textureManager, soundManager);
    
    //Show ball
    show_ball(textureManager);

    //shots
    show_shots(textureManager);

    //sounds
    sounds(soundManager);

    }

    /*
    AHORA SE DIBUJAN SOLO ESTADISTICAS DE LA PARTIDA
    */

    if(remaining_time == 0){
        show_statistics(textureManager, soundManager);
    }

}

void World::update_flags(std::vector<char>& data){
    char* buf = reinterpret_cast<char*>(data.data());

    this->remaining_time = ProtocolDeserializer::deserialize_time(buf);
    this->blue_team_score = ProtocolDeserializer::deserialize_blue_team_score(buf);
    this->red_team_score = ProtocolDeserializer::deserialize_red_team_score(buf);
    this->goal = ProtocolDeserializer::deserialize_goal_flag(buf);
    this->ball_collision = ProtocolDeserializer::deserialize_ball_collision_flag(buf);
    this->car_collision = ProtocolDeserializer::deserialize_car_collision_flag(buf);
}

void World::update_ball(std::vector<char>& data){

    char* buf = reinterpret_cast<char*>(data.data());
    
    ProtocolDeserializer::deserialize_ball(this->ball, buf);

}

void World::update_cars(std::vector<char>& data){

    char* buf = reinterpret_cast<char*>(data.data());
    ProtocolDeserializer::deserialize_cars(this->cars, buf);

}



void World::show_court(TextureManager& textureManager){
    textureManager.renderer.Copy(
        textureManager.court, 
        NullOpt, 
        Rect(
            0,
            0,
            textureManager.renderer.GetOutputWidth(), 
            textureManager.renderer.GetOutputHeight()));
}

void World::show_nitro_bar(TextureManager& textureManager){

    /*
    PARA LA BARRA DE NITRO SE USA UNA BARRA ROJA DE TAMANIO FIJO, Y SUPERPUESTA 
    A ESA UNA BARRA VERDE QUE ES DIBUJADA CON DIFERENTES TAMANIOS DEPENDIENDO 
    DE LA CANTIDAD DE NITRO RESTANTE, DANDO LA ILUSION A UNA BARRA QUE SE LLENA 
    Y SE VACIA DINAMICAMENTE

    SOLO SE DIBUJA LA BARRA DE NITRO DEL AUTO QUE ESTOY MANEJANDO EN MI CLIENTE
    (TODOS LOS CLIENT SABEN LA CANTIDAD DE NITRO QUE TIENEN LOS OTROS JUGADORES,
    PERO LOS USUARIOS NO PUEDEN VERLO)
    */

    textureManager.renderer.Copy(
        textureManager.nitro_bar,
        NullOpt,
        Rect(METERS_TO_PIXELS*this->cars[my_id].x_position - 25,
            (-METERS_TO_PIXELS)*this->cars[my_id].y_position - 25,
            50,
            10));
    
    textureManager.renderer.Copy(
        textureManager.remaining_nitro,
        NullOpt,
        Rect(METERS_TO_PIXELS*this->cars[my_id].x_position - 25,
            (-METERS_TO_PIXELS)*this->cars[my_id].y_position - 25,
            this->cars[my_id].nitro_quantity / 2,
            10));
}

void World::show_cars(TextureManager& textureManager, SoundManager& soundManager){
    
    for(size_t i = 0; i < this->cars.size(); i++){
        cars[i].draw(textureManager, soundManager,this->cars.size());
    }
}

void World::show_ball(TextureManager& textureManager){
    ball.draw(textureManager);
}

void World::show_shots(TextureManager& textureManager){   
    ball.draw_shots(textureManager);
}

void World::sounds(SoundManager& soundManager){
    if(this->ball_collision && !soundManager.mixer.IsChannelPlaying(7)){
        soundManager.mixer.PlayChannel(7, soundManager.ball_sound,0);
        this->ball_collision = false;
    }
    if(!this->goal) soundManager.mixer.HaltChannel(6);
}

void World::replay(TextureManager& textureManager, SoundManager& soundManager){
    
    /*
    AL REPLAY SE LE AGREGAN UN CARTEL DE "GOL!" Y UN LETRERO DE MADERA QUE DICE "REPLAY".

    LUEGO SE DIBUJAN LOS SNAPS RECIBIDOS IGUAL QUE DURANTE LA PARTIDA
    */
    
    textureManager.renderer.Copy(
        textureManager.goal_sign,
        NullOpt,
        Rect(textureManager.renderer.GetOutputWidth()/2-200,
            textureManager.renderer.GetOutputHeight()/4-100,
            400,
            200));
    textureManager.renderer.Copy(textureManager.replay_sign,
                                NullOpt,
                                Rect(120,
                                    textureManager.renderer.GetOutputHeight()-225,
                                    150,
                                    100));
    if(!soundManager.mixer.IsChannelPlaying(6))
        soundManager.mixer.PlayChannel(6,soundManager.goal_sound,0);
}

void World::show_scores_and_time(TextureManager& textureManager){
    std::string red_score, blue_score, time;
    red_score = std::to_string(this->red_team_score);
    blue_score = std::to_string(this->blue_team_score);
    time = convert_time();

    Texture red_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended(red_score, SDL_Color{255, 0, 0, 255})
        );
    Texture blue_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended(blue_score, SDL_Color{0, 0, 255, 255})
        );
    Texture time_text_sprite(
            textureManager.renderer,
            textureManager.time_font.RenderText_Blended(time, SDL_Color{255, 255, 255, 255})
        );

    //show scores
    textureManager.renderer.Copy(
        red_text_sprite, 
        NullOpt, 
        Rect(
            375, 
            120, 
            red_text_sprite.GetWidth(), 
            red_text_sprite.GetHeight()));
                                    
    textureManager.renderer.Copy(
        blue_text_sprite, 
        NullOpt, 
        Rect(
            585, 
            120, 
            blue_text_sprite.GetWidth(), 
            blue_text_sprite.GetHeight()));
    
    //show time
    textureManager.renderer.Copy(
        time_text_sprite, 
        NullOpt, 
        Rect(
            462, 
            150, 
            time_text_sprite.GetWidth(), 
            time_text_sprite.GetHeight()));
}

std::string World::convert_time(){
    std::string time;
    if(this->remaining_time / 60 < 10){
        time = "0";
    }
    time += std::to_string(this->remaining_time / 60);
    time += ":";
    if(this->remaining_time % 60 < 10){
        time += "0";
        time += std::to_string(this->remaining_time % 60);
    } else {
        time += std::to_string(this->remaining_time % 60);
    }
    return time;
}

void World::show_statistics(TextureManager& textureManager, SoundManager& soundManager){
    std::cout << "ya terminamos" << std::endl;

    std::string winner_team;
    if(winner == 0) winner_team = "ROJO";
    if(winner == 1) winner_team = "AZUL";
    if(winner == 3) winner_team = "empate..";

    Texture winner_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended("Winner: ", SDL_Color{255, 255, 255, 255})
        );
    textureManager.renderer.Copy(
        winner_text_sprite, 
        NullOpt, 
        Rect(
            50, 
            50, 
            winner_text_sprite.GetWidth(), 
            winner_text_sprite.GetHeight()));



     Texture winner_team_text_sprite(
            textureManager.renderer,
            textureManager.score_font.RenderText_Blended(winner_team, SDL_Color{255, 255, 255, 255})
        );
    
    textureManager.renderer.Copy(
        winner_team_text_sprite, 
        NullOpt, 
        Rect(
            500, 
            50, 
            winner_text_sprite.GetWidth(), 
            winner_text_sprite.GetHeight()));

    for(size_t i=0; i < this->cars.size(); i++){

        std::string car_number = "Player " + std::to_string(i);

        Texture car_text_sprite(
            textureManager.renderer,
            textureManager.time_font.RenderText_Blended(car_number, SDL_Color{255, 255, 255, 255})
        );
        textureManager.renderer.Copy(
        car_text_sprite, 
        NullOpt, 
        Rect(
            200, 
            100 + 100 * (i+1), 
            car_text_sprite.GetWidth(), 
            car_text_sprite.GetHeight()));

        std::string car_goals = "Goals: " + std::to_string(cars[i].goals);

        Texture goals_text_sprite(
            textureManager.renderer,
            textureManager.time_font.RenderText_Blended(car_goals, SDL_Color{255, 255, 255, 255})
        );
        textureManager.renderer.Copy(
        goals_text_sprite, 
        NullOpt, 
        Rect(
            300, 
            100 + 50 + 100 * (i+1), 
            car_text_sprite.GetWidth(), 
            car_text_sprite.GetHeight()));

        std::string car_assists = "Assists: " + std::to_string(cars[i].assists);

        Texture assists_text_sprite(
            textureManager.renderer,
            textureManager.time_font.RenderText_Blended(car_assists, SDL_Color{255, 255, 255, 255})
        );
        textureManager.renderer.Copy(
        assists_text_sprite, 
        NullOpt, 
        Rect(
            500, 
            100 + 50 + 100 * (i+1),
            car_text_sprite.GetWidth(), 
            car_text_sprite.GetHeight()));

    }




    std::cout << "winner: " << (int)this->winner << std::endl;
    for(size_t i=0; i < this->cars.size(); i++){
        std::cout << "\t car " << (int)i << std::endl;
        std::cout << "\t\t goals:" << (int)cars[i].goals;
        std::cout << "\t\t assists:" << (int)cars[i].assists << std::endl;
    }
}

World::~World(){}
