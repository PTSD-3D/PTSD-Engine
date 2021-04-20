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

// enum FMOD_RESULT;

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
		FMOD::ChannelGroup* musicChannelGroup = nullptr;
		std::vector<FMOD::ChannelGroup*> genChannelGroups;
		std::vector<FMOD::Channel*> genChannels;
		FMOD::Channel* musicChannel = nullptr;
		int result;
		int nChannels = 128; //ATM this is arbitrary. It could be configured by the developer.
		int currentChannel = -1;

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

		//ChannelGroupManagement
		//From each channelGroup, you can manage the volume of each sound Type (ambient, dialog...)
		void pauseChannelGroup(int soundType);
		void resumeChannelGroup(int soundType);
		void muteChannelGroup(int soundType);
		void unmuteChannelGroup(int soundType);
		void setChannelGroupVolume(int soundType, float vol);
		void endChannelGroupSounds(int soundType);
		bool isChannelGroupPaused(int soundType);

		//Sound Management
		//With these functions you can modify specific sounds.
		void playSound(PTSD::Sound* sound);
		void playSound(const std::string& path, int soundType, float vol = 1, bool loop = false);
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
		void changeMusic(const std::string& path, bool loop);
		void pauseMusic();
		void resumeMusic();
		void muteMusic();
		void unmuteMusic();
		void setMusicVolume(float vol);
		bool isMusicPaused();
	};
}