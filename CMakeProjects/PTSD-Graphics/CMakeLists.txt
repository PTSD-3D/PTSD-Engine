#################
#Setup variables#
#################

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}bin/")
set (CMAKE_CXX_STANDARD 17)
set ("NAME" "PTSD-Graphics")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

##################################
#Add as library with source macro#
##################################

macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
add_source( PTSDGraphics GraphicsImplementation Camera CameraImplementation GraphicsLogger )#<----- Add al sources here
add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}" PUBLIC "${PTSD_LOGGER_INCLUDE}")
target_compile_definitions(${NAME} PUBLIC _PTSDGraphics)

##########################
#Ogre linking and include#
##########################

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(OGRE_MAIN_DEBUG, "_d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries(${NAME} LINK_PUBLIC "OgreMain${OGRE_MAIN_DEBUG}")
#target_link_libraries(${NAME} LINK_PUBLIC "OgreBites")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/build/include")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/dependencies/include")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/src/OgreMain/include/")


#########################
#SDL linking and include#
#########################

find_package(SDL2 REQUIRED)
target_include_directories(${NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${NAME} PRIVATE ${SDL2_LIBRARIES})

#######################################################
#PTSD MODULE variables for PTSD Core to link propertly#
#######################################################

list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)
