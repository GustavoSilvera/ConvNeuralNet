CC=clang++
FLAGS=-Wall -Wextra -Werror -Wshadow -pedantic -g -fwrapv -pthread  

.PHONY:
	c0vm c0vmd clean
default:
	$(CC) $(FLAGS) -o app neuron.cpp layer.cpp net.cpp convneuralnet.cpp main.cpp

clean:
	rm -Rf app
