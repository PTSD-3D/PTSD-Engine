#include <string>

namespace FMOD {
	class Sound;
}

namespace PTSD {
	class Sound {
	private:
		std::string path;
		int channelPlayed = -1; //-1 is not being played at any channel
		int soundType;
		float volume = 1;
		bool loop = false;

		FMOD::Sound* fmodSound;
		FMOD::Sound* getFmodSound();

	public:
		Sound(std::string path, int soundType);

		//Setters
		void setVolume(float v);
		void setLoop(bool l);
		void setChannelPlayed(int c);

		//Getters
		std::string getPath();
		int getChannelPlayed();
		int getSoundType();
		int getVolume();
		bool getLoop();

		friend class Attorney;
	};
}