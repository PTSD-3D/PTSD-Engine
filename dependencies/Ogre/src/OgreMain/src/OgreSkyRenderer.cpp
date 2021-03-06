/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "OgreStableHeaders.h"

#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreViewport.h"

namespace Ogre {
SceneManager::SkyRenderer::SkyRenderer(SceneManager* owner)
    : mSceneManager(owner), mSceneNode(0), mEnabled(false)
{
}

void SceneManager::SkyRenderer::nodeDestroyed(const Node*)
{
    // Remove sky nodes since they've been deleted
    mSceneNode = 0;
    mEnabled = false;
}

void SceneManager::SkyRenderer::setEnabled(bool enable)
{
    if(enable == mEnabled) return;
    mEnabled = enable;
    enable ? mSceneManager->addListener(this) : mSceneManager->removeListener(this);
}

void SceneManager::SkyPlaneRenderer::setSkyPlane(
                               bool enable,
                               const Plane& plane,
                               const String& materialName,
                               Real gscale,
                               Real tiling,
                               uint8 renderQueue,
                               Real bow,
                               int xsegments, int ysegments,
                               const String& groupName)
{
    if (enable)
    {
        String meshName = mSceneManager->mName + "SkyPlane";
        mSkyPlane = plane;

        MaterialPtr m = MaterialManager::getSingleton().getByName(materialName, groupName);
        if (!m)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Sky plane material '" + materialName + "' not found.",
                "SceneManager::setSkyPlane");
        }
        // Make sure the material doesn't update the depth buffer
        m->setDepthWriteEnabled(false);
        // Ensure loaded
        m->load();

        // Set up the plane
        MeshPtr planeMesh = MeshManager::getSingleton().getByName(meshName, groupName);
        if (planeMesh)
        {
            // Destroy the old one
            MeshManager::getSingleton().remove(planeMesh);
        }

        // Create up vector
        Vector3 up = plane.normal.crossProduct(Vector3::UNIT_X);
        if (up == Vector3::ZERO)
            up = plane.normal.crossProduct(-Vector3::UNIT_Z);

        // Create skyplane
        if( bow > 0 )
        {
            // Build a curved skyplane
            planeMesh = MeshManager::getSingleton().createCurvedPlane(
                meshName, groupName, plane, gscale * 100, gscale * 100, gscale * bow * 100,
                xsegments, ysegments, false, 1, tiling, tiling, up);
        }
        else
        {
            planeMesh = MeshManager::getSingleton().createPlane(
                meshName, groupName, plane, gscale * 100, gscale * 100, xsegments, ysegments, false,
                1, tiling, tiling, up);
        }

        // Create entity
        if (mSkyPlaneEntity)
        {
            // destroy old one, do it by name for speed
            mSceneManager->destroyEntity(meshName);
            mSkyPlaneEntity = 0;
        }
        // Create, use the same name for mesh and entity
        // manually construct as we don't want this to be destroyed on destroyAllMovableObjects
        MovableObjectFactory* factory =
            Root::getSingleton().getMovableObjectFactory(EntityFactory::FACTORY_TYPE_NAME);
        NameValuePairList params;
        params["mesh"] = meshName;
        mSkyPlaneEntity = static_cast<Entity*>(factory->createInstance(meshName, mSceneManager, &params));
        mSkyPlaneEntity->setMaterialName(materialName, groupName);
        mSkyPlaneEntity->setCastShadows(false);
        mSkyPlaneEntity->setRenderQueueGroup(renderQueue);

        MovableObjectCollection* objectMap = mSceneManager->getMovableObjectCollection(EntityFactory::FACTORY_TYPE_NAME);
        objectMap->map[meshName] = mSkyPlaneEntity;

