#Makefile for linux
# Could be extended to support Mac in future

rsync ?= yes

ifeq ($(rsync),yes)
cp = rsync -u
else
cp = cp -u
endif

ifeq ($(debug),1)
debug_specific_cflags = -g -O0
debug_csharp = /define:DEBUG /debug+
build_dir = Debug
openhome_configuration = Debug
else
debug_specific_cflags = -g -O2
debug_csharp = /optimize+
build_dir = Release
openhome_configuration = Release
endif



# Figure out platform, openhome_system and openhome_architecture

gcc_machine = $(shell ${CROSS_COMPILE}gcc -dumpmachine)
MACHINE = $(shell uname -s)

$(info CROSS_COMPILE: ${CROSS_COMPILE})
$(info Machine reported by compiler is: ${gcc_machine})
$(info Machine reported by uname is: ${MACHINE})

ifeq ($(MACHINE),Darwin)
  ifeq ($(mac-arm),1)
    platform = iOS
    detected_openhome_system = iOs
    detected_openhome_architecture = armv7
  else
    platform = IntelMac
    detected_openhome_system = Mac
    ifeq ($(mac-64),1)
      detected_openhome_architecture = x64
    else
      detected_openhome_architecture = x86
    endif
  endif
else
  # At present, platform == Vanilla is used for Kirkwood, x86 and x64 Posix builds.
  platform ?= Vanilla

    ifneq (,$(findstring linux,$(gcc_machine)))
      detected_openhome_system = Linux
    endif
    ifeq ($(gcc_machine),arm-none-linux-gnueabi)
      detected_openhome_architecture = armel
    endif
    ifeq ($(gcc_machine),arm-linux-gnueabi)
      detected_openhome_architecture = armel
    endif
    ifeq ($(gcc_machine),arm-linux-gnueabihf)
      detected_openhome_architecture = armhf
    endif
    ifneq (,$(findstring i686,$(gcc_machine)))
      detected_openhome_architecture = x86
    endif
    ifneq (,$(findstring i586,$(gcc_machine)))
      detected_openhome_architecture = x86
    endif
    ifneq (,$(findstring i486,$(gcc_machine)))
      detected_openhome_architecture = x86
    endif
    ifneq (,$(findstring i386,$(gcc_machine)))
      detected_openhome_architecture = x86
    endif
    ifneq (,$(findstring amd64,$(gcc_machine)))
      detected_openhome_architecture = x64
    endif
    ifneq (,$(findstring x86_64,$(gcc_machine)))
      detected_openhome_architecture = x64
    endif


endif

detected_openhome_system ?= Unknown
detected_openhome_architecture ?= Unknown

ifneq (${openhome_system},)
  ifneq (${openhome_system},${detected_openhome_system})
    $(warning Detected compiler is for system ${detected_openhome_system} but expected ${openhome_system}. Build will probably fail.)
  endif
endif

ifneq (${openhome_architecture},)
  ifneq (${openhome_architecture},${detected_openhome_architecture})
    $(warning Detected compiler is for architecture ${detected_openhome_architecture} but expected ${openhome_architecture}. Build will probably fail.)
  endif
endif

openhome_system = ${detected_openhome_system}
openhome_architecture = ${detected_openhome_architecture}

$(info Building for system ${openhome_system} and architecture ${openhome_architecture})


ifeq ($(platform),iOS)
	linkopts_ohNet =
	devroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer
	sdkroot=$(devroot)/SDKs/iPhoneOS5.1.sdk
	platform_cflags = -I$(sdkroot)/usr/lib/gcc/arm-apple-darwin10/4.2.1/include/ -I$(sdkroot)/usr/include/ -I/usr/bin/arm-apple-darwin10-gcc -miphoneos-version-min=2.2 -pipe -no-cpp-precomp -isysroot $(sdkroot) -DPLATFORM_MACOSX_GNU -DPLATFORM_IOS -I$(sdkroot)/usr/include/c++/4.2.1/armv7-apple-darwin10/ 
	# TODO: Support i386 (x86) for simulator and armv6 for old devices
	osbuilddir = iOs-armv7
	objdir = Build/Obj/$(osbuilddir)/$(build_dir)/
	platform_linkflags = -L$(sdkroot)/usr/lib/ -arch armv7  -L$(sdkroot)/usr/lib/system
	compiler = $(devroot)/usr/bin/llvm-gcc-4.2  -arch armv7 -isysroot $(sdkroot) -o $(objdir)
	# No support for linking Shared Objects for ARM MAC
	# link = $(devroot)/usr/bin/llvm-gcc-4.2  -pthread -Wl $(platform_linkflags)
	ar = $(devroot)/usr/bin/ar rc $(objdir)
	csharpdefines = /define:IOS /r:monotouch.dll
	no_shared_objects = yes
	openhome_system = iOs
	openhome_architecture = armv7
