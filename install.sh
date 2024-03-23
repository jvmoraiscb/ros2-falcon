#!/bin/sh

sudo apt-get install -y build-essential cmake libusb-1.0.0 && \
sudo cp linux/40-novint-falcon-udev.rules /etc/udev/rules.d && \
mkdir build && \
cd build && \
cmake -G "Unix Makefiles" .. && \
make && \
sudo make install && \
sudo /sbin/ldconfig -v