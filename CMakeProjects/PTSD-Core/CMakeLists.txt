#################
#Setup variables#
#################

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")
set (CMAKE_CXX_STANDARD 17)
set ("NAME" "PTSD-Core")
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
add_source( main test )#<----- Add al sources here
add_executable(${NAME} ${SRCS})
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")


##################################
#PTSD-Modules linking and include#
##################################

target_include_directories(PTSD-Core PUBLIC "${PTSD_MODULES_INCLUDES}")
target_link_libraries(PTSD-Core LINK_PRIVATE ${PTSD_MODULES})

# target_link_directories(PTSD-Core PRIVATE "${PTSD_ROOT}dependencies/Ogre/build/lib")
