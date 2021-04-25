#include "SoundManager.h"
#include "fmod.h"
#include "fmod_common.h"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include <iostream>
#include "fmod.hpp"
#include "LogManager.h"
#include <vector>

#include "Sound.h"
#include "SoundAttorney.h"

namespace PTSD {

    SoundManager* SoundManager::mInstance = nullptr;

    int SoundManager::init()
    {
        PTSD_ASSERT(mInstance == nullptr, "SoundManager already initialized");
        mInstance = new SoundManager();
        //Sound system initialization
        mInstance->result = FMOD::System_Create(&mInstance->sys);
        if (mInstance->result != FMOD_OK) {
            PTSD::LOG("The sound system wasn't created correctly @SoundManager.cpp, init()", PTSD::Critical); //If this one fails, an exception IS going to ocurr.
        }
        
        mInstance->result = mInstance->sys->init(512, FMOD_INIT_NORMAL, 0);    //Not sure about this 512
        if (mInstance->result != FMOD_OK) {
            PTSD::LOG("The sound system wasn't initialized correctly @SoundManager.cpp, init()", PTSD::Critical);
        }
        
        mInstance->genChannelGroups = std::vector<FMOD::ChannelGroup*>(ChannGroupCount, nullptr);

        for (int k = 0; k < ChannGroupCount; k++) {
            mInstance->result = mInstance->sys->createChannelGroup("ch" + k, &mInstance->genChannelGroups[k]); //We could have multiple channel groups: Music/AmbientEffects... so we can handle them more independently
                                                                              //For now I think it's ok to just have 5 (Music, player sounds, enemies? ...).
            if (mInstance->result != FMOD_OK) {
                PTSD::LOG("A channelGroup wasn't created correctly @SoundManager.cpp, init()", PTSD::Error);
            }
        }

        mInstance->genChannels = std::vector<FMOD::Channel*>(mInstance->nChannels, nullptr);

        //Music Channel Group initialization
        mInstance->result = mInstance->sys->createChannelGroup("general", &mInstance->musicChannelGroup);
        if (mInstance->result != FMOD_OK) {
            PTSD::LOG("The Music ChannelGroup wasn't created correctly @SoundManager.cpp, init()", PTSD::Error);
        }

        PTSD::LOG("Finished SoundManager init", PTSD::Trace);

        return 0;
    }

    void SoundManager::update() {
        sys->update();
    }

    void SoundManager::shutdown()
    {
        for (int k = 0; k < ChannGroupCount; k++) {
            genChannelGroups[k]->release();
            musicChannelGroup->release();
        }
    }

    void SoundManager::playSound(const std::string& path, int soundType, float vol, bool loop) {
        currentChannel++;
        if (currentChannel > nChannels) currentChannel = 0;

        FMOD::Sound* fmodSound;
        result = sys->createSound(path.c_str(), FMOD_3D_HEADRELATIVE, NULL, &fmodSound);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be loaded. Please check the file's path @SoundManager.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = sys->playSound(fmodSound, genChannelGroups[soundType], false, &genChannels[currentChannel]);

        if (loop) genChannels[currentChannel]->setMode(FMOD_LOOP_NORMAL);
        else genChannels[currentChannel]->setMode(FMOD_LOOP_OFF);
        genChannels[currentChannel]->setVolume(vol);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be played. Error while trying to play the sound. @SoundManager.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = genChannels[currentChannel]->setChannelGroup(genChannelGroups[soundType]);
        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be added to its channelGroup. @SoundManager.cpp, PlaySound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void SoundManager::playSound(PTSD::Sound *sound)
    {
        playSound(sound->getPath(), sound->getSoundType(), sound->getVolume(), sound->getLoop());
        sound->setChannelPlayed(currentChannel);
    }

    void SoundManager::pauseChannelGroup(int soundType)
    {
        result = genChannelGroups[soundType]->setPaused(true);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be paused. @SoundManager.cpp, PauseSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void SoundManager::pauseSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be paused. It most likely has already ended. @SoundManager.cpp, PauseSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setPaused(true);
        }
    }

