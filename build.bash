#!/bin/bash

# -------------------------------- COLOR VARIABLES
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

#   ------------------------------ UTILITY FUNCTIONS
function printRed()
{
	for arg in "$@"; do
		printf "${RED}${arg}${NC}\n"
	done
}

function printGreen()
{
	for arg in "$@"; do
		printf "${GREEN}${arg}${NC}\n"
	done
}

#Checks for dir, otherwise exit
function checkOrFail(){
	if [[ ! -d "${1}" ]]; then
		printRed "Required directory missing: \n${1}"
		exit 1
	fi
}

#Checks for dir, otherwise make it
function checkOrMake(){
	if [[ ! -d "${1}" ]]; then
			mkdir "${1}";
	fi
}

#Changes Dir and makes it if needed
function checkAndCD(){
	checkOrMake ${1};
	cd "${1}";
}
#-------------------------------------------------------

#-------------------------------------------------------#
#                       Build Ogre                      #
#-------------------------------------------------------#


# Setup and check dirs
BinDir="${PWD}/bin/";
DependenciesDir="${PWD}/dependencies";
OgreDir="${PWD}/dependencies/Ogre/";
SpdlogDir="${PWD}/dependencies/spdlog/";
LuaDir="${PWD}/dependencies/lua/lua-5.4.2/";
BulletDir="${PWD}/dependencies/bullet/";
CEGUI="${PWD}/dependencies/CEGUI/";

