#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// Mpeg4Box

Mpeg4Box::Mpeg4Box(IContainer& aContainer, Mpeg4Box* aParent, const TChar* aIdName, TUint aOffset)
    : iContainer(&aContainer)
    , iController(NULL)
    , iInput(NULL)
    , iParent(aParent)
    , iBytesRead(0)
    , iBoxSize(0)
    , iOffset(aOffset)
{
    if (iParent != NULL) {
        iOffset = iParent->FileOffset();
    }
    ExtractHeaderId();
    if (aIdName != NULL) {
        FindBox(aIdName);
    }
}

Mpeg4Box::Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent, const TChar* aIdName)
    : iContainer(NULL)
    , iController(&aController)
    , iInput(NULL)
    , iParent(aParent)
    , iBytesRead(0)
    , iBoxSize(0)
    , iOffset(0)
{
    ExtractHeaderId();
    if (aIdName != NULL)
        FindBox(aIdName);
}

Mpeg4Box::Mpeg4Box(const Brx& aBuffer, Mpeg4Box* aParent, const TChar* aIdName, TUint aOffset)
    : iContainer(NULL)
    , iController(NULL)
    , iInput(&aBuffer)
    , iParent(aParent)
    , iBytesRead(0)
    , iBoxSize(0)
    , iOffset(aOffset)
{
    if (iParent != NULL) {
        iOffset = iParent->FileOffset();
    }
    ExtractHeaderId();
    if (aIdName != NULL)
        FindBox(aIdName);
}

Mpeg4Box::~Mpeg4Box()
{
}

TBool Mpeg4Box::FindBox(const TChar* aIdName)
{
    if (iParent == NULL) {
        // We don't have a parent, so don't have bounds for searching.
        ASSERTS();
        return false;
    }
    while (!iParent->Empty()) {
        if (Match(aIdName)) {
            //LOG(kCodec, "Mpeg4 box found %d (", iBoxSize);
            //LOG_HEX(kCodec, iId);
            //LOG(kCodec, ")\n");
            return true;            // found required id
        }
        SkipEntry();                // skip over this entry
        iOffset += iBytesRead;      // Starting a new box, so update offset.
        Reset();
        ExtractHeaderId();
    }
    return false;
}

void Mpeg4Box::Reset()
{
    // No need to reset parent; only want to reset box-specific data.
    iId.SetBytes(0);
    iBytesRead = 0;
    iBoxSize = 0;
}

TBool Mpeg4Box::Empty()
{ 
//    LOG(kCodec, "  Empty? %d > %d \n", iBoxSize, BytesRead());
    if (iBoxSize == 0 && iBytesRead == 0) {
        return false;
    }
    return (iBoxSize > iBytesRead ? false : true);
}

void Mpeg4Box::ExtractHeaderId()
{
    iBuf.SetBytes(0);
    Read(iBuf, 4);
    iBoxSize = Converter::BeUint32At(iBuf, 0);
    iId.SetBytes(0);
    Read(iId, 4);
    //LOG(kCodec, "Mpeg4 header %u (", iBoxSize);
    //LOG(kCodec, iId);
    //LOG(kCodec, ")\n");
}

void Mpeg4Box::Read(Bwx& aData, TUint aBytes)
{
   if (iContainer) {
       iContainer->Read(aData, iOffset+iBytesRead, aBytes);
   }
   else if (iController) {
       iController->Read(aData, aBytes);
   }
   else { // Reading from a buffer.
       // If we're reading from a buffer, check we have enough data for this read.
       // Otherwise, we're likely trying to process a non-MPEG4 file.
       if (iOffset+iBytesRead+aBytes > iInput->Bytes()) {
           //LOG(kCodec, "Mpeg4Box::ExtractHeaderId bytes read: %u, iInput: %u\n", iOffset+iBytesRead+aBytes, iInput->Bytes());
           THROW(MediaMpeg4FileInvalid);
       }
       aData.Replace(iInput->Ptr()+iOffset+iBytesRead, aBytes);
   }
   UpdateBytesRead(aBytes);
}

