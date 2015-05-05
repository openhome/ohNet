#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Debug.h>

#include <limits>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;


// Mpeg4Info

Mpeg4Info::Mpeg4Info()
    : iSampleRate(0)
    , iTimescale(0)
    , iChannels(0)
    , iBitDepth(0)
    , iDuration (0)
{
}

Mpeg4Info::Mpeg4Info(const Brx& aCodec, TUint aSampleRate, TUint aTimescale, TUint aChannels, TUint aBitDepth, TUint64 aDuration, const Brx& aStreamDescriptor)
    : iCodec(aCodec)
    , iSampleRate(aSampleRate)
    , iTimescale(aTimescale)
    , iChannels(aChannels)
    , iBitDepth(aBitDepth)
    , iDuration(aDuration)
    , iStreamDescriptor(aStreamDescriptor)
{
}

TBool Mpeg4Info::Initialised() const
{
    const TBool initialised =
        iCodec.Bytes() > 0
        && iSampleRate != 0
        && iTimescale != 0
        && iChannels != 0
        && iBitDepth != 0
        && iDuration != 0
        && iStreamDescriptor.Bytes() > 0;
    return initialised;
}

const Brx& Mpeg4Info::Codec() const
{
    return iCodec;
}

TUint Mpeg4Info::SampleRate() const
{
    // FIXME - ASSERT if not set?
    return iSampleRate;
}

TUint Mpeg4Info::Timescale() const
{
    return iTimescale;
}

TUint Mpeg4Info::Channels() const
{
    return iChannels;
}

TUint Mpeg4Info::BitDepth() const
{
    return iBitDepth;
}

TUint64 Mpeg4Info::Duration() const
{
    return iDuration;
}

const Brx& Mpeg4Info::StreamDescriptor() const
{
    return iStreamDescriptor;
}

void Mpeg4Info::SetCodec(const Brx& aCodec)
{
    iCodec.Replace(aCodec);
}

void Mpeg4Info::SetSampleRate(TUint aSampleRate)
{
    // FIXME - ASSERT if already set?
    iSampleRate = aSampleRate;
}

void Mpeg4Info::SetTimescale(TUint aTimescale)
{
    iTimescale = aTimescale;
}

void Mpeg4Info::SetChannels(TUint aChannels)
{
    iChannels = aChannels;
}

void Mpeg4Info::SetBitDepth(TUint aBitDepth)
{
    iBitDepth = aBitDepth;
}

void Mpeg4Info::SetDuration(TUint64 aDuration)
{
    iDuration = aDuration;
}

void Mpeg4Info::SetStreamDescriptor(const Brx& aDescriptor)
{
    iStreamDescriptor.Replace(aDescriptor);
}


// Mpeg4InfoReader

Mpeg4InfoReader::Mpeg4InfoReader(IReader& aReader)
    : iReader(aReader)
{
}

void Mpeg4InfoReader::Read(IMpeg4InfoWritable& aInfo)
{
    // These may throw up ReaderError, catch and rethrow?
    ReaderBinary readerBin(iReader);
    try {
        Bws<IMpeg4InfoWritable::kCodecBytes> codec;
        Bws<IMpeg4InfoWritable::kMaxStreamDescriptorBytes> streamDescriptor;

        readerBin.ReadReplace(codec.MaxBytes(), codec);
        aInfo.SetCodec(codec);

        const TUint sampleRate = readerBin.ReadUintBe(4);
        aInfo.SetSampleRate(sampleRate);

        const TUint timescale = readerBin.ReadUintBe(4);
        aInfo.SetTimescale(timescale);

        const TUint channels = readerBin.ReadUintBe(4);
        aInfo.SetChannels(channels);

        const TUint bitDepth = readerBin.ReadUintBe(4);
        aInfo.SetBitDepth(bitDepth);

        const TUint64 duration = readerBin.ReadUint64Be(8);
        aInfo.SetDuration(duration);

        const TUint streamDescriptorBytes = readerBin.ReadUintBe(4);
        readerBin.ReadReplace(streamDescriptorBytes, streamDescriptor);
        aInfo.SetStreamDescriptor(streamDescriptor);

        //ASSERT(aInfo.Initialised());
    }
    catch (ReaderError&) {
        THROW(MediaMpeg4FileInvalid);
    }
}


// Mpeg4InfoWriter

Mpeg4InfoWriter::Mpeg4InfoWriter(const IMpeg4InfoReadable& aInfo)
    : iInfo(aInfo)
{
}

void Mpeg4InfoWriter::Write(IWriter& aWriter) const
{
    //ASSERT(iInfo.Initialised());
    WriterBinary writer(aWriter);
    writer.Write(iInfo.Codec());
    writer.WriteUint32Be(iInfo.SampleRate());
    writer.WriteUint32Be(iInfo.Timescale());
    writer.WriteUint32Be(iInfo.Channels());
    writer.WriteUint32Be(iInfo.BitDepth());
    writer.WriteUint64Be(iInfo.Duration());
    writer.WriteUint32Be(iInfo.StreamDescriptor().Bytes());
    writer.Write(iInfo.StreamDescriptor());
    aWriter.WriteFlush();   // FIXME - required?
}


