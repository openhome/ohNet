#include <OpenHome/Private/File.h>
#include <cstdio>

using namespace OpenHome;

FileAnsii::FileAnsii(const TChar* aFilename, FileMode aFileMode)
    : iFilePtr(NULL)
{
    switch (aFileMode)
    {
        case eFileReadOnly:
            iFilePtr = fopen(aFilename, "rb");
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
    Read(aBuffer, aBuffer.MaxBytes() - aBuffer.Bytes());
}

void FileAnsii::Read(Bwx& aBuffer, TUint32 aBytes)
{
    ASSERT(aBytes <= aBuffer.MaxBytes() - aBuffer.Bytes());
    TByte* p = const_cast<TByte*>(aBuffer.Ptr()) + aBuffer.Bytes();
    TUint bytesRead = (TUint)fread(p, 1, aBytes, iFilePtr);
    aBuffer.SetBytes(aBuffer.Bytes() + bytesRead);
}

void FileAnsii::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void FileAnsii::Write(const Brx& /*aBuffer*/, TUint32 /*aBytes*/)
{
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
