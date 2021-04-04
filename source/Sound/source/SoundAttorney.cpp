#include "SoundAttorney.h"
#include "Sound.h"

namespace PTSD {
    FMOD::Sound* SoundAttorney::getFmodSound(Sound* sound) {
        return sound->getFmodSound();
    }
}