// Mpeg4Box

Mpeg4Box::Mpeg4Box()
    : iReader(NULL)
    , iSize(0)
    , iOffset(0)
{
}

Mpeg4Box::~Mpeg4Box()
{
}

void Mpeg4Box::Set(IReader& aReader)
{
    //Clear();

    //iReader = NULL;
    iSize = 0;
    iId.SetBytes(0);
    iOffset = 0;

    iReader = &aReader;
}

void Mpeg4Box::Clear()
{
    //iReader = NULL;   // Clear() should definitely do this, but then Set() must be called afterwards. Otherwise, ReadFlush() could do the following.
    iSize = 0;
    iId.SetBytes(0);
    iOffset = 0;
}

void Mpeg4Box::ReadHeader()
{
    ASSERT(iReader != NULL);
    // FIXME - can just call Read() here!
    TUint remaining = kBoxHeaderBytes;
    Bws<kBoxHeaderBytes> header;
    while (remaining > 0) {
        Brn buf = iReader->Read(remaining);
        if (buf.Bytes() == 0) {
            THROW(MediaMpeg4EndOfData); // FIXME - throw invalid instead?
        }
        header.Append(buf);
        remaining -= buf.Bytes();
        iOffset += buf.Bytes();
    }
    iSize = Converter::BeUint32At(header, 0);
    iId.Replace(header.Ptr()+kBoxSizeBytes, kBoxNameBytes);
    //Read(iId, 4);
    //LOG(kCodec, "Mpeg4 header %u (", iBoxSize);
    //LOG(kCodec, iId);
    //LOG(kCodec, ")\n");
}

TUint Mpeg4Box::Size() const
{
    ASSERT(iReader != NULL);
    return iSize;
}

const Brx& Mpeg4Box::Id() const
{
    ASSERT(iReader != NULL);
    return iId;
}
//
//TUint Mpeg4Box::Offset() const
//{
//    return iOffset;
//}
//
//void Mpeg4Box::Read(Bwx& aBuf, TUint aBytes)
//{
//    ASSERT(iSize >= iOffset);
//    ASSERT(iOffset+aBytes <= iSize);
//    TUint remaining = aBytes;
//    while (remaining > 0) {
//        Brn buf = iReader.Read(remaining);
//        if (buf.Bytes() == 0) {
//            THROW(MediaMpeg4EndOfData); // FIXME - throw invalid instead?
//        }
//        aBuf.Append(buf);
//        remaining -= buf.Bytes();
//        iOffset += buf.Bytes();
//    }
//}

void Mpeg4Box::SkipRemaining()
{
    ASSERT(iReader != NULL);
    ASSERT(iSize >= iOffset);
    const TUint remaining = iSize - iOffset;
    Skip(remaining);
}

void Mpeg4Box::Skip(TUint aBytes)
{
    ASSERT(iReader != NULL);
    ASSERT(iSize >= iOffset);
    TUint remaining = iSize - iOffset;
    ASSERT(aBytes <= remaining);

    if (aBytes < remaining) {
        remaining = aBytes;
    }

    while (remaining > 0) {
        Brn buf = iReader->Read(remaining);  // FIXME - catch ReaderError and rethrow as Mpeg4 exception?
        if (buf.Bytes() == 0) {
            THROW(MediaMpeg4EndOfData); // FIXME - throw invalid instead?
        }
        remaining -= buf.Bytes();
        iOffset += buf.Bytes();
    }
}

Brn Mpeg4Box::Read(TUint aBytes)
{
    ASSERT(iReader != NULL);
    ASSERT(iOffset <= iSize);
    ASSERT(iOffset+aBytes <= iSize);
    Brn buf = iReader->Read(aBytes);
    iOffset += buf.Bytes();
    return buf;
}

void Mpeg4Box::ReadFlush()
{
    ASSERTS();
}

void Mpeg4Box::ReadInterrupt()
{
    ASSERTS();
}


// SampleSizeTable

SampleSizeTable::SampleSizeTable()
{
}

SampleSizeTable::~SampleSizeTable()
{
    Clear();
}

void SampleSizeTable::Init(TUint aMaxEntries)
{
    iTable.reserve(aMaxEntries);
}

void SampleSizeTable::Clear()
{
    iTable.clear();
}

void SampleSizeTable::AddSampleSize(TUint aSize)
{
    if (iTable.size() == iTable.capacity()) {
        THROW(MediaMpeg4FileInvalid);
    }
    iTable.push_back(aSize);
}

