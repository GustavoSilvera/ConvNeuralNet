#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

# create bin directory if needed
mkdir -p bin

#clean up old binary (if exists)
if [-f bin/ConvNeuralNet] ; then rm bin/ConvNeuralNet fi

#Run makefile
make tty

#create obj files
if [-f obj/ConvNeuralNet] ; then rm -rf obj/ConvNeuralNet fi #if already compiled before
mkdir -p obj
mkdir -p obj/ConvNeuralNet

#move obj files
mv src/ConvNeuralNet/*.o obj/ConvNeuralNet/

printf "\n\nNote: the input data should still be in data/data.txt"
printf "\nSUCCESS! enter bin/ to run using \"./ConvNeuralNet\""

