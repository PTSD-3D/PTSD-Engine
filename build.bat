@ECHO OFF
:: Por ahora voy a hacer esto para mover los .dll de Ogre a nuestro /bin/ Pero en teoría
::además debería de buildear Ogre llamando a cmake con parametros y demás
TITLE Build

echo Copiando DLLs de Ogre...

copy dependencies\Ogre\build\bin\debug\OgreMain_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\relwithdebinfo\OgreMain.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\relwithdebinfo\zlib.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\debug\RenderSystem_GL_d.dll bin\ 1>NUL
copy dependencies\Ogre\build\bin\release\RenderSystem_GL.dll bin\ 1>NUL


echo Copiando DLLs de CEGUI...
copy dependencies\CEGUI\build\bin\CEGUIBase-0_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\freetype.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\freetype_d.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\pcre.dll bin\ 1>NUL
copy dependencies\CEGUI\src\dependencies\bin\pcre_d.dll bin\ 1>NUL

PAUSE