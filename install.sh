#!/bin/sh

# Download and install taglib

TAGLIB="taglib.tar.gz"
TAGLIB_PATH="taglib-1.13"
TAGLIB_URI="https://taglib.org/releases/taglib-1.13.tar.gz"

curl $TAGLIB_URI --output $TAGLIB
tar -xvf $TAGLIB
cd $TAGLIB_PATH
cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release .
make
sudo make install
cd .. && rm -rf $TAGLIB_PATH $TAGLIB

