cmake_minimum_required (VERSION 3.10)
project (PTSD-Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PTSD_ROOT "${PROJECT_SOURCE_DIR}/../")
set(PTSD_PROJECTS "${PROJECT_SOURCE_DIR}/../projects/")
set(PTSD_MODULES, "")

link_directories("/usr/local/lib")

#add all PTSD modules before core
add_subdirectory(PTSD-Core)

