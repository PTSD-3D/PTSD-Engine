#include "PTSDSound.h"
#include "fmod.h"
#include "fmod_common.h"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include <iostream>
#include "fmod.hpp"
#include "PTSDLog.h"
#include <vector>

#include "Sound.h"
#include "SoundAttorney.h"

namespace PTSD {

    PTSDSound* PTSDSound::mInstance = nullptr;

    int PTSDSound::Init()
    {
        //Sound system initialization
        result = FMOD::System_Create(&sys);
        if (result != FMOD_OK) {
            PTSD::LOG("The sound system wasn't created correctly @PTSDSound.cpp, Init()", PTSD::Critical); //If this one fails, an exception IS going to ocurr.
        }
        
        result = sys->init(512, FMOD_INIT_NORMAL, 0);    //Not sure about this 512
        if (result != FMOD_OK) {
            PTSD::LOG("The sound system wasn't initialized correctly @PTSDSound.cpp, Init()", PTSD::Critical);
        }
        
        genChannelGroups = std::vector<FMOD::ChannelGroup*>(ChannGroupCount, nullptr);

        for (int k = 0; k < ChannGroupCount; k++) {
            result = sys->createChannelGroup("ch" + k, &genChannelGroups[k]); //We could have multiple channel groups: Music/AmbientEffects... so we can handle them more independently
                                                                              //For now I think it's ok to just have 5 (Music, player sounds, enemies? ...).
            if (result != FMOD_OK) {
                PTSD::LOG("A channelGroup wasn't created correctly @PTSDSound.cpp, Init()", PTSD::Error);
            }
        }

        genChannels = std::vector<FMOD::Channel*>(nChannels, nullptr);

        //Music Channel Group initialization
        result = sys->createChannelGroup("general", &musicChannelGroup);
        if (result != FMOD_OK) {
            PTSD::LOG("The Music ChannelGroup wasn't created correctly @PTSDSound.cpp, Init()", PTSD::Error);
        }

        PTSD::LOG("Finished PTSDSound Init", PTSD::Trace);

        return 0;
    }

    void PTSDSound::update() {
        sys->update();
    }

    void PTSDSound::shutdown()
    {
        for (int k = 0; k < ChannGroupCount; k++) {
            genChannelGroups[k]->release();
            musicChannelGroup->release();
        }
    }

    void PTSDSound::playSound(const std::string& path, int soundType, float vol, bool loop) {
        currentChannel++;
        if (currentChannel > nChannels) currentChannel = 0;

        FMOD::Sound* fmodSound;
        result = sys->createSound(path.c_str(), FMOD_3D_HEADRELATIVE, NULL, &fmodSound);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be loaded. Please check the file's path @PTSDSound.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = sys->playSound(fmodSound, genChannelGroups[soundType], false, &genChannels[currentChannel]);

        if (loop) genChannels[currentChannel]->setMode(FMOD_LOOP_NORMAL);
        else genChannels[currentChannel]->setMode(FMOD_LOOP_OFF);
        genChannels[currentChannel]->setVolume(vol);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be played. Error while trying to play the sound. @PTSDSound.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = genChannels[currentChannel]->setChannelGroup(genChannelGroups[soundType]);
        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be added to its channelGroup. @PTSDSound.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void PTSDSound::playSound(PTSD::Sound *sound)
    {
        playSound(sound->getPath(), sound->getSoundType(), sound->getVolume(), sound->getLoop());
        sound->setChannelPlayed(currentChannel);
    }

    void PTSDSound::pauseChannelGroup(int soundType)
    {
        result = genChannelGroups[soundType]->setPaused(true);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be paused. @PTSDSound.cpp, PauseSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void PTSDSound::pauseSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be paused. It most likely has already ended. @PTSDSound.cpp, PauseSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setPaused(true);
        }
    }

