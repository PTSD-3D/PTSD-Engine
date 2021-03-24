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
OgreDir="${PWD}/dependencies/Ogre/";
SpdlogDir="${PWD}/dependencies/spdlog/";

function setupDirectories()
{
	checkOrMake "${1}Debug"; 
	checkOrMake "${1}RelWithDebInfo";
	checkOrMake "${1}build";
	checkOrFail "${1}src";
}


function buildOgreRelease(){
	cd "${OgreDir}build";
	printGreen "Configurando CMake" && cmake -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" "../src/";
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
	cd "${OgreDir}build";
	printGreen "Configuring CMake" && cmake -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_BUILD_TOOLS:BOOL="0" -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="/usr/local" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" "../src/";
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
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake ../src;
	printGreen "Building Spdlog with Release" && cmake --build ".";
	cp *.a ../RelWithDebInfo/
}


function buildSpdlogDebug(){
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" ../src;
	printGreen "Building Spdlog with Debug" && cmake --build ".";
	cp *.a ../Debug/
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
	elif [ ${inputVar} == '1' ]; then
		buildOgreDebug;
		buildSpdlogDebug;
	elif [ ${inputVar} == '2' ]; then
		buildOgreDebug;
		buildOgreRelease;
		buildSpdlogRelease;
		buildSpdlogDebug;
	elif [ ${inputVar} == '3' ]; then
		return 0;
	else
		echo "Option ${inputVar} not supported. Try again.";
		buildOgre;
	fi
}

setupDirectories ${OgreDir};
setupDirectories ${SpdlogDir};

buildAll;
# buildSpdlogRelease;
exit 0;
