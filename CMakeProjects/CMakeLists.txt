cmake_minimum_required (VERSION 3.12)
project (PTSD-Engine VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PTSD_ROOT "${PROJECT_SOURCE_DIR}/../")
set(PTSD_SOURCE "${PROJECT_SOURCE_DIR}/../source/")
set(PTSD_MODULES "")
set(PTSD_MODULES_INCLUDES "")
set(PTSD_MODULES_SOURCES "")

set(LOGGER "${PTSD_ROOT}source/Logger/")
set(INPUT "${PTSD_ROOT}source/Input/")
set(PHYSICS "${PTSD_ROOT}source/Physics/")
set(SCRIPTING "${PTSD_ROOT}source/Scripting/")
set(SOUND "${PTSD_ROOT}source/Sound/")
set(UI "${PTSD_ROOT}source/UI/")
set(CORE "${PTSD_ROOT}source/Core/")
set(GRAPHICS "${PTSD_ROOT}source/Graphics/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PTSD_ROOT}bin)

list(APPEND PTSD_MODULES ${LOGGER} ${INPUT} ${PHYSICS} ${SCRIPTING} ${SOUND} ${UI} ${CORE} ${GRAPHICS})
foreach(PTSD_MOD in ${PTSD_MODULES})
	list(APPEND PTSD_MODULES_INCLUDES ${PTSD_MOD}include/ )
	list(APPEND PTSD_MODULES_SOURCES ${PTSD_MOD}source/ )
endforeach(PTSD_MOD)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS 
     "../source/*/*.h"
     "../source/*/*.cpp"
)

include_directories(PTSD_Core PUBLIC ${PTSD_MODULES_INCLUDES})
add_executable(PTSD_Core ${SRC})
find_package(SDL2 REQUIRED)
target_include_directories(PTSD_Core 
																																PRIVATE ${SDL2_INCLUDE_DIRS}
																																PRIVATE  ${PTSD_ROOT}dependencies/fmod/src/
																																PRIVATE  ${PTSD_ROOT}dependencies/Ogre/src/OgreMain/include/
																																PRIVATE  ${PTSD_ROOT}dependencies/Ogre/build/include/
																																PRIVATE  ${PTSD_ROOT}dependencies/spdlog/src/include/
																																PRIVATE  ${PTSD_ROOT}dependencies/bullet/src/src/
																																PRIVATE  ${PTSD_ROOT}dependencies/scripting/lua/include/
																																PRIVATE  ${PTSD_ROOT}dependencies/scripting/
																																PRIVATE  ${PTSD_ROOT}dependencies/CEGUI/src/cegui/include/
																																PRIVATE  ${PTSD_ROOT}dependencies/CEGUI/build/cegui/include/
																																)
target_link_libraries(PTSD_Core 
																											PRIVATE ${SDL2_LIBRARIES}
																											PRIVATE ${PTSD_ROOT}dependencies/fmod/libfmod.so
																											PRIVATE ${PTSD_ROOT}bin/liblua5.4.2.so
																											PRIVATE ${PTSD_ROOT}bin/Codec_STBI.so
																											PRIVATE ${PTSD_ROOT}bin/libBullet3Geometry.so
																											PRIVATE ${PTSD_ROOT}bin/libBulletCollision.so
																											PRIVATE ${PTSD_ROOT}bin/libBulletDynamics.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUIBase-0.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUICommonDialogs-0.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUICoreWindowRendererSet.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUIExpatParser.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUILibXMLParser.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUIOgreRenderer-0.so
																											PRIVATE ${PTSD_ROOT}bin/libCEGUISDL2ImageCodec.so
																											PRIVATE ${PTSD_ROOT}bin/libLinearMath.so
																											PRIVATE ${PTSD_ROOT}bin/libOgreMain.so
																											PRIVATE ${PTSD_ROOT}bin/libzzip.a
																											PRIVATE /usr/lib/x86_64-linux-gnu/libz.so
																											)

##############
#PTSD Modules#
##############

# add_subdirectory(PTSD-Logger)
# add_subdirectory(PTSD-Graphics)
# add_subdirectory(PTSD-Input)
# add_subdirectory(PTSD-UI)
# add_subdirectory(PTSD-Physics)
# add_subdirectory(PTSD-Scripting)
# add_subdirectory(PTSD-Sound)


# ###########
# #PTSD Core#
# ###########

# add_subdirectory(PTSD-Core/)