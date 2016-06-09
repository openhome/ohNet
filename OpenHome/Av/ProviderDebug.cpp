#include <OpenHome/Av/ProviderDebug.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Optional.h>
#include <OpenHome/Av/Logger.h>

using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Net;

ProviderDebug::ProviderDebug(DvDevice& aDevice, RingBufferLogger& aLogger, Optional<ILogPoster> aLogPoster)
    : DvProviderAvOpenhomeOrgDebug1(aDevice)
    , iLogger(aLogger)
    , iLogPoster(aLogPoster)
{
    EnableActionGetLog();
    EnableActionSendLog();
}

void ProviderDebug::GetLog(IDvInvocation& aInvocation, IDvInvocationResponseString& aLog)
{
    aInvocation.StartResponse();
    iLogger.Read(aLog);
    aLog.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderDebug::SendLog(IDvInvocation& aInvocation, const Brx& aData)
{
    if (!iLogPoster.Ok()) {
        aInvocation.Error(801, Brn("Not supported"));
    }
    iLogPoster.Unwrap().SendLog(iLogger, aData);
    aInvocation.StartResponse();
    aInvocation.EndResponse();
}
