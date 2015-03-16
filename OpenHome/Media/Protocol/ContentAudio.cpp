#include <OpenHome/Media/Protocol/ContentAudio.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ContentAudio

ContentAudio::ContentAudio(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new SupplyAggregatorBytes(aMsgFactory, aDownstream);
}

ContentAudio::~ContentAudio()
{
    delete iSupply;
}

TBool ContentAudio::Recognise(const Brx& /*aUri*/, const Brx& /*aMimeType*/, const Brx& /*aData*/)
{
    /* Assume that this processor will be offered content last.
       Content we don't support will be rejected.
       ...so we might as well have a go at treating everything as audio. */
    return true;
}

ProtocolStreamResult ContentAudio::Stream(IReader& aReader, TUint64 aTotalBytes)
{
    ProtocolStreamResult res = EProtocolStreamSuccess;
    try {
        for (;;) {
            Brn buf = aReader.Read(kMaxReadBytes);
            iSupply->OutputData(buf);
            if (aTotalBytes > 0) {
                if (buf.Bytes() > aTotalBytes) { // aTotalBytes is inaccurate - ignore it
                    aTotalBytes = 0;
                }
                else {
                    aTotalBytes -= buf.Bytes();
                    if (aTotalBytes == 0) {
                        iSupply->Flush();
                        break;
                    }
                }
            }
        }
    }
    catch (ReaderError&) {
        res = EProtocolStreamErrorRecoverable;
        iSupply->Flush();
    }
    /* FIXME - following catch()es are temporary, allowing time for ProtocolHls to be updated
               to stop throwing custom exceptions out of IReader::Read() */
    catch (AssertionFailed&) {
        throw;
    }
    catch (...) {
        iSupply->Flush();
        throw;
    }
    return res;
}
