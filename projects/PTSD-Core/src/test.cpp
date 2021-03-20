#include "test.h"
#include <iostream>
#include <OgreRoot.h>
//#include <SDL.c>


namespace PTSD
{
	void test()
	{
		std::cout << "Hola Proyecto\n";

		Ogre::Root* root;
		root = new Ogre::Root();

		root->createRenderWindow("hola", 400, 300, false);

		//SDL.c esta en PTSD-Engine\dependencies\Ogre\build\SDL2-2.0.10\src\SDL.c

		//SDL_Init(SDL_INIT_EVERYTHING);

		//SDL_Surface* screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);;

		//Ogre::RenderWindow* window;
		//root->initialise(false);

		//SDL_SysWMinfo wmi;
		//SDL_VERSION(&wmi.version);

		//SDL_GetWMInfo(&wmi);


		//Ogre::NameValuePairList misc;
		//misc["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned int)wmi.window);
		//window = root->createRenderWindow("Render Window", 800, 600, false, &misc);

		std::cout << "Hola Ogre\n";
	}
}