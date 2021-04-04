#pragma once
#include <vector>
#include <string>

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

enum FMOD_RESULT;

namespace PTSD {
	enum SoundChannels {
		Ambient,
		PlayerEffects,
		Dialog,
		ChannGroupCount,
	};

	class PTSDSound
	{
	private:
		static PTSDSound* mInstance;
		FMOD::System* sys = nullptr;
		//FMOD::ChannelGroup* genChannelGroup = nullptr;
		FMOD::ChannelGroup* musicChannelGroup = nullptr;
		std::vector<FMOD::ChannelGroup*> genChannelGroups;
		std::vector<FMOD::Channel*> genChannels;
		FMOD::Channel* musicChannel = nullptr;
		FMOD_RESULT result;
		int nChannels = 128; //ATM this is arbitrary. It could be configured by the developer.
		int currentChannel = -1;

	public:
		PTSDSound() = default;
		~PTSDSound() = default;
		int Init();
		void update();
		static PTSDSound* getInstance() {
			if (mInstance == nullptr) mInstance = new PTSDSound();
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
		void playSound(std::string path, int soundType, float vol = 1, bool loop = false);
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
		void playMusic(std::string path, bool loop);
		void changeMusic(std::string path, bool loop);
		void pauseMusic();
		void resumeMusic();
		void muteMusic();
		void unmuteMusic();
		void setMusicVolume(float vol);
		bool isMusicPaused();
	};
}