    void SoundManager::resumeSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be resumed. It most likely has already ended. @SoundManager.cpp, ResumeSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setPaused(false);
        }
    }

    void SoundManager::muteSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be muted. It most likely has already ended. @SoundManager.cpp, MuteSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setMute(true);
        }
    }

    void SoundManager::unmuteSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be unmuted. It most likely has already ended. @SoundManager.cpp, UnmuteSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->setMute(false);
        }
    }

    void SoundManager::setSoundVolume(PTSD::Sound* sound, float vol) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be paused. It most likely has already ended. @SoundManager.cpp, SetSoundVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            sound->setVolume(vol);
            genChannels[sound->getChannelPlayed()]->setVolume(vol);
        }
    }

    void SoundManager::endSound(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " couldn't be stopped. It most likely has already ended. @SoundManager.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            genChannels[sound->getChannelPlayed()]->stop();
        }
    }

    void SoundManager::setLoopingSound(PTSD::Sound* sound, bool loop) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + " 's looping state couldn't be modified. It most likely has already ended. @SoundManager.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            sound->setLoop(loop);
            if (loop) genChannels[sound->getChannelPlayed()]->setMode(FMOD_LOOP_NORMAL);
            else genChannels[sound->getChannelPlayed()]->setMode(FMOD_LOOP_OFF);
        }
    }

    bool SoundManager::isSoundPaused(PTSD::Sound* sound) {
        FMOD::Sound* currSound;
        result = genChannels[sound->getChannelPlayed()]->getCurrentSound(&currSound);
        if (result != FMOD_OK || SoundAttorney::getFmodSound(sound) != currSound) {
            std::string errMsg = sound->getPath() + "'s paused state couldn't be checked. It most likely has already ended. @SoundManager.cpp, EndSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Warning);
        }
        else {
            bool playing = false;
            return genChannels[sound->getChannelPlayed()]->isPlaying(&playing);
            return playing;
        }
        return false;
    }

    void SoundManager::resumeChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setPaused(false);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be resumed. @SoundManager.cpp, ResumeSound()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }
    
    void SoundManager::muteChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setMute(true);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be muted. @SoundManager.cpp, MuteChannel()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void SoundManager::unmuteChannelGroup(int soundType) {
        result = genChannelGroups[soundType]->setMute(false);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be unmuted. @SoundManager.cpp, UnmuteChannel()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void SoundManager::setChannelGroupVolume(int soundType, float volume)
    {
        genChannelGroups[soundType]->setVolume(volume);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup's volume couldn't be adjusted. @SoundManager.cpp, SetChannelVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    void SoundManager::endChannelGroupSounds(int soundType)
    {
        result = genChannels[soundType]->stop();
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup couldn't be stopped. @SoundManager.cpp, SetChannelVolume()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }
    }

    bool SoundManager::isChannelGroupPaused(int soundType)
    {
        bool paused;
        result = genChannels[soundType]->isPlaying(&paused);
        if (result != FMOD_OK) {
            std::string errMsg = soundType + " channelGroup's paused state couldn't be checked. @SoundManager.cpp, isChannelPaused()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        return paused;
    }

    void SoundManager::playMusic(const std::string& path, bool loop)
    {
        bool needsToBeAdded = false;
        if (musicChannel == nullptr) needsToBeAdded = true;

        FMOD::Sound* sound;
        result = sys->createSound(path.c_str(), FMOD_CREATESTREAM, NULL, &sound);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be loaded. Please check the file's path @SoundManager.cpp, PlayMusic()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        if (loop) {
            result = sound->setMode(FMOD_LOOP_NORMAL);
        }

        result = sys->playSound(sound, musicChannelGroup, false, &musicChannel);

        if (result != FMOD_OK) {
            std::string errMsg = path + " couldn't be played. Error while trying to play the music. @SoundManager.cpp, PlayMusic()";
            PTSD::LOG(errMsg.c_str(), PTSD::Error);
        }

        result = musicChannel->setChannelGroup(musicChannelGroup);

        if (result != FMOD_OK) {
            PTSD::LOG("Error at assigning musicChannel to its channelGroup @SoundManager.cpp, PlayMusic()", PTSD::Error);
        }

    }

    void SoundManager::changeMusic(const std::string& path, bool loop)
    {
        FMOD::Sound* sound = nullptr;
        musicChannel->getCurrentSound(&sound);
        if (sound != nullptr) sound->release();

        playMusic(path, loop);
    }

    void SoundManager::pauseMusic()
    {
        result = musicChannel->setPaused(true);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be paused @SoundManager.cpp, PauseMusic()", PTSD::Error);
        }
    }

    void SoundManager::resumeMusic()
    {
        result = musicChannel->setPaused(false);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be resumed @SoundManager.cpp, ResumeMusic()", PTSD::Error);
        }
    }

    void SoundManager::muteMusic()
    {
        result = musicChannel->setMute(false);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be muted @SoundManager.cpp, MuteMusic()", PTSD::Error);
        }
    }

    void SoundManager::unmuteMusic()
    {
        result = musicChannel->setMute(true);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel couldn't be unmuted @SoundManager.cpp, UnmuteMusic()", PTSD::Error);
        }
    }

    void SoundManager::setMusicVolume(float vol)
    {
        result = musicChannel->setVolume(vol);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel's volume couldn't be adjusted @SoundManager.cpp, SetMusicVolume()", PTSD::Error);
        }
    }

    bool SoundManager::isMusicPaused()
    {
        bool paused;
        result = musicChannel->isPlaying(&paused);
        if (result != FMOD_OK) {
            PTSD::LOG("musicChannel's paused state couldn't be checked. @SoundManager.cpp, isChannelPaused()", PTSD::Error);
        }

        return paused;
    }
}