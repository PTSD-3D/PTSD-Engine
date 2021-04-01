#################
#Setup variables#
#################

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")
set (CMAKE_CXX_STANDARD 17)
set ("NAME" "PTSD-Input")
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
add_source( PTSDInput InputImplementation)#<----- Add al sources here
add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")
target_compile_definitions(${NAME} PUBLIC _PTSDINPUT)


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
