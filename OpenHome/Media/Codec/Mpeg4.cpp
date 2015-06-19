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
    // FIXME - can just call Read() here! - but would need to call it until all bytes read.
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


// Mpeg4BoxStack

Mpeg4BoxStack::Mpeg4BoxStack(TUint aNestCount)
    : iReader(NULL)
    , iIndex(0)
{
    iBoxes.reserve(aNestCount);
    for (TUint i=0; i<aNestCount; i++) {
        iBoxes.push_back(new Mpeg4Box());
    }
}

Mpeg4BoxStack::~Mpeg4BoxStack()
{
    for (TUint i=0; i<iBoxes.size(); i++) {
        delete iBoxes[i];
    }
}

void Mpeg4BoxStack::Set(IReader& aReader)
{
    //ASSERT(iReader == NULL);
    iReader = &aReader;
}

void Mpeg4BoxStack::Push()
{
    ASSERT(iReader != NULL);
    ASSERT(iIndex < iBoxes.size());

    IReader* reader = iReader;
    if (iIndex > 0) {
        reader = iBoxes[iIndex-1];
    }

    iIndex++;
    iBoxes[iIndex-1]->Set(*reader);
}

void Mpeg4BoxStack::Pop()
{
    ASSERT(iIndex > 0);
    iIndex--;
}

void Mpeg4BoxStack::Reset()
{
    for (TUint i=0; i<iBoxes.size(); i++) {
        iBoxes[i]->Clear();
    }
    iIndex = 0;
}

void Mpeg4BoxStack::Clear()
{
    ASSERT(iIndex > 0);
    iBoxes[iIndex-1]->Clear();
}

void Mpeg4BoxStack::ReadHeader()
{
    ASSERT(iIndex > 0);
    iBoxes[iIndex-1]->ReadHeader();
}

TUint Mpeg4BoxStack::Size() const
{
    ASSERT(iIndex > 0);
    return iBoxes[iIndex-1]->Size();
}

const Brx& Mpeg4BoxStack::Id() const
{
    ASSERT(iIndex > 0);
    return iBoxes[iIndex-1]->Id();
}

void Mpeg4BoxStack::SkipRemaining()
{
    ASSERT(iIndex > 0);
    return iBoxes[iIndex-1]->SkipRemaining();
}

void Mpeg4BoxStack::Skip(TUint aBytes)
{
    ASSERT(iIndex > 0);
    iBoxes[iIndex-1]->Skip(aBytes);
}

Brn Mpeg4BoxStack::Read(TUint aBytes)
{
    ASSERT(iIndex > 0);
    return iBoxes[iIndex-1]->Read(aBytes);
}

void Mpeg4BoxStack::ReadFlush()
{
    ASSERT(iIndex > 0);
    iBoxes[iIndex-1]->ReadFlush();
}

void Mpeg4BoxStack::ReadInterrupt()
{
    ASSERT(iIndex > 0);
    iBoxes[iIndex-1]->ReadInterrupt();
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
    ASSERT(iTable.size() == 0);
    iTable.reserve(aMaxEntries);
}

void SampleSizeTable::Clear()
{
    iTable.clear();
}

void SampleSizeTable::AddSampleSize(TUint aSize)
{
    if (iTable.size() == iTable.capacity()) {
        // File contains more sample sizes than it reported (and than we reserved capacity for).
        THROW(MediaMpeg4FileInvalid);
    }
    iTable.push_back(aSize);
}

TUint32 SampleSizeTable::SampleSize(TUint aIndex) const
{
    if(aIndex > iTable.size()-1) {
        THROW(MediaMpeg4FileInvalid);   // FIXME - sign of corrupt file or programmer error (i.e., should ASSERT)?
    }
    return iTable[aIndex];
}

TUint32 SampleSizeTable::Count() const
{
    return iTable.size();
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

    // FIXME - don't move through loop backwards.
    TUint current = iSamplesPerChunk.size() - 1;
    for (;;) {
        // Note: aChunkIndex = 0 => iFirstChunk = 1
        if (iSamplesPerChunk[current].iFirstChunk <= aChunkIndex + 1) {
            return iSamplesPerChunk[current].iSamples;
        }
        ASSERT(current != 0);
        current--;
    }
}

