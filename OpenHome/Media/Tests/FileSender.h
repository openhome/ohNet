#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Printer.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Private/Terminal.h>
#include <OpenHome/Media/PipelineManager.h>
#include <OpenHome/Media/Codec/Flac.h>
#include <OpenHome/Media/Codec/Wav.h>
#include <OpenHome/Media/DriverSongcastSender.h>
#include <OpenHome/Media/Msg.h>
#include <OpenHome/Av/InfoProvider.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Debug.h>
#include "AllocatorInfoLogger.h"

namespace OpenHome {
namespace Media {

class SupplierFile : public Thread, public ISupplier
{
public:
    SupplierFile();
    ~SupplierFile();
    TBool LoadFile(const Brx& aFileName);
    void Block();
    void Unblock();
private: // from Thread
    void Run();
private:
    MsgAudioEncoded* CreateAudio();
private: // from ISupplier
    void Initialise(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstreamElement);
    void Play();
    void Flush(Msg* aMsg);
    void Quit(Msg* aMsg);
private:
    Mutex iLock;
    Semaphore iBlocker;
    MsgFactory* iMsgFactory;
    IPipelineElementDownstream* iPipeline;
    Msg* iPendingMsg;
    TBool iBlock;
    TBool iQuit;
    IFile* iFile;
    Bwh   iBuf;
    TUint iDataSize;
    TUint iBytesRemaining;
};

class FileSender : private IPipelineObserver
{
    static const TUint kMaxDriverJiffies = Jiffies::kJiffiesPerMs * 5;
public:
    FileSender(Environment& aEnv, ITerminal& aTerminal, Net::DvStack& aDvStack, const Brx& aFileName, TIpAddress aAdapter, const Brx& aSenderUdn, const TChar* aSenderFriendlyName, TUint aSenderChannel, TBool aMulticast);
    virtual ~FileSender();
    int Run();
private: // from IPipelineObserver
    void NotifyPipelineState(EPipelineState aState);
    void NotifyTrack();
    void NotifyMetaText(const Brx& aText);
    void NotifyTime(TUint aSeconds, TUint aTrackDurationSeconds);
    void NotifyStreamInfo(const DecodedStreamInfo& aStreamInfo);
private:
    ITerminal& iTerminal;
    SupplierFile* iSupplier;
    AllocatorInfoLogger iInfoAggregator;
    PipelineManager* iPipeline;
    Net::DvDeviceStandard* iDevice;
    DriverSongcastSender* iDriver;
    Brh iFileName;
};

} // namespace Media
} // namespace OpenHome