        // Create node and attach
        if (!mSceneNode)
        {
            mSceneNode = mSceneManager->createSceneNode(meshName + "Node");
            mSceneNode->setListener(this);
        }
        else
        {
            mSceneNode->detachAllObjects();
        }
        mSceneNode->attachObject(mSkyPlaneEntity);

    }
    setEnabled(enable);
    mSkyPlaneGenParameters.skyPlaneBow = bow;
    mSkyPlaneGenParameters.skyPlaneScale = gscale;
    mSkyPlaneGenParameters.skyPlaneTiling = tiling;
    mSkyPlaneGenParameters.skyPlaneXSegments = xsegments;
    mSkyPlaneGenParameters.skyPlaneYSegments = ysegments;
}

void SceneManager::SkyBoxRenderer::setSkyBox(
                             bool enable,
                             const String& materialName,
                             Real distance,
                             uint8 renderQueue,
                             const Quaternion& orientation,
                             const String& groupName)
{
    if (enable)
    {
        MaterialPtr m = MaterialManager::getSingleton().getByName(materialName, groupName);
        if (!m)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Sky box material '" + materialName + "' not found.",
                "SceneManager::setSkyBox");
        }
        // Ensure loaded
        m->load();

        bool valid = m->getBestTechnique() && m->getBestTechnique()->getNumPasses();
        if(valid)
        {
            Pass* pass = m->getBestTechnique()->getPass(0);
            valid = valid && pass->getNumTextureUnitStates() &&
                    pass->getTextureUnitState(0)->getTextureType() == TEX_TYPE_CUBE_MAP;
        }

        if (!valid)
        {
            LogManager::getSingleton().logWarning("skybox material " + materialName +
                                                  " is not supported, defaulting");
            m = MaterialManager::getSingleton().getDefaultSettings();
        }

        // Create node
        if (!mSceneNode)
        {
            mSceneNode = mSceneManager->createSceneNode("SkyBoxNode");
            mSceneNode->setListener(this);
        }

        // Create object
        if (!mSkyBoxObj)
        {
            mSkyBoxObj.reset(new ManualObject("SkyBox"));
            mSkyBoxObj->setCastShadows(false);
            mSceneNode->attachObject(mSkyBoxObj.get());
        }
        else
        {
            if (!mSkyBoxObj->isAttached())
            {
                mSceneNode->attachObject(mSkyBoxObj.get());
            }
            mSkyBoxObj->clear();
        }

        mSkyBoxObj->setRenderQueueGroup(renderQueue);
        mSkyBoxObj->begin(materialName, RenderOperation::OT_TRIANGLE_LIST, groupName);

        // Set up the box (6 planes)
        for (uint16 i = 0; i < 6; ++i)
        {
            Vector3 middle;
            Vector3 up, right;

            switch(i)
            {
            case BP_FRONT:
                middle = Vector3(0, 0, -distance);
                up = Vector3::UNIT_Y * distance;
                right = Vector3::UNIT_X * distance;
                break;
            case BP_BACK:
                middle = Vector3(0, 0, distance);
                up = Vector3::UNIT_Y * distance;
                right = Vector3::NEGATIVE_UNIT_X * distance;
                break;
            case BP_LEFT:
                middle = Vector3(-distance, 0, 0);
                up = Vector3::UNIT_Y * distance;
                right = Vector3::NEGATIVE_UNIT_Z * distance;
                break;
            case BP_RIGHT:
                middle = Vector3(distance, 0, 0);
                up = Vector3::UNIT_Y * distance;
                right = Vector3::UNIT_Z * distance;
                break;
            case BP_UP:
                middle = Vector3(0, distance, 0);
                up = Vector3::UNIT_Z * distance;
                right = Vector3::UNIT_X * distance;
                break;
            case BP_DOWN:
                middle = Vector3(0, -distance, 0);
                up = Vector3::NEGATIVE_UNIT_Z * distance;
                right = Vector3::UNIT_X * distance;
                break;
            }

            // 3D cubic texture
            // Note UVs mirrored front/back
            // I could save a few vertices here by sharing the corners
            // since 3D coords will function correctly but it's really not worth
            // making the code more complicated for the sake of 16 verts
            // top left
            Vector3 pos = middle + up - right;
            mSkyBoxObj->position(orientation * pos);
            mSkyBoxObj->textureCoord(pos.normalisedCopy() * Vector3(1,1,-1));
            // bottom left
            pos = middle - up - right;
            mSkyBoxObj->position(orientation * pos);
            mSkyBoxObj->textureCoord(pos.normalisedCopy() * Vector3(1,1,-1));
            // bottom right
            pos = middle - up + right;
            mSkyBoxObj->position(orientation * pos);
            mSkyBoxObj->textureCoord(pos.normalisedCopy() * Vector3(1,1,-1));
            // top right
            pos = middle + up + right;
            mSkyBoxObj->position(orientation * pos);
            mSkyBoxObj->textureCoord(pos.normalisedCopy() * Vector3(1,1,-1));

            uint16 base = i * 4;
            mSkyBoxObj->quad(base, base+1, base+2, base+3);
        } // for each plane

        mSkyBoxObj->end();
    }
    setEnabled(enable);
    mSkyBoxGenParameters.skyBoxDistance = distance;
}

