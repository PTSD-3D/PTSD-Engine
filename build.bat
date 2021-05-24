@ECHO OFF
:: Por ahora voy a hacer esto para mover los .dll de Ogre a nuestro /bin/ Pero en teoría
::además debería de buildear Ogre llamando a cmake con parametros y demás
TITLE Build


echo Introduce the folder where PythonX.X is stored
set /p inPy="Example: for C:\User\Things\Python39 introduce C:\User\Things:   "

cd dependencies\Ogre\
call build.bat
cd ..\CEGUI\
call build.bat
cd ..\bullet\
call build.bat %inPy%
cd ..\..\

echo Copiando DLLs de Ogre...

copy dependencies\Ogre\build\bin\debug\OgreMain_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\release\OgreMain.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\debug\OgreMain_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\release\zlib.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\debug\RenderSystem_GL_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\release\RenderSystem_GL.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\release\Codec_STBI.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\debug\Codec_STBI_d.dll bin\ 1>NUL

echo Copiando DLLs de SDL2...

copy dependencies\Ogre\build\SDL2-build\Debug\SDL2d.dll bin\ 1>NUL
copy dependencies\Ogre\build\SDL2-build\RelWithDebInfo\SDL2.dll bin\ 1>NUL

echo Copiando DLLs de Bullet...

copy dependencies\bullet\src\bin\pybullet_vs2010_x64_release.dll bin\ 1>NUL
copy dependencies\bullet\src\bin\pybullet_vs2010_x64_debug.dll bin\ 1>NUL

echo Copiando DLLs de FMOD...
copy dependencies\fmod\fmod.dll bin\ 1>NUL
copy dependencies\fmod\fmodL.dll bin\ 1>NUL

echo Copiando DLLs de CEGUI...

copy dependencies\CEGUI\build\bin\CEGUIBase-0_d.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIBase-0.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\freetype.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\freetype_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\libexpat.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\libexpat_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\pcre.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\pcre_d.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\libexpat.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\libexpat_d.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUICoreWindowRendererSet.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUICoreWindowRendererSet_d.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIExpatParser.dll bin\ 1>NUL
copy dependencies\CEGUI\build\bin\CEGUIExpatParser_d.dll bin\ 1>NUL


echo Copiando DLLs scripting...

copy dependencies\scripting\lua\lua54.dll bin\ 1>NUL

MSBuild .\PTSD.sln /p:Configuration=Release
MSBuild .\PTSD.sln /p:Configuration=Debug

PAUSE
