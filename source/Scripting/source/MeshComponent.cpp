#include "MeshComponent.h"
#include "GraphicsManager.h"
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
		assert(entity_->hasComponent(Transform));
		if(!sceneNode)
			sceneNode = entity_->getComponent<TransformComponent>(Transform)->getNode()->createChildSceneNode();
		Ogre::Entity* ob = (sceneNode->getAttachedObjects().size() >= 1) ? 
		(Ogre::Entity*)sceneNode->getAttachedObjects().at(0):nullptr;
		if(!ob)//Asumiendo que no vamos a tener varios objetos por malla.. 
			{
				sceneNode->attachObject(GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_));
				ob=(Ogre::Entity*)sceneNode->getAttachedObject(0);
			}
		else
			{
				entity_->getComponent<TransformComponent>(Transform)->getNode()->detachObject((unsigned short int)0);
				GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_);
			}
			PTSD::LOG(mMaterial_.c_str());
			ob->setMaterialName(mMaterial_);
	}
	void MeshComponent::setMaterial(const std::string& material)
	{
		if(material != mMaterial_)
		{
			getEntity()->setMaterialName(material);
			mMaterial_ = material;
		}
	};
	void MeshComponent::setMesh(const std::string& mesh)
	{
		if(mesh != mMesh_)
		{
			mMesh_ = mesh;
			sceneNode->detachObject((unsigned short int)0);
			GraphicsImplementation::getInstance()->getSceneMgr()->createEntity(mMesh_);
			getEntity()->setMaterialName(mMaterial_);
		}
	};
	Ogre::Entity* MeshComponent::getEntity(){
		Ogre::Entity* entt = (Ogre::Entity*)(sceneNode)->getAttachedObjects().at(0);
		assert(entt != nullptr);
		return entt;
		return nullptr;
	};
}