#ifndef HEADER_FILE
#define HEADER_FILE

#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>

#include <cstdio>

EXCEPTION(FileOpenError)
EXCEPTION(FileReadError)
EXCEPTION(FileWriteError)
EXCEPTION(FileSeekError)

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
public:
    virtual ~IFile() {}
    virtual void Read(Bwx& aBuffer) = 0;                        // Fills remaining bytes in aBuffer, or throws FileReadError
    virtual void Read(Bwx& aBuffer, TUint aBytes) = 0;          // Appends aBytes or throws FileReadError
    virtual void Write(const Brx& aBuffer) = 0;                 // Writes all buffer bytes, or throws FileWriteError
    virtual void Write(const Brx& aBuffer, TUint32 aBytes) = 0; // Writes aBytes, or throws FileWriteError
    virtual void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart) = 0; // Seeks, or throws FileSeekError
    virtual TUint32 Tell() const = 0;                           // Current position in file
    virtual TUint32 Bytes() const = 0;                          // Size of file
};

// IFileSystem
class IFileSystem
{
public:
    virtual IFile* Open(const TChar* aFilename, FileMode aFileMode) = 0; // throws FileOpenError
    virtual ~IFileSystem() {}
};

class FileSystemAnsii : public IFileSystem
{
public: // IFileSystem
    IFile* Open(const TChar* aFilename, FileMode aFileMode);
};

class FileAnsii : public IFile
{
public:
    FileAnsii(const TChar* aFilename, FileMode aFileMode);
    ~FileAnsii();
public: // from IFile
    void Read(Bwx& aBuffer);
    void Read(Bwx& aBuffer, TUint aBytes);
    void Write(const Brx& aBuffer);
    void Write(const Brx& aBuffer, TUint32 aBytes);
    void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    TUint32 Tell() const;
    TUint32 Bytes() const;
private:
    FILE* iFilePtr;
};

class FileBrx : public IFile
{
public:
    FileBrx(const Brx& aBuffer);
    FileBrx(const TChar* aBuffer); // aBuffer is file content, not file name
public: // from IFile
    void Read(Bwx& aBuffer);
    void Read(Bwx& aBuffer, TUint aBytes);
    void Write(const Brx& aBuffer);
    void Write(const Brx& aBuffer, TUint32 aBytes);
    void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    TUint32 Tell() const;
    TUint32 Bytes() const;
private:
    Brn     iBuffer;
    TUint32 iCursor;
};

class FileStream : public IWriter, public IReaderSource
{
public:
    FileStream();
    FileStream(const TChar* aFilename, FileMode aFileMode);
    void OpenFile(const TChar* aFilename, FileMode aFileMode);
    void SetFile(IFile* aFile);
    void CloseFile();
    void Interrupt(TBool aInterrupt);
    void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    TUint32 Tell() const;
    TUint32 Bytes() const;
public: // from IWriter
    void Write(TByte aValue);
    void Write(const Brx& aBuffer);
    void WriteFlush();
public: // from IReaderSource
    void Read(Bwx& aBuffer);
    void ReadFlush();
    void ReadInterrupt();
private:
    IFile* iFile;
    Mutex iLock;
    TBool iInterrupt;
    TUint iSize;
    TUint iPos;
};

} // namespace OpenHome

#endif // HEADER_FILE

