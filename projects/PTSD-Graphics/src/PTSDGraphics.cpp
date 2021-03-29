#include <iostream>
#include "PTSDGraphics.h"
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include "GraphicsLogger.hpp"

namespace PTSD {
	int Graphics::Init() {
		Ogre::LogManager* logMgr = new Ogre::LogManager();
		Ogre::Log* log = Ogre::LogManager::getSingleton().createLog("logs/Ogre.log", true, false, true);
		log->addListener(new PTSDLogListener());
		Ogre::Root* root;
		root = new Ogre::Root();
		Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("GET OUT OF MY SWAMP",Ogre::LML_WARNING);
		PTSD::LOG("Graphics system initialized");
		return 0;
	}
}