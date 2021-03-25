set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PTSD_ROOT}/bin/")

set("NAME" "PTSD-Physics")
set ("MY_SOURCE" "${PTSD_PROJECTS}${NAME}/src/")
set ("MY_INCLUDE" "${PTSD_PROJECTS}${NAME}/include/")

#Add all sources
macro(add_source)
		foreach (_src ${ARGN})
				list(APPEND SRCS "${MY_SOURCE}${_src}")
		endforeach()
endmacro()
				
#My sources
add_source(PTSDPhysics)

#Create lib as target
add_library(${NAME} SHARED ${SRCS})

#My include
target_include_directories(${NAME} PUBLIC "${MY_INCLUDE}")


#Bullet include
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/bullet/src/src")
target_include_directories(${NAME} PUBLIC "${PTSD_ROOT}dependencies/bullet/src/Extras")
target_compile_definitions(${NAME} PUBLIC _PTSDPHYS)

#Bullet linking

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set( PYBULLET_LIB_DIR ${PTSD_ROOT}dependencies/bullet/Debug/lib/)
ELSE()
	set( PYBULLET_LIB_DIR ${PTSD_ROOT}dependencies/bullet/RelWithDebInfo/lib/)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

target_link_directories(${NAME} PUBLIC ${PYBULLET_LIB_DIR})
target_link_libraries( ${NAME} 
															${PYBULLET_LIB_DIR}libLinearMath.so
															${PYBULLET_LIB_DIR}libBulletCollision.so
															${PYBULLET_LIB_DIR}libBullet3Geometry.so
															${PYBULLET_LIB_DIR}libBulletDynamics.so
															)

# find_package(Bullet REQUIRED)
# include_directories(${BULLET_INCLUDE_DIR})
# target_link_libraries(${NAME} ${BULLET_LIBRARIES})


#Append my target as a PTSD module and my include as such
list(APPEND PTSD_MODULES ${NAME})
set(PTSD_MODULES ${PTSD_MODULES} PARENT_SCOPE)

list(APPEND PTSD_MODULES_INCLUDES ${MY_INCLUDE})
set(PTSD_MODULES_INCLUDES ${PTSD_MODULES_INCLUDES} PARENT_SCOPE)
# $(SolutionDir)\dependencies\bullet\src\src;
# $(SolutionDir)\dependencies\bullet\build\vs2010;
# $(SolutionDir)\dependencies\bullet\src\Extras;