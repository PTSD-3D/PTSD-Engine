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

#My modules include
target_include_directories(PTSD-Core PUBLIC "${PTSD_MODULES_INCLUDES}")

target_link_libraries(PTSD-Core LINK_PRIVATE ${PTSD_MODULES})
target_link_directories(PTSD-Core PRIVATE "${PTSD_ROOT}dependencies/Ogre/build/lib")
