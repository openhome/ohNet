# Makefile for Windows
#

# Macros used by Common.mak
ar = lib /nologo /out:$(objdir)
cflags = /MDd /W4 /WX /EHsc /RTC1 /Zi /FR /Gz -DDEFINE_LITTLE_ENDIAN -DDEFINE_TRACE -D_CRT_SECURE_NO_WARNINGS /Od -DDllImport=__declspec(dllimport) -DDllExport=__declspec(dllexport)
objdirbare = Build\Obj\Windows
objdir = $(objdirbare)\\
inc_build = Build\\Include
includes = -IBuild\\Include -IBuild\\Include\\Cpp
proxySrcCppCore = ControlPoint\\Services\\Cpp\\Core\\
proxySrcC = ControlPoint\\Services\\C\\
proxySrcCppStd = ControlPoint\\Services\\Cpp\\Std\\
deviceSrcCppCore = Device\\Services\\Cpp\\Core\\
deviceSrcCppStd = Device\\Services\\Cpp\\Std\\
deviceSrcC = Device\\Services\\C\\
osdir = Windows
objext = obj
libprefix = 
libext = lib
exeext = exe
compiler = cl /nologo /Fo$(objdir)
linker = link /nologo /debug /machine:I386 /SUBSYSTEM:CONSOLE /map Ws2_32.lib Iphlpapi.lib /out:$(objdir)
dllprefix =
dllext = dll
linker_dll = link /nologo /debug /machine:I386  /map Ws2_32.lib Iphlpapi.lib /dll /out:$(objdir)
linker_dll_service = link /nologo /debug /machine:I386  /map $(objdir)ZappUpnp.lib Ws2_32.lib Iphlpapi.lib /dll /out:$(objdir)

# Actual building of code is shared between platforms
include Common.mak

# Following macros must be provided by each file which wraps Common.mak

TestProxyCs: ZappUpnpDll CpUpnpOrgConnectionManager1Dll
	csc /nologo /unsafe /platform:x86 /t:exe -out:$(objdir)TestProxyCs.exe Public\\Cs\\CpDevice.cs Public\\Cs\\CpDeviceUpnp.cs Public\\Cs\\CpProxy.cs Public\\Cs\\Zapp.cs Public\\Cs\\AssemblyInfo.cs ControlPoint\\Services\\Cs\\CpUpnpOrgConnectionManager1.cs  Public\\Cs\\TestProxy.cs

TestDvDeviceCs: ZappUpnpDll CpZappOrgTestBasic1Dll DvZappOrgTestBasic1Dll
	csc /nologo /d:DEBUG /debug /unsafe /platform:x86 /t:exe -out:$(objdir)TestDvDeviceCs.exe Public\\Cs\\CpDevice.cs Public\\Cs\\CpDeviceUpnp.cs Public\\Cs\\CpProxy.cs Public\\Cs\\Zapp.cs Public\\Cs\\AssemblyInfo.cs ControlPoint\\Services\\Cs\\CpZappOrgTestBasic1.cs  Public\\Cs\\DvDevice.cs Public\\Cs\\DvServiceErrors.cs Device\\Services\\Cs\\DvZappOrgTestBasic1.cs  Public\\Cs\\TestDvDevice.cs

TestDvLightsCs: ZappUpnpDll CpZappOrgTestLights1Dll DvZappOrgTestLights1Dll
	csc /nologo /d:DEBUG /debug /unsafe /platform:x86 /t:exe -out:$(objdir)TestDvLightsCs.exe Public\\Cs\\CpDevice.cs Public\\Cs\\CpDeviceUpnp.cs Public\\Cs\\CpProxy.cs Public\\Cs\\Zapp.cs Public\\Cs\\AssemblyInfo.cs ControlPoint\\Services\\Cs\\CpZappOrgTestLights1.cs  Public\\Cs\\DvDevice.cs Public\\Cs\\DvServiceErrors.cs Device\\Services\\Cs\\DvZappOrgTestLights1.cs  Public\\Cs\\TestDvLights.cs

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
	copy ControlPoint\Upnp\*.h $(inc_build) > nul
	copy Device\*.h $(inc_build) > nul
	copy Device\Upnp\*.h $(inc_build) > nul
	copy Network\*.h $(inc_build) > nul
	copy Service\*.h $(inc_build) > nul
	copy Ssdp\*.h $(inc_build) > nul
	copy Os\*.h $(inc_build) > nul
	copy Os\*.inl $(inc_build) > nul
	copy Os\C\Os.h $(inc_build)\C > nul
	copy Public\C\*.h $(inc_build)\C > nul
	copy Thread\Thread.h $(inc_build) > nul
	copy Timer\Timer.h $(inc_build) > nul
	copy Utils\*.h $(inc_build) > nul
	copy TestFramework\*.h $(inc_build) > nul

clean :
	del /q $(objdir)*
	rd /s/q $(inc_build)
