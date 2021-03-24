#include <iostream>
#include "PTSDGraphics.h"
#include <OgreRoot.h>

namespace PTSD {
	int Graphics::Init() {
		std::cout << "Graphics system initialized\n";
		Ogre::Root* root;
		root = new Ogre::Root();
		return 0;
	}
}