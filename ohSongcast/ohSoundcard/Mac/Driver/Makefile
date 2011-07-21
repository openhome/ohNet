

ifeq ($(release), 1)
debug_specific_flags = -O2
build_dir = Release
else
debug_specific_flags = -g -O0
build_dir = Debug
endif


objdir = Build/Obj/Mac/$(build_dir)/
compiler = gcc -c -x c++ -arch i386 -pipe -nostdinc -fno-builtin -Wall -fno-exceptions -fno-rtti -fcheck-new -fasm-blocks -force_cpusubtype_ALL -msoft-float $(debug_specific_flags) -fno-common -mkernel -finline -fno-keep-inline-functions -fapple-kext -mmacosx-version-min=10.6 -gdwarf-2 -I/System/Library/Frameworks/Kernel.framework/Headers -o $(objdir)

link = g++ -arch i386 -mmacosx-version-min=10.6 -lcpp_kext -Xlinker -kext -nostdlib -lkmodc++ -lkmod -lcc_kext
linkoutput = -o 


default : kextexe infoplist

headers = AudioDevice.h AudioDeviceInterface.h AudioEngine.h AudioUserClient.h
objects = $(objdir)AudioDevice.o $(objdir)AudioEngine.o $(objdir)AudioUserClient.o

$(objdir)AudioDevice.o : AudioDevice.cpp $(headers)
	$(compiler)AudioDevice.o AudioDevice.cpp
$(objdir)AudioEngine.o : AudioEngine.cpp $(headers)
	$(compiler)AudioEngine.o AudioEngine.cpp
$(objdir)AudioUserClient.o : AudioUserClient.cpp $(headers)
	$(compiler)AudioUserClient.o AudioUserClient.cpp


kextfolders :
	mkdir -p $(objdir)ohSoundcard.kext
	mkdir -p $(objdir)ohSoundcard.kext/Contents
	mkdir -p $(objdir)ohSoundcard.kext/Contents/MacOS


infoplist : $(objdir)ohSoundcard.kext/Contents/Info.plist
$(objdir)ohSoundcard.kext/Contents/Info.plist: Info.plist kextfolders
	cp Info.plist $(objdir)ohSoundcard.kext/Contents/Info.plist


kextexe : $(objdir)ohSoundcard.kext/Contents/MacOS/ohSoundcard
$(objdir)ohSoundcard.kext/Contents/MacOS/ohSoundcard : $(objects) kextfolders
	$(link) $(objects) $(linkoutput)$(objdir)ohSoundcard.kext/Contents/MacOS/ohSoundcard