TUint SeekTable::StartSample(TUint aChunkIndex) const
{
    // NOTE: chunk indexes passed in start from 0, but chunks referenced within seek table start from 1.
    TUint startSample = 0;
    const TUint desiredChunk = aChunkIndex+1;
    TUint prevFirstChunk = 1;
    TUint prevSamples = 0;
    for (TUint i=0; i<iSamplesPerChunk.size(); i++) {
        const TUint nextFirstChunk = iSamplesPerChunk[i].iFirstChunk;
        const TUint nextSamples = iSamplesPerChunk[i].iSamples;

        // Desired chunk was within last chunk range.
        if (nextFirstChunk >= desiredChunk) {
            const TUint chunkDiff = desiredChunk - prevFirstChunk;
            startSample += chunkDiff*prevSamples;
            break;
        }

        const TUint chunkDiff = nextFirstChunk - prevFirstChunk;
        startSample += chunkDiff*prevSamples;
        prevFirstChunk = nextFirstChunk;
        prevSamples = nextSamples;
    }

    return startSample;
}

TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint64& aSample)
{
    if (iSamplesPerChunk.size() == 0 || iAudioSamplesPerSample.size() == 0 || iOffsets.size() == 0) {
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
    for (TUint entry = 0; entry < iAudioSamplesPerSample.size(); entry++) {
        samplecount = iAudioSamplesPerSample[entry].iSampleCount;
        audiosamples = iAudioSamplesPerSample[entry].iAudioSamples;
        if (aAudioSample <= (totalaudiosamples + samplecount * audiosamples)) {
            break; // audio samples are within this range
        }
        totalaudiosamples += samplecount * audiosamples;
        totalsamples = samplecount;

    }
    if (totalaudiosamples != 0 && aAudioSample>totalaudiosamples) {
        aAudioSample = totalaudiosamples - 1; // keep within range
    }
    if (audiosamples == 0)
        THROW(CodecStreamCorrupt); // invalid table // FIXME - THROW Mpeg4MediaFileInvalid instead?

    aSample = totalsamples + (aAudioSample - totalaudiosamples) / audiosamples; // convert audio sample count to codec samples

    // stsc:
    // chunk is found by searching to the entry in the table before samples > first chunk
    // and interpolating to get exact chunk
    totalsamples = 0;
    TUint32 nextspc = 0, spc = 0, chunks = 0;
    TUint32 seekchunk = 0, firstchunk = 1, nextchunk = 1;
    for (TUint entry = 0; entry < iSamplesPerChunk.size(); entry++) {
        nextchunk = iSamplesPerChunk[entry].iFirstChunk;
        nextspc = iSamplesPerChunk[entry].iSamples;
        chunks = nextchunk - firstchunk;
        if (aSample < (totalsamples + chunks * spc)) {
            break; // sample is within previous range
        }

        totalsamples += chunks * spc;
        firstchunk = nextchunk;
        spc = nextspc;
    }

    seekchunk = (TUint32)(firstchunk + ((aSample - totalsamples) / spc)); // calculate chunk that this sample is in
    TUint64 adjsample = ((seekchunk - firstchunk) * spc) + totalsamples; // calculate index to first sample in chunk
    aAudioSample -= (aSample - adjsample) * audiosamples;                // adjust audio sample count to index first sample in chunk
    aSample = adjsample;                                                 // adjust codec sample count to index first sample in chunk
    seekchunk -= 1;                                                      // adjust for array index (i.e. -1)

    //stco:
    if (seekchunk >= iOffsets.size()) { // error - required chunk doesn't exist
        THROW(CodecStreamCorrupt); // asserts later on !!! ToDo // FIXME - THROW Mpeg4MediaFileInvalid instead? - would still assert later on; need to catch and convert it to something that allows codec to send appropriate signal.
    }
    return iOffsets[seekchunk]; // entry found - return offset to required chunk
}


//TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint& aSample)
//{
//    Log::Print("aAudioSample: %llu, aSample: %u\n", aAudioSample, aSample);
//    if (iSamplesPerChunk.size() == 0 || iAudioSamplesPerSample.size() == 0 || iOffsets.size()==0) {
//        THROW(CodecStreamCorrupt); // seek table empty - cannot do seek // FIXME - throw a MpegMediaFileInvalid exception, which is actually expected/caught?
//    }
//    aSample = 0;
//    // fistly determine the required sample from the audio sample using the stts data,
//    // then work through samples per chunk table (stsc data) to get the chunk number for
//    // this particular sample, then get the chunk offset from the offset table (stco data)
//
//    // stts:
//    TUint64 totSamplesAudio = 0;
//    TUint totSamplesCodec = 0;
//
//    for (TUint i=0; i<iAudioSamplesPerSample.size(); i++) {
//        const TUint sampleCount = iAudioSamplesPerSample[i].iSampleCount;
//        const TUint audioSamples = iAudioSamplesPerSample[i].iAudioSamples;
//
//        TBool codecSampleFound = false;
//        for (TUint sample = 0; sample < sampleCount; sample++) {
//            if (totSamplesAudio + audioSamples >= aAudioSample) {
//                codecSampleFound = true;  // Audio samples are within this range.
//                break;
//            }
//
//            totSamplesAudio += audioSamples;
//            totSamplesCodec++;
//        }
//
//        if (codecSampleFound) {
//            break;
//        }
//    }
//
//    // FIXME - if stss box was present, must use it here to find appropriate sync sample.
//    // If stss box not present all codec samples are sync samples.
//
//    // stsc:
//    // chunk is found by searching to the entry in the table before samples > first chunk
//    // and interpolating to get exact chunk
//    TUint chunk = 0;
//    TUint samplesTotalStsc = 0;
//    for (TUint i = 0; i < iSamplesPerChunk.size(); i++) {
//        const TUint samples = iSamplesPerChunk[i].iSamples;
//        const TUint nextChunk = iSamplesPerChunk[i].iFirstChunk;
//        const TUint chunkDiff = nextChunk - chunk;
//
//        TBool chunkFound = false;
//        const TUint endChunk = chunk + chunkDiff;
//        for (TUint chunkEntry = chunk; chunkEntry < endChunk; chunkEntry++) {
//            if (samplesTotalStsc + samples >= totSamplesCodec) {
//                chunkFound = true;
//                break;
//            }
//            samplesTotalStsc += samples;
//            chunk++;
//        }
//
//        if (chunkFound) {
//            break;
//        }
//    }
//
//    // Update output params to match chunk.
//    aSample = samplesTotalStsc;
//
//    TUint chunkStartSampleAudio = 0;
//    TUint chunkStartSampleCodec = 0;
//    for (TUint i = 0; i < iAudioSamplesPerSample.size(); i++) {
//        const TUint sampleCount = iAudioSamplesPerSample[i].iSampleCount;
//        const TUint audioSamples = iAudioSamplesPerSample[i].iAudioSamples;
//
//        TBool startSampleFound = false;
//        for (TUint sample = 0; sample < sampleCount; sample++) {
//            if (chunkStartSampleCodec + 1 >= samplesTotalStsc) {
//                startSampleFound = true;  // Audio samples are within this range.
//                break;
//            }
//
//            chunkStartSampleAudio += audioSamples;
//            chunkStartSampleCodec++;
//        }
//    }
//
//    aAudioSample = chunkStartSampleAudio;
//
//
//    //stco:
//    if (chunk >= iOffsets.size()) { // error - required chunk doesn't exist
//        THROW(CodecStreamCorrupt); // asserts later on !!! ToDo // FIXME - THROW Mpeg4MediaFileInvalid instead? - would still assert later on; need to catch and convert it to something that allows codec to send appropriate signal.
//    }
//    return iOffsets[chunk]; // entry found - return offset to required chunk
//}

TUint64 SeekTable::GetOffset(TUint aChunkIndex) const
{
    ASSERT(aChunkIndex < iOffsets.size());
    return iOffsets[aChunkIndex];
}

void SeekTable::Write(IWriter& aWriter) const
{
    WriterBinary writerBin(aWriter);

    const TUint samplesPerChunkCount = iSamplesPerChunk.size();
    writerBin.WriteUint32Be(samplesPerChunkCount);
    for (TUint i=0; i<samplesPerChunkCount; i++) {
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iFirstChunk);
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iSamples);
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iSampleDescriptionIndex);
    }

    const TUint audioSamplesPerSampleCount = iAudioSamplesPerSample.size();
    writerBin.WriteUint32Be(audioSamplesPerSampleCount);
    for (TUint i=0; i<audioSamplesPerSampleCount; i++) {
        writerBin.WriteUint32Be(iAudioSamplesPerSample[i].iSampleCount);
        writerBin.WriteUint32Be(iAudioSamplesPerSample[i].iAudioSamples);
    }

    const TUint chunkCount = iOffsets.size();
    writerBin.WriteUint32Be(chunkCount);
    for (TUint i=0; i<chunkCount; i++) {
        writerBin.WriteUint64Be(iOffsets[i]);
    }
}


