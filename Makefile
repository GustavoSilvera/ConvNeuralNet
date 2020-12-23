# Makefile for Gustavo Silvera's 2019 Convolutional Neural Net Project:
OF_ROOT=$HOME/OF

CC=g++ # OpenFrameworks uses g++ clang++ also works for terminal though
CPPFLAGS=-Wall -Wextra -Werror -Wshadow -pedantic -g -fwrapv -pthread 

# either the tty or graphical version
# OF_ROOT=$(realpath ../../../OF)

TTY_DIR=src/tty
TTY_OBJS=${TTY_DIR}/neuron.o \
${TTY_DIR}/layer.o \
${TTY_DIR}/net.o \
${TTY_DIR}/convneuralnet.o \
${TTY_DIR}/main.o

# TODO: add clean to remove all .o's
all: tty graphical

tty: bin/ConvNeuralNet

bin/ConvNeuralNet: ${TTY_OBJS}
	$(CC) $(FLAGS) -o bin/ConvNeuralNet ${TTY_OBJS} -lpthread

graphical:
	make -C src/graphical
