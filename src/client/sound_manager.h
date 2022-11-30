#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2pp/SDL2pp.hh>

class SoundManager {
    public:
    SDL2pp::Mixer mixer;
    SDL2pp::Chunk ingition_sound;
	SDL2pp::Chunk ball_sound;
	SDL2pp::Chunk nitro_sound;

    SoundManager();

    ~SoundManager();
};

#endif