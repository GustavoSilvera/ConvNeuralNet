# Makefile for Gustavo Silvera's 2019 Convolutional Neural Net Project:
CC=clang++
FLAGS=-Wall -Wextra -Werror -Wshadow -pedantic -g -fwrapv -pthread
#either the terminal or graphical version
.PHONY: terminal graphical clean
default: graphical

graphical:
# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
OF_ROOT=$(realpath ../../..)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk


terminal: 
	$(CC) $(FLAGS) -o ConvNeuralNet neuron.cpp layer.cpp net.cpp convneuralnet.cpp main.cpp

clean:
rm -Rf bin/ConvNeuralNet
