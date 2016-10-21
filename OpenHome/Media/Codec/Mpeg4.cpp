#include <OpenHome/Media/Codec/Mpeg4.h>
#include <OpenHome/Media/Codec/ContainerFactory.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Media/Debug.h>
#include <OpenHome/Media/MimeTypeList.h>

#include <limits>
#include <vector>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

ContainerBase* ContainerFactory::NewMpeg4(IMimeTypeList& aMimeTypeList)
{ // static
    return new Mpeg4Container(aMimeTypeList);
}



// Mpeg4Info

Mpeg4Info::Mpeg4Info() :
        iSampleRate(0), iTimescale(0), iChannels(0), iBitDepth(0), iDuration(0)
{
}

Mpeg4Info::Mpeg4Info(const Brx& aCodec, TUint aSampleRate, TUint aTimescale,
        TUint aChannels, TUint aBitDepth, TUint64 aDuration,
        const Brx& aStreamDescriptor) :
        iCodec(aCodec), iSampleRate(aSampleRate), iTimescale(aTimescale), iChannels(
                aChannels), iBitDepth(aBitDepth), iDuration(aDuration), iStreamDescriptor(
                aStreamDescriptor)
{
}

TBool Mpeg4Info::Initialised() const
{
    const TBool initialised = iCodec.Bytes() > 0 && iSampleRate != 0
            && iTimescale != 0 && iChannels != 0 && iBitDepth != 0
            && iDuration != 0 && iStreamDescriptor.Bytes() > 0;
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

Mpeg4InfoReader::Mpeg4InfoReader(IReader& aReader) :
        iReader(aReader)
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
    } catch (ReaderError&) {
        THROW(MediaMpeg4FileInvalid);
    }
}

// Mpeg4InfoWriter

Mpeg4InfoWriter::Mpeg4InfoWriter(const IMpeg4InfoReadable& aInfo) :
        iInfo(aInfo)
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

// Mpeg4BoxHeaderReader

void Mpeg4BoxHeaderReader::Reset(IMsgAudioEncodedCache& aCache)
{
    iCache = &aCache;
    iHeader.SetBytes(0);
    iId.Set(Brx::Empty());
    iBytes = 0;
    iHeaderReadPending = false;
}

Msg* Mpeg4BoxHeaderReader::ReadHeader()
{
    ASSERT(iCache != nullptr);
    while (iId.Bytes() == 0) {
        if (!iHeaderReadPending) {
            iCache->Inspect(iHeader, iHeader.MaxBytes());
            iHeaderReadPending = true;
        }
        Msg* msg = iCache->Pull();
        if (msg != nullptr) {
            return msg;
        }

        if (msg == nullptr && iHeader.Bytes() == 0) {
            // Was unable to read from cache.
            return nullptr;
        }

        iBytes = Converter::BeUint32At(iHeader, 0);
        iId.Set(iHeader.Ptr() + kSizeBytes, kNameBytes);
    }

    return nullptr;
}

TUint Mpeg4BoxHeaderReader::Bytes() const
{
    return iBytes;
}

TUint Mpeg4BoxHeaderReader::PayloadBytes() const
{
    ASSERT(iBytes >= kHeaderBytes);
    return iBytes - kHeaderBytes;
}

const Brx& Mpeg4BoxHeaderReader::Id() const
{
    return iId;
}

// Mpeg4BoxSwitcherRoot

const TChar* Mpeg4BoxSwitcherRoot::kNoTargetId = "";

Mpeg4BoxSwitcherRoot::Mpeg4BoxSwitcherRoot(IMpeg4BoxProcessorFactory& aProcessorFactory)
    : iProcessorFactory(aProcessorFactory)
    , iCache(nullptr)
    , iTargetId(kNoTargetId)
{
    Reset();
}

void Mpeg4BoxSwitcherRoot::Reset()
{
    iProcessor = nullptr;
    iState = eNone;
    iOffset = 0;
}

void Mpeg4BoxSwitcherRoot::Set(IMsgAudioEncodedCache& aCache, const TChar* aTargetId)
{
    iCache = &aCache;
    iTargetId.Set(aTargetId);
}

