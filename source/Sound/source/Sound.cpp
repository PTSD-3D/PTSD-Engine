#pragma once
#include "Sound.h"

namespace PTSD {
    Sound::Sound(const std::string& p, int type)
    {
        path = p;
        soundType = type;
    }

    void Sound::setVolume(float v)
    {
        volume = v;
    }

    void Sound::setLoop(bool l)
    {
        loop = l;
    }

    void Sound::setChannelPlayed(int c)
    {
        channelPlayed = c;
    }

    const std::string& Sound::getPath()
    {
        return path;
    }

    int Sound::getChannelPlayed()
    {
        return channelPlayed;
    }

    int Sound::getSoundType()
    {
        return soundType;
    }

    bool Sound::getLoop()
    {
        return loop;
    }

    int Sound::getVolume() {
        return volume;
    }

    //Only accesible by PTSD-Sound
    FMOD::Sound* Sound::getFmodSound() {
        return fmodSound;
    }
}