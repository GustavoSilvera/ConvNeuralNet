#!/bin/bash

GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

# removes all generated .o files and executables:

rm -rf obj/
rm -rf bin/
echo -e "${GREEN}All files cleaned! ${NC}"