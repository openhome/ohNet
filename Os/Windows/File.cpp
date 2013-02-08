#include <OpenHome/Private/File.h>
#include <OpenHome/Exception.h>
#include <cstdio>

namespace OpenHome {

class FileAnsii : public IFile
{
public:
    FileAnsii(const TChar* aFilename, FileMode aFileMode);
    virtual ~FileAnsii();

    virtual void Read(Bwx& aBuffer);
    virtual void Read(Bwx& aBuffer, TUint aBytes);

    virtual void Write(const Brx& aBuffer);
    virtual void Write(const Brx& aBuffer, TUint32 aBytes);

    virtual void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    virtual TUint32 Tell() const;
    virtual TUint32 Bytes();
private:
    FILE* iFilePtr;
};

IFile* IFile::Open(const TChar* aFilename, FileMode aFileMode)
{
    return new FileAnsii(aFilename, aFileMode);
}

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

