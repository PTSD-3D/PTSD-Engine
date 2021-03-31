cmake_minimum_required (VERSION 3.12)
project (PTSD-Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PTSD_ROOT "${PROJECT_SOURCE_DIR}/../")
set(PTSD_PROJECTS "${PROJECT_SOURCE_DIR}/../projects/")
set(PTSD_MODULES "")
set(PTSD_MODULES_INCLUDES "")
set(PTSD_LOGGER_INCLUDE  "${PTSD_ROOT}/projects/PTSD-Logger/include")
link_directories("${PTSD_ROOT}bin/")

##############
#PTSD Modules#
##############

add_subdirectory(PTSD-Logger)
add_subdirectory(PTSD-Graphics)
add_subdirectory(PTSD-Input)
add_subdirectory(PTSD-UI)
add_subdirectory(PTSD-Physics)
add_subdirectory(PTSD-Scripting)
add_subdirectory(PTSD-Sound)


###########
#PTSD Core#
###########

add_subdirectory(PTSD-Core/)