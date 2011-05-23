# Makefile for linux
# Could be extended to support Mac in future

ifeq ($(release),1)
debug_specific_cflags = -O2
build_dir = Release
else
debug_specific_cflags = -g -O0
build_dir = Debug
endif

# Macros used by Common.mak
ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) -Wno-psabi -fvisibility=hidden -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))"
objdir = Build/Obj/Posix/$(build_dir)/
inc_build = Build/Include
includes = -IBuild/Include/ -IBuild/Include/Cpp/
bundle_build = Build/Bundles
osdir = Posix
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread
linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc
link_dll_service = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc -lZappUpnp -L$(objdir)
csharp = gmcs /nologo
publiccsdir = Public/Cs/
dirsep = /
prefix = /usr/local
installlibdir = $(prefix)/lib/zapp
installincludedir = $(prefix)/include/zapp
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
	mkdir -p $(inc_build)/C
	mkdir -p $(inc_build)/Cpp
	mkdir -p $(inc_build)/Cpp/Core
	mkdir -p $(inc_build)/Cpp/Std
	cp -u Api/*.h $(inc_build)
	cp -u Api/C/*.h $(inc_build)/C
	cp -u Api/Cpp/*.h $(inc_build)/Cpp
	cp -u Api/Cpp/*.inl $(inc_build)/Cpp
	cp -u Api/Cpp/Core/*.h $(inc_build)/Cpp/Core
	cp -u Api/Cpp/Std/*.h $(inc_build)/Cpp/Std
	cp -u *.h $(inc_build)
	cp -u Bonjour/*.h $(inc_build)
	cp -u Bonjour/mDNSCore/*.h $(inc_build)
	cp -u ControlPoint/*.h $(inc_build)
	cp -u ControlPoint/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	cp -u ControlPoint/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	cp -u ControlPoint/Services/C/*.h $(inc_build)/C
	cp -u ControlPoint/Dv/*.h $(inc_build)
	cp -u ControlPoint/Upnp/*.h $(inc_build)
	cp -u Device/*.h $(inc_build)
	cp -u Device/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	cp -u Device/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	cp -u Device/Services/C/*.h $(inc_build)/C
	cp -u Device/Upnp/*.h $(inc_build)
	cp -u Network/*.h $(inc_build)
	cp -u Service/*.h $(inc_build)
	cp -u Ssdp/*.h $(inc_build)
	cp -u Os/*.h $(inc_build)
	cp -u Os/*.inl $(inc_build)
	cp -u Public/C/*.h $(inc_build)/C
	cp -u Public/Cpp/Std/*.h $(inc_build)/Cpp/Std
	cp -u Thread/Thread.h $(inc_build)
	cp -u Utils/*.h $(inc_build)
	cp -u TestFramework/*.h $(inc_build)

install : install-pkgconf install-libs install-includes

uninstall : uninstall-pkgconf uninstall-libs uninstall-includes

install-pkgconf : tt
	mkdir -p $(installpkgconfdir)
	$(t4) -o $(installpkgconfdir)/managed.zapp.pc T4/Templates/managed.zapp.pc.tt -a xml:Service/Services.xml
	#TODO: Install a pkg-config file for the native interface.

install-libs :
	mkdir -p $(installlibdir)
	cp -ut $(installlibdir) $(objdir)* 

install-includes :
	mkdir -p $(installincludedir)
	cp -urt $(installincludedir) $(inc_build)/*

uninstall-pkgconf :
	rm -f $(installpkgconfdir)/managed.zapp.pc

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
	perl ./JsDoc/jsdoc.pl -d Build/Docs/Js ControlPoint/Services/Js

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
