#!/bin/bash

# be SURE to have installed OF as described earlier

#Run makefile
make graphical

#create obj files
rm -rf obj/graphical #if already compiled before
mkdir obj
mkdir obj/graphical #new dir
#move obj files
mv src/graphical/obj/* obj/graphical/
rm -rf src/graphical/obj #clean up obj folder

#move bin files
rm -f bin/graphical #remove old graphical binary
rm -f bin/lib*      #remove old graphical library
mv src/graphical/bin/* ./bin

rm -rf src/graphical/bin #clean up bin folder
printf "\n\nNote: the input data should still be in data/data.txt"
printf "\nSUCCESS! enter bin/ to run graphical using \"./graphical\""
