// IDv3 container
// Based on description from http://id3.org/id3v2.3.0

#include <OpenHome/Media/Codec/Id3v2.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Av/Debug.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

Id3v2::Id3v2()
{
}

void Id3v2::Initialise()
{
    iSize = 0;
}

TBool Id3v2::Recognise()
{
    Bws<10> data;
    iContainer->Read(data, 0, 10);
    if (data.Bytes() < 10) {
        return false;
    }
    static const char* kContainerStart = "ID3";
    if (strncmp((const TChar*)(data.Ptr()), kContainerStart, sizeof(kContainerStart)-1) != 0) {
        return false;
    }
    if (data[3] > 4) { // We only support upto Id3v2.4
        return false;
    }
    const TBool hasFooter = ((data[5] & 0x10) != 0); // FIXME - docs suggest this is an experimental field rather than footer indicator
    // remaining 4 bytes give the size of container data
    // bit 7 of each byte must be zero (to avoid being mistaken for the sync frame of mp3)
    // ...so each byte only holds 7 bits of sizing data
    for (TUint i=6; i<10; i++) {
        if ((data[i] & 0x80) != 0) {
            return false;
        }
    }
    
    iSize = ((data[6] << 21) | (data[7] << 14) | (data[8] << 7) | data[9]);
    iSize += 10; // for header
    if(hasFooter) {
        iSize += 10; // for footer if present
    }
    LOG(kMedia, "Id3v2 header found: %d bytes\n", iSize);
    return true;
}

TUint Id3v2::Size()
{
    return iSize;
}

TBool Id3v2::AppendDuringSeek()
{
    return true;
}

TUint Id3v2::Process()
{
    TUint prevTagSize = iSize;
    TUint nextTagSize = 0;
    if (Recognise()) {
        nextTagSize = iSize;
        iSize += prevTagSize;
        LOG(kMedia, "Id3v2::Process found next set of tags; size: %u\n", nextTagSize);
        return nextTagSize; // amount to be removed
    }
    return 0;
}

TUint Id3v2::Split()
{
    return 0;
}
