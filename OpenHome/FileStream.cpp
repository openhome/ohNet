#include <OpenHome/Private/File.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;

FileStream::FileStream()
    : iFile(NULL)
    , iLock("FSTR")
    , iInterrupt(false)
    , iSize(0)
    , iPos(0)
{
}

FileStream::FileStream(const TChar* aFilename, FileMode aFileMode)
    : iFile(IFile::Open(aFilename, aFileMode))
    , iLock("FSTR")
    , iInterrupt(false)
    , iSize(Bytes())
    , iPos(Tell())
{
}


void FileStream::OpenFile(const TChar* aFilename, FileMode aFileMode)
{
    ASSERT(iFile == NULL);
    iFile = IFile::Open(aFilename, aFileMode);
    iSize = Bytes();
    iPos = Tell();
}

void FileStream::SetFile(IFile* aFile)
{
    /* Don't assert that iFile is NULL.  We want to allow replacement of stack-allocated
       FileBrx instances so can't assume that failure to call CloseFile when switching
       the source of a stream is an error. */
    iFile = aFile;
    iSize = Bytes();
    iPos = Tell();
}

void FileStream::CloseFile()
{
    ASSERT(iFile != NULL);
    iLock.Wait();
    delete iFile;
    iFile = NULL;
    iLock.Signal();
}

void FileStream::Interrupt(TBool aInterrupt)
{
    ASSERT(iFile != NULL);
    iLock.Wait();
    iInterrupt = aInterrupt;
    iLock.Signal();
}

void FileStream::Seek(TInt32 aBytes, SeekWhence aWhence)
{
    ASSERT(iFile != NULL);
    iFile->Seek(aBytes, aWhence);
    iPos = aBytes;
}

TUint32 FileStream::Tell() const
{
    ASSERT(iFile != NULL);
    return iFile->Tell();
}

TUint32 FileStream::Bytes() const
{
    ASSERT(iFile != NULL);
    return iFile->Bytes();
}

void FileStream::Write(TByte aValue)
{
    Brn buf(&aValue, 1);
    Write(buf);
}

void FileStream::Write(const Brx& aBuffer)
{
    ASSERT(iFile != NULL);
    iFile->Write(aBuffer);
    iSize += aBuffer.Bytes();
}

void FileStream::WriteFlush()
{
    ASSERTS();
}

void FileStream::Read(Bwx& aBuffer)
{
    ASSERT(iFile != NULL);
    AutoMutex a(iLock);
    if (iInterrupt) {
        THROW(ReaderError);
    }
    if (iPos == iSize) {
        // already at the end of the stream.  Throw to encourage any upstream buffer out of an endless read loop
        THROW(ReaderError);
    }
    const TUint before = aBuffer.Bytes();
    if (aBuffer.MaxBytes() == before) {
        THROW(ReaderError);
    }
    try {
        iFile->Read(aBuffer);
    }
    catch (FileReadError&) {
        THROW(ReaderError);
    }
    iPos += aBuffer.Bytes() - before;
}

void FileStream::ReadFlush()
{
    // FIXME - should this do nothing or seek to the start of the file?
}

void FileStream::ReadInterrupt()
{
    Interrupt(true);
}