endif

ifeq ($(platform),IntelMac)
	# Darwin, not ARM -> Intel Mac
	platform ?= IntelMac
	linkopts_ohNet = -Wl,-install_name,@loader_path/libohNet.dylib
	ifeq ($(mac-64),1)
		platform_cflags = -DPLATFORM_MACOSX_GNU -arch x86_64 -mmacosx-version-min=10.4
		platform_linkflags = -arch x86_64 -framework CoreFoundation -framework SystemConfiguration
		osbuilddir = Mac-x64
		openhome_architecture = x64
	else
		platform_cflags = -DPLATFORM_MACOSX_GNU -m32 -mmacosx-version-min=10.4
		platform_linkflags = -m32 -framework CoreFoundation -framework SystemConfiguration		
		osbuilddir = Mac-x86
		openhome_architecture = x86
	endif

	objdir = Build/Obj/$(osbuilddir)/$(build_dir)/
	compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
	link = ${CROSS_COMPILE}g++ -pthread $(platform_linkflags)
	ar = ${CROSS_COMPILE}ar rc $(objdir)
	openhome_system = Mac
endif

ifeq ($(platform), Core-ppc32)
    # platform == Core1
    openhome_system = Core
    openhome_architecture = ppc32
    endian = BIG
    platform_cflags = -mcpu=403
    platform_linkflags = -mcpu=403 ${CROSS_LINKFLAGS}
    linkopts_ohNet =
    osdir = Core
    osbuilddir = Core-ppc32
    objdir = Build/Obj/$(osbuilddir)/$(build_dir)/
    native_only = yes
    compiler = ${CROSS_COMPILE}gcc -o $(objdir)
    link = ${CROSS_COMPILE}g++ $(platform_linkflags)
    ar = ${CROSS_COMPILE}ar rc $(objdir)
endif

ifeq ($(platform), Core-armv6)
    # platform == Core2
    openhome_system = Core
    openhome_architecture = armv6
    endian = LITTLE
    platform_cflags = -mcpu=arm926ej-s -Wno-psabi
    platform_linkflags = -mcpu=arm926ej-s ${CROSS_LINKFLAGS}
    linkopts_ohNet =
    osdir = Core
    osbuilddir = Core-armv6
    objdir = Build/Obj/$(osbuilddir)/$(build_dir)/
    native_only = yes
    compiler = ${CROSS_COMPILE}gcc -o $(objdir)
    link = ${CROSS_COMPILE}g++ $(platform_linkflags)
    ar = ${CROSS_COMPILE}ar rc $(objdir)
endif


ifneq (,$(findstring $(platform),Vanilla))
  ifeq ($(gcc4_1), yes)
    version_specific_cflags = ${CROSS_COMPILE_CFLAGS}
    version_specific_cflags_third_party = -Wno-non-virtual-dtor
    version_specific_java_cflags = -Wstrict-aliasing=0
  else
    version_specific_cflags = -Wno-psabi ${CROSS_COMPILE_CFLAGS}
    version_specific_cflags_third_party =
    version_specific_java_cflags =
  endif

  version_specific_linkflags = ${CROSS_COMPILE_LINKFLAGS}
  version_specific_library_path = ${CROSS_COMPILE_LIBRARY_PATH}
  version_specific_includes = ${CROSS_COMPILE_INCLUDES}

  # Continuing with the non-Darwin settings...
  objdir = Build/Obj/$(osdir)/$(build_dir)/
  compiler = ${CROSS_COMPILE}gcc -o $(objdir)
  link = $(version_specific_library_path) ${CROSS_COMPILE}g++ $(platform_linkflags)
  ar = $(version_specific_library_path) ${CROSS_COMPILE}ar rc $(objdir)
