# Makefile for T4 on Windows

# Macros used by T4.mak

toolsDir = Build\\Tools\\
t4 = $(toolsDir)TextTransform.exe
upnpServiceXml = $(toolsDir)UpnpServiceXml.dll
upnpServiceMake = $(toolsDir)UpnpServiceMake.dll
argumentProcessor = $(toolsDir)ArgumentProcessor.dll
proxySrcCppCore = ControlPoint\\Services\\Cpp\\Core\\
proxyApiCppCore = Api\\Cpp\\Core\\
proxyApiC = Api\\C\\
proxySrcC = ControlPoint\\Services\\C\\
proxyApiCppStd = Api\\Cpp\\Std\\
proxySrcCppStd = ControlPoint\\Services\\Cpp\\Std\\
proxyCs = ControlPoint\\Services\\Cs\\
deviceSrcCppCore = Device\\Services\\Cpp\\Core\\
deviceApiCppCore = $(proxyApiCppCore)
deviceSrcCppStd = Device\\Services\\Cpp\\Std\\
deviceApiCppStd = $(proxyApiCppStd)
deviceSrcC = Device\\Services\\C\\
deviceApiC = $(proxyApiC)
deviceCs = Device\\Services\\Cs\\
tt = $(toolsDir)UpnpServiceXml.dll $(toolsDir)UpnpServiceMake.dll $(toolsDir)Mono.TextTemplating.dll $(toolsDir)TextTransform.exe

tt : $(tt)

$(toolsDir)Mono.TextTemplating.dll :
	@if not exist $(toolsDir) mkdir $(toolsDir)
	@cd T4/TextTemplating/Mono.TextTemplating
	csc /nologo /t:library -out:../../../$(toolsDir)Mono.TextTemplating.dll /recurse:*.cs
	@cd ../../../

$(toolsDir)TextTransform.exe : $(toolsDir)Mono.TextTemplating.dll
	@if not exist $(toolsDir) mkdir $(toolsDir)
	@cd T4/TextTemplating/TextTransform
	csc /nologo /t:exe -out:../../../$(toolsDir)TextTransform.exe /r:../../../$(toolsDir)Mono.TextTemplating.dll  /recurse:*.cs
	@cd ../../../

$(toolsDir)UpnpServiceXml.dll: 	
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceXml) T4\\UpnpServiceXml\\AssemblyInfo.cs T4\\UpnpServiceXml\\UpnpServiceXml.cs
	copy /y T4\\UpnpServiceXml\\UpnpServiceDescription.xsd $(toolsDir)
	copy /y T4\\UpnpServiceXml\\UpnpServiceTemplate.xsd $(toolsDir)

$(toolsDir)UpnpServiceMake.dll:
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceMake) T4\\UpnpServiceMake\\AssemblyInfo.cs T4\\UpnpServiceMake\\UpnpServiceMake.cs

clean-t4:
	rd /s/q $(toolsDir)

mkToolsDir:
	if not exist $(toolsDir) mkdir $(toolsDir)