Msg* Mpeg4BoxSwitcherRoot::Process()
{
    while (iState != eComplete) {
        Msg* msg = nullptr;

        // All pulling calls below returns nullptr when there is something of interest for this class.
        if (iState == eHeader) {
            msg = iHeaderReader.ReadHeader();
        }
        else if (iState == eBox) {
            msg = iProcessor->Process();
        }

        if (msg != nullptr) {
            LOG(kCodec, "<Mpeg4BoxSwitcherRoot::Process pulled non-audio msg: %p\n", msg);
            return msg;
        }

        if (iState == eNone) {
            iHeaderReader.Reset(*iCache);
            iState = eHeader;
        }
        else if (iState == eHeader) {
            if (iHeaderReader.Bytes() == 0) {
                // Didn't manage to read header.
                return nullptr;
            }

            const Brx& id = iHeaderReader.Id();
            LOG(kCodec, "Mpeg4BoxSwitcherRoot::Process found box %.*s, %u bytes\n",
                        PBUF(id), iHeaderReader.Bytes());

            // Got header, now find a processor.
            try {
                iProcessor = &iProcessorFactory.GetMpeg4BoxProcessor(
                        iHeaderReader.Id(), iHeaderReader.PayloadBytes(),
                        *iCache);
                iState = eBox;
            }
            catch (Mpeg4BoxUnrecognised&) {
                const Brx& id = iHeaderReader.Id();
                LOG(kCodec, "Mpeg4BoxSwitcherRoot::Process couldn't find processor for %.*s, %u bytes\n",
                            PBUF(id), iHeaderReader.Bytes());

                iCache->Discard(iHeaderReader.PayloadBytes());
                iOffset += iHeaderReader.Bytes();
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else if (iState == eBox) {
            // If found target box ID, mark as complete. Otherwise, read next box.
            iOffset += iHeaderReader.Bytes();

            if (iHeaderReader.Id() == iTargetId) {
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eComplete;
            }
            else {
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TUint64 Mpeg4BoxSwitcherRoot::BoxOffset() const
{
    return iOffset;
}

// Mpeg4BoxSwitcher

Mpeg4BoxSwitcher::Mpeg4BoxSwitcher(IMpeg4BoxProcessorFactory& aProcessorFactory,
        const Brx& aBoxId) :
        iProcessorFactory(aProcessorFactory), iId(aBoxId)
{
    Reset();
}

Msg* Mpeg4BoxSwitcher::Process()
{
    while (!Complete()) {
        Msg* msg = nullptr;

        // All pulling calls below returns nullptr when there is something of interest for this class.
        if (iState == eHeader) {
            msg = iHeaderReader.ReadHeader();
        }
        else if (iState == eBox) {
            msg = iProcessor->Process();
        }

        if (msg != nullptr) {
            return msg;
        }

        if (iState == eNone) {
            iHeaderReader.Reset(*iCache);
            iState = eHeader;
        }
        else if (iState == eHeader) {
            const Brx& id = iHeaderReader.Id();
            LOG(kCodec, "Mpeg4BoxSwitcher::Process found box %.*s, %u bytes\n",
                        PBUF(id), iHeaderReader.Bytes());

            // Got header, now find a processor.
            try {
                iProcessor = &iProcessorFactory.GetMpeg4BoxProcessor(
                        iHeaderReader.Id(), iHeaderReader.PayloadBytes(),
                        *iCache);
                iState = eBox;
            } catch (Mpeg4BoxUnrecognised&) {
                const Brx& id = iHeaderReader.Id();
                LOG(kCodec, "Mpeg4BoxSwitcher::Process couldn't find processor for %.*s, %u bytes\n",
                            PBUF(id), iHeaderReader.Bytes());

                iCache->Discard(iHeaderReader.PayloadBytes());
                iOffset += iHeaderReader.Bytes();
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else if (iState == eBox) {
            // Box processing is complete.
            iOffset += iHeaderReader.Bytes();

            ASSERT(iOffset <= iBytes);
            if (iOffset == iBytes) {
                iState = eComplete;
            }
            else {
                // Read next box.
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxSwitcher::Complete() const
{
    return iOffset == iBytes;
}

void Mpeg4BoxSwitcher::Reset()
{
    //iCache = nullptr;
    iProcessor = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
}

TBool Mpeg4BoxSwitcher::Recognise(const Brx& aBoxId) const
{
    return aBoxId == iId;
}

void Mpeg4BoxSwitcher::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxProcessorFactory

void Mpeg4BoxProcessorFactory::Add(IMpeg4BoxRecognisable* aProcessor)
{
    iProcessors.push_back(
            std::unique_ptr < IMpeg4BoxRecognisable > (aProcessor));
}

IMpeg4BoxProcessor& Mpeg4BoxProcessorFactory::GetMpeg4BoxProcessor(
        const Brx& aBoxId, TUint aBytes, IMsgAudioEncodedCache& aCache)
{
    for (auto& processor : iProcessors) {
        if (processor->Recognise(aBoxId)) {
            processor->Reset();
            processor->Set(aCache, aBytes);
            return *processor;
        }
    }
    THROW(Mpeg4BoxUnrecognised);
}

void Mpeg4BoxProcessorFactory::Reset()
{
    for (auto& processor : iProcessors) {
        processor->Reset();
    }
}


// Mpeg4BoxMoov

Mpeg4BoxMoov::Mpeg4BoxMoov(IMpeg4BoxProcessorFactory& aProcessorFactory, IMpeg4MetadataNotifiable& aMetadataNotifiable)
    : Mpeg4BoxSwitcher(aProcessorFactory, Brn("moov"))
    , iMetadataNotifiable(aMetadataNotifiable)
{
    Reset();
}

Msg* Mpeg4BoxMoov::Process()
{
    Msg* msg = Mpeg4BoxSwitcher::Process();
    if (msg == nullptr) {
        iMetadataRetrieved = true;
        iMetadataNotifiable.MetadataRetrieved();
    }
    return msg;
}

void Mpeg4BoxMoov::Reset()
{
    Mpeg4BoxSwitcher::Reset();
    iMetadataRetrieved = false;
}

TBool Mpeg4BoxMoov::Recognise(const Brx& aBoxId) const
{
    // Only recognise if metadata has not already been retrieved.
    // i.e., ignore metadata if it was already read out-of-band.
    if (Mpeg4BoxSwitcher::Recognise(aBoxId) && !iMetadataRetrieved) {
        return true;
    }
    return false;
}



// Mpeg4BoxStts

Mpeg4BoxStts::Mpeg4BoxStts(SeekTable& aSeekTable)
    : iSeekTable(aSeekTable)
    , iCache(nullptr)
    , iBytes(0)
    , iOffset(0)
    , iSampleCount(0)
{
}

Msg* Mpeg4BoxStts::Process()
{
    // Table of audio samples per sample - used to convert audio samples to codec samples.

    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = Converter::BeUint32At(iBuf, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eEntries;
        }
        else if (iState == eEntries) {
            iOffset += iBuf.Bytes();
            iEntries = Converter::BeUint32At(iBuf, 0);
            iEntryCount = 0;
            iSeekTable.InitialiseAudioSamplesPerSample(iEntries);

            if (iEntries > 0) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eSampleCount;
            }
            else {
                iState = eComplete;
            }
        }
        else if (iState == eSampleCount) {
            iOffset += iBuf.Bytes();
            iSampleCount = Converter::BeUint32At(iBuf, 0);
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eSampleDelta;
        }
        else if (iState == eSampleDelta) {
            iOffset += iBuf.Bytes();
            const TUint sampleDelta = Converter::BeUint32At(iBuf, 0);
            iSeekTable.SetAudioSamplesPerSample(iSampleCount,
                sampleDelta);
            iSampleCount = 0;

            iEntryCount++;
            if (iEntryCount < iEntries) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eSampleCount;
            }
            else {
                if (!Complete()) {
                    iCache->Discard(iBytes - iOffset);
                    iOffset = iBytes;
                    THROW(MediaMpeg4FileInvalid);
                }
                iState = eComplete;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxStts::Complete() const
{
    return iOffset == iBytes;
}

void Mpeg4BoxStts::Reset()
{
    //iSeekTable.Deinitialise();
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iEntries = 0;
    iEntryCount = 0;
    iSampleCount = 0;
}

TBool Mpeg4BoxStts::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("stts");
}

void Mpeg4BoxStts::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxStsc

Mpeg4BoxStsc::Mpeg4BoxStsc(SeekTable& aSeekTable)
    : iSeekTable(aSeekTable)
{
    Reset();
}

Msg* Mpeg4BoxStsc::Process()
{
    // Table of samples per chunk - used to seek to specific sample.

    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = Converter::BeUint32At(iBuf, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eEntries;
        }
        else if (iState == eEntries) {
            iOffset += iBuf.Bytes();
            iEntries = Converter::BeUint32At(iBuf, 0);
            iEntryCount = 0;
            iSeekTable.InitialiseSamplesPerChunk(iEntries);

            if (iEntries > 0) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eFirstChunk;
            }
            else {
                iState = eComplete;
            }
        }
        else if (iState == eFirstChunk) {
            iOffset += iBuf.Bytes();
            iFirstChunk = Converter::BeUint32At(iBuf, 0);
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eSamplesPerChunk;
        }
        else if (iState == eSamplesPerChunk) {
            iOffset += iBuf.Bytes();
            iSamplesPerChunk = Converter::BeUint32At(iBuf, 0);
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eSampleDescriptionIndex;
        }
        else if (iState == eSampleDescriptionIndex) {
            iOffset += iBuf.Bytes();
            iSampleDescriptionIndex = Converter::BeUint32At(iBuf, 0);
            iSeekTable.SetSamplesPerChunk(iFirstChunk, iSamplesPerChunk,
                    iSampleDescriptionIndex);

            iEntryCount++;
            if (iEntryCount < iEntries) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eFirstChunk;
            }
            else {
                if (!Complete()) {
                    iCache->Discard(iBytes - iOffset);
                    iOffset = iBytes;
                    THROW(MediaMpeg4FileInvalid);
                }
                iState = eComplete;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxStsc::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxStsc::Reset()
{
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
    iEntries = 0;
    iEntryCount = 0;
    iFirstChunk = 0;
    iSamplesPerChunk = 0;
    iSampleDescriptionIndex = 0;
}

TBool Mpeg4BoxStsc::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("stsc");
}

void Mpeg4BoxStsc::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxStco

Mpeg4BoxStco::Mpeg4BoxStco(SeekTable& aSeekTable)
    : iSeekTable(aSeekTable)
{
    Reset();
}

Msg* Mpeg4BoxStco::Process()
{
    // Table of file offsets for each chunk (32-bit offsets).

    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = Converter::BeUint32At(iBuf, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eEntries;
        }
        else if (iState == eEntries) {
            iOffset += iBuf.Bytes();
            iEntries = Converter::BeUint32At(iBuf, 0);
            iEntryCount = 0;
            iSeekTable.InitialiseOffsets(iEntries);

            if (iEntries > 0) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eChunkOffset;
            }
            else {
                iState = eComplete;
            }
        }
        else if (iState == eChunkOffset) {
            iOffset += iBuf.Bytes();
            const TUint offset = Converter::BeUint32At(iBuf, 0);
            iSeekTable.SetOffset(offset);

            iEntryCount++;
            if (iEntryCount < iEntries) {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
                iState = eChunkOffset;
            }
            else {
                if (!Complete()) {
                    iCache->Discard(iBytes - iOffset);
                    iOffset = iBytes;
                    THROW(MediaMpeg4FileInvalid);
                }
                iState = eComplete;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxStco::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxStco::Reset()
{
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
}

TBool Mpeg4BoxStco::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("stco");
}

void Mpeg4BoxStco::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxCo64

Mpeg4BoxCo64::Mpeg4BoxCo64(SeekTable& aSeekTable)
    : iSeekTable(aSeekTable)
{
    Reset();
}

Msg* Mpeg4BoxCo64::Process()
{
    // Table of file offsets for each chunk (64-bit offsets).

    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf32, iBuf32.MaxBytes());
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf32.Bytes();
            const TUint version = Converter::BeUint32At(iBuf32, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf32, iBuf32.MaxBytes());
            iState = eEntries;
        }
        else if (iState == eEntries) {
            iOffset += iBuf32.Bytes();
            iEntries = Converter::BeUint32At(iBuf32, 0);
            iEntryCount = 0;
            iSeekTable.InitialiseOffsets(iEntries);

            if (iEntries > 0) {
                iCache->Inspect(iBuf64, iBuf64.MaxBytes());
                iState = eChunkOffset;
            }
            else {
                iState = eComplete;
            }
        }
        else if (iState == eChunkOffset) {
            iOffset += iBuf64.Bytes();
            const TUint64 offset = Converter::BeUint64At(iBuf64, 0);
            iSeekTable.SetOffset(offset);

            iEntryCount++;
            if (iEntryCount < iEntries) {
                iCache->Inspect(iBuf64, iBuf64.MaxBytes());
                iState = eChunkOffset;
            }
            else {
                if (!Complete()) {
                    iCache->Discard(iBytes - iOffset);
                    iOffset = iBytes;
                    THROW(MediaMpeg4FileInvalid);
                }
                iState = eComplete;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxCo64::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxCo64::Reset()
{
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf32.SetBytes(0);
    iBuf64.SetBytes(0);
    iEntries = 0;
    iEntryCount = 0;
}

TBool Mpeg4BoxCo64::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("co64");
}

void Mpeg4BoxCo64::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxStsz

Mpeg4BoxStsz::Mpeg4BoxStsz(SampleSizeTable& aSampleSizeTable)
    : iSampleSizeTable(aSampleSizeTable)
{
    Reset();
}

Msg* Mpeg4BoxStsz::Process()
{
    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = Converter::BeUint32At(iBuf, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eSampleSize;
        }
        else if (iState == eSampleSize) {
            iOffset += iBuf.Bytes();
            iSampleSize = Converter::BeUint32At(iBuf, 0);
            iCache->Inspect(iBuf, iBuf.MaxBytes());
            iState = eEntryCount;
        }
        else if (iState == eEntryCount) {
            iOffset += iBuf.Bytes();
            const TUint entries = Converter::BeUint32At(iBuf, 0);

            if (entries > 0) {
                if (iSampleSizeTable.Count() > 0) {
                    // Table already initialised.
                    // Can't currently play all files with >1 "trak" atoms, so
                    // give up on this file.

                    // FIXME - See #4779.
                    iCache->Discard(iBytes - iOffset);
                    iOffset = iBytes;
                    THROW(MediaMpeg4FileInvalid);
                }


                iSampleSizeTable.Init(entries);

                // If iSampleSize == 0, there follows an array of sample size entries.
                // If iSampleSize > 0, there are <entries> entries each of size <iSampleSize> (and no array follows).
                if (iSampleSize > 0) {
                    // Sample size table currently doesn't support a cheap way of having
                    // a fixed iSampleSize, so just perform a pseudo-population of it here.
                    for (TUint i=0; i<entries; i++) {
                        iSampleSizeTable.AddSampleSize(iSampleSize);
                    }
                    iState = eComplete;
                }
                else {
                    // Array of sample size entries follows; prepare to read it.
                    iCache->Inspect(iBuf, iBuf.MaxBytes());
                    iState = eEntry;
                }
            }
            else {
                // Can't play a file with no sample size entries.
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
        }
        else if (iState == eEntry) {
            iOffset += iBuf.Bytes();
            const TUint entrySize = Converter::BeUint32At(iBuf, 0);
            iSampleSizeTable.AddSampleSize(entrySize);

            ASSERT(iOffset <= iBytes);
            if (iOffset == iBytes) {
                iState = eComplete;
            }
            else {
                iCache->Inspect(iBuf, iBuf.MaxBytes());
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxStsz::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxStsz::Reset()
{
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
    iSampleSize = 0;
}

TBool Mpeg4BoxStsz::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("stsz");
}

void Mpeg4BoxStsz::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxMdhd

Mpeg4BoxMdhd::Mpeg4BoxMdhd(IMpeg4DurationSettable& aDurationSettable) :
        iDurationSettable(aDurationSettable)
{
    Reset();
}

Msg* Mpeg4BoxMdhd::Process()
{
    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                return msg;
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf32, iBuf32.MaxBytes());  // Set to read version.
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf32.Bytes();
            iVersion = Converter::BeUint32At(iBuf32, 0);
            if (iVersion != kVersion32 && iVersion != kVersion64) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }

            TUint discard = 0;
            if (iVersion == kVersion32) {
                discard = 8;     // Discard creation time and modification time.
            }
            else {
                discard = 16;    // Discard creation time and modification time.
            }
            iCache->Discard(discard);
            iOffset += discard;
            iCache->Inspect(iBuf32, iBuf32.MaxBytes()); // Set to read timescale.
            iState = eTimescale;
        }
        else if (iState == eTimescale) {
            iOffset += iBuf32.Bytes();
            const TUint timescale = Converter::BeUint32At(iBuf32, 0);
            iDurationSettable.SetTimescale(timescale);
            if (iVersion == kVersion32) {
                iCache->Inspect(iBuf32, iBuf32.MaxBytes());
            }
            else {
                iCache->Inspect(iBuf64, iBuf64.MaxBytes());
            }
            iState = eDuration;
        }
        else if (iState == eDuration) {
            TUint64 duration = 0;
            if (iVersion == kVersion32) {
                iOffset += iBuf32.Bytes();
                duration = Converter::BeUint32At(iBuf32, 0);
            }
            else {
                iOffset += iBuf64.Bytes();
                duration = Converter::BeUint64At(iBuf64, 0);
            }
            iDurationSettable.SetDuration(duration);

            if (iOffset < iBytes) {
                const TUint discard = iBytes - iOffset;
                iCache->Discard(discard);
                iOffset += discard;

            }
            iState = eComplete;
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxMdhd::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxMdhd::Reset()
{
    iCache = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf32.SetBytes(0);
    iBuf64.SetBytes(0);
    iVersion = 0;
}

TBool Mpeg4BoxMdhd::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("mdhd");
}

void Mpeg4BoxMdhd::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxCodecBase

Mpeg4BoxCodecBase::Mpeg4BoxCodecBase(const Brx& aCodecId,
        IStreamInfoSettable& aStreamInfoSettable) :
        iId(aCodecId), iStreamInfoSettable(aStreamInfoSettable)
{
    Reset();
}

Msg* Mpeg4BoxCodecBase::Process()
{
    while (!Complete()) {
        Msg* msg = nullptr;

        // All pulling calls below returns nullptr when there is something of interest for this class.
        if (iState == eHeader) {
            msg = iHeaderReader.ReadHeader();
        }
        else if (iState == eBox) {
            msg = iProcessor->Process();
        }
        else if (iState != eNone) {
            msg = iCache->Pull();
        }

        if (msg != nullptr) {
            return msg;
        }

        if (iState == eNone) {
            // Skip 6 byte reserved block.
            // Skip 2 byte data ref index.
            // Skip 4 byte*2 reserved block.
            static const TUint discard = 16;
            iCache->Discard(discard);
            iOffset += discard;
            iCache->Inspect(iBuf, iBuf.MaxBytes());  // Set to read channels.
            iState = eChannels;
        }
        else if (iState == eChannels) {
            iOffset += iBuf.Bytes();
            const TUint channels = Converter::BeUint16At(iBuf, 0);
            iStreamInfoSettable.SetChannels(channels);
            iCache->Inspect(iBuf, iBuf.MaxBytes());  // Set to read bit depth.
            iState = eBitDepth;
        }
        else if (iState == eBitDepth) {
            iOffset += iBuf.Bytes();
            const TUint bitDepth = Converter::BeUint16At(iBuf, 0);
            iStreamInfoSettable.SetBitDepth(bitDepth);

            // Skip 2 byte pre-defined block.
            // Skip 2 byte reserved block.
            static const TUint discard = 4;
            iCache->Discard(discard);
            iOffset += discard;

            iCache->Inspect(iBuf, iBuf.MaxBytes()); // Set to read sample rate (only care about 2 MSBs).
            iState = eSampleRate;
        }
        else if (iState == eSampleRate) {
            iOffset += iBuf.Bytes();
            const TUint sampleRate = Converter::BeUint16At(iBuf, 0);
            iStreamInfoSettable.SetSampleRate(sampleRate);

            // Skip 2 LSBs of sample rate.
            static const TUint discard = 2;
            iCache->Discard(discard);
            iOffset += discard;

            iHeaderReader.Reset(*iCache);
            iState = eHeader;
        }
        else if (iState == eHeader) {
            // Got header, now find a processor.
            try {
                iProcessor = &iProcessorFactory.GetMpeg4BoxProcessor(
                        iHeaderReader.Id(), iHeaderReader.PayloadBytes(),
                        *iCache);
                iState = eBox;
            } catch (Mpeg4BoxUnrecognised&) {
                LOG(kCodec, "Mpeg4CodecBase::Process couldn't find processor for "); LOG(kCodec, iHeaderReader.Id()); LOG(kCodec, "\n");

                iCache->Discard(iHeaderReader.PayloadBytes());
                iOffset += iHeaderReader.Bytes();
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else if (iState == eBox) {
            // Box processing is complete.
            iOffset += iHeaderReader.Bytes();

            ASSERT(iOffset <= iBytes);
            if (iOffset == iBytes) {
                iState = eComplete;
            }
            else {
                // Read next box.
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxCodecBase::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxCodecBase::Reset()
{
    iCache = nullptr;
    iProcessor = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
}

TBool Mpeg4BoxCodecBase::Recognise(const Brx& aBoxId) const
{
    return aBoxId == iId;
}

void Mpeg4BoxCodecBase::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
    iStreamInfoSettable.SetCodec(iId);
}

// Mpeg4BoxCodecMp4a

Mpeg4BoxCodecMp4a::Mpeg4BoxCodecMp4a(IStreamInfoSettable& aStreamInfoSettable,
        ICodecInfoSettable& aCodecInfoSettable) :
        Mpeg4BoxCodecBase(Brn("mp4a"), aStreamInfoSettable)
{
    iProcessorFactory.Add(new Mpeg4BoxEsds(aCodecInfoSettable));
}

// Mpeg4BoxCodecAlac

Mpeg4BoxCodecAlac::Mpeg4BoxCodecAlac(IStreamInfoSettable& aStreamInfoSettable,
        ICodecInfoSettable& aCodecInfoSettable) :
        Mpeg4BoxCodecBase(Brn("alac"), aStreamInfoSettable)
{
    iProcessorFactory.Add(new Mpeg4BoxAlac(aCodecInfoSettable));
}

// Mpeg4BoxEsds

Mpeg4BoxEsds::Mpeg4BoxEsds(ICodecInfoSettable& aCodecInfoSettable) :
        iCodecInfoSettable(aCodecInfoSettable)
{
    Reset();
}

Msg* Mpeg4BoxEsds::Process()
{
    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                msg = msg->Process(iAudioEncodedRecogniser);
                if (msg != nullptr) {
                    return msg;
                }
            }
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());  // Set to read version.
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = iBuf[0];
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }

            // Skip 24-bit field reserved for flags.
            static const TUint discard = 3;
            iCache->Discard(discard);
            iOffset += discard;

            const TUint remaining = iBytes-iOffset;
            iCache->Accumulate(remaining);  // Set to read codec info.
            iState = eCodecInfo;
        }
        else if (iState == eCodecInfo) {
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            iOffset += msg->Bytes();
            iCodecInfoSettable.SetCodecInfo(msg);
            iState = eComplete;
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxEsds::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxEsds::Reset()
{
    iCache = nullptr;
    iAudioEncodedRecogniser.Reset();
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
}

TBool Mpeg4BoxEsds::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("esds");
}

void Mpeg4BoxEsds::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxAlac

Mpeg4BoxAlac::Mpeg4BoxAlac(ICodecInfoSettable& aCodecInfoSettable) :
        iCodecInfoSettable(aCodecInfoSettable)
{
    Reset();
}

Msg* Mpeg4BoxAlac::Process()
{
    while (!Complete()) {
        if (iState != eNone) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                msg = msg->Process(iAudioEncodedRecogniser);
                if (msg != nullptr) {
                    return msg;
                }
            }
        }

        if (iState == eNone) {
            const TUint remainder = iBytes - iOffset;
            iCache->Accumulate(remainder);  // Set to read codec info.
            iState = eCodecInfo;
        }
        else if (iState == eCodecInfo) {
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            iOffset += msg->Bytes();
            iCodecInfoSettable.SetCodecInfo(msg);
            iState = eComplete;
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxAlac::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxAlac::Reset()
{
    iCache = nullptr;
    iAudioEncodedRecogniser.Reset();
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
}

TBool Mpeg4BoxAlac::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("alac");
}

void Mpeg4BoxAlac::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4BoxStsd

Mpeg4BoxStsd::Mpeg4BoxStsd(IStreamInfoSettable& aStreamInfoSettable,
        ICodecInfoSettable& aCodecInfoSettable) :
        iCache(nullptr), iProcessor(nullptr), iState(eNone), iBytes(0), iOffset(
                0)
{
    iProcessorFactory.Add(
            new Mpeg4BoxCodecMp4a(aStreamInfoSettable, aCodecInfoSettable));
    iProcessorFactory.Add(
            new Mpeg4BoxCodecAlac(aStreamInfoSettable, aCodecInfoSettable));
}

Msg* Mpeg4BoxStsd::Process()
{
    while (!Complete()) {
        Msg* msg = nullptr;

        // All pulling calls below return nullptr when there is something of interest for this class.
        if (iState == eHeader) {
            msg = iHeaderReader.ReadHeader();
        }
        else if (iState == eBox) {
            msg = iProcessor->Process();
        }
        else if (iState != eNone) {
            msg = iCache->Pull();
        }

        if (msg != nullptr) {
            return msg;
        }

        if (iState == eNone) {
            iCache->Inspect(iBuf, iBuf.MaxBytes());  // Set to read version.
            iState = eVersion;
        }
        else if (iState == eVersion) {
            iOffset += iBuf.Bytes();
            const TUint version = Converter::BeUint32At(iBuf, 0);
            if (version != kVersion) {
                iCache->Discard(iBytes - iOffset);
                iOffset = iBytes;
                THROW(MediaMpeg4FileInvalid);
            }
            iCache->Inspect(iBuf, iBuf.MaxBytes());  // Set to read entry count.
            iState = eEntries;
        }
        else if (iState == eEntries) {
            iOffset += iBuf.Bytes();
            const TUint entries = Converter::BeUint32At(iBuf, 0);
            LOG(kCodec, "Mpeg4BoxStsd::Process entries: %u\n", entries);
            iHeaderReader.Reset(*iCache);
            iState = eHeader;
        }
        else if (iState == eHeader) {
            // Got header, now find a processor.
            try {
                iProcessor = &iProcessorFactory.GetMpeg4BoxProcessor(
                        iHeaderReader.Id(), iHeaderReader.PayloadBytes(),
                        *iCache);
                iState = eBox;
            } catch (Mpeg4BoxUnrecognised&) {
                LOG(kCodec, "Mpeg4BoxStsd::Process couldn't find processor for "); LOG(kCodec, iHeaderReader.Id()); LOG(kCodec, "\n");

                iCache->Discard(iHeaderReader.PayloadBytes());
                iOffset += iHeaderReader.Bytes();
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else if (iState == eBox) {
            // Box processing is complete.
            iOffset += iHeaderReader.Bytes();

            ASSERT(iOffset <= iBytes);
            if (iOffset == iBytes) {
                iState = eComplete;
            }
            else {
                // Read next box.
                iProcessor = nullptr;
                iHeaderReader.Reset(*iCache);
                iState = eHeader;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxStsd::Complete() const
{
    return iOffset == iBytes;
}

void Mpeg4BoxStsd::Reset()
{
    iProcessor = nullptr;
    iState = eNone;
    iBytes = 0;
    iOffset = 0;
    iBuf.SetBytes(0);
}

TBool Mpeg4BoxStsd::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("stsd");
}

void Mpeg4BoxStsd::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    iCache = &aCache;
    iBytes = aBoxBytes;
}

// Mpeg4Duration

Mpeg4Duration::Mpeg4Duration() :
        iTimescale(0), iDuration(0)
{
}

void Mpeg4Duration::Reset()
{
    iTimescale = 0;
    iDuration = 0;
}

TUint Mpeg4Duration::Timescale() const
{
    return iTimescale;
}

TUint64 Mpeg4Duration::Duration() const
{
    return iDuration;
}

void Mpeg4Duration::SetTimescale(TUint aTimescale)
{
    iTimescale = aTimescale;
}

void Mpeg4Duration::SetDuration(TUint64 aDuration)
{
    iDuration = aDuration;
}

// Mpeg4StreamInfo

Mpeg4StreamInfo::Mpeg4StreamInfo() :
        iChannels(0), iBitDepth(0), iSampleRate(0)
{
}

void Mpeg4StreamInfo::Reset()
{
    iChannels = 0;
    iBitDepth = 0;
    iSampleRate = 0;
    iCodec.SetBytes(0);
}

TUint Mpeg4StreamInfo::Channels() const
{
    return iChannels;
}

TUint Mpeg4StreamInfo::BitDepth() const
{
    return iBitDepth;
}

TUint Mpeg4StreamInfo::SampleRate() const
{
    return iSampleRate;
}

const Brx& Mpeg4StreamInfo::Codec() const
{
    return iCodec;
}

void Mpeg4StreamInfo::SetChannels(TUint aChannels)
{
    iChannels = aChannels;
}

void Mpeg4StreamInfo::SetBitDepth(TUint aBitDepth)
{
    iBitDepth = aBitDepth;
}

void Mpeg4StreamInfo::SetSampleRate(TUint aSampleRate)
{
    iSampleRate = aSampleRate;
}

void Mpeg4StreamInfo::SetCodec(const Brx& aCodec)
{
    iCodec.Replace(aCodec);
}

// Mpeg4CodecInfo

Mpeg4CodecInfo::Mpeg4CodecInfo() :
        iAudioEncoded(nullptr)
{
}

Mpeg4CodecInfo::~Mpeg4CodecInfo()
{
    Reset();
}

void Mpeg4CodecInfo::Reset()
{
    if (iAudioEncoded != nullptr) {
        iAudioEncoded->RemoveRef();
        iAudioEncoded = nullptr;
    }
}

MsgAudioEncoded* Mpeg4CodecInfo::CodecInfo()
{
    MsgAudioEncoded* msg = iAudioEncoded;
    iAudioEncoded = nullptr;
    return msg;
}

void Mpeg4CodecInfo::SetCodecInfo(MsgAudioEncoded* aMsg)
{
    ASSERT(iAudioEncoded == nullptr);
    iAudioEncoded = aMsg;
}

// Mpeg4BoxMdat

Mpeg4BoxMdat::Mpeg4BoxMdat(Mpeg4BoxSwitcherRoot& aBoxSwitcher, IMpeg4MetadataChecker& aMetadataChecker, IMpeg4MetadataProvider& aMetadataProvider, IMpeg4ChunkSeekObservable& aChunkSeeker, IBoxOffsetProvider& aOffsetProvider, SeekTable& aSeekTable, SampleSizeTable& aSampleSizeTable, Mpeg4OutOfBandReader& aOutOfBandReader)
    : iBoxSwitcher(aBoxSwitcher)
    , iMetadataChecker(aMetadataChecker)
    , iMetadataProvider(aMetadataProvider)
    , iOffsetProvider(aOffsetProvider)
    , iSeekTable(aSeekTable)
    , iSampleSizeTable(aSampleSizeTable)
    , iOutOfBandReader(aOutOfBandReader)
    , iLock("MP4D")
{
    aChunkSeeker.RegisterChunkSeekObserver(*this);
    Reset();
}

Msg* Mpeg4BoxMdat::Process()
{
    while (!Complete()) {
        if (iState == eChunk) {
            Msg* msg = iCache->Pull();
            if (msg != nullptr) {
                msg = msg->Process(iAudioEncodedRecogniser);
                if (msg != nullptr) {
                    return msg;
                }
            }
        }

        if (iState == eNone) {
            if (!iMetadataChecker.MetadataAvailable()) {
                iState = eRetrieveMetadata;
            }
            else {
                iState = eTransmitMetadata;
            }
        }
        else if (iState == eRetrieveMetadata) {
            iOutOfBandReader.SetReadOffset(iFileReadOffset+iBytes);
            iBoxSwitcher.Reset();
            iBoxSwitcher.Set(iOutOfBandReader, "moov");
            Msg* msg = iBoxSwitcher.Process();
            ASSERT(msg == nullptr); // Shouldn't get any msgs from out-of-band reader.

            if (!iMetadataChecker.MetadataAvailable()) {
                // Still failed to retrieve metadata.
                return nullptr;
            }

            iState = eTransmitMetadata;
        }
        else if (iState == eTransmitMetadata) {
            MsgAudioEncoded* msg = iMetadataProvider.GetMetadata();

            iChunk = 0;
            iChunkBytesRemaining = ChunkBytes();
            iState = eChunkReadSetup;
            return msg;
        }
        else if (iState == eChunkReadSetup) {

            {
                AutoMutex a(iLock);
                if (iSeek) {
                    LOG(kCodec, "Mpeg4BoxMdat::Process seek occured iSeekChunk: %u\n", iSeekChunk);
                    // Chunk has changed due to seek.
                    iChunk = iSeekChunk;
                    iChunkBytesRemaining = ChunkBytes();
                    iFileReadOffset = iBoxStartOffset+Mpeg4BoxHeaderReader::kHeaderBytes;
                    iOffset = iFileReadOffset - Mpeg4BoxHeaderReader::kHeaderBytes - iBoxStartOffset;

                    const TUint chunkOffset = BytesUntilChunk();
                    iFileReadOffset += chunkOffset;
                    iOffset = chunkOffset;

                    iSeek = false;
                    iSeekChunk = 0;
                }
            }

            const TUint discard = BytesUntilChunk();
            iCache->Discard(discard);
            iOffset += discard;
            iFileReadOffset += discard;

            const TUint readBytes = BytesToRead();
            iCache->Accumulate(readBytes);
            iState = eChunk;
        }
        else if (iState == eChunk) {
            MsgAudioEncoded* msg = iAudioEncodedRecogniser.AudioEncoded();
            ASSERT(msg != nullptr);
            ASSERT(msg->Bytes() <= iChunkBytesRemaining);

            TBool seek = false;
            {
                AutoMutex a(iLock);
                seek = iSeek;
            }

            if (seek) {
                msg->RemoveRef();   // Discard msg; now invalid.
                msg = nullptr;
                iState = eChunkReadSetup;
            }
            else {
                // Chunk still valid.
                iOffset += msg->Bytes();
                iFileReadOffset += msg->Bytes();
                iChunkBytesRemaining -= msg->Bytes();

                if (iChunkBytesRemaining == 0) {
                    ASSERT(iOffset <= iBytes);
                    if (iOffset == iBytes) {
                        iState = eComplete;
                    }
                    else {
                        iChunk++;
                        iChunkBytesRemaining = ChunkBytes();
                        iState = eChunkReadSetup;
                    }
                }
                else {
                    // Bytes remaining from this chunk; set to read next block but remain in this state.
                    const TUint readBytes = BytesToRead();
                    iCache->Accumulate(readBytes);
                    iState = eChunk;
                }
                return msg;
            }
        }
        else {
            // Unhandled state.
            ASSERTS();
        }
    }

    return nullptr;
}

TBool Mpeg4BoxMdat::Complete() const
{
    ASSERT(iOffset <= iBytes);
    return iOffset == iBytes;
}

void Mpeg4BoxMdat::Reset()
{
    iCache = nullptr;
    iAudioEncodedRecogniser.Reset();
    iState = eNone;
    iChunk = 0;
    iSeekChunk = 0;
    iSeek = false;
    iChunkBytesRemaining = 0;
    iBytes = 0;
    iOffset = 0;
    iBoxStartOffset = 0;
    iFileReadOffset = 0;
}

TBool Mpeg4BoxMdat::Recognise(const Brx& aBoxId) const
{
    return aBoxId == Brn("mdat");
}

void Mpeg4BoxMdat::Set(IMsgAudioEncodedCache& aCache, TUint aBoxBytes)
{
    ASSERT(iCache == nullptr);
    iCache = &aCache;
    iBytes = aBoxBytes;
    iBoxStartOffset = iOffsetProvider.BoxOffset();
    iFileReadOffset = iBoxStartOffset + Mpeg4BoxHeaderReader::kHeaderBytes;
}

void Mpeg4BoxMdat::ChunkSeek(TUint aChunk)
{
    AutoMutex a(iLock);
    iSeek = true;
    iSeekChunk = aChunk;
    iState = eChunkReadSetup;
}

TUint Mpeg4BoxMdat::BytesUntilChunk() const
{
    const TUint64 chunkOffset = iSeekTable.GetOffset(iChunk);
    if (chunkOffset < iFileReadOffset) {
        THROW(MediaMpeg4FileInvalid);
    }
    const TUint64 toDiscard = chunkOffset - iFileReadOffset;
    ASSERT(toDiscard <= std::numeric_limits < TUint > ::max());
    const TUint bytes = static_cast<TUint>(toDiscard);
    return bytes;
}

TUint Mpeg4BoxMdat::ChunkBytes() const
{
    ASSERT(iChunk < iSeekTable.ChunkCount());
    const TUint chunkSamples = iSeekTable.SamplesPerChunk(iChunk);
    const TUint startSample = iSeekTable.StartSample(iChunk); // NOTE: this assumes first sample == 0 (which is valid with how our tables are setup), but in MPEG4 spec, first sample == 1.
    TUint chunkBytes = 0;
    // Samples start from 1. However, tables here are indexed from 0.
    for (TUint i = startSample; i < startSample + chunkSamples; i++) {
        const TUint sampleBytes = iSampleSizeTable.SampleSize(i);
        ASSERT(chunkBytes + sampleBytes <= std::numeric_limits<TUint>::max());  // Ensure no overflow.
        chunkBytes += sampleBytes;
    }
    return chunkBytes;
}

TUint Mpeg4BoxMdat::BytesToRead() const
{
    // Read data in sensible-sized blocks.
    // A single file could be composed of a single chunk.
    // Would exhaust allocators if try to buffer entire large file/chunk.
    TUint bytes = iChunkBytesRemaining;
    if (iChunkBytesRemaining > EncodedAudio::kMaxBytes) {
        bytes = EncodedAudio::kMaxBytes;
    }
    return bytes;
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
    if (aIndex > iTable.size() - 1) {
        THROW(MediaMpeg4FileInvalid);
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
    const TBool initialised = iSamplesPerChunk.size() > 0
            && iAudioSamplesPerSample.size() > 0 && iOffsets.size() > 0;
    return initialised;
}

void SeekTable::Deinitialise()
{
    iSamplesPerChunk.clear();
    iAudioSamplesPerSample.clear();
    iOffsets.clear();
}

void SeekTable::SetSamplesPerChunk(TUint aFirstChunk, TUint aSamplesPerChunk,
        TUint aSampleDescriptionIndex)
{
    TSamplesPerChunkEntry entry = { aFirstChunk, aSamplesPerChunk,
            aSampleDescriptionIndex };
    iSamplesPerChunk.push_back(entry);
}

void SeekTable::SetAudioSamplesPerSample(TUint32 aSampleCount,
        TUint32 aAudioSamples)
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

TUint SeekTable::AudioSamplesPerSample() const
{
    return iAudioSamplesPerSample.size();
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
    const TUint desiredChunk = aChunkIndex + 1;
    TUint prevFirstChunk = 1;
    TUint prevSamples = 0;
    for (TUint i = 0; i < iSamplesPerChunk.size(); i++) {
        const TUint nextFirstChunk = iSamplesPerChunk[i].iFirstChunk;
        const TUint nextSamples = iSamplesPerChunk[i].iSamples;

        // Desired chunk was within last chunk range.
        if (nextFirstChunk >= desiredChunk) {
            const TUint chunkDiff = desiredChunk - prevFirstChunk;
            startSample += chunkDiff * prevSamples;
            prevFirstChunk = nextFirstChunk;
            prevSamples = nextSamples;
            break;
        }

        const TUint chunkDiff = nextFirstChunk - prevFirstChunk;
        startSample += chunkDiff * prevSamples;
        prevFirstChunk = nextFirstChunk;
        prevSamples = nextSamples;
    }

    // See if exhausted samples per chunk table without encountering desired chunk.
    if (prevFirstChunk < desiredChunk) {
        const TUint chunkDiff = desiredChunk - prevFirstChunk;
        startSample += chunkDiff * prevSamples;
    }

    return startSample;
}

TUint64 SeekTable::Offset(TUint64& aAudioSample, TUint64& aSample)
{
    if (iSamplesPerChunk.size() == 0 || iAudioSamplesPerSample.size() == 0
            || iOffsets.size() == 0) {
        THROW(CodecStreamCorrupt); // seek table empty - cannot do seek // FIXME - throw a MpegMediaFileInvalid exception, which is actually expected/caught?
    }

    const TUint64 codecSampleFromAudioSample = CodecSample(aAudioSample);

    // FIXME - if stss box was present, must use it here to find appropriate sync sample.
    // If stss box not present all codec samples are sync samples.

    const TUint chunk = Chunk(codecSampleFromAudioSample);
    // FIXME - could go one step further and use chunk-to-sample table to find offset of desired sample within desired chunk.
    const TUint codecSampleFromChunk = CodecSampleFromChunk(chunk);
    const TUint audioSampleFromCodecSample = AudioSampleFromCodecSample(
            codecSampleFromChunk);

    aAudioSample = audioSampleFromCodecSample;
    aSample = codecSampleFromChunk;

    //stco:
    if (chunk >= iOffsets.size()+1) { // error - required chunk doesn't exist
        THROW(MediaMpeg4OutOfRange);
    }
    return iOffsets[chunk - 1]; // entry found - return offset to required chunk
}

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
    for (TUint i = 0; i < samplesPerChunkCount; i++) {
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iFirstChunk);
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iSamples);
        writerBin.WriteUint32Be(iSamplesPerChunk[i].iSampleDescriptionIndex);
    }

    const TUint audioSamplesPerSampleCount = iAudioSamplesPerSample.size();
    writerBin.WriteUint32Be(audioSamplesPerSampleCount);
    for (TUint i = 0; i < audioSamplesPerSampleCount; i++) {
        writerBin.WriteUint32Be(iAudioSamplesPerSample[i].iSampleCount);
        writerBin.WriteUint32Be(iAudioSamplesPerSample[i].iAudioSamples);
    }

    const TUint chunkCount = iOffsets.size();
    writerBin.WriteUint32Be(chunkCount);
    for (TUint i = 0; i < chunkCount; i++) {
        writerBin.WriteUint64Be(iOffsets[i]);
    }
}

TUint64 SeekTable::CodecSample(TUint64 aAudioSample) const
{
    // Use entries from stts box to find codec sample that contains the desired
    // audio sample.
    TUint64 totalCodecSamples = 0;
    TUint64 totalAudioSamples = 0;
    for (TUint entry = 0; entry < iAudioSamplesPerSample.size(); entry++) {
        const TUint sampleCount = iAudioSamplesPerSample[entry].iSampleCount;
        const TUint audioSamples = iAudioSamplesPerSample[entry].iAudioSamples;
        const TUint audioSamplesInrange = sampleCount * audioSamples;
        if (aAudioSample <= totalCodecSamples + audioSamplesInrange) {
            // Audio samples are within this range.

            // Find codec sample in this range that contains given audio sample.
            ASSERT(aAudioSample >= totalAudioSamples);
            const TUint64 audioSampleOffset = aAudioSample - totalAudioSamples;
            const TUint64 codecSampleOffset = audioSampleOffset / audioSamples;
            ASSERT(codecSampleOffset <= sampleCount);

            totalCodecSamples += codecSampleOffset;
            return totalCodecSamples;
        }
        totalCodecSamples += sampleCount;
        totalAudioSamples += audioSamplesInrange;
    }

    if (aAudioSample > totalAudioSamples) {
        THROW(MediaMpeg4OutOfRange);
    }

    // Something went wrong. Could be corrupt table or programmer error!
    LOG(kCodec, "SeekTable::CodecSample could not find aAudioSample: %u\n", aAudioSample);
    THROW(MediaMpeg4FileInvalid);
}

TUint SeekTable::SamplesPerChunkTotal(TUint aIndex) const
{
    // Calculates chunks*samples_per_chunk at given index in samples-per-chunk
    // table.
    ASSERT(aIndex < iSamplesPerChunk.size());
    const TUint startChunk = iSamplesPerChunk[aIndex].iFirstChunk;
    const TUint spc = iSamplesPerChunk[aIndex].iSamples;
    TUint endChunk = 0;

    // Find last chunk in current run.
    if (aIndex + 1 < iSamplesPerChunk.size()) {
        endChunk = iSamplesPerChunk[aIndex + 1].iFirstChunk;
    }
    else {
        // No next entry, so end chunk must be last chunk in file.
        // Since chunk numbers start at one, must be chunk_count+1.
        endChunk = iOffsets.size()+1;
    }

    const TUint chunkDiff = endChunk - startChunk;
    const TUint samplesInRange = chunkDiff * spc;

    return samplesInRange;
}

TUint SeekTable::ChunkWithinSamplesPerChunk(TUint aIndex, TUint aSampleOffset) const
{
    ASSERT(aIndex < iSamplesPerChunk.size());
    const TUint chunk = iSamplesPerChunk[aIndex].iFirstChunk;
    const TUint spc = iSamplesPerChunk[aIndex].iSamples;
    const TUint chunkOffset = static_cast<TUint>(aSampleOffset / spc);
    return chunk + chunkOffset;
}

TUint SeekTable::Chunk(TUint64 aCodecSample) const
{
    // Use data from stsc box to find chunk containing the desired codec sample.
    TUint64 totalSamples = 0;
    for (TUint entry = 0; entry < iSamplesPerChunk.size(); entry++) {
        const TUint samplesInRange = SamplesPerChunkTotal(entry);
        if (aCodecSample < totalSamples + samplesInRange) {
            // Desired sample is in this range.

            // Find chunk in this range that contains the desired sample.
            ASSERT(aCodecSample >= totalSamples);
            const TUint64 sampleOffset64 = aCodecSample - totalSamples;
            ASSERT(sampleOffset64 <= std::numeric_limits<TUint>::max());  // Ensure no issues with casting to smaller type.
            const TUint sampleOffset = static_cast<TUint>(sampleOffset64);
            const TUint chunk = ChunkWithinSamplesPerChunk(entry, sampleOffset);

            return chunk;
        }

        totalSamples += samplesInRange;
    }

    if (aCodecSample > totalSamples) {
        THROW(MediaMpeg4OutOfRange);
    }

    LOG(kCodec, "SeekTable::Chunk could not find aCodecSample: %u\n", aCodecSample);
    THROW(MediaMpeg4FileInvalid);
}

TUint SeekTable::CodecSampleFromChunk(TUint aChunk) const
{
    // Use data from stsc box to find chunk containing the desired codec sample.
    TUint totalSamples = 0;
    TUint chunk = 1;
    for (TUint entry = 0; entry < iSamplesPerChunk.size(); entry++) {
        const TUint startChunk = iSamplesPerChunk[entry].iFirstChunk;
        const TUint spc = iSamplesPerChunk[entry].iSamples;
        TUint endChunk = 0;

        // Find last chunk in current run.
        if (entry + 1 < iSamplesPerChunk.size()) {
            endChunk = iSamplesPerChunk[entry + 1].iFirstChunk;
        }
        else {
            // No next entry, so end chunk must be last chunk in file.
            endChunk = iOffsets.size();
        }

        const TUint chunkDiff = endChunk - startChunk;
        const TUint samplesInRange = chunkDiff * spc;

        if (aChunk <= endChunk) {
            // Desired chunk is in this range.

            const TUint chunkOffset = aChunk - startChunk;
            const TUint sampleOffset = chunkOffset * spc;
            totalSamples += sampleOffset;
            return totalSamples;
        }

        totalSamples += samplesInRange;
        chunk = startChunk;
    }

    if (aChunk > chunk) {
        THROW(MediaMpeg4OutOfRange);
    }

    LOG(kCodec, "SeekTable::CodecSampleFromChunk could not find aCodecSample: %u\n", aChunk);
    THROW(MediaMpeg4FileInvalid);
}

TUint SeekTable::AudioSampleFromCodecSample(TUint aCodecSample) const
{
    // Use entries from stts box to find audio sample that start at given codec sample;
    TUint totalCodecSamples = 0;
    TUint totalAudioSamples = 0;
    for (TUint entry = 0; entry < iAudioSamplesPerSample.size(); entry++) {
        const TUint sampleCount = iAudioSamplesPerSample[entry].iSampleCount;
        const TUint audioSamples = iAudioSamplesPerSample[entry].iAudioSamples;
        if (aCodecSample <= totalCodecSamples + sampleCount) {
            // Codec sample is within this range.

            // Find the number of audio samples at the start of the given codec sample.
            ASSERT(totalCodecSamples <= aCodecSample);
            const TUint codecSampleOffset = aCodecSample - totalCodecSamples;
            const TUint audioSampleOffset = codecSampleOffset * audioSamples;

            totalAudioSamples += audioSampleOffset;
            return audioSampleOffset;
        }
        totalCodecSamples += sampleCount;
        totalAudioSamples += sampleCount * audioSamples;
    }

    if (aCodecSample > totalCodecSamples) {
        THROW(MediaMpeg4OutOfRange);
    }

    // Something went wrong. Could be corrupt table or programmer error!
    LOG(kCodec, "SeekTable::AudioSampleFromCodecSample could not find aCodecSample: %u\n", aCodecSample);
    THROW(MediaMpeg4FileInvalid);
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
    for (TUint i = 0; i < samplesPerChunkCount; i++) {
        const TUint firstChunk = readerBin.ReadUintBe(4);
        const TUint samples = readerBin.ReadUintBe(4);
        const TUint sampleDescriptionIndex = readerBin.ReadUintBe(4);
        iSeekTable.SetSamplesPerChunk(firstChunk, samples,
                sampleDescriptionIndex);
    }

    const TUint audioSamplesPerSampleCount = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseAudioSamplesPerSample(audioSamplesPerSampleCount);
    for (TUint i = 0; i < audioSamplesPerSampleCount; i++) {
        const TUint sampleCount = readerBin.ReadUintBe(4);
        const TUint audioSamples = readerBin.ReadUintBe(4);
        iSeekTable.SetAudioSamplesPerSample(sampleCount, audioSamples);
    }

    const TUint chunkCount = readerBin.ReadUintBe(4);
    iSeekTable.InitialiseOffsets(chunkCount);
    for (TUint i = 0; i < chunkCount; i++) {
        const TUint64 offset = readerBin.ReadUint64Be(8);
        iSeekTable.SetOffset(offset);
    }
    iInitialised = true;
}


// MsgAudioEncodedWriter

MsgAudioEncodedWriter::MsgAudioEncodedWriter(MsgFactory& aMsgFactory) :
        iMsgFactory(aMsgFactory), iMsg(nullptr)
{
}

MsgAudioEncodedWriter::~MsgAudioEncodedWriter()
{
    ASSERT(iMsg == nullptr);
    ASSERT(iBuf.Bytes() == 0);
}

MsgAudioEncoded* MsgAudioEncodedWriter::Msg()
{
    ASSERT(iBuf.Bytes() == 0);  // Ensure no audio still buffered.
    MsgAudioEncoded* msg = iMsg;
    iMsg = nullptr;
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
            iBuf.Append(aBuffer.Ptr() + offset, bytes);
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
    MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(
            Brn(iBuf.Ptr(), iBuf.Bytes()));
    if (iMsg == nullptr) {
        iMsg = msg;
    }
    else {
        iMsg->Add(msg);
    }
    iBuf.SetBytes(0);
}

// Mpeg4OutOfBandReader

Mpeg4OutOfBandReader::Mpeg4OutOfBandReader(MsgFactory& aMsgFactory, IContainerUrlBlockWriter& aBlockWriter)
    : iMsgFactory(aMsgFactory)
    , iBlockWriter(aBlockWriter)
    , iOffset(0)
    , iStreamBytes(0)
    , iDiscardBytes(0)
    , iInspectBytes(0)
    , iAccumulateBytes(0)
    , iInspectBuffer(nullptr)
{
}

void Mpeg4OutOfBandReader::Reset(TUint64 aStreamBytes)
{
    iStreamBytes = aStreamBytes;
    iDiscardBytes = 0;
    iInspectBytes = 0;
    iAccumulateBytes = 0;
    iInspectBuffer = nullptr;
    iReadBuffer.SetBytes(0);
    iAccumulateBuffer.SetBytes(0);
}

void Mpeg4OutOfBandReader::SetReadOffset(TUint64 aStartOffset)
{
    iOffset = aStartOffset;
}

void Mpeg4OutOfBandReader::Discard(TUint aBytes)
{
    ASSERT(iDiscardBytes == 0);
    iDiscardBytes = aBytes;
}

void Mpeg4OutOfBandReader::Inspect(Bwx& aBuf, TUint aBytes)
{
    ASSERT(iInspectBuffer == nullptr);
    ASSERT(aBuf.MaxBytes() >= aBytes);
    aBuf.SetBytes(0);
    iInspectBuffer = &aBuf;
    iInspectBytes = aBytes;
}

void Mpeg4OutOfBandReader::Accumulate(TUint aBytes)
{
    ASSERT(iAccumulateBytes == 0);
    // FIXME - alter MPEG4 parsing so that no metadata processor directly pulls a MsgAudioEncoded?
    ASSERT(iAccumulateBytes <= kMaxAccumulateBytes); // Can't support accumulating more than this.
    iAccumulateBytes = aBytes;
    iAccumulateBuffer.SetBytes(0);
}

Msg* Mpeg4OutOfBandReader::Pull()
{
    // Don't support just pulling msgs.
    ASSERT(iDiscardBytes > 0 || iInspectBytes > 0 || iAccumulateBytes > 0);

    if (iDiscardBytes > 0) {
        if (iDiscardBytes == iReadBuffer.Bytes()) {
            iDiscardBytes = 0;
            iReadBuffer.SetBytes(0);
        }
        else if (iDiscardBytes > iReadBuffer.Bytes()) {
            iDiscardBytes -= iReadBuffer.Bytes();
            iReadBuffer.SetBytes(0);
            iOffset += iDiscardBytes;
            iDiscardBytes = 0;
        }
        else {
            iReadBuffer.Replace(iReadBuffer.Ptr() + iDiscardBytes, iReadBuffer.Bytes() - iDiscardBytes);
            iDiscardBytes = 0;
        }
    }

    if (iInspectBytes > 0) {
        const TBool success = PopulateBuffer(*iInspectBuffer, iInspectBytes);
        iInspectBytes = 0;
        iInspectBuffer = nullptr;   // No need to reference anymore, as won't append more data.
        if (success) {
            return nullptr;
        }
        else {
            THROW(AudioCacheException);
        }
    }

    if (iAccumulateBytes > 0) {
        const TBool success = PopulateBuffer(iAccumulateBuffer, iAccumulateBytes);
        iAccumulateBytes = 0;
        if (success) {
            MsgAudioEncoded* msg = iMsgFactory.CreateMsgAudioEncoded(iAccumulateBuffer);
            iAccumulateBuffer.SetBytes(0);
            return msg;
        }
        else {
            THROW(AudioCacheException);
        }
    }
    ASSERTS();
    return nullptr;
}

TBool Mpeg4OutOfBandReader::PopulateBuffer(Bwx& aBuf, TUint aBytes)
{
    while (aBytes > 0) {
        TBool success = true;
        if (iReadBuffer.Bytes() == 0) {
            WriterBuffer writerBuffer(iReadBuffer);

            // For efficiency, try fill entire read buffer in case more reads come in.
            TUint bytes = iReadBuffer.MaxBytes();
            TUint64 fileBytesRemaining = 0;
            if (iStreamBytes > iOffset) {
                fileBytesRemaining = iStreamBytes - iOffset;
            }
            // Don't want to read beyond end of stream, as TryGetUrl() will return false.
            if (fileBytesRemaining < bytes) {
                // If we get here, fileBytesRemaining MUST fit within TUint.
                bytes = static_cast<TUint>(fileBytesRemaining);
            }
            success = iBlockWriter.TryGetUrl(writerBuffer, iOffset, bytes);
            //success = iBlockWriter.TryGetUrl(writerBuffer, iOffset, iReadBuffer.MaxBytes());
            iOffset += iReadBuffer.Bytes();
        }

        if (iReadBuffer.Bytes() <= aBytes) {
            aBuf.Append(iReadBuffer);
            aBytes -= iReadBuffer.Bytes();
            iReadBuffer.SetBytes(0);
        }
        else {
            aBuf.Append(Brn(iReadBuffer.Ptr(), aBytes));
            iReadBuffer.Replace(Brn(iReadBuffer.Ptr()+aBytes, iReadBuffer.Bytes()-aBytes));
            aBytes = 0;
        }

        if (!success) {
            return false;
        }
    }
    ASSERT(aBytes == 0);
    return true;
}


// Mpeg4MetadataChecker

Mpeg4MetadataChecker::Mpeg4MetadataChecker()
    : iMetadataAvailable(false)
{
}

void Mpeg4MetadataChecker::Reset()
{
    iMetadataAvailable = false;
}

TBool Mpeg4MetadataChecker::MetadataAvailable() const
{
    return iMetadataAvailable;
}

void Mpeg4MetadataChecker::MetadataRetrieved()
{
    iMetadataAvailable = true;
}


// Mpeg4Container

Mpeg4Container::Mpeg4Container(IMimeTypeList& aMimeTypeList)
    : ContainerBase(Brn("MP4"))
    , iBoxRoot(iProcessorFactory)
    , iBoxRootOutOfBand(iProcessorFactory) // Share factory; okay here as neither should access the same box simultaneously.
    , iOutOfBandReader(nullptr)
    , iSeekObserver(nullptr)
    , iLock("MP4L")
{
    aMimeTypeList.Add("audio/mp4");
}

Mpeg4Container::~Mpeg4Container()
{
    delete iOutOfBandReader;
}

void Mpeg4Container::Construct(IMsgAudioEncodedCache& aCache, MsgFactory& aMsgFactory, IContainerSeekHandler& aSeekHandler, IContainerUrlBlockWriter& aUrlBlockWriter, IContainerStopper& aContainerStopper)
{
    ContainerBase::Construct(aCache, aMsgFactory, aSeekHandler, aUrlBlockWriter, aContainerStopper);

    iOutOfBandReader = new Mpeg4OutOfBandReader(aMsgFactory, aUrlBlockWriter);

    iProcessorFactory.Add(new Mpeg4BoxSwitcher(iProcessorFactory, Brn("trak")));
    iProcessorFactory.Add(new Mpeg4BoxSwitcher(iProcessorFactory, Brn("mdia")));
    iProcessorFactory.Add(new Mpeg4BoxSwitcher(iProcessorFactory, Brn("minf")));
    iProcessorFactory.Add(new Mpeg4BoxSwitcher(iProcessorFactory, Brn("stbl")));
    iProcessorFactory.Add(new Mpeg4BoxMoov(iProcessorFactory, iMetadataChecker));
    iProcessorFactory.Add(new Mpeg4BoxStsd(iStreamInfo, iCodecInfo));
    iProcessorFactory.Add(new Mpeg4BoxStts(iSeekTable));
    iProcessorFactory.Add(new Mpeg4BoxStsc(iSeekTable));
    iProcessorFactory.Add(new Mpeg4BoxStco(iSeekTable));
    iProcessorFactory.Add(new Mpeg4BoxCo64(iSeekTable));
    iProcessorFactory.Add(new Mpeg4BoxStsz(iSampleSizeTable));
    iProcessorFactory.Add(new Mpeg4BoxMdhd(iDurationInfo));
    iProcessorFactory.Add(
        new Mpeg4BoxMdat(iBoxRootOutOfBand, iMetadataChecker, *this, *this, iBoxRoot, iSeekTable, iSampleSizeTable, *iOutOfBandReader));

    ASSERT(iSeekObserver != nullptr);

    Reset();
}

Msg* Mpeg4Container::Recognise()
{
    LOG(kMedia, "Mpeg4Container::Recognise\n");

    if (!iRecognitionStarted) {
        static const TUint kSizeBytes = 4;
        iCache->Discard(kSizeBytes);
        iCache->Inspect(iRecogBuf, iRecogBuf.MaxBytes());
        iRecognitionStarted = true;
    }

    // Avoid pulling through new MsgEncodedStream during recognition (which would then be discarded!)
    Msg* msg = iCache->Pull();
    if (msg != nullptr) {
        return msg;
    }

    if (iRecogBuf == Brn("ftyp")) {
        iRecognitionSuccess = true;
        return nullptr;
    }

    return nullptr;
}

TBool Mpeg4Container::Recognised() const
{
    return iRecognitionSuccess;
}

void Mpeg4Container::Reset()
{
    iProcessorFactory.Reset();
    iBoxRoot.Reset();
    iBoxRoot.Set(*iCache, Mpeg4BoxSwitcherRoot::kNoTargetId);
    iBoxRootOutOfBand.Reset();
    iMetadataChecker.Reset();
    iDurationInfo.Reset();
    iStreamInfo.Reset();
    iCodecInfo.Reset();
    iSampleSizeTable.Clear();
    iSeekTable.Deinitialise();
    iRecognitionStarted = false;
    iRecognitionSuccess = false;
}

void Mpeg4Container::Init(TUint64 aStreamBytes)
{
    iOutOfBandReader->Reset(aStreamBytes);
}

TBool Mpeg4Container::TrySeek(TUint aStreamId, TUint64 aOffset)
{
    // As TrySeek requires a byte offset, any codec that uses an Mpeg4 stream MUST find the appropriate seek offset (in bytes) and pass that via TrySeek().
    // i.e., aOffset MUST match a chunk offset.

    const TUint chunkCount = iSeekTable.ChunkCount();
    for (TUint i = 0; i < chunkCount; i++) {
        if (iSeekTable.GetOffset(i) == aOffset) {
            const TBool seek = iSeekHandler->TrySeekTo(aStreamId, aOffset);
            if (seek) {
                iSeekObserver->ChunkSeek(i);
            }
            return seek;
        }
    }
    ASSERTS();
    return false;
}

Msg* Mpeg4Container::Pull()
{
    try {
        return iBoxRoot.Process();
    }
    catch (MediaMpeg4FileInvalid&) {
        THROW(ContainerStreamCorrupt);
    }
}

MsgAudioEncoded* Mpeg4Container::GetMetadata()
{
    // FIXME - should be able to pass codec info msg on directly without copying into buffer here.
    // However, need to know size of it for codecs to unpack it into a buffer, and it's generally small (< 50 bytes) and a one-off per stream so it isn't a huge performance hit.
    MsgAudioEncoded* codecInfo = iCodecInfo.CodecInfo();
    Bws<IMpeg4InfoWritable::kMaxStreamDescriptorBytes> codecInfoBuf;
    ASSERT(codecInfoBuf.MaxBytes() >= codecInfo->Bytes());
    codecInfo->CopyTo(const_cast<TByte*>(codecInfoBuf.Ptr()));
    codecInfoBuf.SetBytes(codecInfo->Bytes());
    codecInfo->RemoveRef();

    Mpeg4Info info(iStreamInfo.Codec(), iStreamInfo.SampleRate(),
            iDurationInfo.Timescale(), iStreamInfo.Channels(),
            iStreamInfo.BitDepth(), iDurationInfo.Duration(), codecInfoBuf);

    Mpeg4InfoWriter writer(info);
    Bws<Mpeg4InfoWriter::kMaxBytes> infoBuf;
    WriterBuffer writerBuf(infoBuf);
    writer.Write(writerBuf);

    // Need to create MsgAudioEncoded w/ data for codec.
    MsgAudioEncoded* msg = iMsgFactory->CreateMsgAudioEncoded(infoBuf);

    // Write sample size table so decoder knows how many bytes to read for each sample (MPEG4 term)/frame (AAC term).
    MsgAudioEncoded* msgSampleSizeTable = WriteSampleSizeTable();
    msg->Add(msgSampleSizeTable);

    // Write seek table so that codec can determine correct byte position that it should request to seek to.
    MsgAudioEncoded* msgSeekTable = WriteSeekTable();
    msg->Add(msgSeekTable);

    return msg;
}

void Mpeg4Container::RegisterChunkSeekObserver(
        IMpeg4ChunkSeekObserver& aChunkSeekObserver)
{
    iSeekObserver = &aChunkSeekObserver;
}

MsgAudioEncoded* Mpeg4Container::WriteSampleSizeTable() const
{
    MsgAudioEncodedWriter writerMsg(*iMsgFactory);
    WriterBinary writerBin(writerMsg);

    const TUint count = iSampleSizeTable.Count();
    writerBin.WriteUint32Be(count);
    for (TUint i = 0; i < count; i++) {
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
