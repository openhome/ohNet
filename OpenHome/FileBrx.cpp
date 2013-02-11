#include <OpenHome/Private/File.h>

namespace OpenHome {

FileBrx::FileBrx(const Brx* aBuffer)
    : iBuffer(aBuffer)
    , iCursor(0)
{
}

FileBrx::~FileBrx()
{
    delete iBuffer;
}

TUint32 FileBrx::Bytes()
{
    return iBuffer->Bytes();
}

TUint32 FileBrx::Tell() const
{
    return iCursor;
}

void FileBrx::Read(Bwx& aBuffer)
{
    Read(aBuffer, aBuffer.MaxBytes());
}

void FileBrx::Read(Bwx& aBuffer, TUint32 aBytes)
{
    ASSERT(aBytes <= aBuffer.MaxBytes());
    TUint32 bytes = ( iCursor + aBytes > Bytes() ? Bytes() - iCursor : aBytes );
    aBuffer.Replace(iBuffer->Split(iCursor, bytes));
    iCursor += bytes;
}

void FileBrx::Write(const Brx& aBuffer)
{
    Write(aBuffer, aBuffer.Bytes());
}

void FileBrx::Write(const Brx& /*aBuffer*/, TUint32 /*aBytes*/)
{
    THROW(FileWriteError);
}

void FileBrx::Seek(TInt32 aBytes, SeekWhence aWhence)
{
    TInt proposedCursor;

    switch(aWhence)
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

    if ( proposedCursor < 0 || proposedCursor > (TInt) Bytes() )
        THROW(FileSeekError);

    iCursor = proposedCursor;
}

} // namespace OpenHome

