#include <OpenHome/Private/File.h>

using namespace OpenHome;

FileBrx::FileBrx(const Brx& aBuffer)
    : iBuffer(aBuffer)
    , iCursor(0)
{
}

FileBrx::FileBrx(const TChar* aBuffer)
    : iBuffer(aBuffer)
    , iCursor(0)
{
}

TUint32 FileBrx::Bytes() const
{
    return iBuffer.Bytes();
}

TUint32 FileBrx::Tell() const
{
    return iCursor;
}

void FileBrx::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.BytesRemaining());
}

void FileBrx::Read(Bwx& aBuffer, TUint32 aBytes)
{
    // IFile implementations must check read length
    ASSERT(aBytes);
    ASSERT(aBytes <= aBuffer.BytesRemaining());
    TUint32 bytes = (iCursor + aBytes > Bytes() ? Bytes() - iCursor : aBytes);
    if ( bytes == 0 )
        THROW(FileReadError);
    aBuffer.Append(iBuffer.Split(iCursor, bytes));
    iCursor += bytes;
}

void FileBrx::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void FileBrx::Write(const Brx& aBuffer, TUint32 aBytes)
{
    // IFile implementations must check write length
    ASSERT(aBytes);
    ASSERT(aBytes <= aBuffer.Bytes());
    THROW(FileWriteError);
}

void FileBrx::Seek(TInt32 aBytes, SeekWhence aWhence)
{
    TInt proposedCursor;
    switch (aWhence)
    {
        case eSeekFromStart:
            proposedCursor = aBytes;
            break;
        case eSeekFromCurrent:
            proposedCursor = iCursor + aBytes;
            break;
        case eSeekFromEnd:
            proposedCursor = Bytes() + aBytes;
            break;
        default:
            THROW(FileSeekError);
    }

    if (proposedCursor < 0 || proposedCursor > (TInt)Bytes())
        THROW(FileSeekError);

    iCursor = proposedCursor;
}

void FileBrx::Flush()
{
}

void FileBrx::Sync()
{
}
