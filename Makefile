# Makefile for linux
# Could be extended to support Mac in future

ifeq ($(release),1)
debug_specific_cflags = -O2
build_dir = Release
else
debug_specific_cflags = -g -O0 
build_dir = Debug
endif

MACHINE = $(shell uname -s)
ifeq ($(MACHINE), Darwin)
ifeq ($(mac-arm),1)
devroot=/Developer/Platforms/iPhoneOS.platform/Developer
sdkroot=$(devroot)/SDKs/iPhoneOS4.3.sdk
platform_cflags = -I$(sdkroot)/usr/lib/gcc/arm-apple-darwin10/4.2.1/include/ -I$(sdkroot)/usr/include/ -I/usr/bin/arm-apple-darwin10-gcc -miphoneos-version-min=2.2 -pipe -no-cpp-precomp -isysroot $(sdkroot) -DPLATFORM_MACOSX_GNU -I$(sdkroot)/usr/include/c++/4.2.1/armv6-apple-darwin10/ 
objdir = Build/Obj/Mac/arm/$(build_dir)/
platform_linkflags = -L$(sdkroot)/usr/lib/ -arch armv6  -L$(sdkroot)/usr/lib/system
compiler = $(devroot)/usr/bin/llvm-gcc-4.2  -arch armv6 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk -o $(objdir)
# No support for linking Shared Objects for ARM MAC
# link = $(devroot)/usr/bin/llvm-gcc-4.2  -lpthread -Wl $(platform_linkflags)
ar = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/ar rc $(objdir)

else
platform_cflags = -DPLATFORM_MACOSX_GNU -arch i386 -mmacosx-version-min=10.4
platform_linkflags = -arch i386
objdir = Build/Obj/Mac/$(build_dir)/
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags)
ar = ${CROSS_COMPILE}ar rc $(objdir)

endif
else
platform_cflags = -Wno-psabi
platform_linkflags =
objdir = Build/Obj/Posix/$(build_dir)/
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags)
ar = ${CROSS_COMPILE}ar rc $(objdir)

endif

# Macros used by Common.mak
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) -fvisibility=hidden $(platform_cflags)
inc_build = Build/Include
includes = -IBuild/Include/
bundle_build = Build/Bundles
osdir = Posix
objext = o
libprefix = lib
libext = a
exeext = elf


linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread  $(platform_linkflags) -shared -shared-libgcc
link_dll_service = ${CROSS_COMPILE}g++ -lpthread  $(platform_linkflags) -shared -shared-libgcc -lohNet -L$(objdir)
csharp = gmcs /nologo
dirsep = /
prefix = /usr/local
installlibdir = $(prefix)/lib/ohNet
installincludedir = $(prefix)/include/ohNet
installpkgconfdir = $(prefix)/lib/pkgconfig
mkdir = mkdir -p
rmdir = rm -rf
uset4 = no

default : all

# Include the rules to prepare the template engine and the macros to use it.
include T4Linux.mak

# Actual building of code is shared between platforms
include Common.mak

# Include the generated makefiles. Because nmake on Windows requires contortions to
# include such files and handle their non-existance, these includes have to be at
# the platform-specific level.
ifeq ($(uset4),yes)
include Generated/GenerateSourceFiles.mak
endif

include Generated/Proxies.mak
include Generated/Devices.mak

include UserTargets.mak

# Following macros must be provided by each file which wraps Common.mak

make_obj_dir:
	mkdir -p $(objdir)

