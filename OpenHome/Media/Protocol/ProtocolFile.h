#ifndef HEADER_PIPELINE_PROTOCOL_FILE
#define HEADER_PIPELINE_PROTOCOL_FILE

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Uri.h>
#include <OpenHome/Private/File.h>
#include <OpenHome/Media/Protocol/Protocol.h>

#include <vector>

namespace OpenHome {
namespace Media {

class ProtocolFile : public Protocol
{
public:
	ProtocolFile(Environment& aEnv);
private: // from Protocol	
    ProtocolStreamResult Stream(const Brx& aUri);
private: // from IStreamHandler
    TBool OkToPlay(TUint aTrackId, TUint aStreamId);
    TUint TrySeek(TUint aTrackId, TUint aStreamId, TUint64 aOffset);
    TUint TryStop(TUint aTrackId, TUint aStreamId);
private:
    static const TUint kReadBufBytes = 4 * 1024;
    Mutex iLock;
    Semaphore iSem;
    OpenHome::Uri iUri;
    FileStream iFileStream;
    Srs<kReadBufBytes> iReaderBuf;
    TUint iStreamId;
    TBool iStop;
    TBool iSeek;
    TUint32 iSeekPos;
    TUint iLastFlushId;
};

};  // namespace Media
};  // namespace OpenHome

#endif  // HEADER_PIPELINE_PROTOCOL_FILE
