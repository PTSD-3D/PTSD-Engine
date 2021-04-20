#pragma once
#include <OgreLogManager.h>
#include <OgreLog.h>
#include "LogManager.h"


	class PTSDLogListener : public Ogre::LogListener
	{
		PTSD::LogLevel OgreToPTSDVerbosity(Ogre::LogMessageLevel lml)
		{
			PTSD::LogLevel ret = PTSD::Trace;
			switch (lml)
			{
			case Ogre::LML_TRIVIAL:
				ret = PTSD::Trace;
				break;
			case Ogre::LML_NORMAL:
				ret = PTSD::Info;
				break;
			case Ogre::LML_WARNING:
				ret = PTSD::Warning;
				break;
			case Ogre::LML_CRITICAL:
				ret = PTSD::Critical;
				break;
			}
			return ret;
		}
		void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String& logName, bool& skipThisMessage) override
		{
			PTSD::LOG(message.c_str(), OgreToPTSDVerbosity(lml));
		}
	};