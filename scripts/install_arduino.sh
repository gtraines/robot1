#! /usr/bin/env bash
 

echo "/*========================*/"
echo "Downloading Arduino 1.8.5"
echo "/*========================*/"

cd ~/Source
wget https://github.com/arduino/Arduino/releases/download/1.8.5/Arduino-1.8.5.tar.xz
tar --xz -xf Arduino-1.8.5.tar.xz 
cd Arduino-1.8.5/build/
cp ~/Source/robot1/scripts/build_arduino_arm.sh .
cp ~/Source/robot1/scripts/reference-1.6.6-3.zip shared/
cd ~/Source/Arduino-1.8.5/build/
chmod +x ~/Source/Arduino-1.8.5/build/build_arduino_arm.sh
sudo bash ~/Source/Arduino-1.8.5/build/build_arduino_arm.sh