void Mpeg4Box::UpdateBytesRead(TUint aBytes)
{
   iBytesRead += aBytes;
   if (iParent != NULL) {
       iParent->UpdateBytesRead(aBytes);
   }
}

void Mpeg4Box::SkipEntry()
{
    //LOG(kCodec, " SkipEntry %d, %d\n", iBoxSize, iBytesRead);
    TUint bytesRemaining = iBoxSize - iBytesRead;

    if (bytesRemaining > 0) {
        Skip(bytesRemaining);
    }
}

void Mpeg4Box::Skip(TUint32 aBytes)
{
    TUint bytesRemaining = aBytes;
    TUint readBytes;

    if (iBytesRead == iBoxSize) {
        return;
    }

    while (bytesRemaining > 0) {
        iBuf.SetBytes(0);
        readBytes = iBuf.MaxBytes();
        if (bytesRemaining < iBuf.MaxBytes()) {
            readBytes = bytesRemaining;
        }
        Read(iBuf, readBytes);
        bytesRemaining -= readBytes;
    }
}

TBool Mpeg4Box::Match(const TChar* aIdName)
{

    if (iId == Brn(aIdName)) {
        //LOG(kCodec, " Match \"%s\" {", aIdName);
        //LOG(kCodec, iId);
        //LOG(kCodec, "}\n");
        return true;
    }
    else {
        return false;   
    }
}

const Brx& Mpeg4Box::Id() const
{
    return iId;
}

TUint Mpeg4Box::BoxSize() const
{
    return iBoxSize;
}

TUint Mpeg4Box::BytesRead() const
{
    return iBytesRead;
}

TUint Mpeg4Box::Offset() const
{
    return iOffset;
}

TUint Mpeg4Box::FileOffset() const
{
    return iOffset+iBytesRead;
}


// Mpeg4

Mpeg4::Mpeg4(IContainer& aContainer)
{
    //LOG(kCodec, "Mpeg4::Mpeg4\n");
    Bws<100> data;
    Bws<4> codec;

    // Read an MPEG4 header until we reach the mdia box.
    // The mdia box contains children with media info about a track.

    Mpeg4Box BoxL0(aContainer);
    if (!BoxL0.Match("ftyp")) {
        //LOG(kCodec, " no ftyp found at start of file\n");
        THROW(MediaMpeg4FileInvalid);
    }
    BoxL0.SkipEntry();

    // data could be stored in different orders in the file but ftyp & moov must come before mdat

    for (;;) {                              // keep on reading until start of data found
        Mpeg4Box BoxL1(aContainer, NULL, NULL, BoxL0.FileOffset());
        if(BoxL1.Match("moov")) {
            // Search through levels until we find mdia box;
            // the container for media info.
            Mpeg4Box BoxL2(aContainer, &BoxL1, "trak");
            Mpeg4Box BoxL3(aContainer, &BoxL2);
            TBool foundMdia = BoxL3.FindBox("mdia");
            if (foundMdia) {
                // Should be pointing at mdhd box, for media
                // data to be extracted from.
                iContainerSize = BoxL3.FileOffset();
                //LOG(kCodec, "Mpeg4Box::Mpeg4Box found mdia, iContainerSize: %u\n", iContainerSize);
                return;
            }
            else {
                THROW(MediaMpeg4FileInvalid);
            }
        } else if(BoxL1.Match("pdin")) {
            // ignore this one
        } else if(BoxL1.Match("moof")) {
            // ignore this one
        } else if(BoxL1.Match("mfra")) {
            // ignore this one
        } else if(BoxL1.Match("free")) {
            // ignore this one
        } else if(BoxL1.Match("skip")) {
            // ignore this one
        } else if(BoxL1.Match("meta")) {
            // ignore this one
        } else {
            //LOG(kCodec, "Mpeg4 Invalid File\n");
            THROW(MediaMpeg4FileInvalid);
        }
        BoxL1.SkipEntry();  // skip to next entry
    }
}

Mpeg4::~Mpeg4()
{
    //LOG(kCodec, "Mpeg4::~Mpeg4\n");
}

TUint Mpeg4::ContainerSize() const
{
    return iContainerSize;
}