// SeekTableInitialiser

SeekTableInitialiser::SeekTableInitialiser(SeekTable& aSeekTable, IReader& aReader)
    : iSeekTable(aSeekTable)
    , iReader(aReader)
    , iInitialised(false)
{
}

void SeekTableInitialiser::Init()
{
    ASSERT(!iInitialised);
    ReaderBinary readerBin(iReader);
    const TUint samplesPerChunkCount = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseSamplesPerChunk(samplesPerChunkCount);
    for (TUint i = 0; i<samplesPerChunkCount; i++) {
        const TUint firstChunk = readerBin.ReadUintBe(4);
        const TUint samples = readerBin.ReadUintBe(4);
        const TUint sampleDescriptionIndex = readerBin.ReadUintBe(4);
        iSeekTable.SetSamplesPerChunk(firstChunk, samples, sampleDescriptionIndex);
    }

    const TUint audioSamplesPerSampleCount = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseAudioSamplesPerSample(audioSamplesPerSampleCount);
    for (TUint i = 0; i<audioSamplesPerSampleCount; i++) {
        const TUint sampleCount = readerBin.ReadUintBe(4);
        const TUint audioSamples = readerBin.ReadUintBe(4);
        iSeekTable.SetAudioSamplesPerSample(sampleCount, audioSamples);
    }

    const TUint chunkCount = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseOffsets(chunkCount);
    for (TUint i = 0; i<chunkCount; i++) {
        const TUint64 offset = readerBin.ReadUint64Be(8);
        iSeekTable.SetOffset(offset);
    }
    iInitialised = true;
}


