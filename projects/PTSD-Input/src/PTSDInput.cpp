#include "PTSDInput.h"

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include <iostream>

namespace PTSD {

	int Input::init() {

		SDL_Init(SDL_INIT_EVERYTHING);

		if (!SDL_WasInit(SDL_INIT_VIDEO))
			SDL_InitSubSystem(SDL_INIT_VIDEO);

		Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

		SDL_Window* sdlWindow = SDL_CreateWindow("HOLI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 300, flags);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);

		//////////For the window to hide the cursor
		SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
		SDL_ShowCursor(false);

		SDL_Event e;

		bool exit = false;

		while (!exit) {

			SDL_PollEvent(&e);
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					std::cout << "Wenas tardes, aqui tu morenito SDL" << "\n";
					exit = true;
					break;
				}
			}

		}

		return 0;
	}
}