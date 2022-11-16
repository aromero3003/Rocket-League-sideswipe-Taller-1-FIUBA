#include "client_interface.h"
#include <iostream>
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
                    640, 480,
                    0),
                    //SDL_WINDOW_RESIZABLE),
            renderer(window, -1, SDL_RENDERER_ACCELERATED){

	this->world = new World();
}

void Client_interface::run_client(const char *serv, const char *port){

	Texture car(renderer, "../data/cars.png");
	Texture car2(renderer, "../data/cars.png");
	Texture ball(renderer, "../data/ball.png");
	//Texture nitro(renderer, "../data/nitro.png");
	Texture road(renderer, "../data/road.png");
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
        render_screen(car, road, ball, court);

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

void Client_interface::render_screen(Texture& car, Texture& road, Texture& ball, Texture& court){
    	renderer.Clear();
        //renderer.SetDrawColor(0xFF, 0xFF, 0xFF, 0xF);
		renderer.Copy(court,NullOpt,Rect(0,0,renderer.GetOutputWidth(),renderer.GetOutputHeight()));
		renderer.Copy(car,
					Rect(120,110,120,50),
					Rect(renderer.GetOutputWidth()/2 + 10*this->world->car1.x_position,
						renderer.GetOutputHeight()/2 + 120 + (-1)*this->world->car1.y_position,
						120,
						50),
					this->world->car1.angle, 
					NullOpt, 
					SDL_FLIP_NONE
					);
		renderer.Copy(car,
					Rect(250,220,120,50), 
					Rect(renderer.GetOutputWidth()/2 + 10*this->world->car2.x_position,
						renderer.GetOutputHeight()/2 + 120 + (-1)*this->world->car2.y_position,
						120,
						50),
					this->world->car2.angle,
					NullOpt,
					SDL_FLIP_HORIZONTAL);
		renderer.Copy(ball,NullOpt,Rect(renderer.GetOutputWidth()/2 + this->world->ball.x_position,renderer.GetOutputHeight()/2 + (-1)*this->world->ball.y_position,50,50));
		//renderer.Copy(road,NullOpt,Rect(0,renderer.GetOutputHeight()/2 - 75,renderer.GetOutputWidth(), 300));
		//renderer.Copy(car, Rect(src_x,src_y,120,50),Rect((int)position,renderer.GetOutputHeight()/2,120,50));	
		//if(nitroing){
		//  renderer.Copy(nitro, Rect(nitro_x,nitro_y,200,200), Rect((int)position - 55,renderer.GetOutputHeight()/2 + 15,70,20));
		//}
		renderer.Present();
    
}

Client_interface::~Client_interface(){}
/*
	bool is_running_right = false;
	bool is_running_left = false;
	bool nitroing = false;
	int run_phase = -1;      // animation phases
	int nitro_phase = -1;
	float position = 0.0;    // car position

	unsigned int prev_ticks = SDL_GetTicks();

    unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;
*/


/*
		float speed = 0.2;
		if (is_running_left) {
			if (nitroing) speed = 1;
			position -= frame_delta * speed;
			run_phase = (frame_ticks / 100) % 2;
		}
		if (is_running_right) {
			if (nitroing) speed = 1;
			position += frame_delta * speed;
			run_phase = (frame_ticks / 100) % 2;			
		}
		 
		if (!is_running_left && !is_running_right) {
			run_phase = 0;
			nitro_phase = 0;
		}

		if (nitroing) {
			nitro_phase = (frame_ticks / 100) % 8;
		}


		// If player passes past the right side of the window, wrap him
		// to the left side
		if (position > renderer.GetOutputWidth())
			position = -50;

	// fin 

		// Clear screen


		int src_x = 120;
		int src_y = 110;
		
		if (is_running_right || is_running_left) {
			src_x = 243;
		}

		int nitro_x = 0;
		int nitro_y = 0;
		if (nitroing) {
			nitro_x = 250 * nitro_phase;
		}
        */
