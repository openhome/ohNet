#!/bin/sh
# optionally takes path to yocto sdk environment file
# get this manually from https://s3-eu-west-1.amazonaws.com/linn-artifacts-private/yocto_core4_sdk/0.1.35/linn-fb-glibc-x86_64-linn-image-core-cortexa9t2hf-neon-linn-imx6dl-toolchain-5.15-kirkstone.sh (VPN required)
# if DS (or another waf-based repo) is also checked out and set up, this could be ../ds/dependencies/Linux-armhf/yocto_core4_sdk/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi
if [ -z $1 ]; then
    YOCTO_SDK_ENV=/opt/linn-wayland/5.15-kirkstone/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi  
else
    YOCTO_SDK_ENV=$1
fi
echo "sourcing $YOCTO_SDK_ENV"
source $YOCTO_SDK_ENV
# Yocto env appends essential build flags to CC/CXX environment variables;
# our makefiles doesn't use CC to determine compiler since we do some more complex stuff to deal with building under other OSes.
# just strip out these flags and place in the CFLAGS variable since this is still used
_CC=$(python -c 'import os; print(" ".join(os.getenv("CC").split(" ")[1:]))')
_CXX=$(python -c 'import os; print(" ".join(os.getenv("CXX").split(" ")[1:]))')
make clean 
CFLAGS=$_CC CXXFLAGS=$_CXX LDFLAGS="--sysroot=$SDKTARGETSYSROOT" openhome_system="linux" openhome_architecture="armhf" openhome_distro="kirkstone" make uset4=yes
