#include <OpenHome/Media/Protocol/ProtocolFile.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Stream.h>

#include <stdlib.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ProtocolFile

ProtocolFile::ProtocolFile(Environment& aEnv)
    : Protocol(aEnv)
    , iLock("PRTF")
    , iReaderBuf(iFileStream)
{
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
            ASSERTS();
        }
        iLock.Signal();
    }

    iFileStream.CloseFile();
    if (contentProcessor != NULL) {
        contentProcessor->Reset();
    }
    return res;
}

EStreamPlay ProtocolFile::OkToPlay(TUint aTrackId, TUint aStreamId)
{
    return iIdProvider->OkToPlay(aTrackId, aStreamId);
}

TUint ProtocolFile::TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset)
{
    iLock.Wait();
    const TBool streamIsValid = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
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

TUint ProtocolFile::TryStop(TUint aTrackId, TUint aStreamId)
{
    iLock.Wait();
    const TBool stop = (iProtocolManager->IsCurrentTrack(aTrackId) && iStreamId == aStreamId);
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
