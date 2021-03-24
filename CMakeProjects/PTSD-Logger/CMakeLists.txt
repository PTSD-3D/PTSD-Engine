set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Logger")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source(Logger PTSDLog)

add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")


#Add spdlog lib and include
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(SPDLOG_DEBUG, "d")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
target_link_libraries(${NAME} LINK_PUBLIC ${PTSD_ROOT}dependencies/spdlog/build/libspdlog${SPDLOG_DEBUG}.a)
# target_link_directories(${NAME} PRIVATE ${PTSD_ROOT}dependencies/spdlog/build/)
target_include_directories(${NAME} PUBLIC ${PTSD_ROOT}dependencies/spdlog/src/include)


target_compile_definitions(${NAME} PUBLIC _PTSDLOG)

list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)