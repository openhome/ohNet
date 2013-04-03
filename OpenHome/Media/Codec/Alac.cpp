#include <OpenHome/Buffer.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Media/Codec/Alac.h>
#include <OpenHome/Media/Codec/CodecController.h>
#include <OpenHome/Media/Codec/Container.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Printer.h>

#include <alac_decoder/stream.h>
#include <alac_decoder/demux.h>
#include <alac_decoder/decomp.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

EXCEPTION(MediaMpeg4FileInvalid);

const TUint kReadReqBytes = 4096;

int host_bigendian;     // used by alac.c

class Mpeg4Box
{
public:
    Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent = NULL, const TChar* aIdName = NULL);
    ~Mpeg4Box();
    void Read(Bwx& aData, TUint aBytes);
    void SkipEntry();
    void Skip(TUint32 aBytes);
    TBool Match(const TChar* aIdName);
    TBool FindBox(const TChar* aIdName);
    TBool Empty();
    const Brx& Id() const { return iId; }
    TUint32 BoxSize() const { return iBoxSize; }
    TUint32 BytesRead() const { return iBytesRead; }
private:
    void ExtractHeaderId();
    void Reset();
    void UpdateParent(TUint aBytes);
private:
    ICodecController& iController;
    Mpeg4Box *iParent;
    Bws<4> iId;            // ID of box.
    Bws<32> iBuf;          // Local buffer.
    TUint32 iBytesRead;    // Bytes read for current entry.
    TUint32 iBoxSize;      // Size of current box.
};

Mpeg4Box::Mpeg4Box(ICodecController& aController, Mpeg4Box* aParent, const TChar* aIdName)
    : iController(aController)
    , iBytesRead(0)
    , iBoxSize(0)
    , iParent(aParent)
{
    ExtractHeaderId();
    if (aIdName != NULL)
        FindBox(aIdName);
}

Mpeg4Box::~Mpeg4Box()
{
}

