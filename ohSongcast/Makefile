objdir = Build/Obj/Posix
incdir = Build/Include
ohnetdir = ../Upnp/Build/Obj/Posix/Debug
toolsDir = ../Upnp/Build/Posix/Tools
templatesDir = ../Upnp/T4/Templates

# Macros used by Common.mak

ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -g -O0 -Wno-psabi -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))"
objdir = Build/Obj/Posix/
inc_build = Build/Include
includes = -I../Upnp/Build/Include/ -I../Upnp/Build/Include/Cpp/
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

all: $(objdir)/WavSender.$(exeext) 

$(objdir)/WavSender.$(exeext) : Ohm.cpp OhmSender.cpp WavSender/WavSender.cpp
	mkdir -p $(objdir)
	$(compiler)/Ohm.$(objext) -c $(cflags) $(includes) Ohm.cpp
	$(compiler)/OhmSender.$(objext) -c $(cflags) $(includes) OhmSender.cpp
	$(compiler)/WavSender.$(objext) -c $(cflags) $(includes) WavSender/WavSender.cpp
	$(link) $(linkoutput)$(objdir)/WavSender.$(exeext) $(objdir)/WavSender.$(objext) $(ohnetdir)/DvAvOpenhomeOrgSender1.$(objext) $(objdir)/Ohm.$(objext) $(objdir)/OhmSender.$(objext) $(ohnetdir)/$(libprefix)ohNetCore.$(libext) $(ohnetdir)/$(libprefix)TestFramework.$(libext)


