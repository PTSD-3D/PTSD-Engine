
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}bin/")
set (CMAKE_CXX_STANDARD 17)
set("NAME" "PTSD-UI")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source(PTSDUI UIImplementation)

add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")

#CEGUI linking
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CEGUI_DEBUG, "_d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries( ${NAME} ${PTSD_ROOT}bin/libCEGUIBase-0${CEGUI_DEBUG}.so)
target_link_libraries( ${NAME} ${PTSD_ROOT}bin/libCEGUIOgreRenderer-0${CEGUI_DEBUG}.so)

#CEGUI includes
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	target_include_directories(${NAME} PUBLIC ${PTSD_ROOT}dependencies/CEGUI/Debug/include)
ELSE()
	target_include_directories(${NAME} PUBLIC ${PTSD_ROOT}dependencies/CEGUI/RelWithDebInfo/include)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
message(>${PTSD_GRAPHICS_INCLUDE})
message(>${PTSD_GRAPHICS_INCLUDE})
message(>${PTSD_GRAPHICS_INCLUDE})
message(>${PTSD_GRAPHICS_INCLUDE})

target_include_directories(${NAME} PUBLIC ${PTSD_ROOT}dependencies/CEGUI/src/cegui/include/ 		PUBLIC 	${PTSD_GRAPHICS_INCLUDE})

#Including all ogre bcs i dont know where the f ogre window is
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/build/include")
#target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/dependencies/include")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}/dependencies/Ogre/src/OgreMain/include/")

#Target compile definition for API
target_compile_definitions(${NAME} PUBLIC _PTSDUI)


list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)
