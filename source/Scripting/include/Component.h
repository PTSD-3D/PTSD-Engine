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
		CmpId id_;
	protected:
		Entity* entity_ = nullptr;
		Component(CmpId id) :
			id_(id) {}
	public:
		virtual ~Component() = default;
		void setEntity(Entity* entity) { entity_ = entity; }
		CmpId getId() { return id_; }
		virtual void init() {}
		virtual void update() {}
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
