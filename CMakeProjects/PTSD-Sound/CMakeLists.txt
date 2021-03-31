#####################
#Setup and variables#
#####################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")
set(CMAKE_CXX_STANDARD 17)
set("NAME" "PTSD-Sound")
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
add_source( PTSDSound ) #<----- Add al sources here
add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")
target_compile_definitions(${NAME} PUBLIC _PTSDSOUND)


################
#Bullet include#
################

target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/fmod/src/")


################
#Bullet linking#
################

#Set the lib directory depending on debug or release
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set( FMOD_DEBUG "L")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

target_link_libraries( ${NAME} 
															fmod${FMOD_DEBUG})


#######################################################
#PTSD MODULE variables for PTSD Core to link propertly#
#######################################################

list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)