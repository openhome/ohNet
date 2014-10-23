#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// Mpeg4Box

Mpeg4Box::Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent, const TChar* aIdName)
    : iController(&aController)
    , iInput(NULL)
    , iParent(aParent)
    , iIdName(aIdName)
    , iBytesRead(0)
    , iBoxSize(0)
    , iOffset(0)
{
}

Mpeg4Box::Mpeg4Box(const Brx& aBuffer, Mpeg4Box* aParent, const TChar* aIdName, TUint aOffset)
    : iController(NULL)
    , iInput(&aBuffer)
    , iParent(aParent)
    , iIdName(aIdName)
    , iBytesRead(0)
    , iBoxSize(0)
    , iOffset(aOffset)
{
    if (iParent != NULL) {
        iOffset = iParent->FileOffset();
    }
}

Mpeg4Box::~Mpeg4Box()
{
}

void Mpeg4Box::Initialise()
{
    ExtractHeaderId();
    if (iIdName != NULL)
        FindBox(iIdName);
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
   if (iController) {
       iController->Read(aData, aBytes);
       if (aData.Bytes() < aBytes) {
           THROW(MediaMpeg4EndOfData);
       }
   }
   else { // Reading from a buffer.
       // If we're reading from a buffer, check we have enough data for this read.
       // Otherwise, we're likely trying to process a non-MPEG4 file.
       if (iOffset+aBytes > iInput->Bytes()) {
           //LOG(kCodec, "Mpeg4Box::ExtractHeaderId bytes read: %u, iInput: %u\n", iOffset+iBytesRead+aBytes, iInput->Bytes());
           THROW(MediaMpeg4FileInvalid);
       }
       aData.Replace(iInput->Ptr()+iOffset, aBytes);
   }
   UpdateBytesRead(aBytes);
}

void Mpeg4Box::UpdateBytesRead(TUint aBytes)
{
   iBytesRead += aBytes;
   iOffset += aBytes;
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
    return iOffset;//+iBytesRead;
}


// SampleSizeTable

SampleSizeTable::SampleSizeTable()
{
}

SampleSizeTable::~SampleSizeTable()
{
    Deinitialise();
}

void SampleSizeTable::Initialise(TUint aCount)
{
    iTable.reserve(aCount);
}

void SampleSizeTable::Deinitialise()
{
    iTable.clear();
}

void SampleSizeTable::AddSampleSize(TUint32 aSize)
{
    if (iTable.size() == iTable.capacity()) {
        THROW(MediaMpeg4FileInvalid);
    }
    iTable.push_back(aSize);
}

TUint32 SampleSizeTable::SampleSize(TUint aEntry)
{
    if(aEntry > iTable.size()-1) {
        THROW(MediaMpeg4FileInvalid);
    }
    return iTable[aEntry];
}

TUint32 SampleSizeTable::Count()
{
    return iTable.capacity();
}


// SeekTable
// Table of samples->chunk->offset required for seeking

SeekTable::SeekTable()
{
}

SeekTable::~SeekTable()
{
    Deinitialise();
}

void SeekTable::InitialiseSamplesPerChunk(TUint aEntries)
{
    iSamplesPerChunk.reserve(aEntries);
}

void SeekTable::InitialiseAudioSamplesPerSample(TUint aEntries)
{
    iAudioSamplesPerSample.reserve(aEntries);
}

void SeekTable::InitialiseOffsets(TUint aEntries)
{
    iOffsets.reserve(aEntries);
}

void SeekTable::Deinitialise()
{
    iSamplesPerChunk.clear();
    iAudioSamplesPerSample.clear();
    iOffsets.clear();
}

void SeekTable::SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk)
{
    TSamplesPerChunkEntry entry = { aFirstChunk, aSamplesPerChunk };
    iSamplesPerChunk.push_back(entry);
}

void SeekTable::SetAudioSamplesPerSample(TUint32 aSampleCount, TUint32 aAudioSamples)
{
    TAudioSamplesPerSampleEntry entry = { aSampleCount, aAudioSamples };
    iAudioSamplesPerSample.push_back(entry);
}

void SeekTable::SetOffset(TUint64 aOffset)
{
    iOffsets.push_back(aOffset);
}

TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint64& aSample)
{
    if (iSamplesPerChunk.size() == 0 || iAudioSamplesPerSample.size() == 0 || iOffsets.size()==0) {
        THROW(CodecStreamCorrupt); // seek table empty - cannot do seek
    }
    aSample = 0;
    // fistly determine the required sample from the audio sample using the stts data,
    // then work through samples per chunk table (stsc data) to get the chunk number for
    // this particular sample, then get the chunk offset from the offset table (stco data)

    // stts:
    TUint64 totalaudiosamples = 0;
    TUint64 totalsamples = 0;
    TUint32 samplecount = 0;
    TUint32 audiosamples = 0;
    for(TUint entry = 0; entry < iAudioSamplesPerSample.size(); entry++) {
        samplecount = iAudioSamplesPerSample[entry].iSampleCount;
        audiosamples = iAudioSamplesPerSample[entry].iAudioSamples;
        if (aAudioSample <= (totalaudiosamples + samplecount * audiosamples)) {
            break; // audio samples are within this range
        }
        totalaudiosamples += samplecount * audiosamples;
        totalsamples = samplecount;
    }
    if (totalaudiosamples!=0 && aAudioSample>totalaudiosamples) {
        aAudioSample = totalaudiosamples-1; // keep within range
    }
    if(audiosamples == 0)
        THROW(CodecStreamCorrupt); // invalid table

    aSample = totalsamples + (aAudioSample - totalaudiosamples)/audiosamples; // convert audio sample count to codec samples

    // stsc:
    // chunk is found by searching to the entry in the table before samples > first chunk
    // and interpolating to get exact chunk
    totalsamples = 0;
    TUint32 nextspc = 0, spc = 0, chunks = 0;
    TUint32 seekchunk = 0, firstchunk = 1, nextchunk = 1;
    for(TUint entry = 0; entry < iSamplesPerChunk.size(); entry++) {
        nextchunk = iSamplesPerChunk[entry].iFirstChunk;
        nextspc = iSamplesPerChunk[entry].iSamples;
        chunks = nextchunk - firstchunk;
        if(aSample < (totalsamples + chunks * spc)) {
            break; // sample is within previous range
        }

        totalsamples += chunks * spc;
        firstchunk = nextchunk;
        spc = nextspc;
    }
    seekchunk = (TUint32) (firstchunk + ((aSample-totalsamples) / spc)); // calculate chunk that this sample is in
    TUint64 adjsample = ((seekchunk - firstchunk) * spc) + totalsamples; // calculate index to first sample in chunk
    aAudioSample -= (aSample - adjsample) * audiosamples;                // adjust audio sample count to index first sample in chunk
    aSample = adjsample;                                                 // adjust codec sample count to index first sample in chunk
    seekchunk -= 1;                                                      // adjust for array index (i.e. -1)

    //stco:
    if(seekchunk >= iOffsets.size()) { // error - required chunk doesn't exist
        THROW(CodecStreamCorrupt); // asserts later on !!! ToDo
    }
    return iOffsets[seekchunk]; // entry found - return offset to required chunk
}


// Mpeg4Start

Mpeg4Start::Mpeg4Start()
{
    LOG(kMedia, "Mpeg4Start::Mpeg4Start\n");
}

