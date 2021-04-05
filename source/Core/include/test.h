#pragma once

#include "PTSDSound.h"
#include <iostream>
//#include <Windows.h> //Please keep me commented if you are finished testing or Ricardo will kill you.

namespace PTSD
{
	//This needs to be kept commented because Sleep() is a function from Windows, so it wouldn't work on Linux

	static void test_Sound(PTSDSound* m_soundSystem) {
		//std::cout << "This is a sample test for the sound module. @test.cpp, test_Sound()\n If you don't want to test this again, please comment the call to this function in the main() function\n";
		//m_soundSystem->playMusic("./assets/PTSD-Anthem.mp3", true);
		//Sleep(500);
		//m_soundSystem->setMusicVolume(0.2);
		//Sleep(1000);
		//m_soundSystem->changeMusic("./assets/PTSD-Anthem2.mp3", true);
		//m_soundSystem->setMusicVolume(0.5);
		//Sleep(1000);
		//for (int k = 0; k < PTSD::ChannGroupCount; k++) {
		//	for (int l = 0; l < 5; l++) {
		//		if (l == 2) m_soundSystem->setChannelGroupVolume(1, 10);
		//		Sound* oof = new Sound("./assets/oof.mp3", k);
		//		oof->setVolume(0.2 * k * l + 1);
		//		m_soundSystem->playSound(oof);
		//		Sleep(500);
		//	}
		//}
		//std::cout << "Sound testing complete!!!\n";
	}
}