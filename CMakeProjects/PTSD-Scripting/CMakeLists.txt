set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Scripting")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")
set(CMAKE_CXX_STANDARD 17)


#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source( PTSDScripting )

add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PRIVATE "${PTSD_ROOT}dependencies/lua/include")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/")
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")

#Link lua
set(LUA_LIB_DIR "${PTSD_ROOT}dependencies/lua/lua-5.4.2/RelWithDebInfo/liblua5.4.2.so")
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(LUA_LIB_DIR, "${PTSD_ROOT}dependencies/lua/lua-5.4.2/Debug/liblua5.4.2.so")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries(${NAME} ${LUA_LIB_DIR})

#Compiler defs
target_compile_definitions(${NAME} PUBLIC _PTSDSCRIPTING)



#Add myself to list and includes of modules
list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)
