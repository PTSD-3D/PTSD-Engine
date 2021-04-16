#include <string>

namespace FMOD {
	class Sound;
}

//In order to play a sound, you need to create this class, and then pass its pointer to the SoundManager singleton (PlaySound())

namespace PTSD {
	class Sound {
	private:
		std::string path;
		int channelPlayed = -1; //-1 is not being played at any channel
		int soundType; //Ambient, PlayerEffects, Dialog. See the enum at SoundManager
		float volume = 1; //1 is max volume
		bool loop = false;

		FMOD::Sound* fmodSound; 
		FMOD::Sound* getFmodSound(); //Can be accesed by SoundManager. See class SoundAttorney

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

		friend class SoundAttorney;
	};
}