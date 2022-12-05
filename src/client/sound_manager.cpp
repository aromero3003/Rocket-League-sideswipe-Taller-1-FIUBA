#include "sound_manager.h"

SoundManager::SoundManager():mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
                            ingition_sound("../data/car_ignition.wav"),
	                        ball_sound("../data/ball_bounce.wav"),
	                        nitro_sound("../data/nitro2.wav"),
							goal_sound("../data/goal_sound.wav"){
}

SoundManager::~SoundManager(){}