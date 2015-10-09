#!/bin/bash

# Allow to build with sublime text.
# This lives in your project directory, alongside src/, bin/, config.make, etc

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
make Debug -j7 && make RunDebug;