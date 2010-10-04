# Makefile for T4 on linux
# Could be extended to support Mac in future

# Macros used by T4.mak

toolsDir = Build/Tools/
t4 = $(toolsDir)TextTransform.exe
upnpServiceXml = $(toolsDir)UpnpServiceXml.dll
upnpServiceMake = $(toolsDir)UpnpServiceMake.dll
argumentProcessor = $(toolsDir)ArgumentProcessor.dll
proxySrcCppCore = ControlPoint/Services/Cpp/Core/
proxyApiCppCore = Api/Cpp/Core/
proxyApiC = Api/C/
proxySrcC = ControlPoint/Services/C/
proxyApiCppStd = Api/Cpp/Std/
proxySrcCppStd = ControlPoint/Services/Cpp/Std/
proxyCs = ControlPoint/Services/Cs/
deviceSrcCppCore = Device/Services/Cpp/Core/
deviceApiCppCore = $(proxyApiCppCore)
deviceSrcCppStd = Device/Services/Cpp/Std/
deviceApiCppStd = $(proxyApiCppStd)
deviceSrcC = Device/Services/C/
deviceApiC = $(proxyApiC)
deviceCs = Device/Services/Cs/

# Actual building of code is shared between platforms
include T4.mak

# Following macros must be provided by each file which wraps Common.mak

tt: mkToolsDir UpnpServiceXml.dll
	gmcs /t:library -out:$(toolsDir)Mono.TextTemplating.dll \
                          T4/TextTemplating/Mono.TextTemplating/AssemblyInfo.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/DirectiveProcessor.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/DirectiveProcessorException.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/RequiresProvidesDirectiveProcessor.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/ToStringHelper.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/ITextTemplatingEngineHost.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/Engine.cs \
                          T4/TextTemplating/Mono.TextTemplating/Microsoft.VisualStudio.TextTemplating/TextTransformation.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/TemplatingEngine.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/CrossAppDomainAssemblyResolver.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/TemplateGenerator.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/Tokeniser.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/IExtendedTextTemplatingEngineHost.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/TemplateSettings.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/ParsedTemplate.cs \
                          T4/TextTemplating/Mono.TextTemplating/Mono.TextTemplating/CompiledTemplate.cs
	gmcs /t:exe -out:$(toolsDir)TextTransform.exe /r:$(toolsDir)Mono.TextTemplating.dll \
                          T4/TextTemplating/TextTransform/AssemblyInfo.cs \
                          T4/TextTemplating/TextTransform/Options.cs \
                          T4/TextTemplating/TextTransform/TextTransform.cs

UpnpServiceXml.dll: mkToolsDir
	gmcs -target:library -out:$(upnpServiceXml) T4/UpnpServiceXml/AssemblyInfo.cs T4/UpnpServiceXml/UpnpServiceXml.cs
	cp -u T4/UpnpServiceXml/UpnpServiceDescription.xsd $(toolsDir)
	cp -u T4/UpnpServiceXml/UpnpServiceTemplate.xsd $(toolsDir)

UpnpServiceMake.dll: mkToolsDir
	gmcs -target:library -out:$(upnpServiceMake) T4/UpnpServiceMake/AssemblyInfo.cs T4/UpnpServiceMake/UpnpServiceMake.cs

clean:
	if test -d $(toolsDir); then rm -r $(toolsDir); fi

mkToolsDir:
	if test -d $(toolsDir); then echo; else mkdir -p $(toolsDir); fi
