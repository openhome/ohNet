#include <OpenHome/Private/File.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Stream.h>

using namespace OpenHome;

FileStream::FileStream()
    : iFile(NULL)
    , iLock("FSTR")
    , iInterrupt(false)
{
}

void FileStream::OpenFile(const TChar* aFilename, FileMode aFileMode)
{
    ASSERT(iFile != NULL);
    iFile = IFile::Open(aFilename, aFileMode);
}

void FileStream::SetFile(IFile* aFile)
{
    ASSERT(iFile == NULL);
    iFile = aFile;
}

void FileStream::CloseFile()
{
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
    iFile->Read(aBuffer);
}

void FileStream::ReadFlush()
{
    // FIXME - should this do nothing or seek to the start of the file?
}

void FileStream::ReadInterrupt()
{
    Interrupt(true);
}
