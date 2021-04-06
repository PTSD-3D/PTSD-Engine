#pragma once
#include <array>
#include <bitset>
#include <memory>
#include <vector>
#include "ECS.h"
#include "Component.h"

namespace PTSD {
	class EntityManager;
	class Component;
	struct Collision;

	using UUID = unsigned long;//Unique ID for entity
	class Entity {
	private:
		UUID id_;
		bool active_;
		EntityManager* entityManager_ = nullptr;
		std::vector<std::unique_ptr<Component>> components_;
		std::array<Component*, CmpId::MAXCOMPONENTS> componentPtrs_ = {};
		//TODO add reference to lua entity
	public:
		//Component methods
		template<typename T, typename ... TArgs>
		T* addComponent(TArgs&& ...mArgs) {
			T* c(new T(std::forward<TArgs>(mArgs)...));
			std::unique_ptr<Component> uPtr(c);
			components_.push_back(std::move(uPtr));
			componentPtrs_[c->getId()] = c;
			c->setEntity(this);
			c->init();
			return c;
		}
		template<typename T>
		T* getComponent(CmpId id) {
			return static_cast<T*>(componentPtrs_[id]);
		}
		bool hasComponent(CmpId id) const {
			return componentPtrs_[id] != nullptr;
		}

		//Runtime loop methods
		void init()
		{
			for (auto& cmp : components_)
				cmp->init();
		}
		void update()
		{
			for (auto& cmp : components_)
				cmp->update();
		}
		void onCollisionEnter(Collision* col)
		{
			for (auto& cmp : components_)
				cmp->onCollisionEnter(col);
		}
		void onCollisionStay(Collision* col)
		{
			for (auto& cmp : components_)
				cmp->onCollisionStay(col);
		}
		void onCollisionExit(Collision* col)
		{
			for (auto& cmp : components_)
				cmp->onCollisionExit(col);
		}

		//Getters and Setters
		void setActive(bool active = true) { active_ = active; }
		bool isActive() { return active_; }
		UUID getID() { return id_; }
		Entity(UUID id, bool active = true) :
			id_(id), active_(active) {}
		EntityManager* getManger() const { return entityManager_; }
	};
}
