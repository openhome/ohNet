#include <OpenHome/Os.h>
#include <OpenHome/Exception.h>

#include <windows.h>

EXCEPTION(Windows_SEH)

static void SEHTranslator(unsigned int /*u*/, EXCEPTION_POINTERS* /*pExp*/)
{
    THROW(OpenHome::Windows_SEH);
}

extern "C" void OsThreadInstallSignalHandlers()
{
    (void)_set_se_translator(SEHTranslator);
}
