#include <OpenHome/Av/Logger.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/Shell.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Av/ProviderDebug.h>
#include <OpenHome/Av/Product.h>

#include <atomic>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Av;

// LoggerSerial

const TChar* LoggerSerial::kShellCmdSerial = "serial";
const Brn LoggerSerial::kShellCmdSerialOn("on");
const Brn LoggerSerial::kShellCmdSerialOff("off");

LoggerSerial::LoggerSerial(IShell& aShell)
    : iShell(aShell)
{
    iShell.AddCommandHandler(kShellCmdSerial, *this);
    iPassThru.store(false);
    ASSERT(iPassThru.is_lock_free());
    iStarted.store(false);
    ASSERT(iStarted.is_lock_free());
    FunctorMsg functor = MakeFunctorMsg(*this, &LoggerSerial::LogFunctor);
    iDownstream = Log::SwapOutput(functor);
}

LoggerSerial::~LoggerSerial()
{
    iShell.RemoveCommandHandler(kShellCmdSerial);
    (void)Log::SwapOutput(iDownstream);
}

void LoggerSerial::DisablePassThru()
{
    iStarted.store(true);
}

void LoggerSerial::LogFunctor(const TChar* aMsg)
{
    if (iPassThru.load() || !iStarted.load()) {
        iDownstream(aMsg);
    }
}

void LoggerSerial::HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for \'serial\' command\n"));
        return;
    }
    if (Ascii::CaseInsensitiveEquals(aArgs[0], kShellCmdSerialOn)) {
        iPassThru.store(true);
    }
    else if (Ascii::CaseInsensitiveEquals(aArgs[0], kShellCmdSerialOff)) {
        iPassThru.store(false);
    }
    else {
        aResponse.Write(Brn("Unexpected level name for command \'debug\': "));
        aResponse.Write(aArgs[0]);
        aResponse.Write(Brn("\n"));
    }
}

void LoggerSerial::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("serial [on|off]\n"));
    aResponse.Write(Brn("  enable or disable serial logging\n"));
    aResponse.Write(Brn("  (defaults to disabled)\n"));
}


// LoggerBuffered

const TChar* LoggerBuffered::kShellCommandLog = "log";

LoggerBuffered::LoggerBuffered(TUint aBytes, Net::DvDevice& aDevice, Product& aProduct,
                               IShell& aShell, Optional<ILogPoster> aLogPoster)
    : iShell(aShell)
{
    iShell.AddCommandHandler(kShellCommandLog, *this);
    iLoggerSerial = new Av::LoggerSerial(aShell);
    iLoggerRingBuffer = new RingBufferLogger(aBytes);
    iProviderDebug = new ProviderDebug(aDevice, *iLoggerRingBuffer, aLogPoster);
    aProduct.AddAttribute("Debug");
}

LoggerBuffered::~LoggerBuffered()
{
    iShell.RemoveCommandHandler(kShellCommandLog);
    delete iProviderDebug;
    delete iLoggerRingBuffer;
    delete iLoggerSerial;
}

ILoggerSerial& LoggerBuffered::LoggerSerial()
{
    return *iLoggerSerial;
}

RingBufferLogger& LoggerBuffered::LogBuffer()
{
    return *iLoggerRingBuffer;
}

void LoggerBuffered::HandleShellCommand(Brn /*aCommand*/, const std::vector<Brn>& aArgs, IWriter& aResponse)
{
    if (aArgs.size() != 1) {
        aResponse.Write(Brn("Unexpected number of arguments for command \'log\'\n"));
        return;
    }
    if (aArgs[0] != Brn("print")) {
        aResponse.Write(Brn("Unexpected command for \'log\': "));
        aResponse.Write(aArgs[0]);
        aResponse.Write(Brn("\n"));
        return;
    }
    iLoggerRingBuffer->Read(aResponse);
}

void LoggerBuffered::DisplayHelp(IWriter& aResponse)
{
    aResponse.Write(Brn("log print\n"));
    aResponse.Write(Brn("  display all recently logged content\n"));
}
