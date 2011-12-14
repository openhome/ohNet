# Makefile for linux
# Could be extended to support Mac in future

rsync ?= yes

ifeq ($(rsync),yes)
cp = rsync -u
else
cp = cp -u
endif

ifeq ($(release),1)
debug_specific_cflags = -O2
build_dir = Release
else
debug_specific_cflags = -g -O0 
build_dir = Debug
endif

MACHINE = $(shell uname -s)
ifeq ($(MACHINE), Darwin)
    linkopts_ohNet =
ifeq ($(mac-arm),1)
	# Darwin, ARM -> iOS
	devroot=/Developer/Platforms/iPhoneOS.platform/Developer
	sdkroot=$(devroot)/SDKs/iPhoneOS4.3.sdk
	platform_cflags = -I$(sdkroot)/usr/lib/gcc/arm-apple-darwin10/4.2.1/include/ -I$(sdkroot)/usr/include/ -I/usr/bin/arm-apple-darwin10-gcc -miphoneos-version-min=2.2 -pipe -no-cpp-precomp -isysroot $(sdkroot) -DPLATFORM_MACOSX_GNU -DPLATFORM_IOS -I$(sdkroot)/usr/include/c++/4.2.1/armv6-apple-darwin10/ 
	# It seems a bit weird that iOS uses a sub-dir of Build/Obj/Mac, is that deliberate? --AW
	osbuilddir = Mac/arm
	objdir = Build/Obj/Mac/arm/$(build_dir)/
	platform_linkflags = -L$(sdkroot)/usr/lib/ -arch armv6  -L$(sdkroot)/usr/lib/system
	compiler = $(devroot)/usr/bin/llvm-gcc-4.2  -arch armv6 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.3.sdk -o $(objdir)
	# No support for linking Shared Objects for ARM MAC
	# link = $(devroot)/usr/bin/llvm-gcc-4.2  -lpthread -Wl $(platform_linkflags)
	ar = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/ar rc $(objdir)

else
	# Darwin, not ARM -> Intel Mac
	platform_cflags = -DPLATFORM_MACOSX_GNU -arch x86_64 -mmacosx-version-min=10.4
	platform_linkflags = -arch x86_64 -framework CoreFoundation -framework SystemConfiguration
	osbuilddir = Mac
	objdir = Build/Obj/Mac/$(build_dir)/
	compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
	link = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags)
	ar = ${CROSS_COMPILE}ar rc $(objdir)

endif
else
	# Not Darwin
	platform ?= Vanilla
	# At present, platform == Vanilla is used for Kirkwood, x86 and x64 Posix builds.

ifeq ($(platform), Core)
	# platform == Core
	freertoslwipdir ?= ${FREERTOSLWIP}
	platform_cflags = -I$(freertoslwipdir)/include/ -I$(freertoslwipdir)/include/FreeRTOS/ -I$(freertoslwipdir)/include/lwip/ -mcpu=403 -g
	platform_linkflags = -B$(freertoslwipdir)/lib/ -specs bsp_specs -mcpu=403
    linkopts_ohNet =
	osbuilddir = Volkano2
	osdir = Volkano2
	endian = BIG
endif

ifeq ($(platform), Vanilla)
	# platform == Vanilla (i.e. Kirkwood, x86 or x64)
	platform_cflags = -Wno-psabi -fPIC
	platform_linkflags = -lpthread
    linkopts_ohNet = -Wl,-soname,libohNet.so
	osbuilddir = Posix
	osdir = Posix
	endian = LITTLE
endif

	# Continuing with the non-Darwin settings...
	objdir = Build/Obj/$(osdir)/$(build_dir)/
	compiler = ${CROSS_COMPILE}gcc -o $(objdir)
	link = ${CROSS_COMPILE}g++ $(platform_linkflags)
	ar = ${CROSS_COMPILE}ar rc $(objdir)

endif

# Macros used by Common.mak
endian ?= LITTLE
cflags_third_party = -fexceptions -Wall -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_$(endian)_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) -fvisibility=hidden $(platform_cflags)
cflags = $(cflags_third_party) -Werror
inc_build = Build/Include
includes = -IBuild/Include/
bundle_build = Build/Bundles
osdir ?= Posix
objext = o
libprefix = lib
libext = a
sharedlibprefix = lib
sharedlibext = so
exeext = elf


linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread  $(platform_linkflags) -shared -shared-libgcc
link_dll_service = ${CROSS_COMPILE}g++ -lpthread  $(platform_linkflags) -shared -shared-libgcc -lohNet -L$(objdir)
csharp = dmcs /nologo
publicjavadir = OpenHome/Net/Bindings/Java/
includes_jni = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
link_jvm = $(JAVA_HOME)/jre/lib/i386/server/libjvm.so
java_cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) $(platform_cflags)
javac = $(JAVA_HOME)/bin/javac
jar = $(JAVA_HOME)/bin/jar
jarflags = cf
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
	mkdir -p $(inc_build)
	mkdir -p $(inc_build)/OpenHome
	mkdir -p $(inc_build)/OpenHome/Private
	mkdir -p $(inc_build)/OpenHome/Net
	mkdir -p $(inc_build)/OpenHome/Net/Private
	mkdir -p $(inc_build)/OpenHome/Net/Core
	mkdir -p $(inc_build)/OpenHome/Net/C
	mkdir -p $(inc_build)/OpenHome/Net/Cpp
	mkdir -p $(inc_build)/OpenHome/Net/Private/Js
	mkdir -p $(inc_build)/OpenHome/Net/Private/Js/Tests
	mkdir -p $(inc_build)/OpenHome/Net/Private/Js/Tests/proxy
	$(cp) OpenHome/*.h $(inc_build)/OpenHome/Private
	$(cp) OpenHome/Buffer.inl $(inc_build)/OpenHome
	rm $(inc_build)/OpenHome/Private/Buffer.h
	rm $(inc_build)/OpenHome/Private/Exception.h
	rm $(inc_build)/OpenHome/Private/Functor*.h
	rm $(inc_build)/OpenHome/Private/MimeTypes.h
	rm $(inc_build)/OpenHome/Private/OhNetDefines.h
	rm $(inc_build)/OpenHome/Private/OsTypes.h
	rm $(inc_build)/OpenHome/Private/OhNetTypes.h
	$(cp) OpenHome/Buffer.h $(inc_build)/OpenHome
	$(cp) OpenHome/Exception.h $(inc_build)/OpenHome
	$(cp) OpenHome/Functor*.h $(inc_build)/OpenHome
	$(cp) OpenHome/MimeTypes.h $(inc_build)/OpenHome
	$(cp) OpenHome/OhNetDefines.h $(inc_build)/OpenHome
	$(cp) OpenHome/OsTypes.h $(inc_build)/OpenHome
	$(cp) OpenHome/OhNetTypes.h $(inc_build)/OpenHome
	$(cp) OpenHome/TestFramework/*.h $(inc_build)/OpenHome/Private
	$(cp) OpenHome/Net/*.h $(inc_build)/OpenHome/Net/Private
	rm $(inc_build)/OpenHome/Net/Private/FunctorAsync.h
	rm $(inc_build)/OpenHome/Net/Private/OhNet.h
	$(cp) OpenHome/Net/FunctorAsync.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/FunctorAsync.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/OhNet.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/OhNet.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/ControlPoint/AsyncPrivate.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/CpStack.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDevice.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDeviceDv.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDeviceUpnp.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/ControlPoint/CpTopology.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/FunctorCpDevice.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/Cpi*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/FunctorCpiDevice.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/Topology/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/Upnp/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DvStack.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvDevice.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvInvocationResponse.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvProvider.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvProvider.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Device/DvResourceWriter.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvResourceWriter.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Device/DvServerUpnp.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/DvServerUpnp.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Device/DviDevice.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DviServer.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DviService.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DviStack.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DviSubscription.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/FunctorDviInvocation.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/Bonjour/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/Bonjour/mDNSCore/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/Providers/*.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/Device/Upnp/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Bindings/C/*.h $(inc_build)/OpenHome/Net/C
	$(cp) OpenHome/Net/Bindings/C/ControlPoint/*.h $(inc_build)/OpenHome/Net/C
	$(cp) OpenHome/Net/Bindings/C/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/C
	$(cp) OpenHome/Net/Bindings/C/Device/*.h $(inc_build)/OpenHome/Net/C
	$(cp) OpenHome/Net/Bindings/C/Device/Providers/*.h $(inc_build)/OpenHome/Net/C
	$(cp) OpenHome/Net/Bindings/Cpp/ControlPoint/*.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Bindings/Cpp/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Bindings/Cpp/Device/*.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/Bindings/Cpp/Device/Providers/*.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) -r OpenHome/Net/Bindings/Js/ControlPoint/Tests/*.* $(inc_build)/OpenHome/Net/Private/Js/Tests
	$(cp) OpenHome/Net/Bindings/Js/ControlPoint/*.js $(inc_build)/OpenHome/Net/Private/Js/Tests
	$(cp) OpenHome/Net/Bindings/Js/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.js $(inc_build)/OpenHome/Net/Private/Js/Tests/proxy
	$(cp) Os/*.h $(inc_build)/OpenHome
	$(cp) Os/*.inl $(inc_build)/OpenHome

install : install-pkgconf install-libs install-includes

uninstall : uninstall-pkgconf uninstall-libs uninstall-includes

install-pkgconf : tt
	@echo "ERROR: no support for (un)install-pckconf yet"
    #@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

install-libs :
	mkdir -p $(installlibdir)
	$(cp) $(objdir)* $(installlibdir) 

install-includes :
	mkdir -p $(installincludedir)
	$(cp) -r $(inc_build)/* $(installincludedir) 

uninstall-pkgconf :
	@echo "ERROR: no support for (un)install-pckconf yet"
    #@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

uninstall-libs :
	rm -rf $(installlibdir)

uninstall-includes :
	rm -rf $(installincludedir)

java_packages = ohnet \
				openhome.net.controlpoint \
				openhome.net.controlpoint.proxies \
				openhome.net.core \
				org.openhome.net.device \
				org.openhome.net.test \

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
	mkdir -p Build/Docs/Java
	doxygen DoxyfileJava
	mkdir -p Build/Docs/Js
	perl ./JsDoc/jsdoc.pl -d Build/Docs/Js OpenHome/Net/Bindings/Js/ControlPoint OpenHome/Net/Bindings/Js/ControlPoint/Proxies

bundle: tt
	mkdir -p $(bundle_build)
ifeq ($(targetplatform),)
	echo Usage: make bundle targetplatform=Linux-x86
else
	python bundle_binaries.py $(osbuilddir) $(targetplatform) ${releasetype}
endif

bundle-dev: tt
	mkdir -p $(bundle_build)
ifeq ($(targetplatform),)
	echo Usage: make bundle-dev targetplatform=Linux-x86
else
	python bundle_binaries.py --dev $(osbuilddir) $(targetplatform) ${releasetype}
endif
