#                                               -*- cmake -*-
#
#  BulletConfig.cmake(.in)
#

# Use the following variables to compile and link against Bullet:
#  BULLET_FOUND              - True if Bullet was found on your system
#  BULLET_USE_FILE           - The file making Bullet usable
#  BULLET_DEFINITIONS        - Definitions needed to build with Bullet
#  BULLET_INCLUDE_DIR        - Directory where Bullet-C-Api.h can be found
#  BULLET_INCLUDE_DIRS       - List of directories of Bullet and it's dependencies
#  BULLET_LIBRARIES          - List of libraries to link against Bullet library
#  BULLET_LIBRARY_DIRS       - List of directories containing Bullet' libraries
#  BULLET_ROOT_DIR           - The base directory of Bullet
#  BULLET_VERSION_STRING     - A human-readable string containing the version

set ( BULLET_FOUND 1 )
set ( BULLET_USE_FILE     "lib/cmake/bullet/UseBullet.cmake" )
set ( BULLET_DEFINITIONS  "-DBT_USE_DOUBLE_PRECISION" )
set ( BULLET_INCLUDE_DIR  "include/bullet" )
set ( BULLET_INCLUDE_DIRS "include/bullet" )
set ( BULLET_LIBRARIES    "LinearMath;Bullet3Common;BulletInverseDynamics;BulletCollision;BulletDynamics;BulletSoftBody" )
set ( BULLET_LIBRARY_DIRS "lib" )
set ( BULLET_ROOT_DIR     "/home/drathi/DEV/Uni-Tercero/P3/repo/PTSD-Engine/dependencies/bullet/Debug" )
set ( BULLET_VERSION_STRING "3.08" )