TUint32 SampleSizeTable::SampleSize(TUint aIndex)
{
    if(aIndex > iTable.size()-1) {
        THROW(MediaMpeg4FileInvalid);
    }
    return iTable[aIndex];
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

TBool SeekTable::Initialised() const
{
    const TBool initialised =
        iSamplesPerChunk.size() > 0
        && iAudioSamplesPerSample.size() > 0
        && iOffsets.size() > 0;
    return initialised;
}

void SeekTable::Deinitialise()
{
    iSamplesPerChunk.clear();
    iAudioSamplesPerSample.clear();
    iOffsets.clear();
}

void SeekTable::SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk, TUint aSampleDescriptionIndex)
{
    TSamplesPerChunkEntry entry = { aFirstChunk, aSamplesPerChunk, aSampleDescriptionIndex };
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

TUint SeekTable::ChunkCount() const
{
    return iOffsets.size();
}

TUint SeekTable::SamplesPerChunk(TUint aChunkIndex) const
{
    //ASSERT(aChunkIndex < iSamplesPerChunk.size());
    //return iSamplesPerChunk[aChunkIndex];

    for (TUint i=iSamplesPerChunk.size()-1; i>=0; i--) {
        // Note: aChunkIndex = 0 => iFirstChunk = 1
        if (iSamplesPerChunk[i].iFirstChunk <= aChunkIndex+1) {
            return iSamplesPerChunk[i].iSamples;
        }
    }
    ASSERTS();
    return 0;
}

TUint SeekTable::StartSample(TUint aChunkIndex) const
{
    TUint startSample = 0;
    for (TUint i=0; i<iSamplesPerChunk.size(); i++) {
        if ((i<iSamplesPerChunk.size()-1 && iSamplesPerChunk[i+1].iFirstChunk > aChunkIndex+1) || (i == iSamplesPerChunk.size()-1 && iSamplesPerChunk[i].iFirstChunk < aChunkIndex+1)) {
            // Did a check of next entry, and chunk appears somewhere in current entry.
            // OR
            // At last entry, and chunk appears somewhere within current entry.
            const TUint offset = aChunkIndex+1 - iSamplesPerChunk[i].iFirstChunk;
            startSample += iSamplesPerChunk[i].iSamples*offset;
            return startSample;
        }
        else if (iSamplesPerChunk[i].iFirstChunk == aChunkIndex+1) {
            // Chunk start at this entry.
            return startSample;
        }
        else {
            // Chunk is not within this entry; increment startSample and continue.
            startSample += iSamplesPerChunk[i].iSamples;
        }
    }
    ASSERTS();
    return 0;
}

TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint64& aSample)
{
    if (iSamplesPerChunk.size() == 0 || iAudioSamplesPerSample.size() == 0 || iOffsets.size()==0) {
        THROW(CodecStreamCorrupt); // seek table empty - cannot do seek // FIXME - throw a MpegMediaFileInvalid exception, which is actually expected/caught?
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
        THROW(CodecStreamCorrupt); // invalid table // FIXME - THROW Mpeg4MediaFileInvalid instead?

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
        THROW(CodecStreamCorrupt); // asserts later on !!! ToDo // FIXME - THROW Mpeg4MediaFileInvalid instead?
    }
    return iOffsets[seekchunk]; // entry found - return offset to required chunk
}

TUint64 SeekTable::GetOffset(TUint aChunkIndex) const
{
    ASSERT(aChunkIndex < iOffsets.size());
    return iOffsets[aChunkIndex];
}


// Mpeg4Start

Mpeg4Container::Mpeg4Container()
{
    LOG(kMedia, "Mpeg4Start::Mpeg4Start\n");
}

TBool Mpeg4Container::Recognise(Brx& aBuf)
{
    iPos = 0;
    iMetadataRetrieved = false;
    iProcessingMetadataComplete = false;
    iChunkIndex = 0;
    iChunkBytesRemaining = 0;
    iCodec.SetBytes(0);
    iSampleRate = 0;
    iTimescale = 0;
    iChannels = 0;
    iBitDepth = 0;
    iDuration = 0;
    //iSamplesTotal = 0;
    iStreamDescriptor.SetBytes(0);
    iSampleSizeTable.Clear();
    iSeekTable.Deinitialise();

    LOG(kMedia, "Mpeg4Start::Recognise\n");
    if (aBuf.Bytes() >= Mpeg4Box::kBoxHeaderBytes) {
        if (Brn(aBuf.Ptr()+Mpeg4Box::kBoxSizeBytes, Mpeg4Box::kBoxNameBytes) == Brn("ftyp")) {
            return true;
        }
    }

    return false;
}

Msg* Mpeg4Container::ProcessMsg(MsgAudioEncoded* aMsg)
{
    AddToAudioEncoded(aMsg);

    if (!iPulling) {
        Process();

        MsgAudioEncoded* msg = iAudioEncoded;
        iAudioEncoded = NULL;

        return msg;   // FIXME - return this, or msg returned by Process()?
        // Probably better to have Process() manipulate iAudioEncoded, then return the Msg from Process() here?
    }

    //return msg;
    return NULL;
}

