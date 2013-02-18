// IDv3 container
// Based on description from http://id3.org/id3v2.3.0

#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

Id3v2::Id3v2(IContainer& aContainer)
{
    Bws<10> data;
    aContainer.Read(data, 0, 10);
    if (data.Bytes() < 10) {
        THROW(MediaCodecId3v2NotFound); 
    }
    static const char* kContainerStart = "ID3";
    if (strncmp((const TChar*)(data.Ptr()), kContainerStart, sizeof(kContainerStart)-1) != 0) {
        THROW(MediaCodecId3v2NotFound); 
    }
    if (data[3] > 4) { // We only support upto Id3v2.4
        THROW(MediaCodecId3v2NotFound);
    }
    const TBool hasFooter = ((data[5] & 0x10) != 0); // FIXME - docs suggest this is an experimental field rather than footer indicator
    // remaining 4 bytes give the size of container data
    // bit 7 of each byte must be zero (to avoid being mistaken for the sync frame of mp3)
    // ...so each byte only holds 7 bits of sizing data
    for (TUint i=6; i<10; i++) {
        if ((data[i] & 0x80) != 0) {
            THROW(MediaCodecId3v2NotFound);
        }
    }
    
    iContainerSize = ((data[6] << 21) | (data[7] << 14) | (data[8] << 7) | data[9]);
    iContainerSize += 10; // for header
    if(hasFooter) {
        iContainerSize += 10; // for footer if present
    }
    LOG(kMedia, "Id3v2 header found: %d bytes\n", iContainerSize);
}

TUint32 Id3v2::ContainerSize() const
{
    return iContainerSize;
}

/*
// FIXME - code retained just until it can be copied into a new home
TUint Id3v2::BeUint32At(const Brx& aBuf, TUint aIndex)
{ // FIXME - duplicated code.  Needs a home somewhere; preferably not back in Brx; possibly in ohNet's Converter class?
    TUint b[4];
    for (TUint i=0; i<4; i++) {
        b[i] = aBuf[aIndex++];
    }
    return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}*/
