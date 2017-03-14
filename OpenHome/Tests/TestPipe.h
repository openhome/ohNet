#pragma once

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Standard.h>

namespace OpenHome {
namespace Test {

class ITestPipeWritable
{
public:
    virtual void Write(const OpenHome::Brx& aMessage) = 0;
    virtual ~ITestPipeWritable() {}
};

class ITestPipeReadable
{
public:
    virtual TBool Expect(const OpenHome::Brx& aMessage) = 0;
    virtual TBool ExpectEmpty() = 0;
    virtual ~ITestPipeReadable() {}
};

class TestPipeDynamic : public ITestPipeWritable, public ITestPipeReadable
{
public:
    static const TUint kMaxMsgBytes = 256;
public:
    TestPipeDynamic(TUint aSlots = 1024);
    ~TestPipeDynamic();
    void Print();
public: // from ITestPipeWritable
    void Write(const OpenHome::Brx& aMessage) override;
public: // from ITestPipeReadable
    TBool Expect(const OpenHome::Brx& aMessage) override;
    TBool ExpectEmpty() override;
private:
    OpenHome::FifoLiteDynamic<OpenHome::Bwh*> iFifo;
    OpenHome::Mutex iLock;
};

} // namespace Test
} // namespace OpenHome