Brn Mpeg4Container::Read(TUint aBytes)
{
    // After container has been recognised (which just reads from a buffer),
    // processing is sequential, so can discard audio from stream as it's read.

    // IReaders only need to try return up to aBytes.
    // So, if internal buffer capacity is less than aBytes, just return internal buffer.
    TUint bytes = aBytes;
    if (iBuf.MaxBytes() < aBytes) {
        bytes = iBuf.MaxBytes();
    }

    iBuf.SetBytes(0);
    ContainerBase::Read(iBuf, bytes);   // Can't inspect iAudioEncoded directly, so use helper function to copy into buffer.
    ASSERT(iBuf.Bytes() == bytes);
    iPos += bytes;

    DiscardAudio(bytes);    // FIXME - what if MsgEncodedStream is pulled?

    return Brn(iBuf.Ptr(), iBuf.Bytes());
}

void Mpeg4Container::ReadFlush()
{
    // FIXME - this could call DiscardAudio()
    ASSERTS();
}

void Mpeg4Container::ReadInterrupt()
{
    ASSERTS();
}

Msg* Mpeg4Container::Process()
{

    // FIXME - If we did handle files with mdat before moov, would have to ensure we didn't attempt to process moov after end of mdat, i.e., somehow terminate when we reach end of mdat, which is detectable by various means.

    MsgAudioEncoded* msgOut = NULL;

    if (!iProcessingMetadataComplete) {
        TBool metadataProcessed = false;
        try {
            // Start reading boxes. First should be ftyp.
            Mpeg4Box boxFtyp;
            boxFtyp.Set(*this);
            boxFtyp.ReadHeader();
            if (boxFtyp.Id() != Brn("ftyp")) {
                LOG(kMedia, "Mpeg4Container::Process no ftyp found at start of file\n");
                ASSERTS();  // FIXME - corrupt stream (maybe fair to assert, as did see ftyp during Recognise() call).
            }
            boxFtyp.SkipRemaining();

            Mpeg4Box box;
            box.Set(*this);
            for (;;) {
                box.ReadHeader();
                if (box.Id() == Brn("moov")) {
                    // Found metadata box. Parse it.
                    metadataProcessed = ParseMetadataBox(box, box.Size());    // Exception thrown if invalid/EoS.

                    Mpeg4Box subBox;
                    subBox.Set(box);
                    Log::Print("Mpeg4Container::Process found metadata\n");
                }
                else if (box.Id() == Brn("mdat")) {
                    if (!metadataProcessed) {
                        // Not yet encountered metadata (moov) box.
                        // Do out-of-band read to get moov box.
                        Bws<1024> buf;
                        ReaderBuffer reader(buf);
                        //const TUint metadataSize = box.Size();
                        metadataProcessed = ParseMetadataBox(reader, box.Size());

                        if (!metadataProcessed) {
                            // Failed to parse container. Flush the remainder of stream until MsgEncodedStream seen.
                            ASSERTS();  // FIXME - set an iFlushing member and call iAudioEncoded->RemoveRef() until new MsgEncodedStream seen?
                            // Also throw stream corrupt exception?
                        }
                        else {
                            break;  // Just break out; definitely don't want to SkipRemaining() stream data here!
                        }
                    }

                    // FIXME - not quite good enough - would need to skip over mdat in out-of-band read and then potentially have to skip over some more boxes to get to the moov box.
                    // So, pass off to a function that will do out-of-band reads until we get to moov box.
                    // And then, implement a special out-of-band IReader that will read from a small, fixed-size buffer (i.e., 1k) and will go do more out-of-band reads when we attempt to read beyond end of buffer
                    // - will need to ensure read/discard behaviour is decided by then, as only real option for that is to discard audio as we go beyond end of buffer
                    // - that probably means that's the behaviour we should take with normal parsing circumstance - just discard data as it's read (or, discard prev read data on next read so it at least remains in memory while it may be used), as we don't ever backtrace during normal parsing.

                    // In the interim, just flush all remaining data.
                }
                box.SkipRemaining();
                box.Clear();

                if (metadataProcessed) {
                    break;
                }

                // FIXME - what if we exhaust stream - catch one of the exceptions below?
            }

        }
        catch (MediaMpeg4EndOfData&) {

        }
        catch (MediaMpeg4FileInvalid&) {

        }

        ASSERT(metadataProcessed);
        // FIXME - can probably do this in metadata helper method.
        Mpeg4Info info(iCodec, iSampleRate, iTimescale, iChannels, iBitDepth, iDuration, iStreamDescriptor);
        Mpeg4InfoWriter writer(info);
        Bws<Mpeg4InfoWriter::kMaxBytes> infoBuf;
        WriterBuffer writerBuf(infoBuf);
        writer.Write(writerBuf);

        // Need to create MsgAudioEncoded w/ data for codec.
        MsgAudioEncoded* msgInfo = iMsgFactory->CreateMsgAudioEncoded(infoBuf);
        // Then, need to return this msg from Process(MsgAudioEncoded*) so that it is output,
        // and doesn't interfere with audio cached in iAudioEncoded.
        msgOut = msgInfo;

        // Write sample size table so decoder knows how many bytes to read for each sample (MPEG4 term)/frame (AAC term).
        // FIXME - use a buffer of size EncodedAudio::kMaxBytes and iteratively populate it and create a new MsgAudioEncoded until table exhausted.
        Bwh sampleSizeBuf(sizeof(TUint32)+sizeof(TUint32)*iSampleSizeTable.Count()); // FIXME - can this be done without dynamic allocation right here?
        WriterBuffer writerBufSampleSize(sampleSizeBuf);
        WriterBinary writerBin(writerBufSampleSize);
        writerBin.WriteUint32Be(iSampleSizeTable.Count());
        for (TUint i=0; i<iSampleSizeTable.Count(); i++) {
            writerBin.WriteUint32Be(iSampleSizeTable.SampleSize(i));
        }


        static const TUint kMaxEncodedAudioBytes = EncodedAudio::kMaxBytes; // FIXME - move to class declaration.
        TUint samplesTableRemainingBytes = sampleSizeBuf.Bytes();
        TUint offset = 0;
        while (samplesTableRemainingBytes > 0) {
            if (samplesTableRemainingBytes > kMaxEncodedAudioBytes) {
                MsgAudioEncoded* msgSampleTable = iMsgFactory->CreateMsgAudioEncoded(Brn(sampleSizeBuf.Ptr()+offset, kMaxEncodedAudioBytes));
                msgOut->Add(msgSampleTable);
                samplesTableRemainingBytes -= kMaxEncodedAudioBytes;
                offset += kMaxEncodedAudioBytes;
            }
            else {
                MsgAudioEncoded* msgSampleTable = iMsgFactory->CreateMsgAudioEncoded(Brn(sampleSizeBuf.Ptr()+offset, samplesTableRemainingBytes));
                msgOut->Add(msgSampleTable);
                offset += samplesTableRemainingBytes;
                samplesTableRemainingBytes = 0;
            }
        }
    }


    // Output audio chunk-by-chunk.
    while (iChunkIndex < iSeekTable.ChunkCount() && iAudioEncoded != NULL) {

        // Are we at the start of the next chunk?
        if (iChunkBytesRemaining == 0) {
            const TUint64 chunkOffset = iSeekTable.GetOffset(iChunkIndex);
            if (chunkOffset < iPos) {
                THROW(MediaMpeg4FileInvalid);
            }
            const TUint64 toDiscard = chunkOffset-iPos;
            ASSERT(toDiscard <= std::numeric_limits<TUint>::max());
            iBytesToDiscard = static_cast<TUint>(toDiscard);

            // FIXME - make TUint ChunkBytes(TUint aChunkIndex) a member of seek table.
            const TUint chunkSamples = iSeekTable.SamplesPerChunk(iChunkIndex);
            const TUint startSample = iSeekTable.StartSample(iChunkIndex);  // NOTE: this assumes first sample == 0 (which is valid with how our tables are setup), but in MPEG4 spec, first sample == 1.
            TUint chunkBytes = 0;
            // Samples start from 1. However, tables here are indexed from 0.
            for (TUint i=startSample; i<startSample+chunkSamples; i++) {
                const TUint sampleBytes = iSampleSizeTable.SampleSize(i);
                ASSERT(chunkBytes+sampleBytes <= std::numeric_limits<TUint>::max());    // Ensure no overflow.
                chunkBytes += sampleBytes;
            }
            iChunkBytesRemaining = chunkBytes;
        }


        if (iBytesToDiscard > 0) {
            if (iBytesToDiscard >= iAudioEncoded->Bytes()) {
                iBytesToDiscard -= iAudioEncoded->Bytes();
                iPos += iAudioEncoded->Bytes();     // FIXME - provide wrapper for incrementing iPos?
                iAudioEncoded->RemoveRef();
                //iAudioEncoded = NULL;
                iAudioEncoded = msgOut;
                return msgOut;
            }
            else {
                DiscardAudio(iBytesToDiscard);
                iPos += iBytesToDiscard;            // FIXME - provide wrapper for incrementing iPos?
                iBytesToDiscard = 0;
            }
        }

        ASSERT(iAudioEncoded != NULL);
        ASSERT(iBytesToDiscard == 0);
        if (iAudioEncoded->Bytes() > iChunkBytesRemaining) {
            MsgAudioEncoded* remainder = iAudioEncoded->Split(iChunkBytesRemaining);
            iPos += iAudioEncoded->Bytes();     // FIXME - provide wrapper for incrementing iPos?
            if (msgOut == NULL) {
                msgOut = iAudioEncoded;
            }
            else {
                msgOut->Add(iAudioEncoded);
            }
            iAudioEncoded = remainder;
            iChunkBytesRemaining = 0;

            iChunkIndex++;
        }
        else {  // iAudioEncoded->Bytes() <= iChunkBytesRemaining
            iChunkBytesRemaining -= iAudioEncoded->Bytes();
            iPos += iAudioEncoded->Bytes();     // FIXME - provide wrapper for incrementing iPos?
            if (msgOut == NULL) {
                msgOut = iAudioEncoded;
            }
            else {
                msgOut->Add(iAudioEncoded);
            }
            iAudioEncoded = NULL;
        }
    }

    // FIXME - do this here or in ProcessMsg?
    if (iAudioEncoded == NULL) {
        iAudioEncoded = msgOut;
    }
    else {
        // Some iAudioEncoded left, but should have exhausted all chunks.
        // So remaining iAudioEncoded must be other data.
        // FIXME - discard until start of next stream?
        ASSERT(iChunkIndex == iSeekTable.ChunkCount());

        // FIXME - update iPos?

        //msgOut->Add(iAudioEncoded);
        //iAudioEncoded = msgOut;
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }

    //return msgOut;  // FIXME - if manipulating iAudioEncoded here, don't need to do this.
    return NULL;
}

