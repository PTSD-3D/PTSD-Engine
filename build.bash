#!/bin/bash

function printStatus()
{
	height=$(tput lines;)
	height=$(echo "${height}/2" | bc)
	printLogo ${height} 
}
function printLogo()
{
	sz=${1}
	for (( i = 0; i < sz-1; ++i )); do
        printf '%*s/%*s\\\n' "$((sz-i-1))" "" "$((2*i))" ""
	done

	if [[ $sz -gt 1 ]]; then
					printf '/%s\\\n' "$( yes '_' | head -n "$((2*i))" | tr -d '\n' )"
	fi
}

spinner()
{
    local pid=$!
    local delay=0.75
    local spinstr='|/-\'
    while [ "$(ps a | awk '{print $1}' | grep $pid)" ]; do
        local temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    printf "    \b\b\b\b"
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
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

# Setup and check dirs
BinDir="${PWD}/bin/";
DependenciesDir="${PWD}/dependencies";
OgreDir="${PWD}/dependencies/Ogre/";
SpdlogDir="${PWD}/dependencies/spdlog/";
LuaDir="${PWD}/dependencies/scripting/lua/lua-5.4.2/";
BulletDir="${PWD}/dependencies/bullet/";
CEGUI="${PWD}/dependencies/CEGUI/";

function setupDirectories()
{
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
	printf "\-Ogre Release:"
	checkForLib libOgreMain.so 
	if [[ ${?} == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;

	cd "${OgreDir}build";
	printGreen "Configurando CMake" && cmake -DOGRE_CONFIG_ENABLE_ZIP:BOOL="1" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="1" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="1" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" "../src/" &> /dev/null;
	printGreen "Building Ogre en Release" && cmake --build "." &>/dev/null & spinner 
	printGreen "Installing Ogre en ${OgreDir}RelWithDebInfo/";

	cp -r Dependencies ../RelWithDebInfo/Dependencies;
	cp -r include ../RelWithDebInfo/include;
	cp -r lib ../RelWithDebInfo/lib;

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
	cd "${OgreDir}build/Dependencies";
	cp  lib/*.so* ${BinDir}
}
function buildOgreDebug(){
	printf "\-Ogre Debug: "
	checkForLib libOgreMain_d.so
	if [[ $? == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${OgreDir}build";
	printGreen "Configuring CMake" && cmake -DOGRE_INSTALL_CMAKE:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_NODELESS_POSITIONING:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_DEPENDENCIES:BOOL="1" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="1" -DOGRE_BUILD_TOOLS:BOOL="0" -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="/usr/local" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_PLUGIN_STBI:BOOL="1" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="1" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" "../src/" &>/dev/null;
	printGreen "Building Ogre en Debug" && cmake  --build "." &>/dev/null & spinner 
	printGreen "Installing Ogre en ${OgreDir}Debug/";
		cp -r Dependencies ../Debug/Dependencies
		cp -r include ../Debug/include
		cp -r lib ../Debug/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
	cd "${OgreDir}build/Dependencies";
	cp  lib/*.so* ${BinDir};
}


function buildSpdlogRelease(){
	printf "\-Spdlog Release: "
	checkForLib /dependencies/spdlog/build/libspdlog.a ${PWD}
	if [[ $? == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_BUILD_TYPE:STRING="Release" ../src
	printGreen "Building Spdlog with Release" && cmake --build "." &>/dev/null & spinner 
	cp *.a ../RelWithDebInfo/
}
function buildSpdlogDebug(){
	printf "\-Spdlog Debug: "
	checkForLib /dependencies/spdlog/build/libspdlogd.a ${PWD}
	if [[ $? == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${SpdlogDir}build";
	printGreen "Configuring CMake" && cmake -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DCMAKE_BUILD_TYPE:STRING="Debug" ../src &>/dev/null;
	printGreen "Building Spdlog with Debug" && cmake --build "." & spinner
	cp *.a ../Debug/
}


function buildCEGUIDebug(){
	printf "\-CEGUI Debug: "
	checkForLib libCEGUIBase-0_d.so 
	if [[ ${?} == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${CEGUI}build";
	printGreen "Configuring CMake" && cmake -DCEGUI_HAS_FREETYPE:BOOL="1"  -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_DEBUG_POSTFIX:STRING="_d" -DOGRE_LIB_DBG:FILEPATH=${DependenciesDir}"/Ogre/Debug/lib/libOgreMain_d.so" -DCCACHE_FOUND:FILEPATH="CCACHE_FOUND-NOTFOUND" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_PLUGIN_DIR_DBG:STRING=${BinDir} -DOGRE_H_PATH:PATH=${OgreDir}"/src/OgreMain/include" -DOGRE_PLUGIN_DIR_REL:STRING="${BinDir}" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="${OgreDir}/build/include" -DOGRE_LIB:FILEPATH="${OgreDir}RelWithDebInfo/lib/libOgreMain.so"  "../src/" &>/dev/null;
	printGreen "Building CEGUI en Debug \n---------------------------\n" && cmake  --build "." &  spinner
	printGreen "Installing Ogre en ${CEGUI}Debug/";
		
	cp -r Dependencies ../Debug/Dependencies
	cp -r cegui/include ../Debug/include
	cp -r lib ../Debug/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
}
function buildCEGUIRelease(){
	printf "\-CEGUI Release: "
	checkForLib libCEGUIBase-0.so 
	if [[ ${?} == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${CEGUI}build";
	printGreen "Configuring CMake" && cmake  -DCEGUI_FOUND_OGRE_VERSION_MAJOR=1 -DCEGUI_FOUND_OGRE_VERSION_MINOR=12 -DCEGUI_FOUND_OGRE_VERSION_PATCH=14 -DCMAKE_CXX_STANDARD=11 -DCEGUI_HAS_FREETYPE:BOOL="1" -DCMAKE_BUILD_TYPE="Release" -DOGRE_LIB_DBG:FILEPATH=${DependenciesDir}"/Ogre/Debug/lib/libOgreMain_d.so" -DCCACHE_FOUND:FILEPATH="CCACHE_FOUND-NOTFOUND" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_PLUGIN_DIR_DBG:STRING=${BinDir} -DOGRE_H_PATH:PATH=${OgreDir}"/src/OgreMain/include" -DOGRE_PLUGIN_DIR_REL:STRING="${BinDir}" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="${OgreDir}/build/include" -DOGRE_LIB:FILEPATH="${OgreDir}RelWithDebInfo/lib/libOgreMain.so"  "../src/" &>/dev/null;
	sed -i '/define CEGUI_OGRE_VERSION_MAJOR 0/c\#define CEGUI_OGRE_VERSION_MAJOR 1' ${CEGUI}build/cegui/include/CEGUI/Config.h
	sed -i '/define CEGUI_OGRE_VERSION_MINOR 0/c\#define CEGUI_OGRE_VERSION_MINOR 12' ${CEGUI}build/cegui/include/CEGUI/Config.h
	sed -i '/define CEGUI_OGRE_VERSION_PATCH 0/c\#define CEGUI_OGRE_VERSION_PATCH 14' ${CEGUI}build/cegui/include/CEGUI/Config.h
	cmake  --build "." &  spinner 
		
	cp -r Dependencies ../RelWithDebInfo/Dependencies
	cp -r cegui/include ../RelWithDebInfo/include
	cp -r lib ../RelWithDebInfo/lib

	#Move Shared Libraries to bin
	cp  lib/*.so* ${BinDir};
}


function buildBulletRelease(){
	printf "\-Bullet Release: "
	checkForLib libBulletDynamics.so 
	if [[ ${?} == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;

	cd ${BulletDir}src;
	printGreen "Executing bullet build_release.sh" && ./build_cmake_pybullet_double.sh &>/dev/null & spinner;
	cd ./build3;
	chmod +x ./premake4_linux64 
	./premake4_linux64 --double gmake
	cd ./gmake;
	make;	
	cd ${BulletDir}src/build_cmake/src;
	cp	./*/*LinearMath.so* ${BinDir}
	cp	./*/*BulletCollision.so* ${BinDir}
	cp	./*/*Bullet3Geometry.so* ${BinDir}
	cp	./*/*BulletDynamics.so* ${BinDir}
	# rm -rf ${BulletDir}src/build_release/;
}

function buildBulletDebug(){
	printf "\-Bullet Debug: "
	checkForLib libBulletDynamics_d.so 
	if [[ ${?} == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	
	cd ${BulletDir}src;
	printGreen "Executing bullet build_debug.sh" && ./build_debug.sh &>/dev/null;

	cd ${BulletDir}src/build_debug/;
	cmake --install . &  spinner 
	cd ${BulletDir}Debug/lib;
	cp	*LinearMath* ${BinDir}
	cp	*BulletCollision* ${BinDir}
	cp	*Bullet3Geometry* ${BinDir}
	cp	*BulletDynamics* ${BinDir}
	rm -rf ${BulletDir}src/build_debug/;
}


function buildLuaDebug(){
	printf "\-Lua Debug: "
	checkForLib liblua5.4.2_d.so
	if [[ $? == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${LuaDir}";
	make MYCFLAGS="-g -ggdb -fPIC" "R=5.4.2" all &>/dev/null & spinner; 
	# mv ./src/liblua.a ./Debug/
	mv ./src/liblua5.4.2.so ./Debug/
	cp ./Debug/liblua5.4.2.so ${BinDir}liblua5.4.2_d.so
	make clean &>/dev/null; 
}
function buildLuaRelease(){
	printf "\-Lua Release: "
	checkForLib liblua5.4.2.so
	if [[ $? == 1 ]]; then
		echo -e "${GREEN}\xE2\x9C\x94${NC}"
		return;
	fi;
	cd "${LuaDir}";
	make MYCFLAGS="-O3 -fPIC" "R=5.4.2" all &>/dev/null & spinner; 
	# mv ./src/liblua.a ./RelWithDebInfo
	mv ./src/liblua5.4.2.so ./RelWithDebInfo
	cp ./RelWithDebInfo/liblua5.4.2.so ${BinDir}liblua5.4.2.so
	make clean &>/dev/null; 
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
	read -s -n 1 inputVar;
	rgx='^[0-9]+$'
	if ! [[ $inputVar =~ $rgx  ]];then
		echo "Option ${inputVar} not supported. Try again.";
		exit 1
	fi;
	printStatus inputVar
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
	fi
}

setupDirectories ${OgreDir};
setupDirectories ${SpdlogDir};
setupDirectories ${LuaDir};
setupDirectories ${CEGUI};
setupDirectories ${BulletDir};

buildAll;

exit 0;
