:: Build OGRE3D

IF exist build\ goto done

mkdir build
..\cmake\bin\cmake.exe -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -S src\ -B build\

   
MSBuild .\build\OGRE.sln /p:Configuration=Release
MSBuild .\build\OGRE.sln /p:Configuration=Debug

MSBuild .\build\SDL2-build\SDL2.sln /p:Configuration=Release
MSBuild .\build\SDL2-build\SDL2.sln /p:Configuration=Debug
goto end


:done
echo OGRE and SDL already built
:end
