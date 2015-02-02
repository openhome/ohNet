#include <OpenHome/Media/Protocol/ProtocolFactory.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/Supply.h>

#include <stdlib.h>

namespace OpenHome {
namespace Media {

class ProtocolFile : public Protocol, private IProtocolReader
{
public:
    ProtocolFile(Environment& aEnv);
    ~ProtocolFile();
private: // from Protocol
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream);
    void Interrupt(TBool aInterrupt);
    ProtocolStreamResult Stream(const Brx& aUri);
    ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes);
private: // from IStreamHandler
    TUint TrySeek(TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aStreamId);
    TBool TryGet(IWriter& aWriter, TUint aStreamId, TUint64 aOffset, TUint aBytes);
private: // from IProtocolReader
    Brn Read(TUint aBytes);
    Brn ReadUntil(TByte aSeparator);
    void ReadFlush();
    void ReadInterrupt();
    Brn ReadRemaining();
private:
    static const TUint kReadBufBytes = 9 * 1024;
    Mutex iLock;
    Supply* iSupply;
    OpenHome::Uri iUri;
    FileStream iFileStream;
    Srs<kReadBufBytes> iReaderBuf;
    TUint iStreamId;
    TBool iStop;
    TBool iSeek;
    TBool iFileOpen;
    TUint32 iSeekPos;
    TUint iNextFlushId;
};

};  // namespace Media
};  // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Media;


Protocol* ProtocolFactory::NewFile(Environment& aEnv)
{ // static
    return new ProtocolFile(aEnv);
}


// ProtocolFile

ProtocolFile::ProtocolFile(Environment& aEnv)
    : Protocol(aEnv)
    , iLock("PRTF")
    , iSupply(NULL)
    , iReaderBuf(iFileStream)
{
}

ProtocolFile::~ProtocolFile()
{
    delete iSupply;
}

void ProtocolFile::Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new Supply(aMsgFactory, aDownstream);
}

void ProtocolFile::Interrupt(TBool aInterrupt)
{
    iLock.Wait();
    if (aInterrupt) {
        iFileStream.ReadInterrupt();
    }
    iLock.Signal();
}

ProtocolStreamResult ProtocolFile::Stream(const Brx& aUri)
{
    iStreamId = 0;
    iStop = iSeek = false;
    iSeekPos = 0;
    iNextFlushId = MsgFlush::kIdInvalid;
    iUri.Replace(aUri);

    LOG(kMedia, "ProtocolHttp::Stream ");
    LOG(kMedia, iUri.AbsoluteUri());
    LOG(kMedia, "\n");
    if (iUri.Scheme() != Brn("file")) {
        LOG(kMedia, "ProtocolFile::Stream Scheme not recognised\n");
        return EProtocolErrorNotSupported;
    }
    
    Brhz pathBuf(iUri.Path());
    TChar* path = pathBuf.Transfer();
    try {
        IFile* file = IFile::Open(path, eFileReadOnly);
        iFileStream.SetFile(file);
    }
    catch (FileOpenError&) {
        free(path);
        return EProtocolStreamErrorUnrecoverable;
    }
    iFileOpen = true;
    free(path);
    iFileStream.Interrupt(false);
    const TUint fileSize = iFileStream.Bytes();

    ContentProcessor* contentProcessor = NULL;
    try {
        TUint bytes = (fileSize<100? fileSize : 100);
        Brn contentStart = iReaderBuf.Peek(bytes);
        contentProcessor = iProtocolManager->GetContentProcessor(iUri.AbsoluteUri(), Brx::Empty(), contentStart);
    }
    catch (ReaderError&) {
        return EProtocolStreamErrorRecoverable;
    }
    if (contentProcessor != NULL) {
        return contentProcessor->Stream(*this, fileSize);
    }
    
    ProtocolStreamResult res = EProtocolStreamErrorRecoverable;
    iStreamId = iIdProvider->NextStreamId();
    iSupply->OutputStream(iUri.AbsoluteUri(), fileSize, true, false, *this, iStreamId);
    contentProcessor = iProtocolManager->GetAudioProcessor();
    TUint remaining = fileSize;
    while (res == EProtocolStreamErrorRecoverable) {
        res = contentProcessor->Stream(*this, remaining);
        iLock.Wait();
        if (iSeek) {
            iFileStream.Interrupt(false);
            iFileStream.Seek(iSeekPos);
            remaining = fileSize - iSeekPos;
            iSeek = false;
            iSeekPos = 0;
            iSupply->OutputFlush(iNextFlushId);
        }
        else if (iStop) {
            res = EProtocolStreamStopped;
            iSupply->OutputFlush(iNextFlushId);
        }
        else {
            // don't expect any exceptions (other than the above ones we generate) when reading a local file
            ASSERT(res == EProtocolStreamSuccess);
        }
        iLock.Signal();
    }

    iLock.Wait();
    iFileStream.CloseFile();
    iFileOpen = false;
    iLock.Signal();
    if (contentProcessor != NULL) {
        contentProcessor->Reset();
    }
    return res;
}

ProtocolGetResult ProtocolFile::Get(IWriter& /*aWriter*/, const Brx& /*aUri*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return EProtocolGetErrorNotSupported;
}

TUint ProtocolFile::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    iLock.Wait();
    const TBool streamIsValid = (iFileOpen && iProtocolManager->IsCurrentStream(aStreamId));
    if (streamIsValid) {
        iSeek = true;
        iSeekPos = (TUint32)aOffset;
        iNextFlushId = iFlushIdProvider->NextFlushId();
    }
    iLock.Signal();
    if (!streamIsValid) {
        return MsgFlush::kIdInvalid;
    }
    iFileStream.ReadInterrupt();
    return iNextFlushId;
}

TUint ProtocolFile::TryStop(TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = iProtocolManager->IsCurrentStream(aStreamId);
    if (stop) {
        iNextFlushId = iFlushIdProvider->NextFlushId();
        iStop = true;
        iFileStream.ReadInterrupt();
    }
    iLock.Signal();
    if (!stop) {
        return MsgFlush::kIdInvalid;
    }
    return (stop? iNextFlushId : MsgFlush::kIdInvalid);
}

TBool ProtocolFile::TryGet(IWriter& /*aWriter*/, TUint /*aStreamId*/, TUint64 /*aOffset*/, TUint /*aBytes*/)
{
    return false;
}

Brn ProtocolFile::Read(TUint aBytes)
{
    return iReaderBuf.Read(aBytes);
}

Brn ProtocolFile::ReadUntil(TByte aSeparator)
{
    return iReaderBuf.ReadUntil(aSeparator);
}

void ProtocolFile::ReadFlush()
{
    iReaderBuf.ReadFlush();
}

void ProtocolFile::ReadInterrupt()
{
    iReaderBuf.ReadInterrupt();
}

Brn ProtocolFile::ReadRemaining()
{
    return iReaderBuf.Snaffle();
}
