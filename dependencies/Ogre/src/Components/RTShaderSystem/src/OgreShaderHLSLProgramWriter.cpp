/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

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

#include "OgreShaderPrecompiledHeaders.h"

namespace Ogre {
namespace RTShader {

String HLSLProgramWriter::TargetLanguage = "hlsl";

//-----------------------------------------------------------------------
HLSLProgramWriter::HLSLProgramWriter()
{
    initializeStringMaps();

    mIsShaderModel4 = GpuProgramManager::getSingleton().isSyntaxSupported("ps_4_0");

    if(mIsShaderModel4)
    {
        mGpuConstTypeMap[GCT_SAMPLER2DARRAY] = "Sampler2DArray";
        mGpuConstTypeMap[GCT_SAMPLER2DSHADOW] = "Sampler2DShadow";
    }
}

void HLSLProgramWriter::writeUniformParameter(std::ostream& os, const UniformParameterPtr& parameter)
{
    if(!mIsShaderModel4 || !parameter->isSampler())
    {
        CGProgramWriter::writeUniformParameter(os, parameter);
        return;
    }

    switch(parameter->getType())
    {
    case GCT_SAMPLER1D:
        os << "SAMPLER1D(";
        break;
    case GCT_SAMPLER2D:
        os << "SAMPLER2D(";
        break;
    case GCT_SAMPLER3D:
        os << "SAMPLER3D(";
        break;
    case GCT_SAMPLERCUBE:
        os << "SAMPLERCUBE(";
        break;
    case GCT_SAMPLER2DSHADOW:
        os << "SAMPLER2DSHADOW(";
        break;
    case GCT_SAMPLER2DARRAY:
        os << "SAMPLER2DARRAY(";
        break;
    default:
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "unsuppported sampler type");
    }
    os << parameter->getName() << ", " << parameter->getIndex() << ")";
}

HLSLProgramWriter::~HLSLProgramWriter()
{

}

}
}