copy_build_includes:
	if not exist $(inc_build) mkdir $(inc_build)
	if not exist $(inc_build)/OpenHome mkdir $(inc_build)/OpenHome
	if not exist $(inc_build)/OpenHome/Private mkdir $(inc_build)/OpenHome/Private
	if not exist $(inc_build)/OpenHome/Net mkdir $(inc_build)/OpenHome/Net
	if not exist $(inc_build)/OpenHome/Net/Private mkdir $(inc_build)/OpenHome/Net/Private
	if not exist $(inc_build)/OpenHome/Net/Core mkdir $(inc_build)/OpenHome/Net/Core
	if not exist $(inc_build)/OpenHome/Net/C mkdir $(inc_build)/OpenHome/Net/C
	if not exist $(inc_build)/OpenHome/Net/Cpp mkdir $(inc_build)/OpenHome/Net/Cpp
	if not exist $(inc_build)/OpenHome/Net/Private/Js mkdir $(inc_build)/OpenHome/Net/Private/Js
	if not exist $(inc_build)/OpenHome/Net/Private/Js/Tests mkdir $(inc_build)/OpenHome/Net/Private/Js/Tests
	if not exist $(inc_build)/OpenHome/Net/Private/Js/Tests/proxy mkdir $(inc_build)/OpenHome/Net/Private/Js/Tests/proxy
	cp -p OpenHome/*.h $(inc_build)/OpenHome/Private
	cp -p OpenHome/Buffer.inl $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/Buffer.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/Exception.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/Functor*.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/MimeTypes.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/OhNetDefines.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/OsTypes.h $(inc_build)/OpenHome
    mv $(inc_build)/OpenHome/Private/OhNetTypes.h $(inc_build)/OpenHome
	cp -p OpenHome/TestFramework/*.h $(inc_build)/OpenHome/Private
	cp -p OpenHome/Net/*.h $(inc_build)/OpenHome/Net/Private
    mv $(inc_build)/OpenHome/Net/Private/FunctorAsync.h $(inc_build)/OpenHome/Net/Core
    cp -p $(inc_build)/OpenHome/Net/Core/FunctorAsync.h $(inc_build)/OpenHome/Net/Cpp
    mv $(inc_build)/OpenHome/Net/Private/OhNet.h $(inc_build)/OpenHome/Net/Core
    cp -p $(inc_build)/OpenHome/Net/Core/OhNet.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/ControlPoint/AsyncPrivate.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/ControlPoint/CpStack.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/CpDevice.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/CpDeviceDv.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/CpDeviceDv.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/ControlPoint/CpDeviceUpnp.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/ControlPoint/CpTopology.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/FunctorCpDevice.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/FunctorCpDevice.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/ControlPoint/Cpi*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/ControlPoint/FunctorCpiDevice.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/ControlPoint/Topology/*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/ControlPoint/Upnp/*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/DvStack.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvDevice.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvInvocationResponse.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvProvider.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvProvider.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Device/DvResourceWriter.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvResourceWriter.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Device/DvServerUpnp.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/DvServerUpnp.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Device/DviDevice.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/DviServer.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/DviService.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/DviStack.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/DviSubscription.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/FunctorDviInvocation.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/Bonjour/*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/Bonjour/mDNSCore/*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Device/Providers/*.h $(inc_build)/OpenHome/Net/Core
	cp -p OpenHome/Net/Device/Upnp/*.h $(inc_build)/OpenHome/Net/Private
	cp -p OpenHome/Net/Bindings/C/*.h $(inc_build)/OpenHome/Net/C
	cp -p OpenHome/Net/Bindings/C/ControlPoint/*.h $(inc_build)/OpenHome/Net/C
	cp -p OpenHome/Net/Bindings/C/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/C
	cp -p OpenHome/Net/Bindings/C/Device/*.h $(inc_build)/OpenHome/Net/C
	cp -p OpenHome/Net/Bindings/C/Device/Providers/*.h $(inc_build)/OpenHome/Net/C
	cp -p OpenHome/Net/Bindings/Cpp/ControlPoint/*.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Bindings/Cpp/Device/*.h $(inc_build)/OpenHome/Net/Cpp
	cp -p OpenHome/Net/Bindings/Cpp/Device/Providers/*.h $(inc_build)/OpenHome/Net/Cpp
    cp -p -r OpenHome/Net/Bindings/Js/ControlPoint/Tests/*.* $(inc_build)/OpenHome/Net/Private/Js/Tests
    cp -p OpenHome/Net/Bindings/Js/ControlPoint/*.js $(inc_build)/OpenHome/Net/Private/Js/Tests
    cp -p OpenHome/Net/Bindings/Js/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.js $(inc_build)/OpenHome/Net/Private/Js/Tests/proxy
	cp -p Os/*.h $(inc_build)/OpenHome
	cp -p Os/*.inl $(inc_build)/OpenHome

old_copy_build_includes:
	mkdir -p $(inc_build)
	mkdir -p $(inc_build)/C
	mkdir -p $(inc_build)/Cpp
	mkdir -p $(inc_build)/Cpp/Core
	mkdir -p $(inc_build)/Cpp/Std
	rsync -u Api/*.h $(inc_build)
	rsync -u Api/C/*.h $(inc_build)/C
	rsync -u Api/Cpp/*.h $(inc_build)/Cpp
	rsync -u Api/Cpp/*.inl $(inc_build)/Cpp
	rsync -u Api/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync -u Api/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync -u *.h $(inc_build)
	rsync -u Bonjour/*.h $(inc_build)
	rsync -u Bonjour/mDNSCore/*.h $(inc_build)
	rsync -u ControlPoint/*.h $(inc_build)
	rsync -u ControlPoint/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync -u ControlPoint/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync -u ControlPoint/Services/C/*.h $(inc_build)/C
	rsync -u ControlPoint/Dv/*.h $(inc_build)
	rsync -u ControlPoint/Upnp/*.h $(inc_build)
	rsync -u Device/*.h $(inc_build)
	rsync -u Device/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync -u Device/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync -u Device/Services/C/*.h $(inc_build)/C
	rsync -u Device/Upnp/*.h $(inc_build)
	rsync -u Network/*.h $(inc_build)
	rsync -u Service/*.h $(inc_build)
	rsync -u Ssdp/*.h $(inc_build)
	rsync -u Os/*.h $(inc_build)
	rsync -u Os/*.inl $(inc_build)
	rsync -u Public/C/*.h $(inc_build)/C
	rsync -u Public/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync -u Thread/Thread.h $(inc_build)
	rsync -u Utils/*.h $(inc_build)
	rsync -u TestFramework/*.h $(inc_build)

install : install-pkgconf install-libs install-includes

uninstall : uninstall-pkgconf uninstall-libs uninstall-includes

install-pkgconf : tt
	@echo "ERROR: no support for (un)install-pckconf yet"
    #@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

install-libs :
	mkdir -p $(installlibdir)
	rsync -u $(installlibdir) $(objdir)*

install-includes :
	mkdir -p $(installincludedir)
	rsync -ur $(installincludedir) $(inc_build)/*

uninstall-pkgconf :
	@echo "ERROR: no support for (un)install-pckconf yet"
    #@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

uninstall-libs :
	rm -rf $(installlibdir)

uninstall-includes :
	rm -rf $(installincludedir)

docs:
	rm -rf Build/Docs
	mkdir -p Build/Docs
	mkdir -p Build/Docs/C
	doxygen DoxyfileC
	mkdir -p Build/Docs/CppCore
	doxygen DoxyfileCppCore
	mkdir -p Build/Docs/CppStd
	doxygen DoxyfileCppStd
	mkdir -p Build/Docs/Cs
	doxygen DoxyfileCs
	mkdir -p Build/Docs/Js
	perl ./JsDoc/jsdoc.pl -d Build/Docs/Js ControlPoint/Services/Js Public/Js/WebUIsdk

bundle: tt
	mkdir -p $(bundle_build)
ifeq ($(targetplatform),)
	echo Usage: make bundle targetplatform=Linux-x86
else
	python bundle_binaries.py Posix $(targetplatform)
endif

bundle-dev: tt
	mkdir -p $(bundle_build)
ifeq ($(targetplatform),)
	echo Usage: make bundle-dev targetplatform=Linux-x86
else
	python bundle_binaries.py --dev Posix $(targetplatform)
endif