TBool Mpeg4Container::ParseMetadataBox(IReader& aReader, TUint /*aBytes*/)
{
    try {
        Mpeg4Box box1;
        box1.Set(aReader);
        for (;;) {
            box1.ReadHeader();
            if (box1.Id() == Brn("trak")) {
                Mpeg4Box box2;
                box2.Set(box1);
                for (;;) {
                    box2.ReadHeader();
                    if (box2.Id() == Brn("mdia")) {
                        Mpeg4Box box3;
                        box3.Set(box2);
                        for (;;) {
                            box3.ReadHeader();
                            if (box3.Id() == Brn("mdhd")) {
                                ParseBoxMdhd(box3, box3.Size());
                            }
                            else if (box3.Id() == Brn("minf")) {
                                Mpeg4Box box4;
                                box4.Set(box3);
                                for (;;) {
                                    box4.ReadHeader();
                                    if (box4.Id() == Brn("stbl")) {
                                        Mpeg4Box box5;
                                        box5.Set(box4);
                                        for (;;) {
                                            box5.ReadHeader();
                                            if (box5.Id() == Brn("stsd")) {
                                                ReaderBinary readerBin(box5);
                                                box5.Skip(4);   // Skip version info.
                                                const TUint sampleEntries = readerBin.ReadUintBe(4);
                                                Mpeg4Box sampleEntry;
                                                sampleEntry.Set(box5);
                                                for (TUint i=0; i<sampleEntries; i++) {
                                                    sampleEntry.ReadHeader();
                                                    if (sampleEntry.Id() == Brn("mp4a")) {  // Only care about audio.
                                                        ParseBoxMp4a(box5, box5.Size());
                                                        Mpeg4Box streamDescriptorBox;
                                                        streamDescriptorBox.Set(sampleEntry);
                                                        for (;;) {
                                                            streamDescriptorBox.ReadHeader();
                                                            if (streamDescriptorBox.Id() == Brn("esds") || streamDescriptorBox.Id() == Brn("alac")) {
                                                                // FIXME - valid to filter this box by known content type?
                                                                // Should we just process next box, regardless of type, and assume it always sits at this position and is in same format?
                                                                Log::Print("found stream descriptor box\n");

                                                                ParseBoxStreamDescriptor(streamDescriptorBox, streamDescriptorBox.Size());
                                                                break;
                                                            }
                                                        }

                                                        streamDescriptorBox.SkipRemaining();
                                                        streamDescriptorBox.Clear();
                                                        break;  // FIXME - correct thing to do?

                                                    }
                                                    sampleEntry.SkipRemaining();
                                                    sampleEntry.Clear();
                                                }
                                            }
                                            else if (box5.Id() == Brn("stts")) {
                                                ParseBoxStts(box5, box5.Size());
                                            }
                                            else if (box5.Id() == Brn("stsc")) {
                                                ParseBoxStsc(box5, box5.Size());
                                            }
                                            else if (box5.Id() == Brn("stco")) {
                                                // FIXME - check co64 (or stco) hasn't been processed
                                                ParseBoxStco(box5, box5.Size());
                                            }
                                            else if (box5.Id() == Brn("co64")) {
                                                // FIXME - check stco (or co64) hasn't been processed
                                                ParseBoxCo64(box5, box5.Size());
                                            }
                                            else if (box5.Id() == Brn("stsz")) {
                                                ParseBoxStsz(box5, box5.Size());
                                            }
                                            box5.SkipRemaining();
                                            box5.Clear();
                                            //if (iSampleSizeTable.Count() > 0 // may not be valid if SampleSizeTable is changed to support a fixed sample size.
                                            //    && (iSeekTable.SamplesPerChunkCount() > 0
                                            //    && iSeekTable.AudioSamplesPerSampleCount() > 0
                                            //    && iSeekTable.OffsetCount() > 0)
                                            //    && (iChannels != 0
                                            //    && iBitDepth != 0
                                            //    && iSampleRate != 0)
                                            //    )
                                            //{

                                            if ((iSampleSizeTable.Count() > 0) // may not be valid if SampleSizeTable is changed to support a fixed sample size.
                                                && iSeekTable.Initialised()
                                                && (iChannels != 0
                                                && iBitDepth != 0
                                                && iSampleRate != 0)) {
                                                    iProcessingMetadataComplete = true;
                                                    break;
                                            }
                                        }
                                    }
                                    box4.SkipRemaining();
                                    box4.Clear();
                                    if (iProcessingMetadataComplete) {
                                        break;
                                    }
                                }
                            }
                            box3.SkipRemaining();
                            box3.Clear();
                            //if ((iTimescale != 0 && iDuration != 0)                         // from mdhd box.
                            //    && (iChannels != 0 && iBitDepth != 0 && iSampleRate != 0))  // from minf.stbl.stsd.mp4a box.
                            //        {
                            //        break;
                            //}
                            if (iProcessingMetadataComplete) {
                                break;
                            }
                        }
                    }
                    box2.SkipRemaining();
                    box2.Clear();
                    if (iProcessingMetadataComplete) {
                        break;
                    }
                }
            }
            box1.SkipRemaining();
            box1.Clear();
            if (iProcessingMetadataComplete) {
                break;
            }
        }
    }
    catch (ReaderError&) {
        THROW(MediaMpeg4FileInvalid);
    }

    LOG(kCodec, "<Mpeg4Container::ParseMetadataBox\n");

    return iProcessingMetadataComplete; // FIXME - if doing this, use a local var instead.
}

