#include <OpenHome/Private/File.h>
#include <cstdio>

namespace OpenHome {

FileAnsii::FileAnsii(const TChar* aFilename, FileMode aFileMode)
    : iFilePtr(NULL)
{
    switch ( aFileMode )
    {
        case eFileReadOnly:
            iFilePtr = fopen(aFilename, "rb");
            break;
        default:
            iFilePtr = NULL;
            break;
    }

    if ( iFilePtr == NULL )
        THROW(FileOpenError);
}

FileAnsii::~FileAnsii()
{
    if ( fclose(iFilePtr) == EOF )
        THROW(FileCloseError);
}

void FileAnsii::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.MaxBytes());
}

void FileAnsii::Read(Bwx& aBuffer, TUint32 aBytes)
{
    ASSERT(aBytes <= aBuffer.MaxBytes());

    aBuffer.SetBytes(0);
    // Bwx should have a Ptr() that returns a non-const TByte* (viz. const TByte* Brx::Ptr() const)
    TUint bytesRead = (TUint)fread((void*) aBuffer.Ptr(), 1, aBytes, iFilePtr);

    aBuffer.SetBytes(bytesRead);
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

    switch ( aWhence )
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

    if ( fseek(iFilePtr, aBytes, whence) == -1 )
        THROW(FileSeekError);
}

TUint32 FileAnsii::Tell() const
{
    return ftell(iFilePtr);
}

TUint32 FileAnsii::Bytes()
{
    TUint32 currentPos = Tell();
    Seek(0, eSeekFromEnd);
    TUint32 bytes = Tell();
    Seek(currentPos, eSeekFromStart);
    return bytes;
}

} // namespace OpenHome

