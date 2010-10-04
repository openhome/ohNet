# Makefile for linux
# Could be extended to support Mac in future

# Macros used by Common.mak
ar = ar rc $(objdir)
cflags = -fexceptions -Wall -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -g -O0 -Wno-psabi -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))"
objdir = Build/Obj/Posix/
inc_build = Build/Include
includes = -IBuild/Include/ -IBuild/Include/Cpp/
proxySrcCppCore = ControlPoint/Services/Cpp/Core/
proxySrcC = ControlPoint/Services/C/
proxySrcCppStd = ControlPoint/Services/Cpp/Std/
deviceSrcCppCore = Device/Services/Cpp/Core/
deviceSrcCppStd = Device/Services/Cpp/Std/
deviceSrcC = Device/Services/C/
osdir = Posix
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = gcc -o $(objdir)
linker = g++ -lpthread -o $(objdir)
dllprefix = lib
dllext = so
linker_dll = g++ -lpthread -shared -shared-libgcc -o $(objdir)
linker_dll_service = g++ -lpthread -shared -shared-libgcc $(objdir)libZappUpnp.so -o $(objdir)

# Actual building of code is shared between platforms
include Common.mak

# Following macros must be provided by each file which wraps Common.mak

TestProxyCs: ZappUpnpDll CpUpnpOrgConnectionManager1Dll
	gmcs /nologo /unsafe /t:exe -out:$(objdir)TestProxyCs.exe Public/Cs/CpDevice.cs Public/Cs/CpDeviceUpnp.cs Public/Cs/CpProxy.cs Public/Cs/Zapp.cs Public/Cs/AssemblyInfo.cs ControlPoint/Services/Cs/CpUpnpOrgConnectionManager1.cs  Public/Cs/TestProxy.cs

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