void Mpeg4Container::ParseBoxMdhd(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    // May throw ReaderError or MediaMpeg4FileInvalid.
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version == 0) {
        // All values are 32-bits in version 0.

        // FIXME - only reason to pass Mpeg4Box in is to call Skip().
        // Could instead write a helper method that calls Read() on an IReader until all bytes skipped (or throw error).
        // FIXME - also don't need to pass in aBytes if passing in an Mpeg4Box.

        aBox.Skip(4);   // Skip creation_time.
        aBox.Skip(4);   // Skip modification_time.
        iTimescale = readerBin.ReadUintBe(4);
        iDuration = readerBin.ReadUintBe(4);
    }
    else if (version == 1) {
        // Timescale is 32-bits and duration is 64-bits in version 1.
        aBox.Skip(8);   // Skip creation_time.
        aBox.Skip(8);   // Skip modification_time.
        iTimescale = readerBin.ReadUintBe(4);
        iDuration = readerBin.ReadUint64Be(8);
    }
    else {
        THROW(MediaMpeg4FileInvalid);
    }
}

void Mpeg4Container::ParseBoxMp4a(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    iCodec.Replace("mp4a");
    ReaderBinary readerBin(aBox);
    aBox.Skip(6);    // Skip 6-byte reserved block.
    aBox.Skip(2);    // Skip 2 byte data ref index.
    aBox.Skip(4*2);    // Skip 4-byte*2 reserved block.
    iChannels = readerBin.ReadUintBe(2);    // Only 2 bytes!
    iBitDepth = readerBin.ReadUintBe(2);    // Only 2 bytes!
    aBox.Skip(2);    // Skip pre-defined block.
    aBox.Skip(2);    // Skip reserved block.
    iSampleRate = readerBin.ReadUintBe(2);  // Only read upper 2 MSBs of sample rate.
    aBox.Skip(2);    // Don't care about 2 LSBs of sample rate (unused).
}

