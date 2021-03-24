set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Graphics")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source(Graphics PTSDGraphics)

add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")


#Link with Ogre and includes
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(OGRE_MAIN_DEBUG, "_d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries(${NAME} LINK_PUBLIC "OgreMain${OGRE_MAIN_DEBUG}")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/build/include")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/src/OgreMain/include/")

#Add my self to PTSD MODULES list
list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

#Add my self to PTSD INCLUDES listt
list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)

list(APPEND PTSD_Modules ${NAME})