void SceneManager::SkyDomeRenderer::setSkyDome(
                              bool enable,
                              const String& materialName,
                              Real curvature,
                              Real tiling,
                              Real distance,
                              uint8 renderQueue,
                              const Quaternion& orientation,
                              int xsegments, int ysegments, int ySegmentsToKeep,
                              const String& groupName)
{
    if (enable)
    {
        MaterialPtr m = MaterialManager::getSingleton().getByName(materialName, groupName);
        if (!m)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Sky dome material '" + materialName + "' not found.",
                "SceneManager::setSkyDome");
        }
        // Make sure the material doesn't update the depth buffer
        m->setDepthWriteEnabled(false);
        // Ensure loaded
        m->load();

        // Create node
        if (!mSceneNode)
        {
            mSceneNode = mSceneManager->createSceneNode("SkyDomeNode");
            mSceneNode->setListener(this);
        }
        else
        {
            mSceneNode->detachAllObjects();
        }

        // Set up the dome (5 planes)
        for (int i = 0; i < 5; ++i)
        {
            MeshPtr planeMesh = createSkydomePlane((BoxPlane)i, curvature,
                tiling, distance, orientation, xsegments, ysegments,
                i!=BP_UP ? ySegmentsToKeep : -1, groupName);

            String entName = "SkyDomePlane" + StringConverter::toString(i);

            // Create entity
            if (mSkyDomeEntity[i])
            {
                // destroy old one, do it by name for speed
                mSceneManager->destroyEntity(entName);
                mSkyDomeEntity[i] = 0;
            }
            // construct manually so we don't have problems if destroyAllMovableObjects called
            MovableObjectFactory* factory =
                Root::getSingleton().getMovableObjectFactory(EntityFactory::FACTORY_TYPE_NAME);

            NameValuePairList params;
            params["mesh"] = planeMesh->getName();
            mSkyDomeEntity[i] = static_cast<Entity*>(factory->createInstance(entName, mSceneManager, &params));
            mSkyDomeEntity[i]->setMaterialName(m->getName(), groupName);
            mSkyDomeEntity[i]->setCastShadows(false);
            mSkyDomeEntity[i]->setRenderQueueGroup(renderQueue);


            MovableObjectCollection* objectMap = mSceneManager->getMovableObjectCollection(EntityFactory::FACTORY_TYPE_NAME);
            objectMap->map[entName] = mSkyDomeEntity[i];

            // Attach to node
            mSceneNode->attachObject(mSkyDomeEntity[i]);
        } // for each plane

    }
    setEnabled(enable);
    mSkyDomeGenParameters.skyDomeCurvature = curvature;
    mSkyDomeGenParameters.skyDomeDistance = distance;
    mSkyDomeGenParameters.skyDomeTiling = tiling;
    mSkyDomeGenParameters.skyDomeXSegments = xsegments;
    mSkyDomeGenParameters.skyDomeYSegments = ysegments;
    mSkyDomeGenParameters.skyDomeYSegments_keep = ySegmentsToKeep;
}

