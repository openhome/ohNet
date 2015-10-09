#include <OpenHome/Types.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Media/Pipeline/AudioDumper.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/Printer.h>

#include <ctime>

using namespace OpenHome;
using namespace OpenHome::Media;

const TUint AudioDumper::kSupportedMsgTypes =   eMode
                                              | eTrack
                                              | eDrain
                                              | eDelay
                                              | eEncodedStream
                                              | eAudioEncoded
                                              | eMetatext
                                              | eStreamInterrupted
                                              | eHalt
                                              | eFlush
                                              | eWait
                                              | eQuit;

const Brn AudioDumper::kDumpPrefix("AudioDump");

AudioDumper::AudioDumper(IPipelineElementDownstream& aDownstream)
    : PipelineElement(kSupportedMsgTypes)
    , iDownstream(aDownstream)
    , iFile(nullptr)
    , iEnabled(false)
    , iSeq(0)
{
    /**
     * FIXME - bug in current filesystem handling: unable to create dirs.
     * So, can't create an "AudioDump-<time>" dir with all streams under it.
     *
     * Instead, prefix all streams from a session with "AudioDump-<time>-".
     * Initialise current time here so that same time is reused for all
     * filenames in session.
     */
    SetCurrentTime();
}

AudioDumper::~AudioDumper()
{
    if (iFile != nullptr) {
        delete iFile;
        iFile = nullptr;
    }
}

void AudioDumper::SetEnabled(TBool aEnabled)
{
    // If file was allowed to be open when this was set to disabled, would need to close file while holding a mutex to ensure no ProcessMsg() method attempted to write to an invalid file ptr.
    ASSERT(iFile == nullptr);
    iEnabled = aEnabled;
}

void AudioDumper::Push(Msg* aMsg)
{
    Msg* msg = aMsg->Process(*this);
    ASSERT(msg != nullptr);
    iDownstream.Push(msg);
}

Msg* AudioDumper::ProcessMsg(MsgEncodedStream* aMsg)
{
    if (iEnabled) {
        if (iFile != nullptr) {
            delete iFile;
            iFile = nullptr;
        }

        // Don't try create file if URI is empty.
        if (aMsg->Uri().Bytes() > 0) {
            Bws<kMaxFilenameBytes> filename;
            ConstructFilename(aMsg->StreamId(), aMsg->Uri(), filename);
            try {
                iFile = iFileSystem.Open(filename.PtrZ(), eFileReadWrite);
            }
            catch (FileOpenError&) {
                Log::Print("AudioDumper failed to open file %s\n.", filename.PtrZ());
                iFile = nullptr;
            }
        }
    }
    return aMsg;
}

Msg* AudioDumper::ProcessMsg(MsgAudioEncoded* aMsg)
{
    if (iEnabled) {
        if (iFile != nullptr) {
            aMsg->CopyTo(const_cast<TByte*>(iBuf.Ptr()));
            iBuf.SetBytes(aMsg->Bytes());
            try {
                iFile->Write(iBuf);
            }
            catch (FileWriteError&) {
                Log::Print("AudioDumper failed to write audio block. Closing file\n.");
                delete iFile;
                iFile = nullptr;
            }
            iBuf.SetBytes(0);
        }
    }
    return aMsg;
}

void AudioDumper::SetCurrentTime()
{
    // Get current system time.
    time_t timeCurrent = time(nullptr);
    struct tm* timeInfo = localtime(&timeCurrent);

    // Time format:
    // - Year|Month|Day|Hour|Min|Sec
    size_t size = strftime((char*)iTime.Ptr(), iTime.MaxBytes(), "%Y%m%d%H%M%S", timeInfo);
    iTime.SetBytes(size); // Ignores '\0'.
    ASSERT(size == iTime.MaxBytes()-1);
}

void AudioDumper::ConstructFilename(TUint aSeq, const Brx& aUri, Bwx& aBuf)
{
    ASSERT(aUri.Bytes() != 0);
    ASSERT(iTime.Bytes() != 0);

    // Parse URI to get filename.
    Uri uri(aUri);
    Parser p(uri.Path());
    Brn streamFile;
    while (!p.Finished()) {
        streamFile = p.Next('/');
    }

    // Construct file path.

    // Directory part.
    aBuf.Append(kDumpPrefix);
    aBuf.Append('-');
    aBuf.Append(iTime);
    aBuf.Append('-');

    // Filename part.
    // Assume stream dumps will only go into the 100s. Prefix numbers <100 with "0"s.
    ASSERT(aSeq < 1000);
    if (aSeq < 10) {
        aBuf.Append("00");
    }
    else if (aSeq < 100) {
        aBuf.Append("0");
    }
    Ascii::AppendDec(aBuf, aSeq);
    aBuf.Append('-');
    aBuf.Append(streamFile);
}
