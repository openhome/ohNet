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
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
linker = ${CROSS_COMPILE}g++ -lpthread -o $(objdir)
dllprefix = lib
dllext = so
linker_dll = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc -o $(objdir)
linker_dll_service = ${CROSS_COMPILE}g++ -lpthread -shared -shared-libgcc $(objdir)libZappUpnp.so -o $(objdir)
csharp = gmcs /nologo
publiccsdir = Public/Cs/
dirsep = /
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
