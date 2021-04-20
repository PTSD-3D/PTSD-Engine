#pragma once
#include "ECS.h"
#include "LogManager.h"

namespace PTSD
{
	class Entity;
	class Collision;
	class Component
	{
	private:
		Entity* entity_ = nullptr;
		CmpId id_;
	protected:
		Component(CmpId id) :
			id_(id) {}
	public:
		void setEntity(Entity* entity) { entity_ = entity; }
		CmpId getId() { return id_; }
		virtual void init() {}
		virtual void update() {}
		virtual void destroy() {}
		virtual void onCollisionEnter(Collision* collision) {}
		virtual void onCollisionStay(Collision* collision) {}
		virtual void onCollisionExit(Collision* collision) {}
	};

	class DebugComponent: public Component
	{
	public:
		DebugComponent():Component(CmpId::Debug){}
		virtual void init() override
		{
			//LOG("Debug component initialized");
		}
		virtual void update() override
		{
			//LOG("Debug component updated",Trace);
		}
	};
}
