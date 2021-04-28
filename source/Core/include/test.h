#pragma once

#include "SoundManager.h"
#include <memory>
#include "TransformComponent.h"
#include "Entity.h"
#include <OgreEntity.h>
#include "Rigidbody.h"
//#include <Windows.h> //Please keep me commented if you are finished testing or Ricardo will kill you.
#include "MeshComponent.h"
namespace PTSD
{
	//This needs to be kept commented because Sleep() is a function from Windows, so it wouldn't work on Linux

	static void test_Sound(SoundManager* m_soundSystem) {
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

	static PTSD::TransformComponent* test_Transform_Setup(std::shared_ptr<PTSD::Entity> sinbad) {
		// PTSD::TransformComponent* transform = sinbad->addComponent<PTSD::TransformComponent>();
		// sinbad->addComponent<PTSD::MeshComponent>("ogrehead.mesh");
		// transform->setPosition(10, 0, 0);
		// transform->setRotation(0, 90, 0);
		// transform->setScale(0.5, 0.5, 0.5);
		// return transform;
		return nullptr;
	}

	void test_Rigidbody_Setup(std::shared_ptr<PTSD::Entity> sinbad) {
		PTSD::Rigidbody* rb = sinbad->addComponent<PTSD::Rigidbody>(1, 1, Vec3Placeholder(1,1,1));
		rb->setLinearVelocity(Vec3Placeholder(10, 0, 0));
	}

	static void test_Transform_Update(PTSD::TransformComponent* transform) {
		// transform->translate(Vec3Placeholder(0.1, 0, 0));
		// transform->rotate(Vec3Placeholder(0, 3, 0));
		//PTSD::LOG(std::to_string(transform->getPosition().x).c_str(), PTSD::Info);
		//PTSD::LOG(std::to_string(transform->getRotation().y).c_str(), PTSD::Info);
	}

}