// MsgAudioEncodedWriter

MsgAudioEncodedWriter::MsgAudioEncodedWriter(MsgFactory& aMsgFactory)
    : iMsgFactory(aMsgFactory)
    , iMsg(NULL)
{
}

MsgAudioEncodedWriter::~MsgAudioEncodedWriter()
{
    ASSERT(iMsg == NULL);
    ASSERT(iBuf.Bytes() == 0);
}

MsgAudioEncoded* MsgAudioEncodedWriter::Msg()
{
    ASSERT(iBuf.Bytes() == 0);  // Ensure no audio still buffered.
    MsgAudioEncoded* msg = iMsg;
    iMsg = NULL;
    return msg;
}

void MsgAudioEncodedWriter::Write(TByte aValue)
{
    const TUint bufCapacity = iBuf.MaxBytes() - iBuf.Bytes();
    if (bufCapacity >= sizeof(TByte)) {
        iBuf.Append(aValue);
    }
    else {
        AllocateMsg();
        iBuf.Append(aValue);
    }
}

void MsgAudioEncodedWriter::Write(const Brx& aBuffer)
{
    TUint remaining = aBuffer.Bytes();
    TUint offset = 0;

    while (remaining > 0) {
        const TUint bufCapacity = iBuf.MaxBytes() - iBuf.Bytes();

        // Do a partial append of aBuffer if space in iBuf.
        if (bufCapacity > 0) {
            TUint bytes = bufCapacity;
            if (remaining < bufCapacity) {
                bytes = remaining;
            }
            iBuf.Append(iBuf.Ptr() + offset, bytes);
            offset += bytes;
            remaining -= bytes;
        }
        else {
            AllocateMsg();
        }
    }
}

