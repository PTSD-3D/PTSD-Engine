set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Core")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source(main.cpp test.cpp)

add_executable(PTSD-Core ${SRCS})

#My include
target_include_directories(PTSD-Core PUBLIC "${MY_INCLUDE}")

target_include_directories(PTSD-Core PUBLIC "${PTSD-ROOT}/dependencies/Ogre/build/include")
target_include_directories(PTSD-Core PUBLIC "/usr/local/include/OGRE")
target_link_libraries(PTSD-Core LINK_PUBLIC "OgreMain")
target_link_libraries(PTSD-Core LINK_PRIVATE ${PTSD_Modules})