endif

ifeq ($(platform), Vanilla)
	# platform == Vanilla (i.e. Kirkwood, x86 or x64)
	platform_cflags = $(version_specific_cflags) -fPIC
	platform_linkflags = $(version_specific_linkflags) -pthread
        linkopts_ohNet = -Wl,-soname,libohNet.so
	osbuilddir = Posix
	osdir = Posix
	endian ?= LITTLE
	openhome_system = Linux
endif

# Macros used by Common.mak
native_only ?= no
no_shared_objects ?= no
endian ?= LITTLE
cflags_base = -fexceptions -Wall $(version_specific_cflags_third_party) -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_$(endian)_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) -fvisibility=hidden $(platform_cflags)
cflags_third_party = $(cflags_base) -Wno-int-to-pointer-cast
cflags = $(cflags_base) -Werror
inc_build = Build/Include
includes = -IBuild/Include/ $(version_specific_includes)
bundle_build = Build/Bundles
osdir ?= Posix
objext = o
libprefix = lib
libext = a
sharedlibprefix = lib
ifeq ($(MACHINE), Darwin)
	sharedlibext = dylib
	dllext = dylib
else
	sharedlibext = so
	dllext = so
endif
exeext = elf
linkoutput = -o 
dllprefix = lib
link_dll = $(version_specific_library_path) ${CROSS_COMPILE}g++ -pthread  $(platform_linkflags) -shared -shared-libgcc
link_dll_service = $(version_specific_library_path) ${CROSS_COMPILE}g++ -pthread  $(platform_linkflags) -shared -shared-libgcc -lohNet -L$(objdir)
ifeq ($(platform), iOS)
	csharp = /Developer/MonoTouch/usr/bin/smcs /nologo $(debug_csharp)
else
	csharp = dmcs /nologo $(debug_csharp)
endif
csharpdefines ?=
publicjavadir = OpenHome/Net/Bindings/Java/

ifeq ($(platform), IntelMac)
	includes_jni = -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/include/malloc
	link_jvm = /System/Library/Frameworks/JavaVM.framework/JavaVM
	javac = /usr/bin/javac
	jar = /usr/bin/jar
else
	includes_jni = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
	libjvm_dir ?= $(JAVA_HOME)/jre/lib/i386/server
	link_jvm = $(libjvm_dir)/libjvm.so
	javac = $(JAVA_HOME)/bin/javac
	jar = $(JAVA_HOME)/bin/jar
endif

java_cflags = -fexceptions -Wall $(version_specific_java_cflags) -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_$(endian)_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) $(platform_cflags)
jarflags = cf
dirsep = /
prefix = /usr/local
installlibdir = $(prefix)/lib/ohNet
installincludedir = $(prefix)/include/ohNet
installpkgconfdir = $(prefix)/lib/pkgconfig
mkdir = mkdir -p
rmdir = rm -rf
uset4 = no

ifeq ($(native_only), yes)
build_targets = $(native_targets)
else
ifeq ($(no_shared_objects), yes)
build_targets = $(native_targets) ohNet.net.dll
else
build_targets = $(all_targets)
endif
endif

default : all


ifeq (,$(findstring clean,$(MAKECMDGOALS)))
# Include the rules to prepare the template engine and the macros to use it.
ifeq ($(uset4), yes)
include T4Linux.mak
endif

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

endif
include UserTargets.mak

# Following macros must be provided by each file which wraps Common.mak

make_obj_dir:
	$(mkdir) $(objdir)

