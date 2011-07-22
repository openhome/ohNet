# Makefile for Windows
#

!if "$(release)"=="1"
link_flag_debug = 
debug_specific_cflags = /MT /Ox
build_dir = Release
ohnetdir = ../Build/Obj/Windows/Release
!else
link_flag_debug = /debug
debug_specific_cflags = /MTd /Zi /Od /RTC1
build_dir = Debug
ohnetdir = ../Build/Obj/Windows/Debug
!endif

# Macros used by Common.mak

ar = lib /nologo /out:$(objdir)
cflags = $(debug_specific_cflags) /W4 /WX /EHsc /FR$(objdir) /Gd -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS -DDllExport=__declspec(dllexport) -DDllExportClass=
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
csplatform = x64
csharp = csc /nologo /platform:$(csplatform)
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\ohNet
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
uset4 = no

all: $(objdir)/Install64.$(exeext)

$(objdir)/Install64.$(exeext) : ohSoundcard/Windows/Install.cpp
	$(compiler)/Install64.$(objext) -c $(cflags) $(includes) ohSoundcard/Windows/Install.cpp
	$(link) $(linkoutput)$(objdir)/Install64.$(exeext) $(objdir)/Install64.$(objext) setupapi.lib
	signtool sign /v /a /t http://timestamp.verisign.com/scripts/timestamp.dll $(objdir)/Install64.$(exeext)

