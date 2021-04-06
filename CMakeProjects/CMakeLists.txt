cmake_minimum_required (VERSION 3.12)
project (PTSD-Engine VERSION 0.2)

set(CMAKE_CXX_STANDARD 14)
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

list(APPEND PTSD_MODULES ${LOGGER} ${INPUT} ${PHYSICS} ${SCRIPTING} ${SOUND} ${UI} ${CORE} ${GRAPHICS})
foreach(PTSD_MOD in ${PTSD_MODULES})
	list(APPEND PTSD_MODULES_INCLUDES ${PTSD_MOD}include)
	list(APPEND PTSD_MODULES_SOURCES ${PTSD_MOD}source)
endforeach(PTSD_MOD)


# link_directories("${PTSD_ROOT}bin/")

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