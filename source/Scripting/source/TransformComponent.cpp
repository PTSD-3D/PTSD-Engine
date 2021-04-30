#include "TransformComponent.h"
namespace PTSD {
	//Methods to convert from and to quaternions and vec3
	Vec3Placeholder TransformComponent::OgreQuatEuler(const Ogre::Quaternion& quaternion) const
	{
		Ogre::Matrix3 mx2;
		quaternion.ToRotationMatrix(mx2);
		Ogre::Radian x, y, z;
		mx2.ToEulerAnglesYXZ(y, x, z);
		Vec3Placeholder vect(x.valueAngleUnits(),y.valueAngleUnits(), z.valueAngleUnits());
		
		return vect;
	}
	Ogre::Quaternion TransformComponent::EulerToOgreQuat(const Vec3Placeholder& degreesVector) const
	{
		Ogre::Matrix3 mx;
		mx.FromEulerAnglesYXZ(Ogre::Degree(degreesVector.y), Ogre::Degree(degreesVector.x), Ogre::Degree(degreesVector.z));
		Ogre::Quaternion result(mx);
		return result;
	}
	//

	TransformComponent::TransformComponent() : Component(CmpId::Transform) {
		mNode = GraphicsImplementation::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	}
	TransformComponent::TransformComponent(Vec3Placeholder p, Vec3Placeholder r, Vec3Placeholder s): Component(CmpId::Transform) 
	{
		mNode = GraphicsImplementation::getInstance()->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		setPosition(p);
		setRotation(r);
		setScale(s);
	}


	void TransformComponent::translate(Vec3Placeholder translation) { //moves the transform with a vec3
		mNode->translate(translation.x, translation.y, translation.z, Ogre::Node::TS_WORLD);
	}
	void TransformComponent::translate(float x, float y, float z) { //moves the transform with 3 floats
		mNode->translate(x, y, z, Ogre::Node::TS_WORLD);
	}
	void TransformComponent::rotate(Vec3Placeholder rotation) { //changes orientation of the transform using a vec3
		Ogre::Quaternion q = EulerToOgreQuat(rotation);			// It has a little problem with rounding +-(0.00001)
		mNode->rotate(q, Ogre::Node::TS_LOCAL);
	}
	void TransformComponent::rotate(float x, float y, float z) { //changes orientation of the transform using 3 floats
		Vec3Placeholder rotation = (x, y, z);					 // It has a little problem with rounding +-(0.00001)
		Ogre::Quaternion q = EulerToOgreQuat(rotation);			
		mNode->rotate(q, Ogre::Node::TS_LOCAL);
	}
	void TransformComponent::scale(Vec3Placeholder scale) { //adds or substracts from the actual scale with a vec3
		mNode->scale(scale.x, scale.y, scale.z);
	}
	void TransformComponent::scale(float x, float y, float z) { //adds or substracts from the actual scale with 3 floats
		mNode->scale(x, y, z);
	}

	//Setters 
	void TransformComponent::setPosition(Vec3Placeholder position) { //Sets the position of the transform with vec3
		mNode->setPosition(position.x, position.y, position.z);
	}
	void TransformComponent::setPosition(float x, float y, float z) //Sets the position of the transform with 3 floats
	{
		mNode->setPosition(x, y, z);
	}
	void TransformComponent::setRotation(Vec3Placeholder rotation) { //Sets the rotation of the transform
		Ogre::Quaternion q = EulerToOgreQuat(rotation);
		mNode->setOrientation(q);
	};

	void TransformComponent::setRotation(float x, float y, float z) //Sets the rotation of the transform with 3 floats
	{
		Ogre::Quaternion q = EulerToOgreQuat(Vec3Placeholder(x,y,z));
		mNode->setOrientation(q);
	}
	void TransformComponent::setScale(Vec3Placeholder scale) { //Sets the scale of the transform
		mNode->setScale(scale.x, scale.y, scale.z);
	};

	void TransformComponent::setScale(float x, float y, float z) //Sets the scale of the transform with 3 floats
	{
		mNode->setScale(x, y, z);
	}

	void TransformComponent::setChildCamera() //Makes the camera move with the transform
	{
		Ogre::SceneNode* n = GraphicsImplementation::getInstance()->getCamera()->getNode();
		GraphicsImplementation::getInstance()->getSceneMgr()->getRootSceneNode()->removeChild(n);
		mNode->addChild(n);
		n->setPosition(Ogre::Vector3(getPosition().x, getPosition().y, getPosition().z + 100));

	}

	//Getters
	Vec3Placeholder TransformComponent::getPosition() const { //Gets the position of the transform
		Ogre::Vector3 v = mNode->getPosition();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	Vec3Placeholder TransformComponent::getRotation() const { //Gets the rotation of the transform
		Vec3Placeholder v = OgreQuatEuler(mNode->getOrientation());
		return v;
	}
	Vec3Placeholder TransformComponent::getScale() const { //Gets the scale of the transform
		Ogre::Vector3 v = mNode->getScale();
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	Vec3Placeholder TransformComponent::getForward() const { //Gets the local forward vector
		Ogre::Vector3 v = mNode->getLocalAxes().GetColumn(2);
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	Vec3Placeholder TransformComponent::getRight() const { //Gets the local right vector
		Ogre::Vector3 v = mNode->getLocalAxes().GetColumn(0);
		return Vec3Placeholder(v.x, v.y, v.z);
	}
	Ogre::SceneNode* TransformComponent::getNode() const { //Gets the node associated to the transform
		return mNode;
	}

	//

}