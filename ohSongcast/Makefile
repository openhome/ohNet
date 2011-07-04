
# Makefile for linux and mac


ifeq ($(release), 1)
debug_specific_flags = -O2
build_dir = Release
else
debug_specific_flags = -g -O0
build_dir = Debug
endif


MACHINE = $(shell uname -s)
ifeq ($(MACHINE), Darwin)
platform_cflags = -DPLATFORM_MACOSX_GNU -arch i386 -mmacosx-version-min=10.4
platform_linkflags = -arch i386
objdir = Build/Obj/Mac/$(build_dir)/
ohnetdir = ../Upnp/Build/Obj/Mac/$(build_dir)/
else
platform_cflags = -Wno-psabi
platform_linkflags = 
objdir = Build/Obj/Posix/$(build_dir)/
ohnetdir = ../Upnp/Build/Obj/Posix/$(build_dir)/
endif


# Macros used by Common.mak

ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_flags) -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))" $(platform_cflags)
inc_build = Build/Include/
includes = -I../Upnp/Build/Include/ -I../Upnp/Build/Include/Cpp/
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags)
linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags) -shared -shared-libgcc
csharp = gmcs /nologo
dirsep = /


default : all

# Include rules to build the shared code
include Common.mak

# Rules required when Common.mak is included
make_obj_dir :
	mkdir -p $(objdir)

clean :
	rm -rf $(objdir)

all : all_common


