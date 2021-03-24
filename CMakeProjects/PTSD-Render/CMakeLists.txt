set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Render")
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

#Ogre - target_include_directories(${NAME} PUBLIC "${PTSD-ROOT}/dependencies/Ogre/build/include")
#Ogre - target_include_directories(${NAME} PUBLIC "/usr/local/include/OGRE")
#Ogre - target_link_libraries(${NAME} LINK_PUBLIC "OgreMain")
list(APPEND PTSD_Modules ${NAME})