    void PTSDSound::resumeSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be resumed. It most likely has already ended. @PTSDSound.cpp, ResumeSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setPaused(false);
        }
    }

    void PTSDSound::muteSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be muted. It most likely has already ended. @PTSDSound.cpp, MuteSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setMute(true);
        }
    }

    void PTSDSound::unmuteSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be unmuted. It most likely has already ended. @PTSDSound.cpp, UnmuteSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setMute(false);
        }
    }

    void PTSDSound::setSoundVolume(PTSD::Sound* sound, float vol) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be paused. It most likely has already ended. @PTSDSound.cpp, SetSoundVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            sound->setVolume(vol);
            genChannels[sound->getChannelPlayed()]->setVolume(vol);
        }
    }

    void PTSDSound::endSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be stopped. It most likely has already ended. @PTSDSound.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->stop();
        }
    }

    void PTSDSound::setLoopingSound(PTSD::Sound* sound, bool loop) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " 's looping state couldn't be modified. It most likely has already ended. @PTSDSound.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            sound->setLoop(loop);
            if (loop) genChannels[sound->getChannelPlayed()]->setMode(FMOD_LOOP_NORMAL);
            else genChannels[sound->getChannelPlayed()]->setMode(FMOD_LOOP_OFF);
        }
    }

    bool PTSDSound::isSoundPaused(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + "'s paused state couldn't be checked. It most likely has already ended. @PTSDSound.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            bool playing = false;
            return genChannels[sound->getChannelPlayed()]->isPlaying(&playing);
            return playing;
        }
        return false;
    }

    void PTSDSound::resumeChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setPaused(false);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be resumed. @PTSDSound.cpp, ResumeSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }
    
    void PTSDSound::muteChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setMute(true);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be muted. @PTSDSound.cpp, MuteChannel()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void PTSDSound::unmuteChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setMute(false);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be unmuted. @PTSDSound.cpp, UnmuteChannel()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void PTSDSound::setChannelGroupVolume(int soundType, float volume)
    {
        genChannelGroups[soundType]->setVolume(volume);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup's volume couldn't be adjusted. @PTSDSound.cpp, SetChannelVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void PTSDSound::endChannelGroupSounds(int soundType)
    {
        result = genChannels[soundType]->stop();
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be stopped. @PTSDSound.cpp, SetChannelVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    bool PTSDSound::isChannelGroupPaused(int soundType)
    {
        bool paused;
        result = genChannels[soundType]->isPlaying(&paused);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup's paused state couldn't be checked. @PTSDSound.cpp, isChannelPaused()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        return paused;
    }

    void PTSDSound::playMusic(const std::string& path, bool loop)
    {
        bool needsToBeAdded = false;
        if (musicChannel == nullptr) needsToBeAdded = true;

        FMOD::Sound* sound;
        result = sys->createSound(path.c_str(), FMOD_CREATESTREAM, NULL, &sound);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be loaded. Please check the file's path @PTSDSound.cpp, PlayMusic()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        if (loop) {
            result = sound->setMode(FMOD_LOOP_NORMAL);
        }

        result = sys->playSound(sound, musicChannelGroup, false, &musicChannel);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be played. Error while trying to play the music. @PTSDSound.cpp, PlayMusic()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = musicChannel->setChannelGroup(musicChannelGroup);

        if (result != FMOD_OK) {
            PTSD::LOG("Error at assigning musicChannel to its channelGroup @PTSDSound.cpp, PlayMusic()", PTSD::Error);
        }

    }

    void PTSDSound::changeMusic(const std::string& path, bool loop)
    {
        FMOD::Sound* sound = nullptr;
        musicChannel->getCurrentSound(&sound);
        if (sound != nullptr) sound->release();

        playMusic(path, loop);
    }

    void PTSDSound::pauseMusic()
    {
        result = musicChannel->setPaused(true);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be paused @PTSDSound.cpp, PauseMusic()", PTSD::Error);
        }
    }

    void PTSDSound::resumeMusic()
    {
        result = musicChannel->setPaused(false);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be resumed @PTSDSound.cpp, ResumeMusic()", PTSD::Error);
        }
    }

    void PTSDSound::muteMusic()
    {
        result = musicChannel->setMute(false);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be muted @PTSDSound.cpp, MuteMusic()", PTSD::Error);
        }
    }

    void PTSDSound::unmuteMusic()
    {
        result = musicChannel->setMute(true);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be unmuted @PTSDSound.cpp, UnmuteMusic()", PTSD::Error);
        }
    }

    void PTSDSound::setMusicVolume(float vol)
    {
        result = musicChannel->setVolume(vol);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel's volume couldn't be adjusted @PTSDSound.cpp, SetMusicVolume()", PTSD::Error);
        }
    }

    bool PTSDSound::isMusicPaused()
    {
        bool paused;
        result = musicChannel->isPlaying(&paused);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel's paused state couldn't be checked. @PTSDSound.cpp, isChannelPaused()", PTSD::Error);
        }

        return paused;
    }
}