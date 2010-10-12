# Makefile for linux
# Could be extended to support Mac in future

# Macros used by Common.mak
ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -g -O0 -Wno-psabi -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))"
objdir = Build/Obj/Posix/
inc_build = Build/Include
includes = -IBuild/Include/ -IBuild/Include/Cpp/
proxySrcCppCore = ControlPoint/Services/Cpp/Core/
proxySrcC = ControlPoint/Services/C/
proxySrcCppStd = ControlPoint/Services/Cpp/Std/
proxySrcCs = ControlPoint/Services/Cs/
deviceSrcCppCore = Device/Services/Cpp/Core/
deviceSrcCppStd = Device/Services/Cpp/Std/
deviceSrcC = Device/Services/C/
deviceSrcCs = Device/Services/Cs/
osdir = Posix
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = ${CROSS_COMPILE}gcc -o $(objdir)
linker = ${CROSS_COMPILE}g++ -lpthread -o $(objdir)
dllprefix = lib
dllext = so
linker_dll = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc -o $(objdir)
linker_dll_service = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc $(objdir)libZappUpnp.so -o $(objdir)
csharp = gmcs /nologo
publiccsdir = Public/Cs/
dirsep = /
prefix = /usr/local
installlibdir = $(prefix)/lib/zapp
installincludedir = $(prefix)/include/zapp
installpkgconfdir = $(prefix)/lib/pkgconfig
# Actual building of code is shared between platforms
include Common.mak

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
	cp -u Arch/*.h $(inc_build)
	cp -u Arch/I386/ArchSpecific.h $(inc_build)
	cp -u ControlPoint/*.h $(inc_build)
	cp -u ControlPoint/Upnp/*.h $(inc_build)
	cp -u Device/*.h $(inc_build)
	cp -u Device/Upnp/*.h $(inc_build)
	cp -u Network/*.h $(inc_build)
	cp -u Service/*.h $(inc_build)
	cp -u Ssdp/*.h $(inc_build)
	cp -u Os/*.h $(inc_build)
	cp -u Os/*.inl $(inc_build)
	cp -u Os/C/Os.h $(inc_build)/C
	cp -u Public/C/*.h $(inc_build)/C
	cp -u Thread/Thread.h $(inc_build)
	cp -u Timer/Timer.h $(inc_build)
	cp -u Utils/*.h $(inc_build)
	cp -u TestFramework/*.h $(inc_build)

clean :
	rm -rf $(objdir)
	rm -rf $(inc_build)

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

# We need to run a T4 template to generate our pkg-config file for installing, so
# we pull in T4Linux. We could probably restructure these dependencies to be a bit
# nicer in the future.
include T4Linux.mak
