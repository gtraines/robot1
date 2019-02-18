#! /usr/bin/env bash
 

echo "/*========================*/"
echo "Downloading Arduino 1.8.5"
echo "/*========================*/"

cd ~/Source
wget https://github.com/arduino/Arduino/releases/download/1.8.5/Arduino-1.8.5.tar.xz
tar --xz -xf Arduino-1.8.5.tar.xz 
cd Arduino-1.8.5/build/
cp ~/Source/robot1/scripts/build_arduino_arm.sh .
wget https://downloads.arduino.cc/libastylej-2.05.1-3.zip
wget https://downloads.arduino.cc/liblistSerials/liblistSerials-1.4.0.zip
wget https://downloads.arduino.cc/tools/arduino-builder-linuxarm-1.3.25.tar.bz2

cd shared/
wget https://downloads.arduino.cc/reference-1.6.6-3.zip
wget https://downloads.arduino.cc/Galileo_help_files-1.6.2.zip
wget https://downloads.arduino.cc/Edison_help_files-1.6.2.zip
cd ~/Source/Arduino-1.8.5/build/
chmod +x ~/Source/Arduino-1.8.5/build/build_arduino_arm.sh
bash ~/Source/Arduino-1.8.5/build/build_arduino_arm.sh

