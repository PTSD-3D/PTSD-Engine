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
	int PTSDSound::test() {
        
        std::cout << "Soy el modulo de sonido. Mis creadores casi se olvidan de mi!!";

        FMOD_RESULT result;
        FMOD::System* system = nullptr;
        result = FMOD::System_Create(&system); // Create the Studio System object.
        if (result != FMOD_OK)
        {
            std::cout << ("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
            exit(-1);
        }

        // Initialize FMOD Studio, which will also initialize FMOD Core
        result = system->init(512, 0, FMOD_INIT_NORMAL);
        if (result != FMOD_OK)
        {
            printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
            exit(-1);
        }

	}
}