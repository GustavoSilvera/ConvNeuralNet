#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

# create bin directory if needed
mkdir -p bin

# clean up old binary (if exists)
rm -f bin/ConvNeuralNet

# run makefile
make tty || (echo -e "${RED}make failed ${NC}" && exit 1)

# remove old obj files
rm -rf obj/tty

# create obj files
mkdir -p obj
mkdir -p obj/tty

# move obj files
mv src/tty/*.o obj/tty/
echo -e "${GREEN}Successfully installed in ./bin/ConvNeuralNet ${NC}"