/**
 * Fetcher for UPnP device XML
 */

#ifndef HEADER_XML_FETCHER
#define HEADER_XML_FETCHER

#include <AsyncPrivate.h>
#include <Thread.h>
#include <Uri.h>
#include <ZappTypes.h>
#include <Fifo.h>
#include <Stream.h>
#include <Error.h>

#include <list>

EXCEPTION(XmlFetchError);

namespace Zapp {

class SocketTcpClient;
class XmlFetch : public Async
{
public:
    void Set(Zapp::Uri* aUri, FunctorAsync& aFunctor);
    ~XmlFetch();
    const Zapp::Uri& Uri() const;
    void SignalCompleted();
    void SetError(Error::ELevel aLevel, TUint aCode, const Brx& aDescription);
    static Bwh& Xml(IAsync& aAsync);
    void Fetch();
    void Interrupt();
    TBool Interrupted() const;
private:
    XmlFetch();
    TBool Error() const;
    void WriteRequest(SocketTcpClient& aSocket);
    void Read(SocketTcpClient& aSocket);
    virtual void Output(IAsyncOutput& aConsole);
    virtual TUint Type() const;
private:
    static const TUint kRwBufferLength = 1024;
    Zapp::Uri* iUri;
    FunctorAsync iFunctor;
    TUint iSequenceNumber;
    Bwh iXml;
    Zapp::Error iError;
    mutable Mutex iLock;
    TBool iInterrupted;
    SocketTcpClient* iSocket;

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

class XmlFetchManager : public Thread
{
public:
    XmlFetchManager();
    ~XmlFetchManager();
    static XmlFetch* Fetch();
    static void Fetch(XmlFetch* aFetch);
private:
    static XmlFetchManager& Self();
    void Run();
private:
    Mutex iLock;
    std::list<XmlFetch*> iList;
    Fifo<XmlFetcher*> iFree;
    XmlFetcher** iFetchers;
    TBool iActive;
};

} // namespace Zapp

#endif // HEADER_XML_FETCHER
