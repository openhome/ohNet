#include <OpenHome/Private/File.h>
#include <cstdio>
#include <cerrno>

#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace OpenHome;

IFile* FileSystemAnsi::Open(const TChar* aFilename, FileMode aFileMode)
{
    return new FileAnsi(aFilename, aFileMode);
}

void FileSystemAnsi::MakeDir(const TChar* aDirname)
{
#if defined(_WIN32)
    const int error = _mkdir(aDirname);
#else
    const int error = mkdir(aDirname, 0777);
#endif
    if (error == -1) {
        THROW(MakeDirFailed);
    }
}

void FileSystemAnsi::Unlink(const TChar* aFilename)
{
    const int error = remove(aFilename);
    if (error != 0) {
        THROW(UnlinkFailed);
    }
}

FileAnsi::FileAnsi(const TChar* aFilename, FileMode aFileMode)
    : iFilePtr(NULL)
{
    switch (aFileMode)
    {
        case eFileReadOnly:
            iFilePtr = fopen(aFilename, "rb");
            break;
        case eFileReadWrite:
            iFilePtr = fopen(aFilename, "r+b");
            break;
        case eFileWriteOnly:
            iFilePtr = fopen(aFilename, "wb");
            break;
        case eFileReadWriteCreateIfNotExist:
            iFilePtr = fopen(aFilename, "r+b");
            if (iFilePtr == NULL)
            {
                iFilePtr = fopen(aFilename, "w+b");
            }
            break;
        default:
            iFilePtr = NULL;
            break;
    }

    if (iFilePtr == NULL)
        THROW(FileOpenError);
}

FileAnsi::~FileAnsi()
{
    ASSERT(fclose(iFilePtr) != EOF);
}

void FileAnsi::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.BytesRemaining());
}

void FileAnsi::Read(Bwx& aBuffer, TUint32 aBytes)
{
    // IFile implementations must check read length
    ASSERT(aBytes);
    // Check there's enough space in read buffer
    ASSERT(aBytes <= aBuffer.BytesRemaining());
    // Find read pointer
    TByte* p = const_cast<TByte*>(aBuffer.Ptr()) + aBuffer.Bytes();
    // Do the read
    TUint bytesRead = (TUint)fread(p, 1, aBytes, iFilePtr);
    // Register the new content with the buffer
    aBuffer.SetBytes(aBuffer.Bytes() + bytesRead);
    // throw if entire read wasn't performed
    if ( bytesRead == 0 )
        THROW(FileReadError);
}

void FileAnsi::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void FileAnsi::Write(const Brx& aBuffer, TUint32 aBytes)
{
    // IFile implementations must check write length
    ASSERT(aBytes);
    // Check we have enough bytes
    ASSERT(aBuffer.Bytes() >= aBytes);
    // Do the write
    TUint bytesWritten = (TUint)fwrite(aBuffer.Ptr(), 1, aBytes, iFilePtr);
    // throw if entire write was not performed
    if ( bytesWritten != aBytes )
        THROW(FileWriteError);
}

void FileAnsi::Seek(TInt32 aBytes, SeekWhence aWhence)
{
    int whence;
    switch (aWhence)
    {
        case eSeekFromStart:
            whence = SEEK_SET;
            break;
        case eSeekFromCurrent:
            whence = SEEK_CUR;
            break;
        case eSeekFromEnd:
            whence = SEEK_END;
            break;
        default:
            THROW(FileSeekError);
            break;
    }

    if (fseek(iFilePtr, aBytes, whence) == -1)
        THROW(FileSeekError);
}

TUint32 FileAnsi::Tell() const
{
    return ftell(iFilePtr);
}

TUint32 FileAnsi::Bytes() const
{
    FileAnsi* self = const_cast<FileAnsi*>(this);
    TUint32 currentPos = self->Tell();
    TUint32 bytes = 0;
    try {
        self->Seek(0, eSeekFromEnd);
        bytes = Tell();
        self->Seek(currentPos, eSeekFromStart);
    }
    catch(FileSeekError&) {
        // its not reasonable to expect clients to cope with a size querying function throwing and leaving the object in a different, indeterminate, state
        ASSERTS();
    }
    return bytes;
}

void FileAnsi::Flush()
{
    ASSERT(iFilePtr);
    std::fflush(iFilePtr);
}