function setupDirectories()
{
	checkOrMake "${1}Debug"; 
	checkOrMake "${1}RelWithDebInfo";
	checkOrMake "${1}build";
	checkOrFail "${1}src";
}
function checkForLib(){
	local rootdir=${BinDir}
	if [[ ${#} == 2 ]];then
		rootdir=${2};
	fi
	if [[ -f ${rootdir}${1} ]]; then
		return 1
	fi;
	return 0
}

function buildOgreRelease(){
	checkForLib libOgreMain.so 
	if [[ ${?} == 1 ]]; then
		printGreen "Ogre Release already in bin"
		return;
	fi;

	cd "${OgreDir}build";
	printGreen "Configurando CMake" && cmake -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="1" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" "../src/";
	printGreen "Building Ogre en Release" && cmake --build "."
	printGreen "Installing Ogre en ${OgreDir}RelWithDebInfo/";

	cp -r Dependencies ../RelWithDebInfo/Dependencies;
	cp -r include ../RelWithDebInfo/include;
	cp -r lib ../RelWithDebInfo/lib;

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
	cd "${OgreDir}build/Dependencies";
	cp  lib/*.so* ${BinDir} &> /dev/null;
}
function buildOgreDebug(){
	checkForLib libOgreMain_d.so
	if [[ $? == 1 ]]; then
		printGreen "Ogre Debug already in bin"
		return;
	fi;
	cd "${OgreDir}build";
	printGreen "Configuring CMake" && cmake -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_BUILD_TOOLS:BOOL="0" -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="/usr/local" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="1" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" "../src/";
	printGreen "Building Ogre en Debug" && cmake  --build "."
	printGreen "Installing Ogre en ${OgreDir}Debug/";
		cp -r Dependencies ../Debug/Dependencies
		cp -r include ../Debug/include
		cp -r lib ../Debug/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
	cd "${OgreDir}Build/Dependencies";
	cp  lib/*.so* ${BinDir} &> /dev/null;
}


function buildSpdlogRelease(){
	checkForLib /dependencies/spdlog/build/libspdlog.a ${PWD}
	if [[ $? == 1 ]]; then
		printGreen "Spdlog Release already in bin"
		return;
	fi;
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_BUILD_TYPE:STRING="Release" ../src;
	printGreen "Building Spdlog with Release" && cmake --build ".";
	cp *.a ../RelWithDebInfo/
}
function buildSpdlogDebug(){
	checkForLib /dependencies/spdlog/build/libspdlogd.a ${PWD}
	if [[ $? == 1 ]]; then
		printGreen "Spdlog Debug already in bin"
		return;
	fi;
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" ../src;
	printGreen "Building Spdlog with Debug" && cmake --build ".";
	cp *.a ../Debug/
}


function buildCEGUIDebug(){
	checkForLib libCEGUIBase-0_d.so 
	if [[ ${?} == 1 ]]; then
		printGreen "CEGUI Debug already in bin"
		return;
	fi;
	cd "${CEGUI}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DOGRE_LIB_DBG:FILEPATH=${DependenciesDir}"/Ogre/Debug/lib/libOgreMain_d.so" -DCCACHE_FOUND:FILEPATH="CCACHE_FOUND-NOTFOUND" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_PLUGIN_DIR_DBG:STRING=${BinDir} -DOGRE_H_PATH:PATH=${OgreDir}"/src/OgreMain/include" -DOGRE_PLUGIN_DIR_REL:STRING="${BinDir}" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="${OgreDir}/build/include" -DOGRE_LIB:FILEPATH="${OgreDir}RelWithDebInfo/lib/libOgreMain.so"  "../src/";
	printGreen "Building CEGUI en Debug \n---------------------------\n" && cmake  --build "."
	printGreen "Installing Ogre en ${CEGUI}Debug/";
		
	cp -r Dependencies ../Debug/Dependencies
	cp -r cegui/include ../Debug/include
	cp -r lib ../Debug/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
}
function buildCEGUIRelease(){
	checkForLib libCEGUIBase-0.so 
	if [[ ${?} == 1 ]]; then
		printGreen "CEGUI Release already in bin"
		return;
	fi;
	cd "${CEGUI}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_BUILD_TYPE="Release" -DOGRE_LIB_DBG:FILEPATH=${DependenciesDir}"/Ogre/Debug/lib/libOgreMain_d.so" -DCCACHE_FOUND:FILEPATH="CCACHE_FOUND-NOTFOUND" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_PLUGIN_DIR_DBG:STRING=${BinDir} -DOGRE_H_PATH:PATH=${OgreDir}"/src/OgreMain/include" -DOGRE_PLUGIN_DIR_REL:STRING="${BinDir}" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="${OgreDir}/build/include" -DOGRE_LIB:FILEPATH="${OgreDir}RelWithDebInfo/lib/libOgreMain.so"  "../src/";
	printGreen "Building CEGUI en Release \n---------------------------\n" && cmake  --build "."
	printGreen "Installing Ogre en ${CEGUI}Release/";
		
	cp -r Dependencies ../RelWithDebInfo/Dependencies
	cp -r cegui/include ../RelWithDebInfo/include
	cp -r lib ../RelWithDebInfo/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
}


function buildBulletRelease(){
	checkForLib libBulletDynamics.so 
	if [[ ${?} == 1 ]]; then
		printGreen "CEGUI Release already in bin"
		return;
	fi;

	cd ${BulletDir}src;
	printGreen "Executing bullet build_release.sh" && ./build_release.sh;
	cd ${BulletDir}/src/build_release/;
	cmake --install .;
	cd ${BulletDir}/RelWithDebInfo/lib;
	cp	*LinearMath* ${BinDir}
	cp	*BulletCollision* ${BinDir}
	cp	*Bullet3Geometry* ${BinDir}
	cp	*BulletDynamics* ${BinDir}
	rm -rf ${BulletDir}src/build_release/;
}
function buildBulletDebug(){
	checkForLib libBulletDynamics_d.so 
	if [[ ${?} == 1 ]]; then
		printGreen "CEGUI Debug already in bin"
		return;
	fi;
	
	cd ${BulletDir}src;
	printGreen "Executing bullet build_debug.sh" && ./build_debug.sh;

	cd ${BulletDir}/src/build_debug/;
	cmake --install .;
	cd ${BulletDir}/Debug/lib;
	cp	*LinearMath* ${BinDir}
	cp	*BulletCollision* ${BinDir}
	cp	*Bullet3Geometry* ${BinDir}
	cp	*BulletDynamics* ${BinDir}
	rm -rf ${BulletDir}src/build_debug/;
}


function buildLuaDebug(){
	checkForLib liblua5.4.2_d.so
	if [[ $? == 1 ]]; then
		printGreen "Lua Debug already in bin"
		return;
	fi;
	cd "${LuaDir}";
	make MYCFLAGS="-g -ggdb -fPIC" "R=5.4.2" all;
	# mv ./src/liblua.a ./Debug/
	mv ./src/liblua5.4.2.so ./Debug/
	cp ./Debug/liblua5.4.2.so ${BinDir}liblua5.4.2_d.so
	make clean;
}
function buildLuaRelease(){
	checkForLib liblua5.4.2.so
	if [[ $? == 1 ]]; then
		printGreen "Lua Release already in bin"
		return;
	fi;
	cd "${LuaDir}";
	make MYCFLAGS="-O3 -fPIC" "R=5.4.2" all;
	# mv ./src/liblua.a ./RelWithDebInfo
	mv ./src/liblua5.4.2.so ./RelWithDebInfo
	cp ./RelWithDebInfo/liblua5.4.2.so ${BinDir}liblua5.4.2.so
	make clean;
}


function readInput(){
	printf "In wich mode would you like to build PTSD-Engine dependencies:\n"
	printf "[0] Release\n"
	printf "[1] Debug\n"
	printf "[2] Release and Debug\n"
	printf "[3] Quit\n"
}




function buildAll(){
	readInput;
	read -n 1 inputVar;
	if [ ${inputVar} == '0' ]; then
		buildOgreRelease;
		buildSpdlogRelease;
		buildLuaRelease;
		buildCEGUIRelease;
		buildBulletRelease;

	elif [ ${inputVar} == '1' ]; then
		buildOgreDebug;
		buildSpdlogDebug;
		buildLuaDebug;
		buildCEGUIDebug;
		buildBulletDebug;
	elif [ ${inputVar} == '2' ]; then
		buildOgreDebug;
		buildOgreRelease;
		buildSpdlogRelease;
		buildSpdlogDebug;
		buildLuaDebug;
		buildLuaRelease;
		buildCEGUIDebug;
		buildCEGUIRelease;
		buildBulletDebug;
		buildBulletRelease;
	elif [ ${inputVar} == '3' ]; then
		return 0;
	else
		echo "Option ${inputVar} not supported. Try again.";
		buildOgre;
	fi
}

setupDirectories ${OgreDir};
setupDirectories ${SpdlogDir};
setupDirectories ${LuaDir};
setupDirectories ${CEGUI};
setupDirectories ${BulletDir};

buildAll;
exit 0;
