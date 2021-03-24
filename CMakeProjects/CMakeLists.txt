cmake_minimum_required (VERSION 3.10)
project (PTSD-Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PTSD_ROOT "${PROJECT_SOURCE_DIR}/../")
set(PTSD_PROJECTS "${PROJECT_SOURCE_DIR}/../projects/")
set(PTSD_MODULES, "")
set(PTSD_MODULES_INCLUDES, "")

link_directories("${PTSD_ROOT}bin/")

#add all PTSD modules before core
add_subdirectory(PTSD-Logger)
add_subdirectory(PTSD-Graphics)
# add_subdirectory(PTSD-Input)
# add_subdirectory(PTSD-UI)
# add_subdirectory(PTSD-Physics)
# add_subdirectory(PTSD-Script)
#add_subdirectory(PTSD-Audio)

add_subdirectory(PTSD-Core/)