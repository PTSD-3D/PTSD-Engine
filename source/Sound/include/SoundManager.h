#pragma once
#include <vector>
#include <string>

#include "PTSDAssert.h"

namespace PTSD {
	class Sound;
}

namespace FMOD { //This is so we trick the .h into not exploding into pieces.
	class System;
	class Sound;
	class ChannelGroup;
	class Channel;
	class Sound;
}

struct SoundData { //This type structure will be used to store the sound information provided by the developer. See resources.lua
	FMOD::Sound* fmodSound;
	std::string path;
	int soundType;
	int soundChannel;
	float volume;
	SoundData(FMOD::Sound* fmodSound, const std::string& path, int type,int channel,const float& volume):
		fmodSound(fmodSound), path(path),soundType(type),soundChannel(channel),volume(volume){};
};

namespace PTSD {
	enum SoundChannels {
		Ambient,
		PlayerEffects,
		Dialog,
		ChannGroupCount,
	};

	class SoundManager
	{
	private:
		static SoundManager* mInstance;
		FMOD::System* sys = nullptr;
		//FMOD::ChannelGroup* genChannelGroup = nullptr;
		std::vector<SoundData> loadedSounds;
		FMOD::ChannelGroup* musicChannelGroup = nullptr;
		std::vector<FMOD::ChannelGroup*> genChannelGroups;
		std::vector<FMOD::Channel*> genChannels;
		FMOD::Channel* musicChannel = nullptr;
		int result;
		int nChannels = 128; //ATM this is arbitrary. It could be configured by the developer.
		int currentChannel = -1;
		static void EndOfSound(int currentChannel);

	public:
		SoundManager() = default;
		~SoundManager() = default;
		static int init();
		void update();
		static SoundManager* getInstance() {
			PTSD_ASSERT(mInstance != nullptr, "SoundManager accessed before init");
			return mInstance;
		}
		void shutdown();
		int loadSound(const std::string& path, int soundType, int channelType, float volume);

		//Channel Group Management
		//From each channelGroup, you can manage the volume of each sound Type (ambient, dialog...)
		void pauseChannelGroup(int soundType);
		void resumeChannelGroup(int soundType);
		void muteChannelGroup(int soundType);
		void unmuteChannelGroup(int soundType);
		void setChannelGroupVolume(int soundType, float vol);
		void endChannelGroupSounds(int soundType);
		bool isChannelGroupPaused(int soundType);

		
		//Individual Channel Management
		bool muteChannel(int channelId);
		bool resumeChannel(int channelId);
		bool setChannelVolume(int channelId, float volume);

		//Sound Management
		//With these functions you can modify specific sounds.
		void playSound(PTSD::Sound* sound);
		void playSound(const std::string& path, int soundType, float vol = 1, bool loop = false);
		int playSound(int id);
		void pauseSound(PTSD::Sound* sound);
		void resumeSound(PTSD::Sound* sound);
		void muteSound(PTSD::Sound* sound);
		void unmuteSound(PTSD::Sound* sound);
		void setSoundVolume(PTSD::Sound* sound, float vol);
		void setLoopingSound(PTSD::Sound* sound, bool loop);
		void endSound(PTSD::Sound* sound);
		bool isSoundPaused(PTSD::Sound* sound);

		//Music Management
		//Only 1 song can be played at a time. This could be improved upon in the future.
		void playMusic(const std::string& path, bool loop);
		void playMusic(int id, bool loop);
		void changeMusic(const std::string& path, bool loop);
		void pauseMusic();
		void resumeMusic();
		void muteMusic();
		void unmuteMusic();
		void setMusicVolume(float vol);
		bool isMusicPaused();
	};
}