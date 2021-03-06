/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2008 Renato Araujo Oliveira Filho <renatox@gmail.com>
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

#include "OgreException.h"
#include "OgreLogManager.h"
#include "OgreStringConverter.h"
#include "OgreRoot.h"

#include "OgreRenderSystem.h"

#include "OgreEGLSupport.h"
#include "OgreEGLWindow.h"
#include "OgreEGLRenderTexture.h"


namespace Ogre {


    EGLSupport::EGLSupport(int profile)
        : GLNativeSupport(profile), mGLDisplay(0),
          mNativeDisplay(EGL_DEFAULT_DISPLAY)
    {
    }

    EGLDisplay EGLSupport::getGLDisplay(void)
    {
        mGLDisplay = eglGetDisplay(mNativeDisplay);
        EGL_CHECK_ERROR

        if(mGLDisplay == EGL_NO_DISPLAY)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
                        "Couldn`t open EGLDisplay " + getDisplayName(),
                        "EGLSupport::getGLDisplay");
        }

        if (eglInitialize(mGLDisplay, &mEGLMajor, &mEGLMinor) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
                        "Couldn`t initialize EGLDisplay ",
                        "EGLSupport::getGLDisplay");
        }
        EGL_CHECK_ERROR

        return mGLDisplay;
    }


    String EGLSupport::getDisplayName(void)
    {
        return "todo";
    }

    EGLConfig* EGLSupport::chooseGLConfig(const EGLint *attribList, EGLint *nElements)
    {
        EGLConfig *configs;

        if (eglChooseConfig(mGLDisplay, attribList, NULL, 0, nElements) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Failed to choose config");

            *nElements = 0;
            return 0;
        }
        EGL_CHECK_ERROR
        configs = (EGLConfig*) malloc(*nElements * sizeof(EGLConfig));
        if (eglChooseConfig(mGLDisplay, attribList, configs, *nElements, nElements) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Failed to choose config");

            *nElements = 0;
            free(configs);
            return 0;
        }
        EGL_CHECK_ERROR
        return configs;
    }

    EGLConfig* EGLSupport::getConfigs(EGLint *nElements)
    {
        EGLConfig *configs;

        if (eglGetConfigs(mGLDisplay, NULL, 0, nElements) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Failed to choose config");

            *nElements = 0;
            return 0;
        }
        EGL_CHECK_ERROR
        configs = (EGLConfig*) malloc(*nElements * sizeof(EGLConfig));
        if (eglGetConfigs(mGLDisplay, configs, *nElements, nElements) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Failed to choose config");

            *nElements = 0;
            free(configs);
            return 0;
        }
        EGL_CHECK_ERROR
        return configs;
    }

    EGLBoolean EGLSupport::getGLConfigAttrib(EGLConfig glConfig, EGLint attribute, EGLint *value)
    {
        EGLBoolean status;

        status = eglGetConfigAttrib(mGLDisplay, glConfig, attribute, value);
        EGL_CHECK_ERROR
        return status;
    }

    void* EGLSupport::getProcAddress(const char* name) const
    {
        return (void*)eglGetProcAddress(name);
    }

    ::EGLConfig EGLSupport::getGLConfigFromContext(::EGLContext context)
    {
        ::EGLConfig glConfig;
        EGLint id = 0;
        ::EGLConfig *configs;
        EGLint numConfigs;

        if (eglQueryContext(mGLDisplay, context, EGL_CONFIG_ID, &id) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Fail to get config from context");
            return 0;
        }
        EGL_CHECK_ERROR
        configs = getConfigs(&numConfigs);
        glConfig = configs[id];
        free(configs);
        return glConfig;
    }

    ::EGLConfig EGLSupport::getGLConfigFromDrawable(::EGLSurface drawable,
                                                    unsigned int *w, unsigned int *h)
    {
        ::EGLConfig glConfig;
        EGLint id = 0;
        ::EGLConfig *configs;
        EGLint numConfigs;

        if (eglQuerySurface(mGLDisplay, drawable, EGL_CONFIG_ID, &id) == EGL_FALSE)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Fail to get config from drawable");
            return 0;
        }
        EGL_CHECK_ERROR
        eglQuerySurface(mGLDisplay, drawable, EGL_WIDTH, (EGLint *) w);
        EGL_CHECK_ERROR
        eglQuerySurface(mGLDisplay, drawable, EGL_HEIGHT, (EGLint *) h);
        EGL_CHECK_ERROR
        configs = getConfigs(&numConfigs);
        glConfig = configs[id];
        free(configs);
        return glConfig;
    }

    //------------------------------------------------------------------------
    // A helper class for the implementation of selectFBConfig
    //------------------------------------------------------------------------
    class GLConfigAttribs
    {
        public:
            GLConfigAttribs(const int* attribs)
            {
                fields[EGL_CONFIG_CAVEAT] = EGL_NONE;

                for (int i = 0; attribs[2*i] != EGL_NONE; i++)
                {
                    fields[attribs[2*i]] = attribs[2*i+1];
                }
            }

            void load(EGLSupport* const glSupport, EGLConfig glConfig)
            {
                std::map<int,int>::iterator it;

                for (it = fields.begin(); it != fields.end(); it++)
                {
                    it->second = EGL_NONE;

                    glSupport->getGLConfigAttrib(glConfig, it->first, &it->second);
                }
            }

            bool operator>(GLConfigAttribs& alternative)
            {
                // Caveats are best avoided, but might be needed for anti-aliasing
                if (fields[EGL_CONFIG_CAVEAT] != alternative.fields[EGL_CONFIG_CAVEAT])
                {
                    if (fields[EGL_CONFIG_CAVEAT] == EGL_SLOW_CONFIG)
                    {
                        return false;
                    }

                    if (fields.find(EGL_SAMPLES) != fields.end() &&
                        fields[EGL_SAMPLES] < alternative.fields[EGL_SAMPLES])
                    {
                        return false;
                    }
                }

                std::map<int,int>::iterator it;

                for (it = fields.begin(); it != fields.end(); it++)
                {
                    if (it->first != EGL_CONFIG_CAVEAT &&
                        fields[it->first] > alternative.fields[it->first])
                    {
                        return true;
                    }
                }

                return false;
            }

            std::map<int,int> fields;
    };

    ::EGLConfig EGLSupport::selectGLConfig(const int* minAttribs, const int *maxAttribs)
    {
        EGLConfig *glConfigs;
        EGLConfig glConfig = 0;
        int config, nConfigs = 0;

        glConfigs = chooseGLConfig(minAttribs, &nConfigs);

        if (!nConfigs)
        {
            glConfigs = getConfigs(&nConfigs);
        }

        if (!nConfigs)
        {
            return 0;
        }

        glConfig = glConfigs[0];

        if (maxAttribs)
        {
            GLConfigAttribs maximum(maxAttribs);
            GLConfigAttribs best(maxAttribs);
            GLConfigAttribs candidate(maxAttribs);

            best.load(this, glConfig);

            for (config = 1; config < nConfigs; config++)
            {
                candidate.load(this, glConfigs[config]);

                if (candidate > maximum)
                {
                    continue;
                }

                if (candidate > best)
                {
                    glConfig = glConfigs[config];

                    best.load(this, glConfig);
                }
            }
        }

        free(glConfigs);
        return glConfig;
    }

    void EGLSupport::switchMode(void)
    {
        return switchMode(mOriginalMode.width,
                          mOriginalMode.height, mOriginalMode.refreshRate);
    }

    ::EGLContext EGLSupport::createNewContext(EGLDisplay eglDisplay,
                          ::EGLConfig glconfig,
                                              ::EGLContext shareList) const 
    {
        EGLint contextAttrs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
        };

        if(mContextProfile != CONTEXT_ES) {
            if (!eglBindAPI(EGL_OPENGL_API))
            {
                OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
                        "Couldn`t initialize API ",
                        "EGLSupport::getGLDisplay");
            }
            EGL_CHECK_ERROR

            contextAttrs[0] = EGL_NONE;
        }

