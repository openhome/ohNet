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
       iContainer->Read(aData, iOffset, aBytes);
       if (aData.Bytes() < aBytes) {
           THROW(MediaMpeg4FileInvalid);
       }
   }
   else if (iController) {
       iController->Read(aData, aBytes);
       if (aData.Bytes() < aBytes) {
           THROW(MediaMpeg4FileInvalid);
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

SampleSizeTable::SampleSizeTable() :  iCount(0), iEntry(0), iTable(0)
{
//    LOG(kCodec, "SampleSizeTable::SampleSizeTable()\n");
}

SampleSizeTable::~SampleSizeTable()
{
    Deinitialise();
}

void SampleSizeTable::Initialise(TUint aCount)
{
    //LOG(kCodec, "SampleSizeTable::Initialise(%d)\n", aCount);

    TUint tablesize = aCount * sizeof(TUint32);
    iCount = aCount;
    iEntry = 0;
    iTable = new Bwh(tablesize);
}

void SampleSizeTable::Deinitialise()
{
    //LOG(kCodec, "SampleSizeTable::Deinitialise()\n");
    if (iTable) {
        delete iTable;
        iTable = 0;
    }
}

void SampleSizeTable::SetSampleSize(TUint32 aSize)
{
    if(iEntry > iTable->MaxBytes()/sizeof(TUint32)) {
        THROW(MediaMpeg4FileInvalid);
    }

    ((TUint32 *)iTable->Ptr())[iEntry++] = aSize;
}

TUint32 SampleSizeTable::SampleSize(TUint aEntry)
{
    //LOG(kCodec, "SampleSizeTable::SampleSize(%d)\n", aEntry);

    if(aEntry > iEntry) {
        THROW(MediaMpeg4FileInvalid);
    }
    return ((TUint32 *)iTable->Ptr())[aEntry];
}

TUint32 SampleSizeTable::Count()
{
    //LOG(kCodec, "SampleSizeTable::Count()\n");

    return iCount;
}


// SeekTable
// Table of samples->chunk->offset required for seeking

SeekTable::SeekTable() : iSPCEntries(0), iSPCEntry(0), iSamplesPerChunk(0), iASPSEntries(0), iASPSEntry(0), iAudioSamplesPerSample(0), iOffsetEntries(0), iOffsetEntry(0), iOffsets(0)
{
//    LOG(kCodec, "SeekTable::SeekTable()\n");
}

SeekTable::~SeekTable()
{
    //LOG(kCodec, "SeekTable::~SeekTable()\n");
    Deinitialise();
}

void SeekTable::InitialiseSamplesPerChunk(TUint aEntries)
{
    //LOG(kCodec, "SeekTable::InitialiseSamplesPerChunk(%d)\n", aEntries);

    TUint tablesize = aEntries * sizeof(TSamplesPerChunkEntry);
    iSPCEntries = aEntries;
    iSPCEntry = 0;
    iSamplesPerChunk = new Bwh(tablesize);
}

void SeekTable::InitialiseAudioSamplesPerSample(TUint aEntries)
{
    //LOG(kCodec, "SeekTable::InitialiseAudioSamplesPerSample(%d)\n", aEntries);

    TUint tablesize = aEntries * sizeof(TAudioSamplesPerSampleEntry);
    iASPSEntries = aEntries;
    iASPSEntry = 0;
    iAudioSamplesPerSample = new Bwh(tablesize);
}

void SeekTable::InitialiseOffsets(TUint aEntries)
{
    //LOG(kCodec, "SeekTable::InitialiseOffsets(%d)\n", aEntries);
    TUint tablesize = aEntries * sizeof(TUint64);
    iOffsetEntries = aEntries;
    iOffsetEntry = 0;
    iOffsets = new Bwh(tablesize);
}


void SeekTable::Deinitialise()
{
    //LOG(kCodec, "SeekTable::Deinitialise()\n");
    if (iSamplesPerChunk) {
        delete iSamplesPerChunk;
        iSamplesPerChunk = 0;
    }
    if (iAudioSamplesPerSample) {
        delete iAudioSamplesPerSample;
        iAudioSamplesPerSample = 0;
    }
    if (iOffsets) {
        delete iOffsets;
        iOffsets = 0;
    }
}

void SeekTable::SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk)
{
    //LOG(kCodec, "SeekTable::SetSamplesPerChunk(%d, %d)\n",  aFirstChunk, aSamplesPerChunk);
    if(iSPCEntry >= iSPCEntries) {
        THROW(MediaMpeg4FileInvalid);
    }

    ((TSamplesPerChunkEntry *)iSamplesPerChunk->Ptr())[iSPCEntry].iFirstChunk = aFirstChunk;
    ((TSamplesPerChunkEntry *)iSamplesPerChunk->Ptr())[iSPCEntry].iSamples = aSamplesPerChunk;
    iSPCEntry++;
}



void SeekTable::SetAudioSamplesPerSample(TUint32 aSampleCount, TUint32 aAudioSamples)
{
    //LOG(kCodec, "SeekTable::SetAudioSamplesPerSample(%d, %d)\n",  aSampleCount, aAudioSamples);
    if(iASPSEntry >= iASPSEntries) {
        THROW(MediaMpeg4FileInvalid);        // seek table empty - cannot do seek
    }

    ((TAudioSamplesPerSampleEntry *)iAudioSamplesPerSample->Ptr())[iASPSEntry].iSampleCount = aSampleCount;   // store this entry
    ((TAudioSamplesPerSampleEntry *)iAudioSamplesPerSample->Ptr())[iASPSEntry].iAudioSamples = aAudioSamples;
    iASPSEntry++;
}


void SeekTable::SetOffset(TUint64 aOffset)
{
    //LOG(kCodec, "SeekTable::SetOffset(%lld)\n",  aOffset);
    if(iOffsetEntry >= iOffsetEntries) {
        THROW(MediaMpeg4FileInvalid);        // seek table empty - cannot do seek
    }

    ((TUint64 *)iOffsets->Ptr())[iOffsetEntry++] = aOffset;   // store this offset
}


TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint64& aSample)
{
    //LOG(kCodec, "SeekTable::Offset(%lld)\n", aAudioSample);
    if((iSPCEntry == 0) || (iASPSEntry == 0) || (iOffsetEntry == 0)) {
        THROW(CodecStreamCorrupt);        // seek table empty - cannot do seek
    }
    aSample = 0;

// fistly determine the required sample from the audio sample using the stts data,
// then work through samples per chunk table (stsc data) to get the chunk number for this particular sample
// then get the chunk offset from the offset table (stco data)

// stts:
    TUint64 totalaudiosamples = 0;
    TUint64 totalsamples = 0;
    TUint32 samplecount = 0;
    TUint32 audiosamples = 0;
    for(TUint entry = 0; entry < iASPSEntry; entry++) {

        samplecount = ((TAudioSamplesPerSampleEntry *)iAudioSamplesPerSample->Ptr())[entry].iSampleCount;
        audiosamples =  ((TAudioSamplesPerSampleEntry *)iAudioSamplesPerSample->Ptr())[entry].iAudioSamples;
        //LOG(kCodec, "SeekTable::Offset()  - ASPS - samplecount %d, audiosamples %d\n", samplecount, audiosamples);

        if( aAudioSample > (totalaudiosamples + samplecount * audiosamples)) {
            totalaudiosamples += samplecount * audiosamples;
            totalsamples = samplecount;
        } else {
            break;                  // audio samples are within this range
        }
    }
    if( (totalaudiosamples != 0) && (aAudioSample > totalaudiosamples)) {
        aAudioSample = totalaudiosamples-1;		// keep within range
    }

    if(audiosamples == 0)
        THROW(CodecStreamCorrupt);        // invalid table

    aSample = totalsamples + (aAudioSample - totalaudiosamples)/audiosamples;     // convert audio sample count to codec samples

    //LOG(kCodec, "SeekTable::Offset()  - ASPS - aSample %lld, totalsamples %lld, totalaudiosamples %lld\n", aSample, totalsamples, totalaudiosamples);

// stsc:
// chunk is found by searching to the entry in the table before samples > first chunk
// and interpolating to get exact chunk

    totalsamples = 0;
    TUint32 nextspc = 0, spc = 0, chunks = 0;
    TUint32 seekchunk = 0, firstchunk = 1, nextchunk = 1;
    for(TUint entry = 0; entry < iSPCEntry; entry++) {

        nextchunk = ((TSamplesPerChunkEntry *)iSamplesPerChunk->Ptr())[entry].iFirstChunk;
        nextspc =  ((TSamplesPerChunkEntry *)iSamplesPerChunk->Ptr())[entry].iSamples;

        chunks = nextchunk - firstchunk;
        if(aSample < (totalsamples + chunks * spc)) {
                    // sample is within previous range
            break;
        }

        totalsamples += chunks * spc;
        firstchunk = nextchunk;
        spc = nextspc;
        //LOG(kCodec, "SeekTable::Offset()  - totalsamples %lld, firstchunk %d\n", totalsamples, firstchunk);
    }
    seekchunk = (TUint32) (firstchunk + ((aSample-totalsamples) / spc));    // calculate chunk that this sample is in

    TUint64 adjsample = ((seekchunk - firstchunk) * spc) + totalsamples;  // calculate index to first sample in chunk

    aAudioSample -= (aSample - adjsample) * audiosamples;             // adjust audio sample count to index first sample in chunk
    aSample = adjsample;                                              // adjust codec sample count to index first sample in chunk
    //LOG(kCodec, "SeekTable::Offset()  - found chunk = %d, spc %d, adjusted sample %lld,%lld\n", seekchunk, spc, aSample, aAudioSample);

    seekchunk -= 1;                                             // adjust for array index (i.e. -1)

//stco:
    if(seekchunk >= iOffsetEntries) {
                                               // error - required chunk doesn't exist
        //LOG(kCodec, "SeekTable::Offset()  - chunk %d doesn't exist\n", seekchunk);
        THROW(CodecStreamCorrupt);        // asserts later on !!! ToDo
    }
    return ((TUint64 *)iOffsets->Ptr())[seekchunk];       // entry found - return offset to required chunk
}


