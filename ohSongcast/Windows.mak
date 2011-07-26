# Makefile for Windows
#

!if "$(release)"=="1"
link_flag_debug = 
debug_specific_cflags = /MT /Ox
build_dir = Release
!else
link_flag_debug = /debug
debug_specific_cflags = /MTd /Zi /Od /RTC1
build_dir = Debug
!endif

# Macros used by Common.mak

ar = lib /nologo /out:$(objdir)
cflags = $(debug_specific_cflags) /W4 /WX /EHsc /FR$(objdir) -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS 
ohnetdir = ..\Build\Obj\Windows\$(build_dir)^\
objdirbare = Build\Obj\Windows\$(build_dir)
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -I..\Build\Include
bundle_build = Build\Bundles
osdir = Windows
objext = obj
libprefix = lib
libext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
link = link /nologo $(link_flag_debug) /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib /incremental:no
linkoutput = /out:
dllprefix =
dllext = dll
link_dll = link /nologo $(link_flag_debug) /map Ws2_32.lib Iphlpapi.lib /dll
link_dll_service = link /nologo $(link_flag_debug)  /map $(objdir)ohNet.lib Ws2_32.lib Iphlpapi.lib /dll
csplatform = x86
csharp = csc /nologo /platform:$(csplatform)
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\ohNet
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
uset4 = no


all: $(objdir)$(dllprefix)ohSoundcard.$(dllext) $(objdir)TestSoundcard.$(exeext) $(objdir)TestSoundcardCs.$(exeext) all_common


# Include rules to build platform independent code
include Common.mak

$(objects_songcast) : make_obj_dir

make_obj_dir : $(objdirbare)

$(objdirbare) :
	if not exist $(objdirbare) mkdir $(objdirbare)

clean:
	del /S /Q $(objdirbare)


$(objdir)$(dllprefix)ohSoundcard.$(dllext) : $(objects_songcast) $(objects_soundcard) ohSoundcard\Windows\SoundcardDriver.cpp
	$(compiler)SoundcardDriver.$(objext) -c $(cflags) $(includes) ohSoundcard\Windows\SoundcardDriver.cpp
	$(link_dll) $(linkoutput)$(objdir)$(dllprefix)ohSoundcard.$(dllext) $(ohnetdir)$(libprefix)ohNetCore.lib $(objects_topology) $(objects_songcast) $(objects_soundcard) $(objdir)SoundcardDriver.$(objext) kernel32.lib setupapi.lib shell32.lib

$(objdir)$(dllprefix)ohSoundcard.net.$(dllext) : $(objdir)$(dllprefix)ohSoundcard.$(dllext) ohSoundcard\Windows\Soundcard.cs
	$(csharp) /unsafe /t:library \
		/out:$(objdir)$(dllprefix)ohSoundcard.net.$(dllext) \
		ohSoundcard\Windows\Soundcard.cs

$(objdir)TestSoundcardCs.$(exeext) : $(objdir)$(dllprefix)ohSoundcard.net.$(dllext) ohSoundcard\Windows\TestSoundcardCs.cs
	$(csharp) /target:exe /debug+ \
		/out:$(objdir)TestSoundcardCs.$(exeext) \
		/reference:System.dll \
		/reference:System.Net.dll \
		/reference:$(objdir)$(dllprefix)ohSoundcard.net.$(dllext)  \
		ohSoundcard\Windows\TestSoundcardCs.cs

$(objdir)ohSoundcard.$(exeext) : $(objdir)$(dllprefix)ohSoundcard.net.$(dllext) ohSoundcard\Windows\Wpf\ohSoundcard\ReceiverList.cs ohSoundcard\Windows\Wpf\ohSoundcard\ExtendedNotifyIcon.cs ohSoundcard\Windows\Wpf\ohSoundcard\App.xaml.cs ohSoundcard\Windows\Wpf\ohSoundcard\MainWindow.xaml.cs
	$(csharp) /target:exe /debug+ \
		/out:$(objdir)ohSoundcard.$(exeext) \
		/reference:WindowsBase.dll \
		/reference:PresentationCore.dll \
		/reference:PresentationFramework.dll \
		/reference:System.dll \
		/reference:System.Net.dll \
		/reference:System.Core.dll \
		/reference:System.Drawing.dll \
		/reference:System.Windows.Forms.dll \
		/reference:System.Xaml.dll \
		/reference:$(objdir)$(dllprefix)ohSoundcard.net.$(dllext)  \
		ohSoundcard\Windows\Wpf\ohSoundcard\ReceiverList.cs \
		ohSoundcard\Windows\Wpf\ohSoundcard\ExtendedNotifyIcon.cs \
		ohSoundcard\Windows\Wpf\ohSoundcard\App.xaml.cs \
		ohSoundcard\Windows\Wpf\ohSoundcard\MainWindow.xaml.cs \
 	
$(objdir)TestSoundcard.$(exeext) : $(objdir)$(dllprefix)ohSoundcard.$(dllext) ohSoundcard\TestSoundcard.cpp
	$(compiler)TestSoundcard.$(objext) -c $(cflags) $(includes) ohSoundcard\TestSoundcard.cpp
	$(link) $(linkoutput)$(objdir)TestSoundcard.$(exeext) $(objdir)ohSoundcard.$(libext) $(objdir)TestSoundcard.$(objext) 