copy_build_includes:
	$(mkdir) $(inc_build)
	$(mkdir) $(inc_build)/OpenHome
	$(mkdir) $(inc_build)/OpenHome/Private
	$(mkdir) $(inc_build)/OpenHome/Net
	$(mkdir) $(inc_build)/OpenHome/Net/Private
	$(mkdir) $(inc_build)/OpenHome/Net/Core
	$(mkdir) $(inc_build)/OpenHome/Net/C
	$(mkdir) $(inc_build)/OpenHome/Net/Cpp
	$(mkdir) $(inc_build)/OpenHome/Net/Private/Js
	$(mkdir) $(inc_build)/OpenHome/Net/Private/Js/Tests
	$(mkdir) $(inc_build)/OpenHome/Net/Private/Js/Tests/lib
	$(mkdir) $(inc_build)/OpenHome/Net/Private/Js/Tests/proxies
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
	$(cp) OpenHome/Net/Shell/*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/AsyncPrivate.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/CpStack.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDevice.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDeviceDv.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpDeviceUpnp.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/CpProxy.h $(inc_build)/OpenHome/Net/Cpp
	$(cp) OpenHome/Net/ControlPoint/FunctorCpDevice.h $(inc_build)/OpenHome/Net/Core
	$(cp) OpenHome/Net/ControlPoint/Cpi*.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/FunctorCpiDevice.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/Dv/CpiDeviceDv.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/ControlPoint/Proxies/*.h $(inc_build)/OpenHome/Net/Core
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
	$(cp) OpenHome/Net/Device/DviPropertyUpdateCollection.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/FunctorDviInvocation.h $(inc_build)/OpenHome/Net/Private
	$(cp) OpenHome/Net/Device/DviProviderSubscriptionLongPoll.h $(inc_build)/OpenHome/Net/Private
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
	$(cp) OpenHome/Net/Bindings/Js/ControlPoint/lib/*.js $(inc_build)/OpenHome/Net/Private/Js/Tests/lib
	$(cp) OpenHome/Net/Bindings/Js/ControlPoint/Proxies/CpOpenhomeOrgTestBasic1.js $(inc_build)/OpenHome/Net/Private/Js/Tests/proxies
	$(cp) OpenHome/Net/Bindings/Js/ControlPoint/Proxies/CpOpenhomeOrgSubscriptionLongPoll1.js $(inc_build)/OpenHome/Net/Private/Js/Tests/proxies
	$(cp) Os/*.h $(inc_build)/OpenHome
	$(cp) Os/*.inl $(inc_build)/OpenHome

install : install-pkgconf install-libs install-includes

uninstall : uninstall-pkgconf uninstall-libs uninstall-includes

install-pkgconf : tt
	@echo "ERROR: no support for (un)install-pckconf yet"
	#@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

install-libs :
	$(mkdir) $(installlibdir)
	$(cp) $(objdir)* $(installlibdir) 

install-includes :
	$(mkdir) $(installincludedir)
	$(cp) -r $(inc_build)/* $(installincludedir) 

uninstall-pkgconf :
	@echo "ERROR: no support for (un)install-pckconf yet"
	#@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

uninstall-libs :
	$(rmdir) $(installlibdir)

uninstall-includes :
	$(rmdir) $(installincludedir)

java_packages = ohnet \
				openhome.net.controlpoint \
				openhome.net.controlpoint.proxies \
				openhome.net.core \
				org.openhome.net.device \
				org.openhome.net.test \

docs:
	rm -rf Build/Docs
	$(mkdir) Build/Docs
	$(mkdir) Build/Docs/C
	doxygen DoxyfileC
	$(mkdir) Build/Docs/CppCore
	doxygen DoxyfileCppCore
	$(mkdir) Build/Docs/CppStd
	doxygen DoxyfileCppStd
	$(mkdir) Build/Docs/Cs
	doxygen DoxyfileCs
	$(mkdir) Build/Docs/Java
	doxygen DoxyfileJava
	$(mkdir) Build/Docs/Js
	perl ./JsDoc/jsdoc.pl -d Build/Docs/Js OpenHome/Net/Bindings/Js/ControlPoint OpenHome/Net/Bindings/Js/ControlPoint/Proxies

bundle-after-build: $(build_targets)
	$(mkdir) $(bundle_build)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration) --managed

bundle:
	$(mkdir) $(bundle_build)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration)
	python bundle_binaries.py --system $(openhome_system) --architecture $(openhome_architecture) --configuration $(openhome_configuration) --managed

ifeq ($(platform),iOS)
ohNet.net.dll :  $(objdir)ohNet.net.dll
else
ohNet.net.dll :  $(objdir)ohNet.net.dll ohNetDll
endif
