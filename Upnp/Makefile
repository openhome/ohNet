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
MACHINE = $(shell uname -s)
ifeq ($(MACHINE), Darwin)
platform_cflags = -DPLATFORM_MACOSX_GNU
else
platform_cflags = -Wno-psabi
endif
ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_cflags) -fvisibility=hidden -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))" $(platform_cflags)
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
link_dll_service = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc -lohNet -L$(objdir)
csharp = gmcs /nologo
publiccsdir = Public/Cs/
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
	mkdir -p $(inc_build)/C
	mkdir -p $(inc_build)/Cpp
	mkdir -p $(inc_build)/Cpp/Core
	mkdir -p $(inc_build)/Cpp/Std
	rsync Api/*.h $(inc_build)
	rsync Api/C/*.h $(inc_build)/C
	rsync Api/Cpp/*.h $(inc_build)/Cpp
	rsync Api/Cpp/*.inl $(inc_build)/Cpp
	rsync Api/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync Api/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync *.h $(inc_build)
	rsync Bonjour/*.h $(inc_build)
	rsync Bonjour/mDNSCore/*.h $(inc_build)
	rsync ControlPoint/*.h $(inc_build)
	rsync ControlPoint/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync ControlPoint/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync ControlPoint/Services/C/*.h $(inc_build)/C
	rsync ControlPoint/Dv/*.h $(inc_build)
	rsync ControlPoint/Upnp/*.h $(inc_build)
	rsync Device/*.h $(inc_build)
	rsync Device/Services/Cpp/Core/*.h $(inc_build)/Cpp/Core
	rsync Device/Services/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync Device/Services/C/*.h $(inc_build)/C
	rsync Device/Upnp/*.h $(inc_build)
	rsync Network/*.h $(inc_build)
	rsync Service/*.h $(inc_build)
	rsync Ssdp/*.h $(inc_build)
	rsync Os/*.h $(inc_build)
	rsync Os/*.inl $(inc_build)
	rsync Public/C/*.h $(inc_build)/C
	rsync Public/Cpp/Std/*.h $(inc_build)/Cpp/Std
	rsync Thread/Thread.h $(inc_build)
	rsync Utils/*.h $(inc_build)
	rsync TestFramework/*.h $(inc_build)

install : install-pkgconf install-libs install-includes

uninstall : uninstall-pkgconf uninstall-libs uninstall-includes

install-pkgconf : tt
	@echo "ERROR: no support for (un)install-pckconf yet"
    #@echo "see http://www.mono-project.com/Guidelines:Application_Deployment for an example of how to implement this"

install-libs :
	mkdir -p $(installlibdir)
	rsync $(installlibdir) $(objdir)*

install-includes :
	mkdir -p $(installincludedir)
	rsync -r $(installincludedir) $(inc_build)/*

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
