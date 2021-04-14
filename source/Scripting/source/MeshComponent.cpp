#include "MeshComponent.h"
#include "PTSDGraphics.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <assert.h>
namespace PTSD{
	MeshComponent::MeshComponent(): Component(Mesh){};
	MeshComponent::MeshComponent(const std::string& mesh): Component(Mesh)
	{
		//assume entity_ as protected
		/*
		assert(entity->hasComponent(Transform))
		Ogre::SceneNode* node = getComponent<TransformComponent>(Transform)->getNode();
		Ogre::Entity* ob = (Ogre::Entity*)node->getAttachedObject(0);
		if(!ob)//Asumiendo que no vamos a tener varios objetos por malla.. 
			{
				node->attachObject(GraphicsImplementation::getInstance()->getSceneManager()->createEntity(mesh));
				ob=(Ogre::Entity*)node->getAttachedObject(0);
			}
		else
			ob->setMesh(mesh);
		*/
		mMesh_ = mesh;
	};
	MeshComponent::MeshComponent(const std::string& mesh, const std::string& material): Component(Mesh)
	{
		/*
		assert(entity->hasComponent(Transform))
		Ogre::SceneNode* node = getComponent<TransformComponent>(Transform)->getNode();
		Ogre::Entity* ob = (Ogre::Entity*)node->getAttachedObject(0);
		if(!ob)//Asumiendo que no vamos a tener varios objetos por malla.. 
			{node->attachObject(GraphicsImplementation::getInstance()->getSceneManager()->createEntity(mesh));ob=node->getAttachedObject(0);}
		else
			ob->setMesh(mesh);
		ob->setMaterialName(material);
		*/
		mMesh_ = mesh;
		mMaterial_ = material;
	};
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
			//getComponent<TransformComponent>(Transform)->getNode()->dettachObject(0);
			//GraphicsImplementation::getInstance()->getSceneManager()->createEntity(mMesh_);
			getEntity()->setMaterialName(mMaterial_);
		}
	};
	Ogre::Entity* MeshComponent::getEntity(){
		//Ogre::SceneNode* = getComponent<TransformComponent>(Transform)->getNode();
		//Ogre::Entity* entt = (Ogre::Entity* )->getAttachedObject(0)
		//assert(entt != nullptr);
		//return entt;
		return nullptr;
	};
}