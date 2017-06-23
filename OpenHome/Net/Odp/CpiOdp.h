#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Net/Private/CpiService.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>

namespace OpenHome {
    class IWriter;
    class WriterJsonObject;
    class JsonParser;
namespace Net {
    class CpiSubscription;

class ICpiOdpResponse
{
public:
    virtual TBool HandleOdpResponse(const JsonParser& aJsonParser) = 0;
    virtual ~ICpiOdpResponse() {}
};

class ICpiOdpDevice
{
public:
    virtual IWriter& WriteLock(ICpiOdpResponse& aResponseHandler) = 0;
    virtual void WriteUnlock() = 0;
    virtual void WriteEnd(IWriter& aWriter) = 0;
    virtual const Brx& Alias() const = 0;
    virtual ~ICpiOdpDevice() {}
};

class CpiOdpInvocable : public IInvocable
                      , private ICpiOdpResponse
                      , private INonCopyable
{
public:
    CpiOdpInvocable(ICpiOdpDevice& aDevice);
private: // from IInvocable
    void InvokeAction(Invocation& aInvocation) override;
private: // from ICpiOdpResponse
    TBool HandleOdpResponse(const JsonParser& aJsonParser) override;
private:
    ICpiOdpDevice& iDevice;
    Semaphore iSem;
    Invocation* iInvocation;
    IWriter* iWriter;
};

class CpiOdpWriterArgs : private IInputArgumentProcessor
                       , private INonCopyable
{
public:
    CpiOdpWriterArgs(WriterJsonObject& aWriterObject);
    void Process(Argument& aArg);
private: // from IInputArgumentProcessor
    void ProcessString(const Brx& aVal) override;
    void ProcessInt(TInt aVal) override;
    void ProcessUint(TUint aVal) override;
    void ProcessBool(TBool aVal) override;
    void ProcessBinary(const Brx& aVal) override;
private:
    void WriteString(const Brx& aVal);
private:
    WriterJsonObject& iWriterObject;
    Argument* iArg;
};

class CpiOdpOutputProcessor : public IOutputProcessor
{
private: // from IOutputProcessor
    void ProcessString(const Brx& aBuffer, Brhz& aVal) override;
    void ProcessInt(const Brx& aBuffer, TInt& aVal) override;
    void ProcessUint(const Brx& aBuffer, TUint& aVal) override;
    void ProcessBool(const Brx& aBuffer, TBool& aVal) override;
    void ProcessBinary(const Brx& aBuffer, Brh& aVal) override;
};

class CpiOdpSubscriber : private ICpiOdpResponse
                       , private INonCopyable
{
public:
    CpiOdpSubscriber(ICpiOdpDevice& aDevice);
    void Subscribe(CpiSubscription& aSubscription);
private: // from ICpiOdpResponse
    TBool HandleOdpResponse(const JsonParser& aJsonParser) override;
private:
    ICpiOdpDevice& iDevice;
    Semaphore iSem;
    CpiSubscription* iSubscription;
};

class CpiOdpUnsubscriber : private ICpiOdpResponse
                         , private INonCopyable
{
public:
    CpiOdpUnsubscriber(ICpiOdpDevice& aDevice);
    void Unsubscribe(const Brx& aSid);
private: // from ICpiOdpResponse
    TBool HandleOdpResponse(const JsonParser& aJsonParser) override;
private:
    ICpiOdpDevice& iDevice;
    Semaphore iSem;
};

// takes write locked session, unlocks on destruction
class AutoOdpDevice : private INonCopyable
{
public:
    AutoOdpDevice(ICpiOdpDevice& aDevice);
    ~AutoOdpDevice();
private:
    ICpiOdpDevice& iDevice;
};

} // namespace Net
} // namespace OpenHome
