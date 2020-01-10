#!bin/bash

#do everything in downloads
cd ~/Downloads
#download openframeworks
wget https://openframeworks.cc/versions/v0.11.0/of_v0.11.0_linux64gcc6_release.tar.gz
#unzip it
tar -xvf of_v*
#rename to OF
mv of_v0.11.0_linux64gcc6_release OF
#move to home directory
mv OF ~
cd ~/OF
#now have to install dependencies depending on linux distro...
#archlinux (x86 & armv7), debian, fedora, ubuntu, extra
cd scripts/linux/ubuntu
#run script
./install_dependencies.sh
