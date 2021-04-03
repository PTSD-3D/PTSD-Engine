#include "SoundAttorney.h"
#include "Sound.h"

namespace PTSD {
    FMOD::Sound* Attorney::getFmodSound(Sound* sound) {
        return sound->getFmodSound();
    }
}