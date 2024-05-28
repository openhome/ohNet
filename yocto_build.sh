#!/bin/sh
if [ -z $1 ]; then
    YOCTO_SDK_ENV=/opt/linn-fb/5.15-kirkstone/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi  
else
    YOCTO_SDK_ENV=$1
fi
source $YOCTO_SDK_ENV
# Yocto env appends essential build flags to CC/CXX environment variables;
# our makefiles doesn't use CC to determine compiler since we do some more complex stuff to deal with building under other OSes.
# just strip out these flags and place in the CFLAGS variable since this is still used
_CC=$(python -c 'import os; print(" ".join(os.getenv("CC").split(" ")[1:]))')
_CXX=$(python -c 'import os; print(" ".join(os.getenv("CXX").split(" ")[1:]))')
make clean 
CFLAGS=$_CC CXXFLAGS=$_CXX LDFLAGS="--sysroot=$SDKTARGETSYSROOT" make
