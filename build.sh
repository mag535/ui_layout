#!/bin/sh


GEN="-G ${1}" # generator
ARC="-A ${2}" # architecture

if [ -z $1 ] # if $1 is empty, make GEN empty so CMake uses default generator
then
    echo "No generator specified, using cmake default"
    GEN=""
fi

if [ -z $2 ] # if $2 is empty, make ARC empty so CMake uses default architecture
then
    echo "No architecture specified, using cmake default"
    ARC=""
fi


# Use build system
cmake -S . -B build $GEN $ARC -DCMAKE_BUILD_TYPE=Debug
# Compile executable
cmake --build build
