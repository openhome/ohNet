#include <OpenHome/Private/File.h>
#include <cstdio>
using namespace OpenHome;

IFile* FileSystemAnsii::Open(const TChar* aFilename, FileMode aFileMode)
{
    return new FileAnsii(aFilename, aFileMode);
}

FileAnsii::FileAnsii(const TChar* aFilename, FileMode aFileMode)
    : iFilePtr(NULL)
{
    switch (aFileMode)
    {
        case eFileReadOnly:
            iFilePtr = fopen(aFilename, "rb");
            break;
        case eFileReadWrite:
            iFilePtr = fopen(aFilename, "wb");
            break;
        default:
            iFilePtr = NULL;
            break;
    }

    if (iFilePtr == NULL)
        THROW(FileOpenError);
}

FileAnsii::~FileAnsii()
{
    ASSERT(fclose(iFilePtr) != EOF);
}

void FileAnsii::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.BytesRemaining());
}

void FileAnsii::Read(Bwx& aBuffer, TUint32 aBytes)
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

void FileAnsii::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void FileAnsii::Write(const Brx& aBuffer, TUint32 aBytes)
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

void FileAnsii::Seek(TInt32 aBytes, SeekWhence aWhence)
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

TUint32 FileAnsii::Tell() const
{
    return ftell(iFilePtr);
}

TUint32 FileAnsii::Bytes() const
{
    FileAnsii* self = const_cast<FileAnsii*>(this);
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

void FileAnsii::Flush()
{
    ASSERT(iFilePtr);
    std::fflush(iFilePtr);
}
