#!/bin/bash

mkdir build &> /dev/null

cd build || exit 1

cmake  -DCMAKE_BUILD_TYPE=Release .. >> /dev/null # -G Ninja
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

make -j16

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

cd .. || exit 1

./build/bin/indproj
