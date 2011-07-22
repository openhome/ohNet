
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
platform_linkflags = -arch i386 -framework IOKit
platform_include = -I/System/Library/Frameworks/IOKit.framework/Headers/
osdir = Mac
else
platform_cflags = -Wno-psabi
platform_linkflags = 
platform_include = 
osdir = Posix
endif


# Macros used by Common.mak

ar = ${CROSS_COMPILE}ar rc $(objdir)
cflags = -fexceptions -Wall -Werror -pipe -D_GNU_SOURCE -D_REENTRANT -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE $(debug_specific_flags) -fvisibility=hidden -DDllImport="__attribute__ ((visibility(\"default\")))" -DDllExport="__attribute__ ((visibility(\"default\")))" -DDllExportClass="__attribute__ ((visibility(\"default\")))" $(platform_cflags)
ohnetdir = ../Build/Obj/$(osdir)/$(build_dir)/
objdir = Build/Obj/$(osdir)/$(build_dir)/
inc_build = Build/Include/
includes = -I../Build/Include/ $(platform_includes)
objext = o
libprefix = lib
libext = a
exeext = elf
compiler = ${CROSS_COMPILE}gcc -fPIC -o $(objdir)
link = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags)
linkoutput = -o 
dllprefix = lib
dllext = so
link_dll = ${CROSS_COMPILE}g++ -lpthread $(platform_linkflags) -shared -shared-libgcc --whole-archive
csharp = gmcs /nologo
dirsep = /


default : all

# Include rules to build the shared code
include Common.mak

$(objects_songcast) : | make_obj_dir
make_obj_dir :
	mkdir -p $(objdir)

clean :
	rm -rf $(objdir)

all : all_common $(objdir)$(dllprefix)ohSoundcard.$(dllext) $(objdir)TestSoundcard.$(exeext)


ifeq ($(MACHINE), Darwin)
objects_soundcard_os = $(objdir)SoundcardDriver.$(objext)

$(objdir)SoundcardDriver.$(objext) : ohSoundcard/Mac/SoundcardDriver.cpp
	$(compiler)SoundcardDriver.$(objext) -c $(cflags) $(includes) ohSoundcard/Mac/SoundcardDriver.cpp
else
objects_soundcard_os = $(objdir)SoundcardDriver.$(objext)

$(objdir)SoundcardDriver.$(objext) : ohSoundcard/Posix/SoundcardDriver.cpp
	$(compiler)SoundcardDriver.$(objext) -c $(cflags) $(includes) ohSoundcard/Posix/SoundcardDriver.cpp
endif


$(objdir)$(dllprefix)ohSoundcard.$(dllext) : $(objects_songcast) $(objects_soundcard) $(objects_soundcard_os)
	$(link_dll) $(linkoutput)$(objdir)$(dllprefix)ohSoundcard.$(dllext) $(objects_topology) $(objects_songcast) $(objects_soundcard) $(objects_soundcard_os) $(ohnetdir)$(libprefix)ohNetCore.$(libext)


$(objdir)TestSoundcard.$(exeext) : $(objdir)$(dllprefix)ohSoundcard.$(dllext) ohSoundcard/TestSoundcard.cpp
	$(compiler)TestSoundcard.$(objext) -c $(cflags) $(includes) ohSoundcard/TestSoundcard.cpp
	$(link) $(linkoutput)$(objdir)TestSoundcard.$(exeext) $(objdir)TestSoundcard.$(objext) $(objdir)$(dllprefix)ohSoundcard.$(dllext)


