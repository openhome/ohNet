/**
 * Fetcher for UPnP device XML
 */

#ifndef HEADER_XML_FETCHER
#define HEADER_XML_FETCHER

#include <OpenHome/Net/Private/AsyncPrivate.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/Fifo.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Net/Private/Error.h>
#include <OpenHome/Exception.h>

#include <list>

EXCEPTION(XmlFetchError)

namespace OpenHome {
class SocketTcpClient;
namespace Net {

class CpStack;

class XmlFetch : public Async
{
public:
    void Set(const Brx& aAbsoluteUri, FunctorAsync& aFunctor);
    void CheckContactable(const Brx& aAbsoluteUri, FunctorAsync& aFunctor);
    ~XmlFetch();
    const OpenHome::Uri& Uri() const;
    void SignalCompleted();
    void SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription);
    static Bwh& Xml(IAsync& aAsync);
    static TBool WasContactable(IAsync& aAsync);
    void Fetch();
    void Interrupt();
    TBool Interrupted() const;
private:
    XmlFetch(CpStack& aCpStack);
    TBool Error() const;
    void WriteRequest(const Brx& aMethod);
    void Read();
    virtual void Output(IAsyncOutput& aConsole);
    virtual TUint Type() const;
private:
    static const TUint kRwBufferLength = 16*1024;
    static const TUint kResponseTimeoutMs = 60 * 1000;
    CpStack& iCpStack;
    OpenHome::Uri iUri;
    FunctorAsync iFunctor;
    TUint iSequenceNumber;
    Bwh iXml;
    OpenHome::Net::Error iError;
    mutable OpenHome::Mutex iLock;
    TBool iInterrupted;
    TBool iCheckContactable;
    TBool iContactable;
    OpenHome::SocketTcpClient iSocket;
    Srs<1024> iReadBuffer;
    ReaderUntilS<1024> iReaderUntil;
    ReaderHttpChunked iDechunker;
    ReaderHttpEntity iReaderEntity;

    friend class XmlFetchManager;
};

class XmlFetcher : public Thread
{
public:
    XmlFetcher(const TChar* aName, Fifo<XmlFetcher*>& aFree);
    ~XmlFetcher();
    void Fetch(XmlFetch* aFetch);
private:
    void LogError(const TChar* aErr);
    void Run();
private:
    Fifo<XmlFetcher*>& iFree;
    XmlFetch* iFetch;
};

class CpStack;

class XmlFetchManager : public Thread
{
public:
    XmlFetchManager(CpStack& aCpStack);
    ~XmlFetchManager();
    XmlFetch* Fetch();
    void Fetch(XmlFetch* aFetch);
private:
    void Run();
private:
    CpStack& iCpStack;
    OpenHome::Mutex iLock;
    std::list<XmlFetch*> iList;
    Fifo<XmlFetcher*> iFree;
    XmlFetcher** iFetchers;
    TBool iActive;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_XML_FETCHER
