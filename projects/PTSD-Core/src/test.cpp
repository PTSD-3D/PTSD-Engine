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


		SDL_Init(SDL_INIT_EVERYTHING);

		if (!SDL_WasInit(SDL_INIT_VIDEO))
			SDL_InitSubSystem(SDL_INIT_VIDEO);

		Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

		SDL_Window* sdlWindow = SDL_CreateWindow("HOLI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 300, flags);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
				"Couldn't get WM Info! (SDL2)",
				"BaseApplication::setup");
		}

		Ogre::NameValuePairList params;

		/*params["FSAA"] = CurrentGraphicsConfiguration["FSAA"].currentValue;
		params["vsync"] = false;
		params["gamma"] = false;

		params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));*/

		//root->createRenderWindow("HOLI", 200, 200, false);


		//////////por si queremos que la ventana oculte el cursor
		SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
		SDL_ShowCursor(false);

		SDL_Event e;

		bool paco = false;

		while (!paco) {

			SDL_PollEvent(&e);
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					std::cout << "Wenas tardes" << "\n";
					paco = true;
					break;
				}
			}
			
		}

		std::cout << "Hola Ogre\n";
	}
}