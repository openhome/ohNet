#ifndef HEADER_FILE
#define HEADER_FILE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

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

class IFileSeekable
{
public:
    virtual void Seek(TInt32 aBytes, SeekWhence aWhence) = 0;
    virtual TUint32 Tell() const = 0;
    virtual TUint32 Bytes() = 0;
};

class IFileReadable
{
public:
    virtual void Read(Bwx& aBuffer) = 0;
    virtual void Read(Bwx& aBuffer, TUint32 aBytes) = 0;
};

class IFileWriteable
{
public:
    virtual void Write(const Brx& aBuffer) = 0;
    virtual void Write(const Brx& aBuffer, TUint32 aBytes) = 0;
};

class File : public IFileSeekable, public IFileReadable, public IFileWriteable
{
public:
    File(const TChar* aFilename, FileMode aFileMode);
    virtual ~File();

    virtual void Read(Bwx& aBuffer);
    virtual void Read(Bwx& aBuffer, TUint aBytes);

    virtual void Write(const Brx& aBuffer);
    virtual void Write(const Brx& aBuffer, TUint32 aBytes);

    virtual void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    virtual TUint32 Tell() const;
    virtual TUint32 Bytes();
protected:
    THandle iHandle;
};

} // namespace OpenHome

#endif // HEADER_FILE

