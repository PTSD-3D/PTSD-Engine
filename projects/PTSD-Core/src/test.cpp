#include "test.h"
#include <iostream>
#include <OgreRoot.h>

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>


namespace PTSD
{
	void test()
	{
		std::cout << "Hola Proyecto\n";

		Ogre::Root* root;
		root = new Ogre::Root();

		std::cout << "Hola Ogre\n";
	}
}