void MsgAudioEncodedWriter::WriteFlush()
{
    if (iBuf.Bytes() > 0) {
        AllocateMsg();
    }
}

void MsgAudioEncodedWriter::AllocateMsg()
{
    ASSERT(iBuf.Bytes() > 0);
    MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(Brn(iBuf.Ptr(), iBuf.Bytes()));
    if (iMsg == NULL) {
        iMsg = msg;
    }
    else {
        iMsg->Add(msg);
    }
    iBuf.SetBytes(0);
}


// Mpeg4Container

Mpeg4Container::Mpeg4Container()
    : iBoxStack(kMetadataBoxDepth)
{
    LOG(kMedia, "Mpeg4Container::Mpeg4Container\n");
    Clear();
}

TBool Mpeg4Container::Recognise(Brx& aBuf)
{
    LOG(kMedia, "Mpeg4Container::Recognise\n");
    if (aBuf.Bytes() >= Mpeg4Box::kBoxHeaderBytes) {
        if (Brn(aBuf.Ptr()+Mpeg4Box::kBoxSizeBytes, Mpeg4Box::kBoxNameBytes) == Brn("ftyp")) {
            return true;
        }
    }

    return false;
}

Msg* Mpeg4Container::ProcessMsg(MsgEncodedStream* aMsg)
{
    Msg* msg = ContainerBase::ProcessMsg(aMsg);
    Clear();
    return msg;
}

Msg* Mpeg4Container::ProcessMsg(MsgAudioEncoded* aMsg)
{
    AddToAudioEncoded(aMsg);

    if (!iPulling) {
        MsgAudioEncoded* msg = Process();
        ASSERT(iAudioEncoded == NULL);  // iAudioEncoded should have been exhausted.
        return msg;
    }
    return NULL;
}

TUint Mpeg4Container::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    // As TrySeek requires a byte offset, any codec that uses an Mpeg4 stream MUST find the appropriate seek offset (in bytes) and pass that via TrySeek().
    // i.e., aOffset MUST match a chunk offset.
    const TUint chunkCount = iSeekTable.ChunkCount();

    // FIXME - need lock
    for (TUint i = 0; i < chunkCount; i++) {
        if (iSeekTable.GetOffset(i) == aOffset) {
            iExpectedFlushId = iStreamHandler->TrySeek(aStreamId, aOffset);
            if (iExpectedFlushId != MsgFlush::kIdInvalid) {
                iPos = aOffset;
                iBuf.SetBytes(0);
                iChunkIndex = i;
                iChunkBytesRemaining = 0;
                iBytesToDiscard = 0;
            }
            return iExpectedFlushId;
        }
    }
    ASSERTS();
    return MsgFlush::kIdInvalid;
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

void Mpeg4Container::Clear()
{
    iBoxStack.Reset();
    iPos = 0;
    iBuf.SetBytes(0);
    iMetadataRetrieved = false;
    iChunkIndex = 0;
    iChunkBytesRemaining = 0;
    iBytesToDiscard = 0;
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
}

