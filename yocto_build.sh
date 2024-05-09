#!/bin/sh
if [ -z $1 ]; then
    YOCTO_SDK_ENV=/opt/linn-fb/5.15-kirkstone/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi  
else
    YOCTO_SDK_ENV=$1
fi
source $YOCTO_SDK_ENV
_CC=$(python -c 'import os; print(" ".join(os.getenv("CC").split(" ")[1:]))')
_CXX=$(python -c 'import os; print(" ".join(os.getenv("CXX").split(" ")[1:]))')
make clean 
CFLAGS=$_CC CXXFLAGS=$_CXX LDFLAGS="--sysroot=$SDKTARGETSYSROOT" make
