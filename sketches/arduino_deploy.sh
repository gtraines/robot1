#!/usr/bin/env bash
./set_arduino_sketchbook_path.sh && \
arduino --board arduino:avr:mega --port /dev/ttyUSB0 --upload $1
