#!/bin/bash

#clean up old binary (if exists)
rm bin/terminal

#Run makefile
make terminal

#create obj files
rm -rf obj/terminal #if already compiled before
mkdir obj
mkdir obj/terminal
#move obj files
mv src/terminal/*.o obj/terminal/

printf "\n\nNote: the input data should still be in data/data.txt"
printf "\nSUCCESS! enter /bin to run terminal using \"./terminal\""

