#ifndef HEADER_FILE
#define HEADER_FILE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <cstdio>

EXCEPTION(FileOpenError);
EXCEPTION(FileCloseError);
EXCEPTION(FileReadError);
EXCEPTION(FileWriteError);
EXCEPTION(FileSeekError);

namespace OpenHome {

typedef enum {
    eSeekFromStart,
    eSeekFromCurrent,
    eSeekFromEnd
} SeekWhence;

typedef enum {
    eFileReadOnly,
    eFileReadWrite,
} FileMode;

class IFile 
{
public:

    static IFile* Open(const TChar* aFilename, FileMode aFileMode);

    virtual ~IFile() {}

    virtual void Read(Bwx& aBuffer) = 0;
    virtual void Read(Bwx& aBuffer, TUint aBytes) = 0;

    virtual void Write(const Brx& aBuffer) = 0;
    virtual void Write(const Brx& aBuffer, TUint32 aBytes) = 0;

    virtual void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart) = 0;
    virtual TUint32 Tell() const = 0;
    virtual TUint32 Bytes() = 0;
};

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

class FileBrx : public IFile
{
public:
    FileBrx(const Brx* aBuffer);
    virtual ~FileBrx();

    virtual void Read(Bwx& aBuffer);
    virtual void Read(Bwx& aBuffer, TUint aBytes);

    virtual void Write(const Brx& aBuffer);
    virtual void Write(const Brx& aBuffer, TUint32 aBytes);

    virtual void Seek(TInt32 aBytes, SeekWhence aWhence);
    virtual TUint32 Tell() const;
    virtual TUint32 Bytes();
private:
    const Brx*  iBuffer;
    TUint32     iCursor;
};

} // namespace OpenHome

#endif // HEADER_FILE

