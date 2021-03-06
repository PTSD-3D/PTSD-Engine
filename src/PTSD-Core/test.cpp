#include "test.h"
#include <iostream>
#include <OgreRoot.h>


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