MsgAudioEncoded* Mpeg4Container::Process()
{

    // FIXME - If we did handle files with mdat before moov, would have to ensure we didn't attempt to process moov after end of mdat, i.e., somehow terminate when we reach end of mdat, which is detectable by various means.

    MsgAudioEncoded* msgOut = NULL;

    if (!iMetadataRetrieved) {
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
                    ParseMetadataBox(box, box.Size());    // Exception thrown if invalid/EoS.
                    iMetadataRetrieved = true;
                }
                else if (box.Id() == Brn("mdat")) {
                    if (!iMetadataRetrieved) {
                        // Not yet encountered metadata (moov) box.
                        // Do out-of-band read to get moov box.
                        Bws<1024> buf;
                        ReaderBuffer reader(buf);
                        //const TUint metadataSize = box.Size();
                        ParseMetadataBox(reader, box.Size()); // Exception thrown if invalid/EoS.
                        iMetadataRetrieved = true;
                    }

                    break;

                    // FIXME - not quite good enough - would need to skip over mdat in out-of-band read and then potentially have to skip over some more boxes to get to the moov box.
                    // So, pass off to a function that will do out-of-band reads until we get to moov box.
                    // And then, implement a special out-of-band IReader that will read from a small, fixed-size buffer (i.e., 1k) and will go do more out-of-band reads when we attempt to read beyond end of buffer
                    // - will need to ensure read/discard behaviour is decided by then, as only real option for that is to discard audio as we go beyond end of buffer
                    // - that probably means that's the behaviour we should take with normal parsing circumstance - just discard data as it's read (or, discard prev read data on next read so it at least remains in memory while it may be used), as we don't ever backtrace during normal parsing.

                    // In the interim, just flush all remaining data.
                }
                box.SkipRemaining();
                box.Clear();
            }
        }
        // Exhausted/invalid stream while processing container.
        // Should just silently drop all remaining audio until new stream seen.
        catch (MediaMpeg4EndOfData&) {

        }
        catch (MediaMpeg4FileInvalid&) {

        }

        ASSERT(iMetadataRetrieved);
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
        MsgAudioEncoded* msgSampleSizeTable = WriteSampleSizeTable();
        ASSERT(msgSampleSizeTable != NULL);
        msgOut->Add(msgSampleSizeTable);

        // Write seek table so that codec can determine correct byte position that it should request to seek to.
        // FIXME - there should be no need for a codec to know this, but IStreamHandler requires seek position in bytes, for which SeekTable is required.
        MsgAudioEncoded* msgSeekTable = WriteSeekTable();
        ASSERT(msgSeekTable != NULL);
        msgOut->Add(msgSeekTable);
    }


    MsgAudioEncoded* msgAudio = ProcessNextAudioBlock();
    ASSERT(iAudioEncoded == NULL);
    if (msgOut == NULL) {
        msgOut = msgAudio;
    }
    else {
        if (msgAudio != NULL) {
            msgOut->Add(msgAudio);
        }
    }

    return msgOut;
}

MsgAudioEncoded* Mpeg4Container::WriteSampleSizeTable() const
{
    MsgAudioEncodedWriter writerMsg(*iMsgFactory);
    WriterBinary writerBin(writerMsg);

    const TUint count = iSampleSizeTable.Count();
    writerBin.WriteUint32Be(count);
    for (TUint i=0; i<count; i++) {
        writerBin.WriteUint32Be(iSampleSizeTable.SampleSize(i));
    }
    writerMsg.WriteFlush();

    MsgAudioEncoded* msg = writerMsg.Msg();
    return msg;
}

MsgAudioEncoded* Mpeg4Container::WriteSeekTable() const
{
    MsgAudioEncodedWriter writerMsg(*iMsgFactory);
    iSeekTable.Write(writerMsg);
    writerMsg.WriteFlush();

    MsgAudioEncoded* msg = writerMsg.Msg();
    return msg;
}

MsgAudioEncoded* Mpeg4Container::ProcessNextAudioBlock()
{
    MsgAudioEncoded* msg = NULL;
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
                iAudioEncoded = NULL;
                return msg;
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
            if (msg == NULL) {
                msg = iAudioEncoded;
            }
            else {
                msg->Add(iAudioEncoded);
            }
            iAudioEncoded = remainder;
            iChunkBytesRemaining = 0;

            iChunkIndex++;
        }
        else {  // iAudioEncoded->Bytes() <= iChunkBytesRemaining
            iChunkBytesRemaining -= iAudioEncoded->Bytes();
            iPos += iAudioEncoded->Bytes();     // FIXME - provide wrapper for incrementing iPos?
            if (msg == NULL) {
                msg = iAudioEncoded;
            }
            else {
                msg->Add(iAudioEncoded);
            }
            iAudioEncoded = NULL;
        }
    }

    if (iAudioEncoded != NULL) {
        // Some iAudioEncoded left, but should have exhausted all chunks.
        // So remaining iAudioEncoded must be other data.
        // FIXME - discard until start of next stream?
        ASSERT(iChunkIndex == iSeekTable.ChunkCount());

        // FIXME - update iPos?
        iAudioEncoded->RemoveRef();
        iAudioEncoded = NULL;
    }

    return msg;
}

