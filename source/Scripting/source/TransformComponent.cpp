#include "TransformComponent.h"
#include "GraphicsManager.h"

namespace PTSD {
	//Methods to convert from and to quaternions and vec3
	Vec3 TransformComponent::OgreQuatEuler(const Ogre::Quaternion& quaternion) const
	{
		Ogre::Matrix3 mx2;
		quaternion.ToRotationMatrix(mx2);
		Ogre::Radian x, y, z;
		mx2.ToEulerAnglesYXZ(y, x, z);
		Vec3 vect(x.valueAngleUnits(), y.valueAngleUnits(), z.valueAngleUnits());

		return vect;
	}
	Ogre::Quaternion TransformComponent::EulerToOgreQuat(const Vec3& degreesVector) const
	{
		Ogre::Matrix3 mx;
		mx.FromEulerAnglesYXZ(Ogre::Degree(degreesVector.y), Ogre::Degree(degreesVector.x), Ogre::Degree(degreesVector.z));
		Ogre::Quaternion result(mx);
		return result;
	}
	//

	TransformComponent::TransformComponent() : Component(CmpId::Transform) {
		mNode = GraphicsManager::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	}
	TransformComponent::TransformComponent(Vec3 p, Vec3 r, Vec3 s) : Component(CmpId::Transform)
	{
		mNode = GraphicsManager::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		setPosition(p);
		setRotation(r);
		setScale(s);
	}

	TransformComponent::~TransformComponent()
	{
		//Since Transform handles the base node for all ogre based things we do this here.
		DestroyNodeAndChildren(mNode);
		mNode = nullptr;
	}

	void TransformComponent::DestroyNodeAndChildren(Ogre::SceneNode* node)
	{
		//Destroy all the attached objects
		for (auto elem : node->getAttachedObjects()) {
			node->getCreator()->destroyMovableObject(elem);
		}

		//This way is now deprecated: refer to OgreSceneNode.h
		/*Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();

		while (itObject.hasMoreElements())
		{
			Ogre::MovableObject* pObject = static_cast<Ogre::MovableObject*>(itObject.getNext());
			node->getCreator()->destroyMovableObject(pObject);
		}*/

		// Recurse to child SceneNodes
		for (auto child : node->getChildren()) {
			DestroyNodeAndChildren(static_cast<Ogre::SceneNode*>(child));
		}

		//Old methods
		/*Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

		while (itChild.hasMoreElements())
		{
			Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
			DestroyNodeAndChildren(pChildNode);
		}*/

		if(node->isInSceneGraph())
			GraphicsManager::getInstance()->getSceneMgr()->destroySceneNode(node);
	}


	void TransformComponent::translate(Vec3 translation) { //moves the transform with a vec3
		mNode->translate(translation.x, translation.y, translation.z, Ogre::Node::TS_WORLD);
	}
	void TransformComponent::translate(float x, float y, float z) { //moves the transform with 3 floats
		mNode->translate(x, y, z, Ogre::Node::TS_WORLD);
	}
	void TransformComponent::rotate(Vec3 rotation) { //changes orientation of the transform using a vec3
		Ogre::Quaternion q = EulerToOgreQuat(rotation);			// It has a little problem with rounding +-(0.00001)
		mNode->rotate(q, Ogre::Node::TS_LOCAL);
	}
	void TransformComponent::rotate(float x, float y, float z) { //changes orientation of the transform using 3 floats
		Vec3 rotation = (x, y, z);					 // It has a little problem with rounding +-(0.00001)
		Ogre::Quaternion q = EulerToOgreQuat(rotation);
		mNode->rotate(q, Ogre::Node::TS_LOCAL);
	}
	void TransformComponent::scale(Vec3 scale) { //adds or substracts from the actual scale with a vec3
		mNode->scale(scale.x, scale.y, scale.z);
	}
	void TransformComponent::scale(float x, float y, float z) { //adds or substracts from the actual scale with 3 floats
		mNode->scale(x, y, z);
	}

	//Setters 
	void TransformComponent::setPosition(Vec3 position) { //Sets the position of the transform with vec3
		mNode->setPosition(position.x, position.y, position.z);
	}
	void TransformComponent::setPosition(float x, float y, float z) //Sets the position of the transform with 3 floats
	{
		mNode->setPosition(x, y, z);
	}
	void TransformComponent::setRotation(Vec3 rotation) { //Sets the rotation of the transform
		Ogre::Quaternion q = EulerToOgreQuat(rotation);
		mNode->setOrientation(q);
	};

	void TransformComponent::setRotation(float x, float y, float z) //Sets the rotation of the transform with 3 floats
	{
		Ogre::Quaternion q = EulerToOgreQuat(Vec3(x, y, z));
		mNode->setOrientation(q);
	}
	void TransformComponent::setScale(Vec3 scale) { //Sets the scale of the transform
		mNode->setScale(scale.x, scale.y, scale.z);
	};

	void TransformComponent::setScale(float x, float y, float z) //Sets the scale of the transform with 3 floats
	{
		mNode->setScale(x, y, z);
	}

	void TransformComponent::setChildCamera(Vec3 offset) //Makes the camera move with the transform
	{
		GraphicsManager::getInstance()->getCam()->lookAt(Vec3(0, 0, 10000));
		Ogre::SceneNode* n = GraphicsManager::getInstance()->getCam()->getNode();
		GraphicsManager::getInstance()->getSceneMgr()->getRootSceneNode()->removeChild(n);
		mNode->addChild(n);
		n->setPosition(offset.x, offset.y, offset.z);
	}

	//Getters
	Vec3 TransformComponent::getPosition() const { //Gets the position of the transform
		Ogre::Vector3 v = mNode->getPosition();
		return Vec3(v.x, v.y, v.z);
	}
	Vec3 TransformComponent::getRotation() const { //Gets the rotation of the transform
		Vec3 v = OgreQuatEuler(mNode->getOrientation());
		return v;
	}
	Vec3 TransformComponent::getScale() const { //Gets the scale of the transform
		Ogre::Vector3 v = mNode->getScale();
		return Vec3(v.x, v.y, v.z);
	}
	Vec3 TransformComponent::getForward() const { //Gets the local forward vector
		Ogre::Vector3 v = mNode->getLocalAxes().GetColumn(2);
		return Vec3(v.x, v.y, v.z);
	}
	Vec3 TransformComponent::getRight() const { //Gets the local right vector
		Ogre::Vector3 v = -mNode->getLocalAxes().GetColumn(0);
		return Vec3(v.x, v.y, v.z);
	}
	Ogre::SceneNode* TransformComponent::getNode() const { //Gets the node associated to the transform
		return mNode;
	}

	//

}