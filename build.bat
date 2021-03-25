@ECHO OFF
:: Por ahora voy a hacer esto para mover los .dll de Ogre a nuestro /bin/ Pero en teoría
::además debería de buildear Ogre llamando a cmake con parametros y demás
TITLE Build

echo Copiando DLLs...

copy dependencies\Ogre\build\bin\debug\OgreMain_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\relwithdebinfo\OgreMain.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\relwithdebinfo\zlib.dll bin\ 1>NUL
copy dependencies\bullet\src\bin\pybullet_vs2010_x64_release.dll bin\ 1>NUL
copy dependencies\bullet\src\bin\pybullet_vs2010_x64_debug.dll bin\ 1>NUL
copy dependencies\Ogre\build\SDL2-build\Debug\SDL2d.dll bin\ 1>NUL
copy dependencies\Ogre\build\SDL2-build\RelWithDebInfo\SDL2.dll bin\ 1>NUL

echo Copiando DLLs scripting...

copy dependencies\lua\lua54.dll bin\ 1>NUL

PAUSE