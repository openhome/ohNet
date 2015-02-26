#include <OpenHome/Media/Protocol/ContentAudio.h>
#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Media/Pipeline/Msg.h>
#include <OpenHome/Buffer.h>

using namespace OpenHome;
using namespace OpenHome::Media;

// ContentAudio

ContentAudio::ContentAudio(MsgFactory& aMsgFactory, IPipelineElementDownstream& aDownstream)
{
    iSupply = new Supply(aMsgFactory, aDownstream);
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

ProtocolStreamResult ContentAudio::Stream(IProtocolReader& aReader, TUint64 aTotalBytes)
{
    ProtocolStreamResult res = EProtocolStreamSuccess;
    iBuf.SetBytes(0);
    TUint remaining = kMaxReadBytes;
    const TBool finite = (aTotalBytes!=0);
    try {
        for (;;) {
            if (finite && aTotalBytes < remaining) {
                remaining = (TUint)aTotalBytes;
            }
            while (remaining > 0) {
                TUint bytes = remaining;
                if (bytes > kMaxReadBytes) {
                    bytes = kMaxReadBytes;
                }
                Brn buf = aReader.Read(bytes);
                iBuf.Append(buf);
                remaining -= buf.Bytes();
            }
            iSupply->OutputData(iBuf);
            if (finite) {
                aTotalBytes -= iBuf.Bytes();
                if (aTotalBytes == 0) {
                    break;
                }
            }
            remaining = kMaxReadBytes;
            iBuf.SetBytes(0);
        }
    }
    catch (ReaderError&) {
        res = EProtocolStreamErrorRecoverable;
        iBuf.Append(aReader.ReadRemaining());
        iSupply->OutputData(iBuf);
        if (finite) {
            aTotalBytes -= iBuf.Bytes();
        }
    }
    return res;
}
