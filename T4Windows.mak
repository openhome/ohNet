# Makefile for T4 on Windows

# Macros used by T4.mak

toolsDir = Build\Tools^\
t4 = $(toolsDir)TextTransform.exe
ohNetGen = $(toolsDir)OhNetGen.exe
upnpServiceXml = $(toolsDir)UpnpServiceXml.dll
upnpServiceMake = $(toolsDir)UpnpServiceMake.dll
argumentProcessor = $(toolsDir)ArgumentProcessor.dll
tt = $(toolsDir)UpnpServiceXml.dll $(toolsDir)UpnpServiceMake.dll $(toolsDir)Mono.TextTemplating.dll $(toolsDir)TextTransform.exe $(toolsDir)OhNetGen.exe

tt : $(tt)

dllsources =	OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\AssemblyInfo.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\DirectiveProcessor.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\DirectiveProcessorException.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\RequiresProvidesDirectiveProcessor.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\ToStringHelper.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\ITextTemplatingEngineHost.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\Engine.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Microsoft.VisualStudio.TextTemplating\\TextTransformation.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplatingEngine.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\CrossAppDomainAssemblyResolver.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplateGenerator.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\Tokeniser.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\IExtendedTextTemplatingEngineHost.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\TemplateSettings.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\ParsedTemplate.cs \
                OpenHome\\Net\\T4\\TextTemplating\\Mono.TextTemplating\\Mono.TextTemplating\\CompiledTemplate.cs

$(toolsDir)Mono.TextTemplating.dll : $(dllsources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /nologo /t:library -out:$(toolsDir)Mono.TextTemplating.dll $(dllsources)

exesources =	OpenHome\\Net\\T4\\TextTemplating\\TextTransform\\AssemblyInfo.cs \
                OpenHome\\Net\\T4\\TextTemplating\\TextTransform\\Options.cs \
                OpenHome\\Net\\T4\\TextTemplating\\TextTransform\\TextTransform.cs

$(toolsDir)OhNetGen.exe : $(toolsDir)TextTransform.exe OpenHome\\Net\\T4\\OhNetGen.cs
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /t:exe /out:$(toolsDir)OhNetGen.exe OpenHome\\Net\\T4\\OhNetGen.cs OpenHome\\Net\\T4\\AssemblyInfo.cs

$(toolsDir)TextTransform.exe : $(toolsDir)Mono.TextTemplating.dll $(exesources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc /nologo /t:exe -out:$(toolsDir)TextTransform.exe /r:$(toolsDir)Mono.TextTemplating.dll $(exesources)

$(toolsDir)UpnpServiceDescription.xsd : OpenHome\\Net\\T4\\UpnpServiceXml\\UpnpServiceDescription.xsd
	@if not exist $(toolsDir) mkdir $(toolsDir)
	copy /y OpenHome\\Net\\T4\\UpnpServiceXml\\UpnpServiceDescription.xsd $(toolsDir)

$(toolsDir)UpnpServiceTemplate.xsd : OpenHome\\Net\\T4\\UpnpServiceXml\\UpnpServiceTemplate.xsd
	@if not exist $(toolsDir) mkdir $(toolsDir)
	copy /y OpenHome\\Net\\T4\\UpnpServiceXml\\UpnpServiceTemplate.xsd $(toolsDir)


xmlsources =	OpenHome\\Net\\T4\\UpnpServiceXml\\AssemblyInfo.cs \
                OpenHome\\Net\\T4\\UpnpServiceXml\\UpnpServiceXml.cs


$(toolsDir)UpnpServiceXml.dll: $(toolsDir)UpnpServiceDescription.xsd $(toolsDir)UpnpServiceTemplate.xsd $(xmlsources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceXml) $(xmlsources)
	

makesources =	OpenHome\\Net\\T4\\UpnpServiceMake\\AssemblyInfo.cs \
                OpenHome\\Net\\T4\\UpnpServiceMake\\UpnpServiceMake.cs

$(toolsDir)UpnpServiceMake.dll : $(makesources)
	@if not exist $(toolsDir) mkdir $(toolsDir)
	csc -target:library -out:$(upnpServiceMake) $(makesources)

clean-t4:
	$(rmdir) $(toolsDir)

mkToolsDir:
	if not exist $(toolsDir) mkdir $(toolsDir)
