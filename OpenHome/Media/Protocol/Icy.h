#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Stream.h>

namespace OpenHome {
namespace Media {

class HeaderIcyMetadata : public HttpHeader
{
public:
    static void Write(WriterHttpHeader& aWriter);
    TUint Bytes() const;
private: // from HttpHeader
    TBool Recognise(const Brx& aHeader);
    void Process(const Brx& aValue);
private:
    TUint iBytes;
};

class IIcyObserver
{
public:
    static const TUint kIcyMetadataBytes = 255 * 16;
public:
    virtual void NotifyIcyData(const Brx& aIcyData) = 0;
    virtual ~IIcyObserver() {}
};

class ReaderIcy : public IReader
{
    static const TUint kIcyMetadataBytes = 255 * 16;
public:
    ReaderIcy(IReader& aReader, IIcyObserver& aObserver, TUint64& aStreamOffset);
    void Reset();
    void SetEnabled(TUint aChunkBytes);
public: // from IReader
    Brn Read(TUint aBytes) override;
    void ReadFlush() override;
    void ReadInterrupt() override;
private:
    void ExtractMetadata();
private:
    IReader& iReader;
    IIcyObserver& iObserver;
    TUint64& iOffset;
    Bws<kIcyMetadataBytes> iIcyData; // only used in a single function but too large to comfortably declare on the stack
    TUint iDataChunkSize;
    TUint iDataChunkRemaining;
    TBool iEnabled;
};

class IcyObserverDidlLite : public IIcyObserver
{
public:
    IcyObserverDidlLite(IIcyObserver& aObserver);
    void Reset();
private: // from IIcyObserver
    void NotifyIcyData(const Brx& aIcyData) override;
private:
    IIcyObserver& iObserver;
    Bws<kIcyMetadataBytes> iIcyMetadata;
    Bws<kIcyMetadataBytes> iNewIcyMetadata; // only used in a single function but too large to comfortably declare on the stack
};

}
}