TBool Mpeg4Box::FindBox(const TChar* aIdName)
{
    if (iParent == NULL) { // We don't have a parent, so we don't know our search bounds.
        return false;
    }
    while (!iParent->Empty()) {
        if (Match(aIdName)) {
            //            LOG(kCodec, "Mpeg4 box found %d (", iDataBytes);
            //            LOG_HEX(kCodec, iId);
            //            LOG(kCodec, ")\n");
            return true;              // found required id
        }
        SkipEntry();                  // skip over this entry
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
    Read(iId, 4);
    //LOG(kCodec, "Mpeg4 header %d (", iDataBytes);
    //LOG(kCodec, iId);
    //LOG(kCodec, ")\n");
}

void Mpeg4Box::Read(Bwx& aData, TUint aBytes)
{
   iController.Read(aData, aBytes);
   iBytesRead += aBytes;
   if (iParent != NULL) {
       UpdateParent(aBytes);
   }
}

void Mpeg4Box::UpdateParent(TUint aBytes)
{
    if (iParent != NULL)
    {
        iParent->iBytesRead += aBytes;
        iParent->UpdateParent(aBytes);
    }
}

void Mpeg4Box::SkipEntry()
{
    //LOG(kCodec, " SkipEntry %d, %d\n", iDataBytes, iBytesRead);
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

const Brn CodecAlac::kCodecAlac("alac");

CodecAlac::CodecAlac() 
    : iName("ALAC")
{
    //LOG(kCodec, "CodecAlac::CodecAlac\n");
}

CodecAlac::~CodecAlac()
{
    //LOG(kCodec, "CodecAlac::~CodecAlac\n");
    iSampleSizeTable.Deinitialise();
    iSeekTable.Deinitialise();
}

TBool CodecAlac::Recognise(const Brx& /*aMsg*/)
{
    //LOG(kCodec, "CodecAlac::Recognise\n");
    Bws<100> data;
    Bws<4> codec;

    Mpeg4Box BoxL0(*iController);
    if (!BoxL0.Match("ftyp")) {
        //LOG(kCodec, " no ftyp found at start of file\n");
        return false;
    }
    BoxL0.SkipEntry();

    // data could be stored in different orders in the file but ftyp & moov must come before mdat
    //This loop terminates when:
    // - we find the start of data
    // - Selector throws an exception (eos, flush)

    for (;;) {                              // keep on reading until start of data found
        Mpeg4Box BoxL1(*iController);
        if(BoxL1.Match("mdat")) {
        //LOG(kCodec, "Mpeg4 data found\n");
        // some files contain extra text at start of the data section which needs to be skipped
            //data.SetBytes(0);
            //BoxL1.Read(data, 16);
            //TByte* datap = (TUint8*)data.Ptr();
            //if((datap[3] == 0x08) && (Brn(&datap[4], 4) == Brn("wide")) && (Brn(&datap[12], 4) == Brn("mdat"))) {
            //    //LOG(kCodec, "extra mdat info found - skip\n");
            //    //iContainerSize += 16;
            //}
            break;
        } else if(BoxL1.Match("moov")) {
            //LOG(kCodec, "Mpeg4 moov found\n");
            // now search through levels for stsd for audio info

            Mpeg4Box BoxL2(*iController, &BoxL1, "trak");
            Mpeg4Box BoxL3(*iController, &BoxL2, "mdia");
            //
            while (!BoxL3.Empty()) {        // while box L3 still contains children
                Mpeg4Box BoxL4(*iController, &BoxL3);
                if(BoxL4.Match("mdhd")) {
                    data.SetBytes(0);
                    BoxL4.Read(data, 4);
                    if(Converter::BeUint32At(data, 0)) {
                        // read as 64 bit values  - ToDo !!!!
                        return false;
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
                    Mpeg4Box BoxL5(*iController, &BoxL4, "stbl");
                    while (!BoxL5.Empty()) {
                        Mpeg4Box BoxL6(*iController, &BoxL5);
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
                                Mpeg4Box BoxL7(*iController, &BoxL6);         // any codec specific info should follow immediately
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
                                    return false;
                                }
                                data.SetBytes(0);
                                BoxL6.Read(data, 4);
                                TUint entries = Converter::BeUint32At(data, 0);
                                TUint sampleSize;

                                // allocate table for sample size entries, needed by alac decoder - remember to delete when finished - ToDo !!!
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
            BoxL3.SkipEntry();
            //BoxL2.SkipEntry();
            //BoxL1.SkipEntry();
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
            return false;
        }
        BoxL1.SkipEntry();                    // skip to next entry
    }

    //iCodecContainer->SetContainerSize(iCodecContainer->ContainerSize() + mpeg4.ContainerSize());

    if (codec == kCodecAlac) {
        //LOG(kCodec, "CodecAlac::Recognise alac\n");
        return true;
    }
    //LOG(kMedia, "CodecAlac::Recognise, end Mpeg4 header stripping size %d\n",mpeg4.ContainerSize());
    return false;           
}

void CodecAlac::StreamInitialise()
{
    //LOG(kCodec, "CodecAlac::StreamInitialise\n");
#ifdef DEFINE_BIG_ENDIAN
    host_bigendian = true; // used within decode_frame()
#else
    host_bigendian = false;
#endif

    alac = create_alac(iBitDepth, iChannels);

    // We initialised codec-specific data in the recognise function.
    Bws<64> info;
    info.SetBytes(20);                          // first 20 bytes are ignored by decoder
    info.Append(iCodecSpecificData);            // add data extracted from MPEG-4 header
    alac_set_info(alac, (char*)info.Ptr());     // configure decoder

    iBitDepth = alac_sample_size(alac);         // sample size may be re-defined in the codec specific data in the MPEG4 header
    iBytesPerSample = iChannels*iBitDepth/8;
    iStartSample = 0;
    iCurrentSample = 0;
    iSamplesWrittenTotal = 0;

    iTrackLengthJiffies = (iSamplesTotal * Jiffies::kJiffiesPerSecond) / iSampleRate;
    iTrackOffset = 0;

    iController->OutputDecodedStream(0, iBitDepth, iSampleRate, iChannels, kCodecAlac, iTrackLengthJiffies, 0, true);
}

TBool CodecAlac::TrySeek(TUint aStreamId, TUint64 aSample) 
{
    //LOG(kCodec, "CodecAlac::TrySeek(%lld)\n", aSample);
    iSamplesWrittenTotal = aSample;
    TUint64 bytes = iSeekTable.Offset(iSamplesWrittenTotal, iStartSample);     // find file offset relating to given audio sample
    //LOG(kCodec, "CodecAlac::TrySeek to sample: %llu, byte: %lld\n", iStartSample, bytes);
    TBool canSeek = iController->TrySeek(aStreamId, bytes);
    if (canSeek) {
        iCurrentSample = iStartSample;
        iTrackOffset = (aSample * Jiffies::kJiffiesPerSecond) / iSampleRate;
        iController->OutputDecodedStream(0 ,iBitDepth, iSampleRate, iChannels, kCodecAlac, iTrackLengthJiffies, aSample, true);
    }
    return canSeek;
}

void CodecAlac::StreamCompleted()
{
    //LOG(kCodec, "CodecAlac::StreamCompleted\n");

    // free all malloc'ed buffers
    alac_free_buffers(alac);
}

void CodecAlac::BigEndianData(TUint aToWrite, TUint aSamplesWritten)
{
    // Alac decoder outputs in little endian.
    TByte* dst = const_cast<TByte*>(iOutBuf.Ptr()) + iOutBuf.Bytes();
    TByte* src = const_cast<TByte*>(iDecodedBuf.Ptr()) + (aSamplesWritten * iBytesPerSample);

    TUint i=0;

    switch(iBitDepth) {
        case 8:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                *dst++ = *src++;
            }
            break;
        case 16:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                *dst++ = src[1];
                *dst++ = src[0];
                src += 2;
            }
            break;
        case 24:
            for(i=0 ; i<aToWrite*iChannels; i++) {
                *dst++ = src[2];
                *dst++ = src[1];
                *dst++ = src[0];
                src += 3;
            }
            break;
        default:
            ASSERTS();
    }
}
 
void CodecAlac::Process() 
{
    //LOG(kCodec, "CodecAlac::Process\n");

    if (iCurrentSample < iSampleSizeTable.Count()) {
        // read in a single alac sample
        iInBuf.SetBytes(0);

        //LOG(kCodec, "CodecAlac::Process  sample = %u, size = %u, inBuf max size %u\n", iCurrentSample, iSampleSizeTable.SampleSize(iCurrentSample), iInBuf.MaxBytes());
        iController->Read(iInBuf, iSampleSizeTable.SampleSize((TUint)iCurrentSample));
        iCurrentSample++;

        // decode sample
        int outputBytes;
        outputBytes = iDecodedBuf.MaxBytes();
        // use alac decoder to decode a frame at a time
        if (decode_frame(alac, (unsigned char*)iInBuf.Ptr(), (void*)iDecodedBuf.Ptr(), &outputBytes) == 0) {
            THROW(CodecStreamCorrupt); // decode error
        }
        iDecodedBuf.SetBytes(outputBytes);
        //LOG(kCodec, "CodecAlac::Process  decoded output %d\n", outputBytes);

        // output samples
        TUint samplesToWrite = iDecodedBuf.Bytes()/iBytesPerSample;
        TUint samplesWritten = 0;
        while (samplesToWrite > 0) {
            TUint bytes = samplesToWrite * (iBitDepth/8) * iChannels;
            TUint samples = samplesToWrite;
            TUint outputSpace = iOutBuf.MaxBytes() - iOutBuf.Bytes();
            if (bytes > outputSpace) {
                samples = outputSpace / (iChannels * (iBitDepth/8));
                bytes = samples * (iBitDepth/8) * iChannels;
            }
            BigEndianData(samples, samplesWritten);
            iOutBuf.SetBytes(iOutBuf.Bytes() + bytes);
            if (iOutBuf.MaxBytes() - iOutBuf.Bytes() < (TUint)(iBitDepth/8) * iChannels) {
                iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
                    iBitDepth, EMediaDataBigEndian, iTrackOffset);
                iOutBuf.SetBytes(0);
            }
            samplesToWrite -= samples;
            samplesWritten += samples;
            iSamplesWrittenTotal += samples;
            //LOG(kCodec, "CodecAlac::iSamplesWrittenTotal: %llu\n", iSamplesWrittenTotal);
        }
    }
    else { // When can we detect CodecStreamStarted?
        // flush remaining samples
        iTrackOffset += iController->OutputAudioPcm(iOutBuf, iChannels, iSampleRate,
            iBitDepth, EMediaDataBigEndian, iTrackOffset);
        iOutBuf.SetBytes(0);
        THROW(CodecStreamEnded);
    }
}