TBool Mpeg4Start::Recognise(Brx& aBuf)
{
    LOG(kMedia, "Mpeg4Start::Recognise\n");
    try {
        Bws<100> data;
        Bws<4> codec;
        iSize = 0;
        iContainerStripped = false;

        // Read an MPEG4 header until we reach the mdia box.
        // The mdia box contains children with media info about a track.

        Mpeg4Box BoxL0(aBuf);
        BoxL0.Initialise();
        if (!BoxL0.Match("ftyp")) {
            LOG(kMedia, "Mpeg4Start no ftyp found at start of file\n");
            return false;
        }
        BoxL0.SkipEntry();

        // data could be stored in different orders in the file but ftyp & moov must come before mdat

        for (;;) {      // keep on reading until start of data found
            Mpeg4Box BoxL1(aBuf, &BoxL0, NULL, BoxL0.FileOffset());
            BoxL1.Initialise();
            if(BoxL1.Match("moov")) {
                // Search through levels until we find mdia box;
                // the container for media info.
                Mpeg4Box BoxL2(aBuf, &BoxL1, "trak");
                BoxL2.Initialise();
                Mpeg4Box BoxL3(aBuf, &BoxL2);
                BoxL3.Initialise();
                TBool foundMdia = BoxL3.FindBox("mdia");
                if (foundMdia) {
                    // Should be pointing at mdhd box, for media
                    // data to be extracted from.
                    iSize = BoxL3.FileOffset();
                    LOG(kMedia, "Mpeg4Start::Recognise found mdia, iSize: %u\n", iSize);
                    return true;
                }
                else {
                    return false;
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
                LOG(kMedia, "Mpeg4Start::Recognise invalid atom\n");
                return false;
            }
            BoxL1.SkipEntry();  // skip to next entry
        }
    }
    catch (MediaMpeg4FileInvalid&) {
        return false;
    }
}

Msg* Mpeg4Start::ProcessMsg(MsgAudioEncoded* aMsg)
{
    // FIXME - assumes enough of container was processed within Recognise from buffer
    MsgAudioEncoded* msg = aMsg;

    if (!iPulling) {
        if (!iContainerStripped) {
            // know the size of this container from Recognise();
            // just make sure enough is pulled through, then split

            AddToAudioEncoded(aMsg);
            msg = NULL;

            PullAudio(iSize);
            if (iSize < iAudioEncoded->Bytes()) {
                MsgAudioEncoded* remainder = iAudioEncoded->Split(iSize);
                iAudioEncoded->RemoveRef();
                iAudioEncoded = remainder;
                // can'safely return remaining iAudioEncoded here; shouldn't have another tag
                msg = iAudioEncoded;
                iAudioEncoded = NULL;
            }
            iContainerStripped = true;
        }
    }

    return msg;
}


// Mpeg4MediaInfoBase

Mpeg4MediaInfoBase::Mpeg4MediaInfoBase(ICodecController& aController)
    : iController(aController)
{
}

Mpeg4MediaInfoBase::~Mpeg4MediaInfoBase()
{
}

void Mpeg4MediaInfoBase::Process()
{
    LOG(kMedia, "Checking for Raop container\n");

    try {
        Bws<60> data;
        iController.Read(data, 4);

        LOG(kMedia, "data %x {", data[0]);
        LOG(kMedia, data);
        LOG(kMedia, "}\n");

        if(data != Brn("Raop")) {
            THROW(MediaCodecRaopNotFound);
        }

        // If RAOP is only used by alac, why bother going to extra lengths and creating a pseudo-identifier?
        //aSelector.iCodecContainer->SetName(Brn("alas"));  // this is used for codec recognition - streamed alac
        iSamplesTotal = 0;  // continual stream

        // fmtp should hold the sdp fmtp numbers from e.g. a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
        // extract enough info from this for codec selector, then pass the raw fmtp through for alac decoder
        // first read the number of bytes in for the fmtp
        data.SetBytes(0);
        iController.Read(data, 4);
        TUint bytes = Ascii::Uint(data);    // size of fmtp string
        data.SetBytes(0);
        iController.Read(data, bytes);
        Parser fmtp(data);

        LOG(kMedia, "fmtp [");
        LOG(kMedia, fmtp.NextLine());
        LOG(kMedia, "]\n");

        fmtp.Set(data);
        iCodecSpecificData.SetBytes(0);

        try {
            WriterBuffer writerBuf(iCodecSpecificData);
            WriterBinary writerBin(writerBuf);
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // ?
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // max_samples_per_frame
            iCodecSpecificData.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // 7a

            iBitDepth = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));                      // bit depth
            writerBin.WriteUint8(static_cast<TUint8>(iBitDepth));

            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_historymult
            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_initialhistory
            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_kmodifier

            iChannels = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));                      // 7f - I think that this is channels
            writerBin.WriteUint8(static_cast<TUint8>(iChannels));

            writerBin.WriteUint16Be(static_cast<TUint16>(Ascii::Uint(fmtp.Next())));       // 80
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // 82
            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // 86

            TUint rate = Ascii::Uint(fmtp.NextLine());
            iTimescale = rate;
            iSampleRate = rate;
            writerBin.WriteUint32Be(rate); // parsed fmtp data to be passed to alac decoder
        }
        catch (AsciiError&) {
            THROW(MediaCodecRaopNotFound);
        }
        data.SetBytes(bytes);

        LOG(kMedia, "Mpeg4MediaInfoBase RAOP header found %d bytes\n", bytes);
    }
    catch (CodecStreamCorrupt&) {
        THROW(MediaCodecRaopNotFound); // not enough data found to be Raop container
    }
}

