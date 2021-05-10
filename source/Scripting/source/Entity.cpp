#include "Entity.h"

void PTSD::Entity::disableEntity()
{
	//LOG("Disabling entity");
	//Hide mesh
	if (componentPtrs_[CmpId::Mesh] != nullptr) {
		componentPtrs_[CmpId::Mesh]->disable();
	}


	//Disable collision
	if (componentPtrs_[CmpId::RigidbodyC] != nullptr) {
		componentPtrs_[CmpId::RigidbodyC]->disable();
	}
}
