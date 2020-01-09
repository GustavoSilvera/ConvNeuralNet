# Makefile for Gustavo Silvera's 2019 Convolutional Neural Net Project:
OF_ROOT=$HOME/OF

CC=g++ #OpenFrameworks uses g++... clang++ also works for terminal though
CPPFLAGS=-Wall -Wextra -Werror -Wshadow -pedantic -g -fwrapv -pthread 

#either the terminal or graphical version

OF_ROOT=$(realpath ../../../OF)

TERM_DIR=src/terminal
TERM_OBJS=${TERM_DIR}/neuron.o \
${TERM_DIR}/layer.o \
${TERM_DIR}/net.o \
${TERM_DIR}/convneuralnet.o \
${TERM_DIR}/main.o

all: terminal graphical

terminal: bin/terminal

bin/terminal: ${TERM_OBJS}
	$(CC) $(FLAGS) -o bin/terminal ${TERM_OBJS} -lpthread

graphical:
	make -C src/graphical
