#include <OpenHome/Private/File.h>
#include <OpenHome/Exception.h>
#include <cstdio>

namespace OpenHome {

static inline THandle ToHandle(FILE* aFile)
{
    return (THandle) aFile;
}

static inline FILE* ToFile(THandle aHandle)
{
    return (FILE*) aHandle;
}

File::File(const char* aFilename, IFile::FileMode aFileMode)
    : iHandle(0)
{
    FILE* filePtr;

    switch ( aFileMode )
    {
        case eFileReadOnly:
            filePtr = fopen(aFilename, "rb");
            break;
        default:
            filePtr = NULL;
            break;
    }

    if ( filePtr == NULL )
        THROW(FileOpenError);

    iHandle = ToHandle(filePtr);
}

File::~File()
{
    if ( fclose(ToFile(iHandle)) == EOF )
        THROW(FileCloseError);
}

void File::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.MaxBytes());
}

void File::Read(Bwx& aBuffer, TUint32 aBytes)
{
    ASSERT(aBytes <= aBuffer.MaxBytes());

    aBuffer.SetBytes(0);
    // Bwx should have a Ptr() that returns a non-const TByte* (viz. const TByte* Brx::Ptr() const)
    size_t bytesRead = fread((void*) aBuffer.Ptr(), aBytes, 1, ToFile(iHandle));

    aBuffer.SetBytes(bytesRead);
}

void File::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void File::Write(const Brx& aBuffer, TUint32 aBytes)
{
    THROW(FileWriteError);
}

void File::Seek(TInt32 aBytes, IFile::SeekWhence aWhence)
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

    if ( fseek(ToFile(iHandle), aBytes, whence) == -1 )
        THROW(FileSeekError);
}

TUint32 File::Tell() const
{
    return ftell(ToFile(iHandle));
}

TUint32 File::Bytes()
{
    TUint32 currentPos = Tell();
    Seek(0, eSeekFromEnd);
    TUint32 bytes = Tell();
    Seek(currentPos, eSeekFromStart);
    return bytes;
}

} // namespace OpenHome

