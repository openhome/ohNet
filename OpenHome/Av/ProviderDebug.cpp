#include <OpenHome/Av/ProviderDebug.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;


ProviderDebug::ProviderDebug(DvDevice& aDevice, RingBufferLogger& aLogger)
    : DvProviderAvOpenhomeOrgDebug1(aDevice)
    , iLogger(aLogger)
{
    EnableActionGetLog();
}

void ProviderDebug::GetLog(IDvInvocation& aInvocation, IDvInvocationResponseString& aLog)
{
    aInvocation.StartResponse();
    iLogger.Read(aLog);
    aLog.WriteFlush();
    aInvocation.EndResponse();
}
