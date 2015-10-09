#ifndef HEADER_PIPELINE_AUDIO_DUMPER
#define HEADER_PIPELINE_AUDIO_DUMPER

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Media/Pipeline/Msg.h>

namespace OpenHome {
namespace Media {

/**
 * This class is only intended for use on platforms where filesystem utilities
 * and time functions exist.
 */
class AudioDumper : public PipelineElement, public IPipelineElementDownstream, private INonCopyable
{
private:
    static const TUint kSupportedMsgTypes;
    /**
    * Time format: Year|Month|Day|Hour|Min|Sec
    * e.g., 9 Oct 2015 10:59:23 == 20151009105923
    */
    static const TUint kMaxTimeFormatBytes = 15;    // Extra byte for '\0'.
    static const TUint kMaxFilenameBytes = 150;
    static const Brn kDumpPrefix;
public:
    AudioDumper(IPipelineElementDownstream& aDownstream);
    ~AudioDumper();
    void SetEnabled(TBool aEnabled);
public: // from IPipelineElementDownstream
    void Push(Msg* aMsg) override;
private: // from PipelineElement
    Msg* ProcessMsg(MsgEncodedStream* aMsg) override;
    Msg* ProcessMsg(MsgAudioEncoded* aMsg) override;
private:
    void SetCurrentTime();
    void ConstructFilename(TUint aSeq, const Brx& aUri, Bwx& aBuf);
private:
    IPipelineElementDownstream& iDownstream;
    FileSystemAnsii iFileSystem;
    Bws<kMaxTimeFormatBytes> iTime;
    IFile* iFile;
    Bws<EncodedAudio::kMaxBytes> iBuf;
    TBool iEnabled;
    TUint iSeq;
};

} // namespace Media
} // namespace OpenHome

#endif  // HEADER_PIPELINE_AUDIO_DUMPER