void Mpeg4Container::ParseBoxStts(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    // Table of audio samples per sample - used to convert audio samples to codec samples.
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint entries = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseAudioSamplesPerSample(entries);
    for (TUint i=0; i<entries; i++) {
        const TUint sampleCount = readerBin.ReadUintBe(4);
        const TUint sampleDelta = readerBin.ReadUintBe(4);
        iSeekTable.SetAudioSamplesPerSample(sampleCount, sampleDelta);
    }
}

void Mpeg4Container::ParseBoxStsc(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    // Table of samples per chunk - used to seek to specific sample.
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint entries = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseSamplesPerChunk(entries);
    for (TUint i=0; i<entries; i++) {
        const TUint firstChunk = readerBin.ReadUintBe(4);
        const TUint samplesPerChunk = readerBin.ReadUintBe(4);
        const TUint sampleDescriptionIndex = readerBin.ReadUintBe(4);

        iSeekTable.SetSamplesPerChunk(firstChunk, samplesPerChunk, sampleDescriptionIndex);
    }
}

void Mpeg4Container::ParseBoxStco(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    // Table of file offsets for each chunk (32-bit offsets).
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint entries = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseOffsets(entries);

    for (TUint i=0; i<entries; i++) {
        const TUint chunkOffset = readerBin.ReadUintBe(4);
        iSeekTable.SetOffset(chunkOffset);
    }
}

void Mpeg4Container::ParseBoxCo64(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    // Table of file offsets for each chunk (64-bit offsets).
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint entries = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseOffsets(entries);

    for (TUint i=0; i<entries; i++) {
        const TUint64 chunkOffset = readerBin.ReadUint64Be(8);
        iSeekTable.SetOffset(chunkOffset);
    }
}