const Brx& Mpeg4MediaInfoBase::CodecSpecificData() const
{
    return iCodecSpecificData;
}

TUint32 Mpeg4MediaInfoBase::SampleRate() const
{
    return iSampleRate;
}

TUint32 Mpeg4MediaInfoBase::Timescale() const
{
    return iTimescale;
}

TUint16 Mpeg4MediaInfoBase::Channels() const
{
    return iChannels;
}

TUint16 Mpeg4MediaInfoBase::BitDepth() const
{
    return iBitDepth;
}

TUint64 Mpeg4MediaInfoBase::Duration() const
{
    return iSamplesTotal;
}


// Mpeg4MediaInfo

Mpeg4MediaInfo::Mpeg4MediaInfo(ICodecController& aController)
    : Mpeg4MediaInfoBase(aController)
{
}

Mpeg4MediaInfo::~Mpeg4MediaInfo()
{
    //LOG(kCodec, "Mpeg4MediaInfo::~Mpeg4MediaInfo\n");
    iSampleSizeTable.Deinitialise();
    iSeekTable.Deinitialise();
}

SampleSizeTable& Mpeg4MediaInfo::GetSampleSizeTable()
{
    return iSampleSizeTable;
}

SeekTable& Mpeg4MediaInfo::GetSeekTable()
{
    return iSeekTable;
}

void Mpeg4MediaInfo::GetCodec(const Brx& aData, Bwx& aCodec)
{
    //LOG(kCodec, "Mpeg4MediaInfo::GetCodec\n");

    // May throw a MediaMpeg4FileInvalid exception.

    TUint offset = 0;
    TBool codecFound = false;

    for (;;) {
        Mpeg4Box BoxL4(aData, NULL, NULL, offset);
        BoxL4.Initialise();
        if(BoxL4.Match("minf")) {
            Mpeg4Box BoxL5(aData, &BoxL4, "stbl");
            BoxL5.Initialise();
            while (!BoxL5.Empty()) {
                Mpeg4Box BoxL6(aData, &BoxL5);
                BoxL6.Initialise();
                if(BoxL6.Match("stsd")) {
                    BoxL6.Skip(12);
                    // Read the codec value.
                    aCodec.SetBytes(0);
                    BoxL6.Read(aCodec, 4);
                    codecFound = true;
                    break;
                }
            }
        }
        if (codecFound) {
            break;
        }
        BoxL4.SkipEntry();
        offset += BoxL4.BytesRead();
    }
}


