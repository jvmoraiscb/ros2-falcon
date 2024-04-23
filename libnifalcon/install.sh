#!/bin/sh

# its always good to update the repositories :)
sudo apt update
# install dependencies
sudo apt install -y build-essential cmake libusb-1.0-0 && \
# add udev rule
sudo cp linux/40-novint-falcon-udev.rules /etc/udev/rules.d && \
# build and install libnifalcon
mkdir build && \
cd build && \
cmake -G "Unix Makefiles" .. && \
make && \
sudo make install && \
sudo /sbin/ldconfig -v
