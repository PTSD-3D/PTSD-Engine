#####################
#Setup and variables#
#####################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")
set(CMAKE_CXX_STANDARD 17)
set("NAME" "PTSD-Physics")
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
add_source(PTSDPhysics) #<----- Add al sources here
add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")
target_compile_definitions(${NAME} PUBLIC _PTSDPHYS)


################
#Bullet include#
################

target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/bullet/src/src")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/bullet/src/Extras")


################
#Bullet linking#
################

#Set the lib directory depending on debug or release
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set( PYBULLET_LIB_SUF "_d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

target_link_libraries( ${NAME} 
															LinearMath${PYBULLET_LIB_SUF}
															BulletCollision${PYBULLET_LIB_SUF}
															Bullet3Geometry${PYBULLET_LIB_SUF}
															BulletDynamics${PYBULLET_LIB_SUF})


#######################################################
#PTSD MODULE variables for PTSD Core to link propertly#
#######################################################

list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)