#if OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN
        // try WebGL2 context
        contextAttrs[1] = 3;
#endif

        ::EGLContext context = 0;
        if (!eglDisplay)
        {
            context = eglCreateContext(mGLDisplay, glconfig, shareList, contextAttrs);
            EGL_CHECK_ERROR
        }
        else
        {
            context = eglCreateContext(eglDisplay, glconfig, 0, contextAttrs);
            EGL_CHECK_ERROR
        }

#if OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN
        if (!context)
        {
            // fall back to WebGL
            contextAttrs[1] = 2;
            context = eglCreateContext(mGLDisplay, glconfig, shareList, contextAttrs);
            EGL_CHECK_ERROR
        }
#endif

        if (!context)
        {
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "Fail to create New context");
            return 0;
        }

        return context;
    }

    void EGLSupport::start()
    {
        LogManager::getSingleton().logMessage(
            "******************************\n"
            "*** Starting EGL Subsystem ***\n"
            "******************************");
        initialiseExtensions();
    }

    void EGLSupport::stop()
    {
        eglTerminate(mGLDisplay);
        EGL_CHECK_ERROR
    }

    void EGLSupport::initialiseExtensions() {
        assert (mGLDisplay);

        const char* propStr = eglQueryString(mGLDisplay, EGL_VENDOR);
        LogManager::getSingleton().stream() << "EGL_VENDOR = " << propStr;

        propStr = eglQueryString(mGLDisplay, EGL_VERSION);
        LogManager::getSingleton().stream() << "EGL_VERSION = " << propStr;

        StringStream ext;

        // client extensions
        propStr = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        ext << propStr << " ";

        // display extension
        propStr = eglQueryString(mGLDisplay, EGL_EXTENSIONS);
        ext << propStr;

        LogManager::getSingleton().stream() << "EGL_EXTENSIONS = " << ext.str();

        String instr;
        while(ext >> instr)
        {
            extensionList.insert(instr);
        }
    }

    void EGLSupport::setGLDisplay( EGLDisplay val )
    {
        mGLDisplay = val;
    }

    GLPBuffer* EGLSupport::createPBuffer( PixelComponentType format, size_t width, size_t height )
    {
        return new EGLPBuffer(this, format, width, height);
    }
}
