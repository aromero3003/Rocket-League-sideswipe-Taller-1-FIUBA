#include "client_interface.h"
#include <iostream>
#include <vector>
#include <exception>
#include <chrono>
#include <string>

Client_interface::Client_interface(const char *serv, const char *port): 
            sdl(SDL_INIT_VIDEO), 
            window("Rocket League 2D",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    1040, 600,
                    0),
            renderer(window, -1, SDL_RENDERER_ACCELERATED),
			mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096){

	this->world = new World();
	this->socket = new Socket(serv, port);
	this->pq = new BlockingQueue<int>();
}

void Client_interface::run_client(){
	int n_cars = 2;

	MenuThread menuThread(this->socket, n_cars);
	menuThread.start();
	menuThread.join();



	//create N cars and car_textures
	this->world->create_cars(n_cars);
	std::vector<Texture> car_textures;
	for(int i = 0; i < n_cars; i++){
		car_textures.emplace_back(renderer, "../data/cars.png");
	}

	//load textures and sounds
	Texture ball(renderer, "../data/ball.png");
	Texture court(renderer, "../data/court.png");

	Chunk sound("../data/car_ignition.wav");
	Chunk ball_sound("../data/ball_bounce.wav");

	//launch threads
	ReceiverThread receiver(this->socket,this->world, n_cars);
	SenderThread sender(this->socket, this->pq);
	receiver.start();
	sender.start();

	// Main loop

    bool running = true;
    bool going_right, going_left, jumping, nitroing = false;

    uint32_t t1 = SDL_GetTicks();
	while (running) {

        running = handle_events(pq, going_right, going_left, nitroing, jumping);
		render_screen_and_sounds(car_textures, ball, court, ball_sound);

        //Constant Rate Loop
        int32_t t2 = SDL_GetTicks();
        int32_t rest = FRAME_RATE - (t2-t1);
        if(rest < 0) {
            int32_t behind = (-1)*rest;
            rest = FRAME_RATE - (behind % FRAME_RATE);
            int32_t lost = behind + rest;
            t1 += lost;
        } else {
		    SDL_Delay(rest);
        }
        t1 += FRAME_RATE;
        //Constant Rate Loop
	}
	mixer.HaltChannel(-1);
}


void Client_interface::render_screen_and_sounds(std::vector<Texture>& car_textures, Texture& ball, Texture& court, Chunk& ball_sound){
		renderer.Clear();
		this->world->draw(car_textures, ball, court, renderer, ball_sound, mixer);	
		renderer.Present();
}

bool Client_interface::handle_events(BlockingQueue<int>* pq, bool& going_right, bool& going_left, bool& nitroing, bool& jumping) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { 
				return false;
				} else if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: case SDLK_q:
								//pq->push(QUIT);
								return false;
						case SDLK_RIGHT:
                            if(!going_right) pq->push(PRESS_RIGHT);
                            going_right = true;
							break;
						case SDLK_LEFT: 
							if(!going_left) pq->push(PRESS_LEFT);
                            going_left = true;
							break;
                        case SDLK_LSHIFT: 
							if(!nitroing) pq->push(PRESS_SHIFT);
                            nitroing = true;
							break;
						case SDLK_SPACE:
							if(!jumping) pq->push(PRESS_SPACE);
                            jumping = true;
							break;
						}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT: 
						pq->push(RELEASE_RIGHT);
                        going_right = false;
						break;
					case SDLK_LEFT: 
						pq->push(RELEASE_LEFT);
                        going_left = false;
						break;
					case SDLK_SPACE:
						pq->push(RELEASE_SPACE);
                        jumping = false;
						break;
					case SDLK_LSHIFT:
						pq->push(RELEASE_SHIFT);
						nitroing = false;
						break;
				}
			}
		}
    return true;
}


Client_interface::~Client_interface(){
	delete this->socket;
	delete this->pq;
}