void Mpeg4Container::ParseMetadataBox(IReader& aReader, TUint /*aBytes*/)
{
    // Need to move through stack to get data from the following boxes:
    // -- moov.trak.mdia.mdhd
    // -- moov.trak.mdia.minf
    // ---- moov.trak.mdia.minf.stbl.stsd
    // ------ moov.trak.mdia.minf.stbl.stsd.mp4a
    // -------- moov.trak.mdia.minf.stbl.stsd.mp4a.esds
    // ---- moov.trak.mdia.minf.stbl.stts
    // ---- moov.trak.mdia.minf.stbl.stsc
    // ---- moov.trak.mdia.minf.stbl.stco
    // ---- moov.trak.mdia.minf.stbl.co64
    // ---- moov.trak.mdia.minf.stbl.stsz

    //iBoxStack.Set(aReader);
    //try {
    //    iBoxStack.Push();
    //    for (;;) {
    //        iBoxStack.ReadHeader();
    //        if (iBoxStack.Id() == Brn("trak")) {
    //            ParseBoxTrak();
    //            break;
    //        }
    //        iBoxStack.SkipRemaining();
    //        iBoxStack.Clear();
    //    }
    //    iBoxStack.SkipRemaining();
    //    iBoxStack.Clear();
    //    iBoxStack.Pop();
    //}
    //catch (ReaderError&) {
    //    THROW(Mpeg4FileInvalid);
    //}
    //catch (Mpeg4FileInvalid&) {
    //    throw;
    //}

    TBool complete = false;

    iBoxStack.Set(aReader);
    try {
        iBoxStack.Push();
        for (;;) {
            iBoxStack.ReadHeader();
            if (iBoxStack.Id() == Brn("trak")) {
                iBoxStack.Push();
                for (;;) {
                    iBoxStack.ReadHeader();
                    if (iBoxStack.Id() == Brn("mdia")) {
                        iBoxStack.Push();
                        for (;;) {
                            iBoxStack.ReadHeader();
                            if (iBoxStack.Id() == Brn("mdhd")) {
                                ParseBoxMdhd(iBoxStack, iBoxStack.Size());
                            }
                            else if (iBoxStack.Id() == Brn("minf")) {
                                iBoxStack.Push();
                                for (;;) {
                                    iBoxStack.ReadHeader();
                                    if (iBoxStack.Id() == Brn("stbl")) {
                                        iBoxStack.Push();
                                        for (;;) {
                                            iBoxStack.ReadHeader();
                                            if (iBoxStack.Id() == Brn("stsd")) {
                                                ReaderBinary readerBin(iBoxStack);
                                                iBoxStack.Skip(4);   // Skip version info.
                                                const TUint sampleEntries = readerBin.ReadUintBe(4);
                                                iBoxStack.Push();
                                                for (TUint i=0; i<sampleEntries; i++) {
                                                    iBoxStack.ReadHeader();
                                                    if (iBoxStack.Id() == Brn("mp4a")) {  // Only care about audio.
                                                        ParseBoxCodec(iBoxStack, iBoxStack.Size(), Brn("mp4a"));
                                                        iBoxStack.Push();
                                                        for (;;) {
                                                            iBoxStack.ReadHeader();
                                                            if (iBoxStack.Id() == Brn("esds")) {
                                                                // FIXME - valid to filter this box by known content type?
                                                                // Should we just process next box, regardless of type, and assume it always sits at this position and is in same format?
                                                                Log::Print("found esds stream descriptor box\n");

                                                                ParseBoxStreamDescriptor(iBoxStack, iBoxStack.Size());
                                                                break;
                                                            }
                                                            iBoxStack.SkipRemaining();
                                                            iBoxStack.Clear();
                                                        }
                                                        iBoxStack.SkipRemaining();
                                                        iBoxStack.Clear();
                                                        iBoxStack.Pop();
                                                        break;  // FIXME - correct thing to do?

                                                    }
                                                    else if (iBoxStack.Id() == Brn("alac")) {
                                                        ParseBoxCodec(iBoxStack, iBoxStack.Size(), Brn("alac"));
                                                        iBoxStack.Push();
                                                        for (;;) {
                                                            iBoxStack.ReadHeader();
                                                            if (iBoxStack.Id() == Brn("alac")) {
                                                                // FIXME - valid to filter this box by known content type?
                                                                // Should we just process next box, regardless of type, and assume it always sits at this position and is in same format?
                                                                Log::Print("found alac stream descriptor box\n");
                                                                ParseBoxAlac(iBoxStack, iBoxStack.Size());
                                                                break;
                                                            }
                                                            iBoxStack.SkipRemaining();
                                                            iBoxStack.Clear();
                                                        }
                                                        iBoxStack.SkipRemaining();
                                                        iBoxStack.Clear();
                                                        iBoxStack.Pop();
                                                        break;  // FIXME - correct thing to do?
                                                    }
                                                    iBoxStack.SkipRemaining();
                                                    iBoxStack.Clear();
                                                    // FIXME - what if we exhaust file (e.g., by not recognising one of the boxes above)? Should not assert (due to attempting to read more data), but should instead cause pipeline to report that stream failed to be recognised.
                                                }
                                                iBoxStack.SkipRemaining();
                                                iBoxStack.Clear();
                                                iBoxStack.Pop();
                                            }
                                            else if (iBoxStack.Id() == Brn("stts")) {
                                                ParseBoxStts(iBoxStack, iBoxStack.Size());
                                            }
                                            else if (iBoxStack.Id() == Brn("stsc")) {
                                                ParseBoxStsc(iBoxStack, iBoxStack.Size());
                                            }
                                            else if (iBoxStack.Id() == Brn("stco")) {
                                                // FIXME - check co64 (or stco) hasn't been processed
                                                ParseBoxStco(iBoxStack, iBoxStack.Size());
                                            }
                                            else if (iBoxStack.Id() == Brn("co64")) {
                                                // FIXME - check stco (or co64) hasn't been processed
                                                ParseBoxCo64(iBoxStack, iBoxStack.Size());
                                            }
                                            else if (iBoxStack.Id() == Brn("stsz")) {
                                                ParseBoxStsz(iBoxStack, iBoxStack.Size());
                                            }
                                            iBoxStack.SkipRemaining();
                                            iBoxStack.Clear();
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
                                                    iBoxStack.Pop();
                                                    complete = true;
                                                    break;
                                            }
                                        }
                                    }
                                    iBoxStack.SkipRemaining();
                                    iBoxStack.Clear();
                                    if (complete) {
                                        iBoxStack.Pop();
                                        break;
                                    }
                                }
                            }
                            iBoxStack.SkipRemaining();
                            iBoxStack.Clear();
                            //if ((iTimescale != 0 && iDuration != 0)                         // from mdhd box.
                            //    && (iChannels != 0 && iBitDepth != 0 && iSampleRate != 0))  // from minf.stbl.stsd.mp4a box.
                            //        {
                            //        break;
                            //}
                            if (complete) {
                                iBoxStack.Pop();
                                break;
                            }
                        }
                    }
                    iBoxStack.SkipRemaining();
                    iBoxStack.Clear();
                    if (complete) {
                        iBoxStack.Pop();
                        break;
                    }
                }
            }
            iBoxStack.SkipRemaining();
            iBoxStack.Clear();
            if (complete) {
                iBoxStack.Pop();
                break;
            }
        }
    }
    catch (ReaderError&) {
        THROW(MediaMpeg4FileInvalid);
    }
    catch (MediaMpeg4FileInvalid&) {
        throw;
    }

    LOG(kCodec, "<Mpeg4Container::ParseMetadataBox\n");
}

void Mpeg4Container::ParseBoxMdhd(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxCodec(IMpeg4Box& aBox, TUint /*aBytes*/, const Brx& aCodec)
{
    iCodec.Replace(aCodec);
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

void Mpeg4Container::ParseBoxStts(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxStsc(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxStco(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxCo64(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxStsz(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxStreamDescriptor(IMpeg4Box& aBox, TUint /*aBytes*/)
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

void Mpeg4Container::ParseBoxAlac(IMpeg4Box& aBox, TUint /*aBytes*/)
{
    // FIXME - instead of doing this, just pass this bit of stream directly on to codec. Means no local storage req'd.
    TUint remaining = aBox.Size() - Mpeg4Box::kBoxHeaderBytes;
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
