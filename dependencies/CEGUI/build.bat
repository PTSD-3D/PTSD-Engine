:: Build CEGUI

if exist build\ goto done
mkdir build
SET mypath=%~dp0
set "mypath=%mypath:\=/%"
SET filepath=""
 ..\cmake\bin\cmake.exe -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DOGRE_H_PATH:PATH="%mypath%../Ogre/src/OgreMain/include" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="%mypath%../Ogre/build/include" -DOGRE_LIB:FILEPATH="%mypath%../Ogre/build/lib/Release/OgreMain.lib" -DOGRE_LIB_DBG:FILEPATH="%mypath%../Ogre/build/lib/Debug/OgreMain_d.lib" -S src\ -B build\

powershell -Command "(gc .\build\cegui\include\CEGUI\config.h) -replace '#   define CEGUI_OGRE_VERSION_MAJOR 0', '#   define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII .\build\cegui\include\CEGUI\config.h"
powershell -Command "(gc .\build\cegui\include\CEGUI\config.h) -replace '#   define CEGUI_OGRE_VERSION_MINOR 0', '#   define CEGUI_OGRE_VERSION_MINOR 12' | Out-File -encoding ASCII .\build\cegui\include\CEGUI\config.h"
powershell -Command "(gc .\build\cegui\include\CEGUI\config.h) -replace '#   define CEGUI_OGRE_VERSION_PATCH 0', '#   define CEGUI_OGRE_VERSION_PATCH 11' | Out-File -encoding ASCII .\build\cegui\include\CEGUI\config.h"

MSBuild .\build\cegui.sln /p:Configuration=Release
MSBuild .\build\cegui.sln /p:Configuration=Debug

goto end

:done
echo CEGUI already built
:end