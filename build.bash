#!/bin/bash
#Call this script to configure project in ./build.
#cmake --build ./build will compile the project
dir="build"

if [ ! -d "${dir}" ]; then
	mkdir "${dir}";
fi


cd "${dir}" && cmake ../CMakeProjects/ &>/dev/null;
