#!/bin/bash
# Run this shell script to build and run the project
# Use './SippetScript.sh' or './SippetScript.sh Debug' for debug build
# Use './SippetScript.sh Release' for release build

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=${1:-Debug} ..
cmake --build .

WORKING_DIRECTORY="$(cd .. && pwd)"
echo "Running SippetScript with working directory: $WORKING_DIRECTORY"
(cd "$WORKING_DIRECTORY" && ./build/SippetScript)

cd ..