#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/FunctorMsg.h>
#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/Optional.h>

#include <atomic>
#include <vector>

EXCEPTION(LogPostError);

namespace OpenHome {
    class RingBufferLogger;
    class Environment;
namespace Net {
    class DvDevice;
}
namespace Av {

class ILoggerSerial
{
public:
    virtual ~ILoggerSerial() {}
    virtual void DisablePassThru() = 0;
};

class ILogPoster
{
public:
    virtual ~ILogPoster() {}
    virtual void SendLog(RingBufferLogger& aLogger, const Brx& aData) = 0;
};

class LoggerSerial : public ILoggerSerial, private Net::IShellCommandHandler
{
    static const TChar* kShellCmdSerial;
    static const Brn kShellCmdSerialOn;
    static const Brn kShellCmdSerialOff;
public:
    LoggerSerial(Net::IShell& aShell);
    ~LoggerSerial();
private: // from ILoggerSerial
    void DisablePassThru() override;
private:
    void LogFunctor(const TChar*);
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) override;
    void DisplayHelp(IWriter& aResponse) override;
private:
    Net::IShell& iShell;
    FunctorMsg iDownstream;
    std::atomic<TBool> iPassThru;
    std::atomic<TBool> iStarted;
};

class Product;
class ProviderDebug;

class LoggerBuffered : private Net::IShellCommandHandler
{
    static const TChar* kShellCommandLog;
public:
    LoggerBuffered(TUint aBytes, Net::DvDevice& aDevice, Product& aProduct,
                   Net::IShell& aShell, Optional<ILogPoster> aLogPoster);
    ~LoggerBuffered();
    ILoggerSerial& LoggerSerial();
    RingBufferLogger& LogBuffer();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse) override;
    void DisplayHelp(IWriter& aResponse) override;
private:
    Net::IShell& iShell;
    Av::LoggerSerial* iLoggerSerial;
    RingBufferLogger* iLoggerRingBuffer;
    ProviderDebug* iProviderDebug;
};

}
} // namespace OpenHome
