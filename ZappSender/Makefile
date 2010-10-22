objdir = Build/Obj/Posix
incdir = Build/Include
toolsDir = ../Upnp/Build/Tools
templatesDir = ../Upnp/T4/Templates



# Macros used by Common.mak

ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -g -O0 -Wno-psabi -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))"
includes = -I../Upnp/Build/Include/ -I../Upnp/Build/Include/Cpp/
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

wavplayer :
	mkdir -p $(objdir)
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/WavSender.$(objext) -c $(cflags) $(includes) WavSender.cpp

t4 = $(toolsDir)/TextTransform.exe

gen: DvLinnCoUkSender1.h DvLinnCoUkSender1.cpp

DvLinnCoUkSender1.h : $(templatesDir)/DvUpnpCppCoreHeader.tt Sender1.xml
	$(t4) -o DvLinnCoUkSender1.h $(templatesDir)/DvUpnpCppCoreHeader.tt -a "xml:Sender1.xml" -a domain:linn.co.uk -a type:MultipusSender -a version:1
DvLinnCoUkSender1.cpp : ../Upnp/T4/Templates/DvUpnpCppCoreSource.tt Sender1.xml
	$(t4) -o DvLinnCoUkSender1.cpp $(templatesDir)/DvUpnpCppCoreSource.tt -a "xml:Sender1.xml" -a domain:linn.co.uk -a type:MultipusSender -a version:1