void Mpeg4Container::ParseBoxStsz(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(4);
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint sampleSize = readerBin.ReadUintBe(4);
    ASSERT(sampleSize == 0); // FIXME - Don't currently support a constant sample size. Would require alterations to SampleSizeTable to allow it to be used with a fixed sample size with 0 entries.
    const TUint sampleCount = readerBin.ReadUintBe(4);
    if (sampleSize == 0) {
        iSampleSizeTable.Init(sampleCount);
        for (TUint i=0; i<sampleCount; i++) {
            const TUint entrySize = readerBin.ReadUintBe(4);
            iSampleSizeTable.AddSampleSize(entrySize);
        }
    }
}

void Mpeg4Container::ParseBoxStreamDescriptor(Mpeg4Box& aBox, TUint /*aBytes*/)
{
    ReaderBinary readerBin(aBox);
    const TUint version = readerBin.ReadUintBe(1);  // Only 1 byte!
    if (version != 0) {
        THROW(MediaMpeg4FileInvalid);
    }
    aBox.Skip(3);    // Skip 24-bit field reserved for flags.

    // FIXME - instead of doing this, just pass this bit of stream directly on to codec. Means no local storage req'd.
    TUint remaining = aBox.Size() - 12;
    iStreamDescriptor.SetBytes(0);
    while (remaining > 0) {
        Brn buf = aBox.Read(remaining);
        if (buf.Bytes() == 0) {

            THROW(MediaMpeg4FileInvalid);
        }
        iStreamDescriptor.Append(buf);
        remaining -= buf.Bytes();
    }
}


// Mpeg4MediaInfoBase

//Mpeg4MediaInfoBase::Mpeg4MediaInfoBase(ICodecController& aController)
//    : iController(aController)
//{
//}
//
//Mpeg4MediaInfoBase::~Mpeg4MediaInfoBase()
//{
//}

//void Mpeg4MediaInfoBase::Process()
//{
//    LOG(kMedia, "Checking for Raop container\n");
//
//    try {
//        Bws<60> data;
//        iController.Read(data, 4);
//
//        LOG(kMedia, "data %x {", data[0]);
//        LOG(kMedia, data);
//        LOG(kMedia, "}\n");
//
//        if(data != Brn("Raop")) {
//            THROW(MediaCodecRaopNotFound);
//        }
//
//        // If RAOP is only used by alac, why bother going to extra lengths and creating a pseudo-identifier?
//        //aSelector.iCodecContainer->SetName(Brn("alas"));  // this is used for codec recognition - streamed alac
//        iSamplesTotal = 0;  // continual stream
//
//        // fmtp should hold the sdp fmtp numbers from e.g. a=fmtp:96 4096 0 16 40 10 14 2 255 0 0 44100
//        // extract enough info from this for codec selector, then pass the raw fmtp through for alac decoder
//        // first read the number of bytes in for the fmtp
//        data.SetBytes(0);
//        iController.Read(data, 4);
//        TUint bytes = Ascii::Uint(data);    // size of fmtp string
//        data.SetBytes(0);
//        iController.Read(data, bytes);
//        Parser fmtp(data);
//
//        LOG(kMedia, "fmtp [");
//        LOG(kMedia, fmtp.NextLine());
//        LOG(kMedia, "]\n");
//
//        fmtp.Set(data);
//        iCodecSpecificData.SetBytes(0);
//
//        try {
//            WriterBuffer writerBuf(iCodecSpecificData);
//            WriterBinary writerBin(writerBuf);
//            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // ?
//            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // max_samples_per_frame
//            iCodecSpecificData.Append(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // 7a
//
//            iBitDepth = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));                      // bit depth
//            writerBin.WriteUint8(static_cast<TUint8>(iBitDepth));
//
//            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_historymult
//            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_initialhistory
//            writerBin.WriteUint8(static_cast<TUint8>(Ascii::Uint(fmtp.Next())));        // rice_kmodifier
//
//            iChannels = static_cast<TUint16>(Ascii::Uint(fmtp.Next()));                      // 7f - I think that this is channels
//            writerBin.WriteUint8(static_cast<TUint8>(iChannels));
//
//            writerBin.WriteUint16Be(static_cast<TUint16>(Ascii::Uint(fmtp.Next())));       // 80
//            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // 82
//            writerBin.WriteUint32Be(Ascii::Uint(fmtp.Next()));           // 86
//
//            TUint rate = Ascii::Uint(fmtp.NextLine());
//            iTimescale = rate;
//            iSampleRate = rate;
//            writerBin.WriteUint32Be(rate); // parsed fmtp data to be passed to alac decoder
//        }
//        catch (AsciiError&) {
//            THROW(MediaCodecRaopNotFound);
//        }
//        data.SetBytes(bytes);
//
//        LOG(kMedia, "Mpeg4MediaInfoBase RAOP header found %d bytes\n", bytes);
//    }
//    catch (CodecStreamCorrupt&) {   // FIXME - can this actually be thrown from operations in here?
//        THROW(MediaCodecRaopNotFound); // not enough data found to be Raop container
//    }
//}
