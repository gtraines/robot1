#!/bin/bash -ex

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
cd ${DIR}

ant -Djava.net.preferIPv4Stack=true -Dplatform=linuxarm $@ clean dist
mv linux/arduino-*-linuxarm.tar.xz ../

