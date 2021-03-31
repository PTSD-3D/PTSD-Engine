#include "PTSDSound.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_common.h"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include <iostream>

//using namespace FMOD;

namespace PTSD {
	int PTSDSound::init() {
        
        std::cout << "Soy el modulo de sonido. Mis creadores casi se olvidan de mi :/\n";

        FMOD_RESULT result;
        FMOD::System* system = NULL;

        result = FMOD::System_Create(&system);      // Create the main system object.
        if (result != FMOD_OK)
        {
            printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
            exit(-1);
        }

        result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
        if (result != FMOD_OK)
        {
            printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
            exit(-1);
        }

        FMOD::ChannelGroup *channelGroup = nullptr;
        FMOD::Channel* channel = nullptr;
        result = system->createChannelGroup("test", &channelGroup);

        FMOD::Sound *sound;
        result = system->createSound("./assets/clowning-around.mp3", FMOD_CREATESTREAM, 0, &sound);
        result = system->playSound(sound, nullptr, false, &channel);
        result = channel->setChannelGroup(channelGroup);
			return 0;
	}
}