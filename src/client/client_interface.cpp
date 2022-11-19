#include "client_interface.h"
#include <iostream>
#include <vector>
#include <exception>
#include <chrono>
#include <string>

#define PRESS_RIGHT 65
#define PRESS_LEFT 66
#define PRESS_SPACE 67
#define PRESS_UP 71
#define RELEASE_RIGHT 68
#define RELEASE_LEFT 69
#define RELEASE_SPACE 70
#define RELEASE_UP 72

#define FRAME_RATE 1000/120

#define QUIT 99


Client_interface::Client_interface(): 
            sdl(SDL_INIT_VIDEO), 
            window("Rocket League 2D",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    920, 600,
                    SDL_WINDOW_RESIZABLE),
                    //SDL_WINDOW_RESIZABLE),
            renderer(window, -1, SDL_RENDERER_ACCELERATED){

	this->world = new World();
}

void Client_interface::run_client(const char *serv, const char *port){

	int n_cars = 2;
	this->world->create_cars(n_cars);

	std::vector<Texture> car_textures;

	for(int i = 0; i < n_cars; i++){
		car_textures.emplace_back(renderer, "../data/cars.png");
	}
	Texture ball(renderer, "../data/ball.png");
	Texture court(renderer, "../data/court.png");

	BlockingQueue<int>* pq = new BlockingQueue<int>();
	Socket* s = new Socket(serv, port);

	ReceiverThread receiver(s,this->world);
	SenderThread sender(s, pq);
	receiver.start();
	sender.start();

	// Main loop

    bool running = true;
    bool going_right, going_left, jumping, nitroing = false;

    uint32_t t1 = SDL_GetTicks();
	while (running) {
        running = handle_events(pq, going_right, going_left, nitroing, jumping);
		render_screen(car_textures, ball, court);

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
    delete pq;
    delete s;
}


void Client_interface::render_screen(std::vector<Texture>& car_textures, Texture& ball, Texture& court){
    	renderer.Clear();
		this->world->draw(car_textures, ball, court, renderer);		
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
								pq->push(QUIT);
								return false;
						case SDLK_RIGHT:
                            if(!going_right) pq->push(PRESS_RIGHT);
                            going_right = true;
							break;
						case SDLK_LEFT: 
							if(!going_left) pq->push(PRESS_LEFT);
                            going_left = true;
							break;
                        case SDLK_UP: 
							if(!jumping) pq->push(PRESS_UP);
                            jumping = true;
							break;
						case SDLK_SPACE:
							if(!nitroing) pq->push(PRESS_SPACE);
                            nitroing = true;
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
                        nitroing = false;
						break;
					case SDLK_UP:
						jumping = false;
				}
			}
		}
    return true;
}


Client_interface::~Client_interface(){}