void Mpeg4MediaInfo::Process()
{
    //LOG(kCodec, "Mpeg4MediaInfo::Mpeg4MediaInfo\n");
    Bws<100> data;
    Bws<4> codec;

    for (;;) {
        Mpeg4Box BoxL4(iController);   // Starting from level 4, because Mpeg4Start should have ended on a L3 box.
        BoxL4.Initialise();
        if(BoxL4.Match("mdat")) {
            //LOG(kCodec, "Mpeg4 data found\n");
            // some files contain extra text at start of the data section which needs to be skipped
            //data.SetBytes(0);
            //BoxL1.Read(data, 16);
            //TByte* datap = (TUint8*)data.Ptr();
            //if((datap[3] == 0x08) && (Brn(&datap[4], 4) == Brn("wide")) && (Brn(&datap[12], 4) == Brn("mdat"))) {
            //    //LOG(kCodec, "extra mdat info found - skip\n");
            //}
            break;
        }
        else if(BoxL4.Match("mdhd")) {
            data.SetBytes(0);
            BoxL4.Read(data, 4);
            if(Converter::BeUint32At(data, 0)) {
                // read as 64 bit values  - ToDo !!!!
                THROW(MediaMpeg4FileInvalid);
            }
            else {
                BoxL4.Skip(8);
                data.SetBytes(0);
                BoxL4.Read(data, 4);
                iTimescale = Converter::BeUint32At(data, 0);
                data.SetBytes(0);
                BoxL4.Read(data, 4);
                iSamplesTotal = Converter::BeUint32At(data, 0);
            }
        } else if(BoxL4.Match("minf")) {
            Mpeg4Box BoxL5(iController, &BoxL4, "stbl");
            BoxL5.Initialise();
            while (!BoxL5.Empty()) {
                Mpeg4Box BoxL6(iController, &BoxL5);
                BoxL6.Initialise();
                if(BoxL6.Match("stsd")) {
                    BoxL6.Skip(12);
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);
                    codec.Append(data.Split(0,4));

                    BoxL6.Skip(16);
                    data.SetBytes(0);
                    BoxL6.Read(data, 2);
                    iChannels = Converter::BeUint16At(data, 0);

                    data.SetBytes(0);
                    BoxL6.Read(data, 2);
                    iBitDepth = Converter::BeUint16At(data, 0);

                    BoxL6.Skip(4);
                    data.SetBytes(0);
                    BoxL6.Read(data, 2);

                    iSampleRate = Converter::BeUint16At(data, 0);
                    BoxL6.Skip(2);              // LSB's of sample rate are ignored

                    if(!BoxL6.Empty()) {
                        Mpeg4Box BoxL7(iController, &BoxL6);         // any codec specific info should follow immediately
                        BoxL7.Initialise();
                        if(BoxL7.Match("alac")) {
                            // extract alac specific info
                            data.SetBytes(0);
                            BoxL7.Read(data, BoxL7.BoxSize() - 8);
                            iCodecSpecificData.Replace(data);
                            BoxL7.SkipEntry();
                        }
                        else if(BoxL7.Match("esds")) {
                            // extract aac specific info
                            data.SetBytes(0);
                            BoxL7.Read(data, BoxL7.BoxSize() - 8);
                            iCodecSpecificData.Replace(data);
                            BoxL7.SkipEntry();
                        }
                    }

                } else if(BoxL6.Match("stts")) {        // table of audio samples per sample - used to convert audio samples to codec samples
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // skip version id
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // extract number of entries
                    TUint entries = Converter::BeUint32At(data, 0);
                    iSeekTable.InitialiseAudioSamplesPerSample(entries);
                    while(entries--) {
                        data.SetBytes(0);
                        BoxL6.Read(data, 8);
                        iSeekTable.SetAudioSamplesPerSample(Converter::BeUint32At(data, 0), Converter::BeUint32At(data, 4));
                    }
                } else if(BoxL6.Match("stsc")) {             // table of samples per chunk - used to seek to specific sample
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // skip version id
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // extract number of entries
                    TUint entries = Converter::BeUint32At(data, 0);
                    iSeekTable.InitialiseSamplesPerChunk(entries);
                    while(entries--) {
                        data.SetBytes(0);
                        BoxL6.Read(data, 12);
                        iSeekTable.SetSamplesPerChunk(Converter::BeUint32At(data, 0), Converter::BeUint32At(data, 4));
                    }
                } else if(BoxL6.Match("stco")) {             // table of file offsets for each chunk   (repeat for 'co64' using 64bit offsets)
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // skip version id
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // extract number of entries
                    TUint entries = Converter::BeUint32At(data, 0);

                    iSeekTable.InitialiseOffsets(entries);
                    for(TUint i = 0; i < entries; i++) {
                        data.SetBytes(0);
                        BoxL6.Read(data, 4);
                        iSeekTable.SetOffset((TUint64)Converter::BeUint32At(data, 0));
                    }
                } else if(BoxL6.Match("stsz")) {             // size of each input sample
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // skip version id
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);                // default sample size expected to be 0 - else a table won't exist
                    if(Converter::BeUint32At(data, 0) != 0) {
                        THROW(MediaMpeg4FileInvalid);
                    }
                    data.SetBytes(0);
                    BoxL6.Read(data, 4);
                    TUint entries = Converter::BeUint32At(data, 0);
                    TUint sampleSize;

                    iSampleSizeTable.Initialise(entries);
                    Bwx* sampleSizeTable = new Bwh(entries*4);
                    BoxL6.Read(*sampleSizeTable, entries*4);
                    for(TUint i = 0; i < entries; i++) {
                        sampleSize = Converter::BeUint32At(*sampleSizeTable, i*4);
                        iSampleSizeTable.AddSampleSize(sampleSize);
                    }
                    delete sampleSizeTable;
                }
                BoxL6.SkipEntry();
            }
            BoxL5.SkipEntry();
        }
        BoxL4.SkipEntry();                    // skip to next entry
    }
}
