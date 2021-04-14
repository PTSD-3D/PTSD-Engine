#include "MeshComponent.h"
#include "PTSDGraphics.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "Entity.h"
#include "TransformComponent.h"
#include <assert.h>
namespace PTSD{
	MeshComponent::MeshComponent(): Component(Mesh){};
	MeshComponent::MeshComponent(const std::string& mesh): Component(Mesh)
	{
		mMesh_ = mesh;
	};
	MeshComponent::MeshComponent(const std::string& mesh, const std::string& material): Component(Mesh)
	{
		mMesh_ = mesh;
		mMaterial_ = material;
	};

	void MeshComponent::init()
	{
				//assume entity_ as protected
		assert(entity_->hasComponent(Transform));
		Ogre::SceneNode* node = entity_->getComponent<TransformComponent>(Transform)->getNode();
		Ogre::Entity* ob = (Ogre::Entity*)(node->getAttachedObjects().size() >= 1) ? 
		(Ogre::Entity*)node->getAttachedObjects().at(0):nullptr;
		if(!ob)//Asumiendo que no vamos a tener varios objetos por malla.. 
			{
				node->attachObject(GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_));
				ob=(Ogre::Entity*)node->getAttachedObject(0);
			}
		else
			{
				entity_->getComponent<TransformComponent>(Transform)->getNode()->detachObject((unsigned short int)0);
				GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_);
			}
			ob->setMaterialName(mMaterial_);
	}
	void MeshComponent::setMaterial(const std::string& material)
	{
		if(material != mMaterial_)
		{
			getEntity()->setMaterialName(material);
		}
	};
	void MeshComponent::setMesh(const std::string& mesh)
	{
		if(mesh != mMesh_)
		{
			mMesh_ = mesh;
			entity_->getComponent<TransformComponent>(Transform)->getNode()->detachObject((unsigned short int)0);
			GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_);
			getEntity()->setMaterialName(mMaterial_);
		}
	};
	Ogre::Entity* MeshComponent::getEntity(){
		Ogre::SceneNode* node= entity_->getComponent<TransformComponent>(Transform)->getNode();
		Ogre::Entity* entt = (Ogre::Entity*)(node)->getAttachedObjects().at(0);
		assert(entt != nullptr);
		return entt;
		return nullptr;
	};
}