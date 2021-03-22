set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

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
#add_source(main.cpp test.cpp)

add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")

#CEGUI - target_include_directories(${NAME} PUBLIC "${PTSD-ROOT}/dependencies/Ogre/build/include")
#CEGUI - target_include_directories(${NAME} PUBLIC "/usr/local/include/OGRE")
#CEGUI && OGRE - target_link_libraries(${NAME} LINK_PUBLIC "OgreMain")
list(APPEND PTSD_Modules ${NAME})
