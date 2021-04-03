namespace FMOD {
	class Sound;
}

namespace PTSD {
	class Sound;
}

namespace PTSD {
	//The user can't have access to GetFmodSound() from the Sound class.
	//This attorney-client structure provides specific access to a select amount of members of the class.
	//For more information, check https://en.wikibooks.org/wiki/More_C++_Idioms/Friendship_and_the_Attorney-Client
	class Attorney {
	private:
		static FMOD::Sound* getFmodSound(Sound* sound);
		friend class PTSDSound;
	};
}