MeshPtr SceneManager::SkyDomeRenderer::createSkydomePlane(
                                       BoxPlane bp,
                                       Real curvature,
                                       Real tiling,
                                       Real distance,
                                       const Quaternion& orientation,
                                       int xsegments, int ysegments, int ysegments_keep,
                                       const String& groupName)
{

    Plane plane;
    String meshName;
    Vector3 up;

    meshName = mSceneManager->mName + "SkyDomePlane_";
    // Set up plane equation
    plane.d = distance;
    switch(bp)
    {
    case BP_FRONT:
        plane.normal = Vector3::UNIT_Z;
        up = Vector3::UNIT_Y;
        meshName += "Front";
        break;
    case BP_BACK:
        plane.normal = -Vector3::UNIT_Z;
        up = Vector3::UNIT_Y;
        meshName += "Back";
        break;
    case BP_LEFT:
        plane.normal = Vector3::UNIT_X;
        up = Vector3::UNIT_Y;
        meshName += "Left";
        break;
    case BP_RIGHT:
        plane.normal = -Vector3::UNIT_X;
        up = Vector3::UNIT_Y;
        meshName += "Right";
        break;
    case BP_UP:
        plane.normal = -Vector3::UNIT_Y;
        up = Vector3::UNIT_Z;
        meshName += "Up";
        break;
    case BP_DOWN:
        // no down
        return MeshPtr();
    }
    // Modify by orientation
    plane.normal = orientation * plane.normal;
    up = orientation * up;

    // Check to see if existing plane
    MeshManager& mm = MeshManager::getSingleton();
    MeshPtr planeMesh = mm.getByName(meshName, groupName);
    if(planeMesh)
    {
        // destroy existing
        mm.remove(planeMesh->getHandle());
    }
    // Create new
    Real planeSize = distance * 2;
    planeMesh = mm.createCurvedIllusionPlane(meshName, groupName, plane,
        planeSize, planeSize, curvature,
        xsegments, ysegments, false, 1, tiling, tiling, up,
        orientation, HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY, HardwareBuffer::HBU_STATIC_WRITE_ONLY,
        false, false, ysegments_keep);

    //planeMesh->_dumpContents(meshName);

    return planeMesh;

}

void SceneManager::SkyPlaneRenderer::_updateRenderQueue(RenderQueue* queue)
{
    if (mSkyPlaneEntity->isVisible())
    {
        mSkyPlaneEntity->_updateRenderQueue(queue);
    }
}

void SceneManager::SkyBoxRenderer::_updateRenderQueue(RenderQueue* queue)
{
    if (mSkyBoxObj->isVisible())
    {
        mSkyBoxObj->_updateRenderQueue(queue);
    }
}

void SceneManager::SkyDomeRenderer::_updateRenderQueue(RenderQueue* queue)
{
    for (uint plane = 0; plane < 5; ++plane)
    {
        if (!mSkyDomeEntity[plane]->isVisible()) continue;

        mSkyDomeEntity[plane]->_updateRenderQueue(queue);
    }
}

void SceneManager::SkyRenderer::postFindVisibleObjects(SceneManager* source, IlluminationRenderStage irs,
                                                       Viewport* vp)
{
    // Queue skies, if viewport seems it
    if (!vp->getSkiesEnabled() || irs == IRS_RENDER_TO_TEXTURE)
        return;

    if(!mEnabled || !mSceneNode)
        return;

    // Update nodes
    // Translate the box by the camera position (constant distance)
    mSceneNode->setPosition(vp->getCamera()->getDerivedPosition());
    _updateRenderQueue(source->getRenderQueue());
}
}
