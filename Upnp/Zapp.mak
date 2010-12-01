# Makefile for Windows
#

# Macros used by Common.mak
ar = lib /nologo /out:$(objdir)
cflags = /MDd /W4 /WX /EHsc /RTC1 /Zi /FR /Gz -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS /Od -DDllImport=__declspec(dllimport) -DDllExport=__declspec(dllexport) -DDllExportClass=
objdirbare = Build\Obj\Windows
objdir = $(objdirbare)^\
inc_build = Build\Include
includes = -IBuild\Include -IBuild\Include\Cpp
proxySrcCppCore = ControlPoint\Services\Cpp\Core^\
proxySrcC = ControlPoint\Services\C^\
proxySrcCppStd = ControlPoint\Services\Cpp\Std^\
proxySrcCs = ControlPoint\Services\Cs^\
deviceSrcCppCore = Device\Services\Cpp\Core^\
deviceSrcCppStd = Device\Services\Cpp\Std^\
deviceSrcC = Device\Services\C^\
deviceSrcCs = Device\Services\Cs^\
osdir = Windows
objext = obj
libprefix = 
libext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
link = link /nologo /debug /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib /incremental:no
linkoutput = /out:
dllprefix =
dllext = dll
link_dll = link /nologo /debug /map Ws2_32.lib Iphlpapi.lib /dll
link_dll_service = link /nologo /debug  /map $(objdir)ZappUpnp.lib Ws2_32.lib Iphlpapi.lib /dll
csharp = csc /nologo /platform:x86
publiccsdir = Public\Cs^\
dirsep = ^\
installdir = $(PROGRAMFILES)\Zapp
installlibdir = $(installdir)\lib
installincludedir = $(installdir)\include
mkdir = Scripts\mkdir.bat
rmdir = Scripts\rmdir.bat
default : all

include T4Windows.mak
# Actual building of code is shared between platforms
include Common.mak

!if exist (Generated\GenerateSourceFiles.mak)
!include Generated\GenerateSourceFiles.mak
!else
!message Note: Generated\GenerateSourceFiles.mak does not yet exist. Try "make generate-makefiles".
!endif

!if exist (Generated\Proxies.mak)
!include Generated\Proxies.mak
!else
!message Note: Generated\Proxies.mak does not yet exist. Try "make generate-makefiles".
!endif

!if exist (Generated\Devices.mak)
!include Generated\Devices.mak
!else
!message Note: Generated\Devices.mak does not yet exist. Try "make generate-makefiles".
!endif

include UserTargets.mak

# Following macros must be provided by each file which wraps Common.mak

make_obj_dir:
	if not exist $(objdirbare) mkdir $(objdirbare)

copy_build_includes:
	if not exist $(inc_build) mkdir $(inc_build)
	if not exist $(inc_build)\C mkdir $(inc_build)\C
	if not exist $(inc_build)\Cpp mkdir $(inc_build)\Cpp
	if not exist $(inc_build)\Cpp\Core mkdir $(inc_build)\Cpp\Core
	if not exist $(inc_build)\Cpp\Std mkdir $(inc_build)\Cpp\Std
	copy Api\*.h $(inc_build) > nul
	copy Api\C\*.h $(inc_build)\C > nul
	copy Api\Cpp\*.h $(inc_build)\Cpp > nul
	copy Api\Cpp\*.inl $(inc_build)\Cpp > nul
	copy Api\Cpp\Core\*.h $(inc_build)\Cpp\Core > nul
	copy Api\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy *.h $(inc_build) > nul
	copy Arch\*.h $(inc_build) > nul
	copy Arch\I386\ArchSpecific.h $(inc_build) > nul
	copy ControlPoint\*.h $(inc_build) > nul
	copy ControlPoint\Dv\*.h $(inc_build) > nul
	copy ControlPoint\Upnp\*.h $(inc_build) > nul
	copy Device\*.h $(inc_build) > nul
	copy Device\Upnp\*.h $(inc_build) > nul
	copy Network\*.h $(inc_build) > nul
	copy Service\*.h $(inc_build) > nul
	copy Ssdp\*.h $(inc_build) > nul
	copy Os\*.h $(inc_build) > nul
	copy Os\*.inl $(inc_build) > nul
	copy Public\C\*.h $(inc_build)\C > nul
	copy Public\Cpp\Std\*.h $(inc_build)\Cpp\Std > nul
	copy Thread\Thread.h $(inc_build) > nul
	copy Timer\Timer.h $(inc_build) > nul
	copy Utils\*.h $(inc_build) > nul
	copy TestFramework\*.h $(inc_build) > nul

install :
	if not exist "$(installdir)" mkdir "$(installdir)"
	if not exist "$(installlibdir)" mkdir "$(installlibdir)"
	if not exist "$(installincludedir)" mkdir "$(installincludedir)"
	copy "$(objdir)*" "$(installlibdir)" > nul
	xcopy "$(inc_build)" "$(installincludedir)" /Y /S /I > nul

uninstall :
	if not exist "$(installdir)" echo Nothing to uninstall && exit /b 1
	if exist "$(installlibdir)" del /q "$(installlibdir)\*" > nul
	if exist "$(installlibdir)" rmdir "$(installlibdir)"
	if exist "$(installincludedir)" rmdir /s /q "$(installincludedir)"
	rmdir "$(installdir)"

