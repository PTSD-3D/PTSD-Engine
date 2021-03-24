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

#Creo que solo deberían hacer falta includes de PTSD-Modules y librerías de la STL si eso
target_include_directories(PTSD-Core PUBLIC "${PTSD_ROOT}/dependencies/Ogre/build/include")
target_include_directories(PTSD-Core PUBLIC "${PTSD_ROOT}/dependencies/Ogre/src/OgreMain/include/")
#target_include_directories(PTSD-Core PUBLIC "/usr/local/include/OGRE")


#-> No debería de linkar con Ogre. Esto es provisional
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(OGRE_MAIN_DEBUG, "_d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries(PTSD-Core LINK_PUBLIC "OgreMain${OGRE_MAIN_DEBUG}")


target_link_libraries(PTSD-Core LINK_PRIVATE ${PTSD_Modules})

target_link_directories(PTSD-Core PRIVATE "${PTSD_ROOT}dependencies/Ogre/build/lib")