// Mpeg4Start

Mpeg4Start::Mpeg4Start(IContainer& aContainer)
{
    //LOG(kCodec, "Mpeg4Start::Mpeg4Start\n");
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

    for (;;) {      // keep on reading until start of data found
        Mpeg4Box BoxL1(aContainer, &BoxL0, NULL, BoxL0.FileOffset());
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

Mpeg4Start::~Mpeg4Start()
{
    //LOG(kCodec, "Mpeg4Start::~Mpeg4Start\n");
}

TUint Mpeg4Start::ContainerSize() const
{
    return iContainerSize;
}


// Mpeg4MediaInfo

Mpeg4MediaInfo::Mpeg4MediaInfo(ICodecController& aController)
{
    //LOG(kCodec, "Mpeg4MediaInfo::Mpeg4MediaInfo\n");
    Bws<100> data;
    Bws<4> codec;

    for (;;) {
        Mpeg4Box BoxL4(aController);   // Starting from level 4, because Mpeg4Start should have ended on a L3 box.
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
            Mpeg4Box BoxL5(aController, &BoxL4, "stbl");
            while (!BoxL5.Empty()) {
                Mpeg4Box BoxL6(aController, &BoxL5);
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
                        Mpeg4Box BoxL7(aController, &BoxL6);         // any codec specific info should follow immediately
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
                        iSampleSizeTable.SetSampleSize(sampleSize);
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

Mpeg4MediaInfo::~Mpeg4MediaInfo()
{
    //LOG(kCodec, "Mpeg4MediaInfo::~Mpeg4MediaInfo\n");
    iSampleSizeTable.Deinitialise();
    iSeekTable.Deinitialise();
}

const Brx& Mpeg4MediaInfo::CodecSpecificData() const
{
    return iCodecSpecificData;
}

SampleSizeTable& Mpeg4MediaInfo::GetSampleSizeTable()
{
    return iSampleSizeTable;
}

SeekTable& Mpeg4MediaInfo::GetSeekTable()
{
    return iSeekTable;
}

TUint32 Mpeg4MediaInfo::SampleRate() const
{
    return iSampleRate;
}

TUint32 Mpeg4MediaInfo::Timescale() const
{
    return iTimescale;
}

TUint16 Mpeg4MediaInfo::Channels() const
{
    return iChannels;
}

TUint16 Mpeg4MediaInfo::BitDepth() const
{
    return iBitDepth;
}

TUint64 Mpeg4MediaInfo::Duration() const
{
    return iSamplesTotal;
}

void Mpeg4MediaInfo::GetCodec(const Brx& aData, Bwx& aCodec)
{
    //LOG(kCodec, "Mpeg4MediaInfo::GetCodec\n");

    // May throw a MediaMpeg4FileInvalid exception.

    TUint offset = 0;
    TBool codecFound = false;

    for (;;) {
        Mpeg4Box BoxL4(aData, NULL, NULL, offset);
        if(BoxL4.Match("minf")) {
            Mpeg4Box BoxL5(aData, &BoxL4, "stbl");
            while (!BoxL5.Empty()) {
                Mpeg4Box BoxL6(aData, &BoxL5);
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
