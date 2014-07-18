#include <OpenHome/Av/Raop/RaopHeader.h>
#include <OpenHome/Types.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Av/Debug.h>

using namespace OpenHome;
using namespace OpenHome::Av;

RaopDataHeader::RaopDataHeader(Brx& aRawData, TUint aSenderSkew, TUint aLatency)
    : iSenderSkew(aSenderSkew)
    , iLatency(aLatency)
{
    if(aRawData.Bytes() < 12) {
        THROW(NetworkError);
    }
    iBytes = static_cast<TUint16>(aRawData.Bytes()-12);
    iVersion = aRawData[0];
    iPayload = aRawData[1];
    iStart = aRawData[1] != 0x60 ? true : false;
    iSeqno = Converter::BeUint16At(aRawData, 2);
    iTimestamp = Converter::BeUint32At(aRawData, 4);
    iMute = false;
    //LOG(kMedia, "RaopDataHeader raw bytes %d, seqno %d, timestamp %d start %d\n", iBytes, iSeqno, iTimestamp, iStart);
}

RaopDataHeader::RaopDataHeader(Brx& aBinData)
{
    iVersion = ((RaopDataHeader*)(aBinData.Ptr()))->Version();
    iPayload = ((RaopDataHeader*)(aBinData.Ptr()))->Payload();
    iSenderSkew = ((RaopDataHeader*)(aBinData.Ptr()))->SenderSkew();
    iLatency = ((RaopDataHeader*)(aBinData.Ptr()))->Latency();
    iBytes = ((RaopDataHeader*)(aBinData.Ptr()))->Bytes();
    iStart = ((RaopDataHeader*)(aBinData.Ptr()))->Start();
    iSeqno = ((RaopDataHeader*)(aBinData.Ptr()))->Seqno();
    iTimestamp = ((RaopDataHeader*)(aBinData.Ptr()))->Timestamp();
    iMute = ((RaopDataHeader*)(aBinData.Ptr()))->Mute();
    //LOG(kMedia, "RaopDataHeader bin bytes %d, seqno %d, timestamp %d start %d\n", iBytes, iSeqno, iTimestamp, iStart);
}

TByte RaopDataHeader::Version()
{
    return iVersion;
}

TByte RaopDataHeader::Payload()
{
    return iPayload;
}

TUint RaopDataHeader::SenderSkew()
{
    return iSenderSkew;
}

TUint RaopDataHeader::Latency()
{
    return iLatency;
}

TUint16 RaopDataHeader::Seqno()
{
    return iSeqno;
}

TUint16 RaopDataHeader::Bytes()
{
    return iBytes;
}

TUint32 RaopDataHeader::Timestamp()
{
    return iTimestamp;
}

TBool RaopDataHeader::Start()
{
    return iStart;
}

TBool RaopDataHeader::Mute()
{
    return iMute;
}

void RaopDataHeader::SetMute()
{
    iMute = true;
}
