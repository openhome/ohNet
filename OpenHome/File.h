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
EXCEPTION(MakeDirFailed)
EXCEPTION(UnlinkFailed)

namespace OpenHome {

typedef enum {
    eSeekFromStart,
    eSeekFromCurrent,
    eSeekFromEnd
} SeekWhence;

typedef enum {
    eFileReadOnly,
    eFileReadWrite,
    eFileWriteOnly,
    eFileReadWriteCreateIfNotExist,
} FileMode;

class IFile
{
public:
    static IFile* Open(const TChar* aFilename, FileMode aFileMode);
public:
    virtual ~IFile() {}
    // Read/Write methods MUST assert that client code is requesting a read/write length that is:
    //  * non-zero
    //  * satisfiable with the buffer provided
    // Read methods throw FileReadError if zero bytes can be read.
    // Write methods throw FileWriteError if write cannot complete, or file is opened as eFileReadOnly
    virtual void Read(Bwx& aBuffer) = 0;                        // Fills remaining bytes in aBuffer.
    virtual void Read(Bwx& aBuffer, TUint aBytes) = 0;          // Appends aBytes to aBuffer.
    virtual void Write(const Brx& aBuffer) = 0;                 // Writes all buffer bytes, or throws FileWriteError
    virtual void Write(const Brx& aBuffer, TUint32 aBytes) = 0; // Writes aBytes, or throws FileWriteError
    virtual void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart) = 0; // Seeks, or throws FileSeekError
    virtual TUint32 Tell() const = 0;                           // Current position in file
    virtual TUint32 Bytes() const = 0;                          // Size of file
    virtual void Flush() = 0;                                   // Ensure file changes visible to other IFiles (fflush)
    virtual void Sync() = 0;                                    // Ensure file changes written to disk (fsync/_commit)
};

// IFileSystem
class IFileSystem
{
public:
    virtual IFile* Open(const TChar* aFilename, FileMode aFileMode) = 0; // throws FileOpenError
    virtual void MakeDir(const TChar* aDirname) = 0; // throws DirAlreadyExists
    virtual void Unlink(const TChar* aFilename) = 0;
    virtual ~IFileSystem() {}
};

class FileSystemAnsi : public IFileSystem
{
public: // IFileSystem
    IFile* Open(const TChar* aFilename, FileMode aFileMode);
    void MakeDir(const TChar* aDirname); // throws DirAlreadyExists
    void Unlink(const TChar* aFilename);
};

class FileAnsi : public IFile
{
public:
    FileAnsi(const TChar* aFilename, FileMode aFileMode);
    ~FileAnsi();
public: // from IFile
    void Read(Bwx& aBuffer);
    void Read(Bwx& aBuffer, TUint aBytes);
    void Write(const Brx& aBuffer);
    void Write(const Brx& aBuffer, TUint32 aBytes);
    void Seek(TInt32 aBytes, SeekWhence aWhence = eSeekFromStart);
    TUint32 Tell() const;
    TUint32 Bytes() const;
    void Flush();
    void Sync();
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
    void Flush();
    void Sync();
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

