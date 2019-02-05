#! /usr/bin/env bash
 
sudo apt-get install openjdk-8-jdk -y
sudo apt-get install ant -y
sudo apt-get install avr-libc binutils-avr avrdude gcc-avr -y
 
echo "/*========================*/"
echo "Downloading Arduino 1.8.5"
echo "/*========================*/"

cd ~/Source
wget https://github.com/arduino/Arduino/releases/download/1.8.5/Arduino-1.8.5.tar.xz
tar --xz -xf Arduino-1.8.5.tar.xz 
cd Arduino-1.8.5/build/linux


