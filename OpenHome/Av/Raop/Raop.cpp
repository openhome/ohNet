#include <OpenHome/Media/Debug.h>
#include <OpenHome/Av/Product.h>
#include <OpenHome/Av/Raop/Raop.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Net/Private/MdnsProvider.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Converter.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/NetworkAdapterList.h>
#include <OpenHome/Private/Parser.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Av/VolumeManager.h>
#include <math.h>

#include <openssl/evp.h>


using namespace OpenHome;
using namespace OpenHome::Av;
using namespace OpenHome::Media;


// RaopDevice

RaopDevice::RaopDevice(Net::DvStack& aDvStack, TUint aDiscoveryPort, IFriendlyNameObservable& aFriendlyNameObservable, TIpAddress aIpAddr, const Brx& aMacAddr)
    : iProvider(*aDvStack.MdnsProvider())
    , iFriendlyNameObservable(aFriendlyNameObservable)
    , iEndpoint(aDiscoveryPort, aIpAddr)
    , iMacAddress(aMacAddr)
    , iRegistered(false)
    , iLock("RADL")
{
    //Endpoint ep(aDiscoveryPort, aIpAddr);
    //Bws<Endpoint::kMaxEndpointBytes> epBuf;
    //ep.AppendEndpoint(epBuf);
    //LOG(kMedia, "RaopDevice::RaopDevice ep: %.*s\n", PBUF(epBuf));

    ASSERT(&iProvider); // Cannot function without MDNS
    iHandleRaop = iProvider.MdnsCreateService();

    ASSERT(aMacAddr.Bytes() == 12);
    iFriendlyNameId = aFriendlyNameObservable.RegisterFriendlyNameObserver(MakeFunctorGeneric<const Brx&>(*this, &RaopDevice::FriendlyNameUpdate));   // Functor is called within this.
}

RaopDevice::~RaopDevice()
{
    Deregister();   // Call this just in case owning object forgot to call it.
    iFriendlyNameObservable.DeregisterFriendlyNameObserver(iFriendlyNameId);
}

void RaopDevice::FriendlyNameUpdate(const Brx& aNewFriendlyName)
{
    AutoMutex a(iLock);
    const TBool wasRegistered = iRegistered;

    if (wasRegistered) {
        DoDeregister();
    }

    iName.Replace("");
    iName.Append(iMacAddress);
    iName.Append("@");
    iName.Append(aNewFriendlyName);

    LOG(kBonjour, "RaopDevice::FriendlyNameUpdate %.*s", PBUF(iName));

    if (wasRegistered) {
        DoRegister();
    }
}

void RaopDevice::Register()
{
    AutoMutex am(iLock);
    if (iRegistered) {
        return; // already registered
    }
    DoRegister();
    iRegistered = true;
}

// Call with iLock held
void RaopDevice::DoRegister()
{
    Bws<200> info;

    iProvider.MdnsAppendTxtRecord(info, "txtvers", "1");
    iProvider.MdnsAppendTxtRecord(info, "ch", "2");
    iProvider.MdnsAppendTxtRecord(info, "cn", "0,1");
    iProvider.MdnsAppendTxtRecord(info, "ek", "1");
    iProvider.MdnsAppendTxtRecord(info, "et", "0,1");
    iProvider.MdnsAppendTxtRecord(info, "sv", "false");
    iProvider.MdnsAppendTxtRecord(info, "da", "true");
    iProvider.MdnsAppendTxtRecord(info, "sr", "44100");
    iProvider.MdnsAppendTxtRecord(info, "ss", "16");
    iProvider.MdnsAppendTxtRecord(info, "pw", "false");
    iProvider.MdnsAppendTxtRecord(info, "sm", "false");
    iProvider.MdnsAppendTxtRecord(info, "tp", "UDP");
    iProvider.MdnsAppendTxtRecord(info, "vn", "3");

    LOG(kBonjour, "RaopDevice::Register name: %.*s port: %u, address: %u\n", PBUF(iName), iEndpoint.Port(), iEndpoint.Address());

    iProvider.MdnsRegisterService(iHandleRaop, iName.PtrZ(), "_raop._tcp", iEndpoint.Address(), iEndpoint.Port(), info.PtrZ());
}

void RaopDevice::Deregister()
{
    AutoMutex am(iLock);
    if (!iRegistered) {
        return; // already registered
    }
    DoDeregister();
    iRegistered = false;
}

void RaopDevice::DoDeregister()
{
    iProvider.MdnsDeregisterService(iHandleRaop);
}

const Endpoint& RaopDevice::GetEndpoint() const
{
    return iEndpoint;
}

const Brx& RaopDevice::MacAddress() const
{
    return iMacAddress;
}

void RaopDevice::MacAddressOctets(TByte (&aOctets)[6]) const
{
    LOG(kBonjour, ">RaopDevice::MacAddressOctets\n");
    aOctets[0] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr(), 2)));
    aOctets[1] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr()+2, 2)));
    aOctets[2] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr()+4, 2)));
    aOctets[3] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr()+6, 2)));
    aOctets[4] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr()+8, 2)));
    aOctets[5] = static_cast<TByte>(Ascii::UintHex(Brn(iMacAddress.Ptr()+10, 2)));

    LOG(kBonjour, "RaopDevice::MacAddressOctets %u:%u:%u:%u:%u:%u\n",
                  aOctets[0], aOctets[1], aOctets[2], aOctets[3], aOctets[4], aOctets[5]);
}


// RaopDiscoverySession

RaopDiscoverySession::RaopDiscoverySession(Environment& aEnv, RaopDiscoveryServer& aDiscovery, RaopDevice& aRaopDevice, TUint aInstance, IVolume& aVolume)
    : iAeskeyPresent(false)
    , iAesSid(0)
    //, iRaopObserver(aObserver)
    , iDiscovery(aDiscovery)
    , iRaopDevice(aRaopDevice)
    , iInstance(aInstance)
    , iActive(false)
    , iShutdownSem("RAOP", 1)
    , iAudioPort(0)
    , iControlPort(0)
    , iTimingPort(0)
    , iClientControlPort(0)
    , iClientTimingPort(0)
    , iVolume(aVolume)
{
    iReaderBuffer = new Srs<1024>(*this);
    iReaderUntil = new ReaderUntilS<kMaxReadBufferBytes>(*iReaderBuffer);
    iReaderProtocol = new ReaderProtocolS<kMaxReadBufferBytes>(*iReaderUntil);
    iWriterBuffer = new Sws<kMaxWriteBufferBytes>(*this);
    iWriterAscii = new WriterAscii(*iWriterBuffer);
    iReaderRequest = new ReaderHttpRequest(aEnv, *iReaderUntil);
    iWriterRequest = new WriterRtspRequest(*iWriterBuffer);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);

    iReaderRequest->AddHeader(iHeaderContentLength);
    iReaderRequest->AddHeader(iHeaderContentType);
    iReaderRequest->AddHeader(iHeaderCSeq);
    iReaderRequest->AddHeader(iHeaderAppleChallenge);
    iReaderRequest->AddHeader(iHeaderRtspTransport);
    iReaderRequest->AddHeader(iHeaderRtpInfo);
    iReaderRequest->AddMethod(RtspMethod::kOptions);
    iReaderRequest->AddMethod(RtspMethod::kAnnounce);
    iReaderRequest->AddMethod(RtspMethod::kSetup);
    iReaderRequest->AddMethod(RtspMethod::kRecord);
    iReaderRequest->AddMethod(RtspMethod::kSetParameter);
    iReaderRequest->AddMethod(RtspMethod::kFlush);
    iReaderRequest->AddMethod(RtspMethod::kTeardown);
    iReaderRequest->AddMethod(RtspMethod::kPost);

    iDeactivateTimer = new Timer(aEnv, MakeFunctor(*this, &RaopDiscoverySession::DeactivateCallback), "RaopDiscoverySession");
}

void RaopDiscoverySession::WriteSeq(TUint aCSeq)
{
    iWriterAscii->Write(Brn("CSeq: "));
    iWriterAscii->WriteUint(aCSeq);
    iWriterAscii->WriteNewline();
}

void RaopDiscoverySession::WriteFply(Brn aData)
{
    const TByte cfply1[] = {
                    0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x82, 0x02, 0x00,

                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const TByte cfply2[] = {
                    0x02, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x14
    };

    Bws<200> fply(Brn("FPLY"));
    if(aData[6] == 1) {     // respond to first POST
        fply.Append(cfply1, sizeof(cfply1));
        fply[13] = aData[14];       // copy current variable count
    }
    else {
        fply.Append(cfply2, sizeof(cfply2));
        fply.Append(&aData[0x90], 0x14);    // data is same as last 0x14 bytes of iTunes data
    }
    iWriterAscii->Write(RtspHeader::kContentLength);
    iWriterAscii->Write(Brn(": "));
    iWriterAscii->WriteUint(fply.Bytes());
    iWriterAscii->WriteNewline();
    iWriterAscii->WriteNewline();
    iWriterAscii->Write(fply);
}

void RaopDiscoverySession::GetRsa()
{
    static const unsigned char key_private[] = {
            0x30, 0x82, 0x04, 0xA5, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00, 0xE7, 0xD7, 0x44, 0xF2,
            0xA2, 0xE2, 0x78, 0x8B, 0x6C, 0x1F, 0x55, 0xA0, 0x8E, 0xB7, 0x05, 0x44, 0xA8, 0xFA, 0x79, 0x45,
            0xAA, 0x8B, 0xE6, 0xC6, 0x2C, 0xE5, 0xF5, 0x1C, 0xBD, 0xD4, 0xDC, 0x68, 0x42, 0xFE, 0x3D, 0x10,
            0x83, 0xDD, 0x2E, 0xDE, 0xC1, 0xBF, 0xD4, 0x25, 0x2D, 0xC0, 0x2E, 0x6F, 0x39, 0x8B, 0xDF, 0x0E,
            0x61, 0x48, 0xEA, 0x84, 0x85, 0x5E, 0x2E, 0x44, 0x2D, 0xA6, 0xD6, 0x26, 0x64, 0xF6, 0x74, 0xA1,
            0xF3, 0x04, 0x92, 0x9A, 0xDE, 0x4F, 0x68, 0x93, 0xEF, 0x2D, 0xF6, 0xE7, 0x11, 0xA8, 0xC7, 0x7A,
            0x0D, 0x91, 0xC9, 0xD9, 0x80, 0x82, 0x2E, 0x50, 0xD1, 0x29, 0x22, 0xAF, 0xEA, 0x40, 0xEA, 0x9F,
            0x0E, 0x14, 0xC0, 0xF7, 0x69, 0x38, 0xC5, 0xF3, 0x88, 0x2F, 0xC0, 0x32, 0x3D, 0xD9, 0xFE, 0x55,
            0x15, 0x5F, 0x51, 0xBB, 0x59, 0x21, 0xC2, 0x01, 0x62, 0x9F, 0xD7, 0x33, 0x52, 0xD5, 0xE2, 0xEF,
            0xAA, 0xBF, 0x9B, 0xA0, 0x48, 0xD7, 0xB8, 0x13, 0xA2, 0xB6, 0x76, 0x7F, 0x6C, 0x3C, 0xCF, 0x1E,
            0xB4, 0xCE, 0x67, 0x3D, 0x03, 0x7B, 0x0D, 0x2E, 0xA3, 0x0C, 0x5F, 0xFF, 0xEB, 0x06, 0xF8, 0xD0,
            0x8A, 0xDD, 0xE4, 0x09, 0x57, 0x1A, 0x9C, 0x68, 0x9F, 0xEF, 0x10, 0x72, 0x88, 0x55, 0xDD, 0x8C,
            0xFB, 0x9A, 0x8B, 0xEF, 0x5C, 0x89, 0x43, 0xEF, 0x3B, 0x5F, 0xAA, 0x15, 0xDD, 0xE6, 0x98, 0xBE,
            0xDD, 0xF3, 0x59, 0x96, 0x03, 0xEB, 0x3E, 0x6F, 0x61, 0x37, 0x2B, 0xB6, 0x28, 0xF6, 0x55, 0x9F,
            0x59, 0x9A, 0x78, 0xBF, 0x50, 0x06, 0x87, 0xAA, 0x7F, 0x49, 0x76, 0xC0, 0x56, 0x2D, 0x41, 0x29,
            0x56, 0xF8, 0x98, 0x9E, 0x18, 0xA6, 0x35, 0x5B, 0xD8, 0x15, 0x97, 0x82, 0x5E, 0x0F, 0xC8, 0x75,
            0x34, 0x3E, 0xC7, 0x82, 0x11, 0x76, 0x25, 0xCD, 0xBF, 0x98, 0x44, 0x7B, 0x02, 0x03, 0x01, 0x00,
            0x01, 0x02, 0x82, 0x01, 0x01, 0x00, 0xE5, 0xF0, 0x0C, 0x72, 0xF5, 0x77, 0xD6, 0x04, 0xB9, 0xA4,
            0xCE, 0x41, 0x22, 0xAA, 0x84, 0xB0, 0x17, 0x43, 0xEC, 0x99, 0x5A, 0xCF, 0xCC, 0x7F, 0x4A, 0xB2,
            0x7C, 0x0B, 0x18, 0x7F, 0x90, 0x66, 0x5B, 0xE3, 0x59, 0xDF, 0x12, 0x59, 0x81, 0x8D, 0xEE, 0xED,
            0x79, 0xD3, 0xB1, 0xEF, 0x84, 0x5E, 0x4D, 0xDD, 0xDA, 0xC9, 0xA1, 0x55, 0x37, 0x3B, 0x5E, 0x27,
            0x0D, 0x8E, 0x13, 0x15, 0x00, 0x1A, 0x2E, 0x52, 0x7D, 0x54, 0xCD, 0xF9, 0x00, 0x0A, 0x57, 0x68,
            0xBC, 0x98, 0xD4, 0x44, 0x6B, 0x37, 0xBB, 0xBD, 0x00, 0xB2, 0x9D, 0xD8, 0xB5, 0x30, 0x62, 0x13,
            0x3B, 0x2A, 0x6E, 0x77, 0xF4, 0xEE, 0x32, 0x50, 0x56, 0x22, 0x90, 0x4D, 0xA7, 0x20, 0xFB, 0x1C,
            0x12, 0xC0, 0x39, 0x96, 0xDA, 0x71, 0x3A, 0x05, 0x06, 0x09, 0x8E, 0xDB, 0xED, 0xEC, 0xF9, 0x36,
            0xD0, 0xFA, 0x9C, 0xBD, 0x59, 0x29, 0xAB, 0xB0, 0xED, 0xA3, 0x57, 0x99, 0x50, 0x2F, 0x98, 0x94,
            0xDC, 0xB8, 0xFC, 0x56, 0x9A, 0x89, 0x2D, 0x17, 0x78, 0x03, 0x24, 0xA2, 0xB6, 0xC3, 0x16, 0x6E,
            0x34, 0x67, 0x09, 0x13, 0x4B, 0x85, 0x40, 0x41, 0xB8, 0x67, 0x70, 0x6B, 0x58, 0xFE, 0xF2, 0xA0,
            0xDB, 0x92, 0x2B, 0x77, 0x62, 0x8B, 0x68, 0xE6, 0x96, 0x93, 0xC7, 0xAF, 0x43, 0xBF, 0x2A, 0x73,
            0xD0, 0xB7, 0x32, 0x37, 0x7A, 0x0B, 0xA1, 0x7B, 0x44, 0xF0, 0x51, 0xE9, 0xBF, 0x79, 0x84, 0x9D,
            0xCB, 0x33, 0x32, 0x57, 0x1F, 0xD8, 0xA7, 0x09, 0x33, 0xC2, 0xD6, 0x0B, 0xDE, 0xC4, 0x79, 0x93,
            0x4A, 0x3D, 0xAC, 0xA4, 0x0B, 0xB6, 0xF2, 0xF3, 0x7C, 0x0A, 0x9D, 0x07, 0x10, 0x6E, 0xAD, 0xC8,
            0xB3, 0x69, 0xA0, 0x3F, 0x2F, 0x41, 0xC8, 0x80, 0x09, 0x8E, 0x8A, 0xDD, 0x46, 0x24, 0x0D, 0xAC,
            0x68, 0xCC, 0x53, 0x54, 0xF3, 0x61, 0x02, 0x81, 0x81, 0x00, 0xF7, 0xE0, 0xBF, 0x5A, 0x1E, 0x67,
            0x18, 0x31, 0x9A, 0x8B, 0x62, 0x09, 0xC3, 0x17, 0x14, 0x44, 0x04, 0x59, 0xF9, 0x73, 0x85, 0x66,
            0x13, 0xB1, 0x7A, 0xE1, 0x50, 0x8B, 0xB3, 0xE6, 0x31, 0x6E, 0x6B, 0x7F, 0x46, 0x2D, 0x2F, 0x7D,
            0x64, 0x41, 0x2B, 0x84, 0xB7, 0x6B, 0xC2, 0x3F, 0x2B, 0x0C, 0x35, 0x62, 0x45, 0x52, 0x79, 0xB2,
            0x43, 0xA9, 0xF7, 0x31, 0x6F, 0x95, 0x80, 0x07, 0xB3, 0x4C, 0x61, 0xF7, 0x68, 0xE2, 0xD4, 0x4E,
            0xD5, 0xFF, 0x2B, 0x27, 0x28, 0x17, 0xEC, 0x32, 0xB3, 0xE4, 0x93, 0x92, 0x92, 0x28, 0xFA, 0xE7,
            0x8E, 0x77, 0x4C, 0xA0, 0xF7, 0x5E, 0xBD, 0x69, 0xD5, 0x92, 0x02, 0x79, 0x8F, 0x11, 0x6E, 0x36,
            0x0C, 0x64, 0x38, 0xB3, 0x2E, 0x1B, 0xD8, 0xB9, 0xDC, 0x1E, 0x32, 0x32, 0xF0, 0xD3, 0x09, 0x18,
            0x88, 0x3C, 0xC4, 0x3E, 0xF8, 0xDD, 0xA2, 0x2C, 0x36, 0x91, 0x02, 0x81, 0x81, 0x00, 0xEF, 0x6F,
            0xFF, 0xF9, 0x94, 0xF1, 0xE5, 0x64, 0x41, 0xAA, 0x00, 0x35, 0xFD, 0x19, 0xA0, 0xC8, 0xD6, 0xF0,
            0x23, 0x78, 0xC7, 0x05, 0x80, 0xD9, 0xC4, 0x84, 0x20, 0x79, 0x1D, 0xF4, 0x07, 0xC5, 0x91, 0xFB,
            0x6E, 0xBF, 0xCA, 0x32, 0x2C, 0x30, 0x86, 0xDD, 0x90, 0x1F, 0xD2, 0xFA, 0xE1, 0xAE, 0xBB, 0x64,
            0xAD, 0xF6, 0xBB, 0x79, 0xFF, 0x80, 0x51, 0xBE, 0xBD, 0x0C, 0xD8, 0x20, 0xAB, 0x89, 0x87, 0x40,
            0x06, 0x01, 0xA7, 0xB2, 0xFE, 0x93, 0x90, 0xCA, 0xCC, 0x9A, 0xCA, 0xB8, 0xED, 0x2B, 0xF9, 0x1D,
            0x18, 0x6D, 0x8F, 0x69, 0x64, 0x3D, 0x7E, 0xFE, 0x0F, 0x5D, 0x56, 0xDF, 0x75, 0x77, 0xA2, 0xD0,
            0x35, 0xEA, 0x54, 0x13, 0xFC, 0x98, 0xD8, 0xF3, 0xF9, 0x08, 0xDA, 0x05, 0x9A, 0x37, 0x9D, 0xA4,
            0xB1, 0xCC, 0x38, 0xF1, 0x5D, 0x56, 0x0A, 0x83, 0xCC, 0x31, 0x71, 0x53, 0xC8, 0x4B, 0x02, 0x81,
            0x81, 0x00, 0xD0, 0xEB, 0xAF, 0xBC, 0x40, 0x25, 0xBA, 0x81, 0x8C, 0x75, 0x70, 0x23, 0x34, 0x38,
            0x4E, 0x8F, 0x69, 0x6F, 0x80, 0x4D, 0x7A, 0xA0, 0xE7, 0x76, 0x4E, 0x50, 0x7B, 0xB7, 0xD3, 0xDF,
            0xEF, 0xC7, 0xD6, 0x78, 0xC6, 0x68, 0x2D, 0x3F, 0xAD, 0x71, 0x34, 0x41, 0xBE, 0xEA, 0xE7, 0x24,
            0xA0, 0x9E, 0xC0, 0x9B, 0xDC, 0x3B, 0xC0, 0x70, 0x9C, 0x91, 0x33, 0xD4, 0x89, 0xEC, 0xE2, 0xA5,
            0x1A, 0xDD, 0x05, 0x31, 0x27, 0x49, 0x0F, 0x92, 0x86, 0xD1, 0x73, 0xC8, 0xA4, 0x05, 0x4D, 0xC2,
            0x0A, 0x57, 0x5C, 0x7E, 0x4C, 0x0C, 0x98, 0x34, 0xF4, 0xA1, 0xDE, 0x87, 0x49, 0x17, 0xA3, 0xE4,
            0x00, 0xEA, 0xF8, 0x85, 0x06, 0x2D, 0xB5, 0xCB, 0x7E, 0x34, 0x36, 0x89, 0xE7, 0x11, 0xF7, 0x5F,
            0xE7, 0x83, 0xD7, 0xE1, 0x91, 0x92, 0xFD, 0x76, 0x9C, 0xD5, 0x42, 0xBE, 0xA4, 0xB9, 0x01, 0x07,
            0xEC, 0xD1, 0x02, 0x81, 0x80, 0x7F, 0x40, 0x18, 0xDC, 0x7D, 0xEA, 0x29, 0x2D, 0xA5, 0x30, 0x42,
            0x38, 0x6F, 0x31, 0x05, 0xA0, 0x77, 0x8A, 0xDC, 0x6F, 0x3D, 0xE6, 0x90, 0xDA, 0x2B, 0x74, 0xC5,
            0x05, 0x59, 0x83, 0xED, 0xF5, 0x74, 0x66, 0x1A, 0x2F, 0xD7, 0xB7, 0xDE, 0x80, 0x53, 0xCC, 0xC0,
            0xE2, 0x08, 0xF0, 0xC8, 0xAC, 0x62, 0x6F, 0x59, 0x7D, 0x3D, 0x99, 0xD2, 0xCE, 0x51, 0xA3, 0x7B,
            0x39, 0xAE, 0x4B, 0x7E, 0x9E, 0xF2, 0xC0, 0x75, 0xF0, 0xBF, 0x3D, 0x83, 0xCA, 0xCD, 0x32, 0xDA,
            0x96, 0x91, 0x92, 0xC2, 0x89, 0x92, 0x35, 0x82, 0x5C, 0x07, 0xD1, 0xCD, 0x32, 0x59, 0xA1, 0x90,
            0x6C, 0xDC, 0xD4, 0x99, 0xCB, 0x61, 0x3E, 0x22, 0xC9, 0x4C, 0xB1, 0xEA, 0x97, 0x19, 0x06, 0x60,
            0x9D, 0xF1, 0xB0, 0xF4, 0x8B, 0x06, 0x3F, 0x17, 0x37, 0x20, 0x34, 0x36, 0x94, 0x99, 0xB5, 0xFD,
            0xF9, 0x70, 0xEF, 0x44, 0x0D, 0x02, 0x81, 0x81, 0x00, 0x90, 0x4E, 0xE9, 0x20, 0xF9, 0x44, 0xEF,
            0x5A, 0xAF, 0x7C, 0x94, 0x20, 0xA0, 0x0F, 0x5E, 0x9B, 0x48, 0x08, 0x2C, 0x0B, 0x84, 0xE0, 0xFB,
            0xB5, 0xDD, 0xA2, 0xA2, 0x26, 0x77, 0xDF, 0xB7, 0xB8, 0x48, 0x8D, 0xB2, 0xBE, 0xE6, 0x4C, 0x9B,
            0xDD, 0x3C, 0xAC, 0x66, 0xFA, 0x32, 0x0E, 0x76, 0xF7, 0x1C, 0xE2, 0xAF, 0x22, 0x72, 0xBB, 0xBD,
            0x76, 0xCA, 0xB9, 0x4E, 0x08, 0x4A, 0x0C, 0x41, 0xD9, 0xB0, 0x77, 0x1D, 0xC6, 0x33, 0x40, 0xC1,
            0xAC, 0xCF, 0x5A, 0x89, 0xDA, 0x01, 0xB4, 0x37, 0x98, 0x6F, 0x26, 0x9C, 0xF0, 0xC2, 0x16, 0xE1,
            0x5E, 0xA1, 0x4A, 0x03, 0x8C, 0xDA, 0x69, 0x2A, 0xF0, 0xEB, 0x6D, 0xB0, 0x0E, 0x78, 0x80, 0x2B,
            0x93, 0x25, 0x20, 0x4D, 0x2D, 0x20, 0x02, 0x8A, 0x3F, 0x8C, 0xB1, 0x34, 0x68, 0xE8, 0x0F, 0x64,
            0x18, 0x8E, 0x10, 0x46, 0xBA, 0x1B, 0xE4, 0x58, 0xA6, 0x97, 0x4F, 0x26
    };

//#warning NOTE: there is currently a problem with rand and PREDICT has been enabled in md_rand to temporarily overcome this

    const unsigned char *keypp = key_private;
    EVP_PKEY *key = d2i_AutoPrivateKey(0, &keypp, sizeof(key_private));

    if (key != nullptr)
        iRsa = EVP_PKEY_get1_RSA(key);
    else
    {
        THROW(HttpError);
    }
    EVP_PKEY_free(key);
}

RaopDiscoverySession::~RaopDiscoverySession()
{
    iDeactivateTimer->Cancel();     // reset timeout
    iReaderRequest->Interrupt();    // terminate run()
    Interrupt(true);
    iShutdownSem.Wait();
    delete iDeactivateTimer;
    delete iWriterResponse;
    delete iWriterRequest;
    delete iReaderRequest;
    delete iWriterAscii;
    delete iWriterBuffer;
    delete iReaderProtocol;
    delete iReaderUntil;
    delete iReaderBuffer;
}

TBool RaopDiscoverySession::Active()
{
    return iActive;
}

void RaopDiscoverySession::Run()
{
    LOG(kMedia, "RaopDiscoverySession::Run %u\n", iInstance);
    iActive = false;
    iAeskeyPresent = false;
    iShutdownSem.Wait();

    LOG(kMedia, "RaopDiscoverySession::Run - Started %u\n", iInstance);
    try {
        for (;;) {
            try {
                iReaderRequest->Read();

                KeepAlive();

                const Brx& method = iReaderRequest->Method();
                LOG(kMedia, "RaopDiscoverySession::Run %u - Read Method %.*s\n", iInstance, PBUF(method));
                if(method == RtspMethod::kPost) {
                    Brn data = iReaderProtocol->Read(iHeaderContentLength.ContentLength());

                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    iWriterResponse->WriteHeader(RtspHeader::kContentType, Brn("application/octet-stream"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    WriteFply(data);
                    iWriterResponse->WriteFlush();
                }
                if(method == RtspMethod::kOptions) {
                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    if(iHeaderAppleChallenge.Received()) {
                        GenerateAppleResponse(iHeaderAppleChallenge.Challenge());   //encrypt challenge using rsa private key
                        iWriterResponse->WriteHeaderBase64(Brn("Apple-Response"), iResponse);
                        iHeaderAppleChallenge.Reset();
                    }
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteHeader(RtspHeader::kPublic, Brn("ANNOUNCE, SETUP, RECORD, PAUSE, FLUSH, TEARDOWN, OPTIONS, GET_PARAMETER, SET_PARAMETER"));
                    iWriterResponse->WriteFlush();
                }
                else if(method == RtspMethod::kAnnounce) {
                    LOG(kMedia, "RaopDiscoverySession::Run kAnnounce %u, iActive: %u\n", iInstance, iActive);
                    if(!iActive && iDiscovery.Active()) { /*i.e. the other connection is active */
                        /* if already actively connected to another device respond with:
                        RTSP/1.0 453 Not Enough Bandwidth
                        Server: AirTunes/102.2
                        CSeq: 1
                        */
                        LOG(kMedia, "RaopDiscoverySession::Run %u. Reject second connection\n", iInstance);
                        iWriterResponse->WriteStatus(RtspStatus::kNotEnoughBandwidth, Http::eRtsp10);
                        iWriterResponse->WriteHeader(Brn("Server"), Brn("AirTunes/102.2"));
                        WriteSeq(1);
                    }
                    else {
                        iDiscovery.Deactivate();     // deactivate both streams (effectively the other one!)
                        iActive = true;     // don't allow second stream to connect
                        LOG(kMedia, "RaopDiscoverySession::Run %u kAnnounce\n", iInstance);
                        ReadSdp(iSdpInfo); //get encoded aes key
                        DecryptAeskey();
                        iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                        iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                        WriteSeq(iHeaderCSeq.CSeq());
                        if(iHeaderAppleChallenge.Received()) {
                            GenerateAppleResponse(iHeaderAppleChallenge.Challenge());   //encrypt challenge using rsa private key
                            iWriterResponse->WriteHeaderBase64(Brn("Apple-Response"), iResponse);
                            iHeaderAppleChallenge.Reset();
                            LOG(kMedia, "RaopDiscoverySession::Run %u. Challenge response\n", iInstance);
                        }
                    }
                    iWriterResponse->WriteFlush();
                }
                else if(method == RtspMethod::kSetup) {
                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteHeader(RtspHeader::kSession, Brn("1"));

                    // get transport info, which gives us UDP ports of Airplay client for control and timing
                    iClientControlPort = iHeaderRtspTransport.ControlPort();
                    iClientTimingPort = iHeaderRtspTransport.TimingPort();

                    Brn prefix("RTP/AVP/UDP;unicast;mode=record");
                    Brn audioPortStr(";server_port=");
                    Brn controlPortStr(";control_port=");
                    Brn timingPortStr(";timing_port=");

                    const TUint portNumBytes = 3* kMaxPortNumBytes; // no. ports * max bytes req'd to represent port string
                    Bwh transResponse(prefix.Bytes() + audioPortStr.Bytes() + controlPortStr.Bytes() + timingPortStr.Bytes() + portNumBytes);
                    transResponse.Append(prefix);
                    transResponse.Append(audioPortStr);
                    Ascii::AppendDec(transResponse, iAudioPort);
                    transResponse.Append(controlPortStr);
                    Ascii::AppendDec(transResponse, iControlPort);
                    transResponse.Append(timingPortStr);
                    Ascii::AppendDec(transResponse, iTimingPort);

                    ASSERT(iAudioPort != 0 && iControlPort != 0 && iTimingPort != 0); // make sure ports have been set
                    iWriterResponse->WriteHeader(Brn("Transport"), transResponse);
                    iWriterResponse->WriteFlush();
                }
                else if(method == RtspMethod::kRecord) {
                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    //Log::Print("RtspMethod::kRecord seq: %u, rtptime: %u\n", iHeaderRtpInfo.Seq(), iHeaderRtpInfo.RtpTime());
                    //iWriterResponse.WriteHeader(Brn("Audio-Latency"), Brn("15409"));  // has no effect on iTunes
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteFlush();

                    // activate RAOP source
                    iDiscovery.NotifySessionStart(iClientControlPort, iClientTimingPort);
                    LOG(kMedia, "RaopDiscoverySession::Run %u. Playing\n", iInstance);
                }
                else if(method == RtspMethod::kSetParameter) {
                    if(iHeaderContentType.Type() == Brn("text/parameters")) {
                        Brn data = iReaderProtocol->Read(iHeaderContentLength.ContentLength());
                        Parser parser(data);
                        Brn entry = parser.Next(':');
                        if(entry == Brn("volume")) {
                            TInt vol = 0;
                            try {
                                Brn remaining = parser.Remaining();

                                // volume range is -30 to 0, < -30 == mute
                                // get int part plus first digit after dp

                                TBool validVolString = false;
                                Bws<Ascii::kMaxIntStringBytes> volBuf;
                                Brn integerPart = parser.Next('.');
                                Brn fractionalPart = parser.Remaining();

                                // Get the integer and fractional parts into a
                                // string.
                                const TUint intBytes = integerPart.Bytes();
                                if (intBytes > 0 && intBytes <= volBuf.MaxBytes()) {
                                    volBuf.Replace(integerPart);

                                    // Integer part was okay. Now try append
                                    // first digit from fractional part.
                                    const TUint capacity = volBuf.MaxBytes()-volBuf.Bytes();
                                    if (fractionalPart.Bytes() > 0 && capacity >= 1) {
                                        volBuf.Append(fractionalPart[0]);
                                        validVolString = true;
                                    }
                                }

                                if (validVolString) {
                                    vol = Ascii::Int(volBuf);

                                    // convert to logorithmic scale to give even volume steps
                                    vol = -vol;         // range 300 to 0
                                    if (vol > 300) {
                                        vol = 300;      // muted
                                    }
                                    vol = 300 - vol;    // 300 = max
                                    double dvol = log10(((double)vol+1.0)/301.0);
                                    double dvol2 = 1000.0 + dvol * 600.0;           //convert to 0-1000 range and bias to match Volkano1
                                    vol = (TInt)dvol2;
                                    if (vol < 0) {
                                        vol = 0;        // muted
                                    }
                                    //Log::Print("dvol %f, dvol2 %f, vol %d\n", dvol, dvol2, vol);
                                    iVolume.SetVolume(vol);
                                }
                                else {
                                    LOG(kMedia, "RaopDiscoverySession::Run %u. Invalid volume string encountered: %.*s\n", iInstance, PBUF(remaining));
                                }
                            }
                            catch (AsciiError&) {
                                // Couldn't parse volume. Ignore it.
                                LOG(kMedia, "RaopDiscoverySession::Run %u. AsciiError while parsing volume\n", iInstance);
                            }
                            catch (RaopVolumeInvalid&) {
                                // Invalid volume passed in.
                                LOG(kMedia, "RaopDiscoverySession::Run %u/ RaopVolumeInvalid %d\n", iInstance, vol);
                            }
                        }
                    }
                    else {
                        // need to purge non text data...  may be bitmap
                        TUint bytes = iHeaderContentLength.ContentLength();
                        while (bytes > 0) {
                            Brn buf = iReaderUntil->Read(bytes);
                            bytes -= buf.Bytes();
                        }
                    }

                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteFlush();
                }
                else if(method == RtspMethod::kFlush) {
                    const TUint seq = iHeaderRtpInfo.Seq();
                    const TUint rtpTime = iHeaderRtpInfo.RtpTime();
                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteFlush();
                    iDiscovery.NotifySessionWait(seq, rtpTime);
                }
                else if(method == RtspMethod::kTeardown) {
                    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eRtsp10);
                    iWriterResponse->WriteHeader(Brn("Audio-Jack-Status"), Brn("connected; type=analog"));
                    WriteSeq(iHeaderCSeq.CSeq());
                    iWriterResponse->WriteFlush();
                    Deactivate();
                    //iDiscovery.NotifySessionEnd();    // Happens in Deactivate() call above.
                    LOG(kMedia, "RaopDiscoverySession::Run %u. kTeardown\n", iInstance);
                    break;
                }
            }
            catch (HttpError&) {
                LOG(kMedia, "RaopDiscoverySession::Run %u. HttpError\n", iInstance);
            }
        }
    }
    catch (ReaderError&) {   // closed by client
        LOG(kMedia, "RaopDiscoverySession::Run %u. ReaderError\n", iInstance);
    }
    catch (WriterError&) {   // closed by client
        LOG(kMedia, "RaopDiscoverySession::Run %u. WriterError\n", iInstance);
    }

    iShutdownSem.Signal();
    LOG(kMedia, "RaopDiscoverySession::Run %u. Exit iActive: %u\n", iInstance, iActive);
}

void RaopDiscoverySession::Close()
{
    LOG(kMedia, "RaopDiscoverySession::Close iActive = %d, instance %d\n", iActive, iInstance);
    // Set timeout and deactivate on expiry.
    KeepAlive();
}

void RaopDiscoverySession::SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming)
{
    iAudioPort = aAudio;
    iControlPort = aControl;
    iTimingPort = aTiming;
}

void RaopDiscoverySession::KeepAlive()
{
    if (iActive) {
        iDeactivateTimer->FireIn(10000);  // 10s timeout - deactivate if no data received
    }
}

void RaopDiscoverySession::DeactivateCallback()
{
    LOG(kMedia, "RaopDiscoverySession::DeactivateCallback %u\n", iInstance);
    Deactivate();
    iReaderRequest->Interrupt();    // terminate run()
}

void RaopDiscoverySession::Deactivate()
{
    LOG(kMedia, "RaopDiscoverySession::Deactivate %u, iActive: %u\n", iInstance, iActive);
    iDeactivateTimer->Cancel();     // reset timeout
    iActive = false;
    iDiscovery.NotifySessionEnd();  // Notify observers that session has timed-out (ended).
}


//encrypt challenge using rsa private key
void RaopDiscoverySession::GenerateAppleResponse(const Brx& aChallenge)
{
    GetRsa();

    unsigned char response[256];
    iResponse.SetBytes(0);

    unsigned char challenge[32];
    TUint i = 16;               // challenge is always 16 bytes
    memcpy(&challenge[0], aChallenge.Ptr(), i);

    TByte ip[4];
    iRaopDevice.GetEndpoint().GetAddressOctets(ip);
    // append ip address (must be actual IP address of device)
    for (TUint j=0; j<sizeof(ip); j++) {
        challenge[i++] = ip[j];
    }

    TByte mac[6];
    iRaopDevice.MacAddressOctets(mac);
    // append mac address (must be same as used in device name before @ symbol, but does not have to relate to device)
    for (TUint j=0; j<sizeof(mac); j++) {
        challenge[i++] = mac[j];
    }

    for (TUint j=0; j<6; j++) {     // shairport zero pads up to 32 bytes
        challenge[i++] = 0;
    }

    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<400> buf("challenge:");
        for (TUint i = 0; i < 32; i++) {
            if (i % 16 == 0) {
                buf.Append("\n    ");
            }
            if (i == 31) {
                buf.AppendPrintf("%02x\n", challenge[i]);
            }
            else {
                buf.AppendPrintf("%02x, ", challenge[i]);
            }
        }
        LOG(kMedia, "%.*s\n", PBUF(buf));
    }

    TInt res = RSA_private_encrypt(32, challenge, response, iRsa, RSA_PKCS1_PADDING);

    if (Debug::TestLevel(Debug::kMedia)) {
        Bws<1280> buf("encrypted response");
        buf.AppendPrintf(" %d:", res);
        for (TInt i = 0; i < res; i++) {
            if (i % 16 == 0) {
                buf.Append("\n    ");
            }
            if (i == res-1) {
                buf.AppendPrintf("%02x\n", response[i]);
            }
            else {
                buf.AppendPrintf("%02x, ", response[i]);
            }
        }
        LOG(kMedia, "%.*s\n", PBUF(buf));
    }

    if(res > 0) {
        iResponse.Replace(response, res);

        unsigned char decrypted[256];
        GetRsa();
        res = RSA_public_decrypt(256, response, decrypted, iRsa, RSA_PKCS1_PADDING);
        if (Debug::TestLevel(Debug::kMedia)) {
            Bws<400> buf("decrypted response %d:%d:");
        }

        if (Debug::TestLevel(Debug::kMedia)) {
            Bws<1280> buf("decrypted response");
            buf.AppendPrintf(" %d:", res);
            for (TInt i = 0; i < res; i++) {
                if (i % 16 == 0) {
                    buf.Append("\n    ");
                }
                if (i == res-1) {
                    buf.AppendPrintf("%02x\n", decrypted[i]);
                }
                else {
                    buf.AppendPrintf("%02x, ", decrypted[i]);
                }
            }
            LOG(kMedia, "%.*s\n", PBUF(buf));
        }
    }
}

void RaopDiscoverySession::DecryptAeskey()
{
    GetRsa();

    Brn rsaaeskey(iSdpInfo.Rsaaeskey());
    unsigned char aeskey[128];
    TInt res = RSA_private_decrypt(rsaaeskey.Bytes(), rsaaeskey.Ptr(), aeskey, iRsa, RSA_PKCS1_OAEP_PADDING);
    if(res > 0) {
        AES_KEY key;
        AES_set_decrypt_key(aeskey, 128, &key);
        iAeskey.Replace((const TByte* )&key, sizeof(AES_KEY));
        iAeskeyPresent = true;
        iAesSid++;
    }
}

TUint RaopDiscoverySession::AesSid()
{
    return iAesSid;
}

const Brx &RaopDiscoverySession::Aeskey()
{
    if(!iAeskeyPresent) {
        THROW(RaopError);
    }
    return iAeskey;
}

const Brx &RaopDiscoverySession::Aesiv()
{
    if(!iAeskeyPresent) {
        THROW(RaopError);
    }
    return iSdpInfo.Aesiv();
}

const Brx &RaopDiscoverySession::Fmtp()
{
    if(!iAeskeyPresent) {
        THROW(RaopError);
    }
    return iSdpInfo.Fmtp();
}

void RaopDiscoverySession::ReadSdp(ISdpHandler& aSdpHandler)
{
    aSdpHandler.Reset();
    Brn line;
    TUint remaining = iHeaderContentLength.ContentLength();
    while (remaining > 0) {
        line.Set(iReaderUntil->ReadUntil(Ascii::kLf));

        LOG(kHttp, "SDP: %.*s\n", PBUF(line));

        remaining -= line.Bytes() + 1;
        Parser parser(line);
        Brn type = parser.Next('=');
        Brn value = Ascii::Trim(parser.Remaining());
        if (type.Bytes() == 1) {
            aSdpHandler.Decode(type[0], value);
        }
    }
}


// RaopDiscoveryServer

const TChar* RaopDiscoveryServer::kAdapterCookie = "RaopDiscoveryServer";

RaopDiscoveryServer::RaopDiscoveryServer(Environment& aEnv, Net::DvStack& aDvStack, NetworkAdapter& aNif, IFriendlyNameObservable& aFriendlyNameObservable, const Brx& aMacAddr, IVolume& aVolume)
    : iEnv(aEnv)
    , iAdapter(aNif)
    , iObserversLock("RDOL")
{
    // NOTE: iRaopDevice is not registered by default
    iAdapter.AddRef(kAdapterCookie);

    iRaopDiscoveryServer = new SocketTcpServer(iEnv, "MDNS", 0, iAdapter.Address(), kPriority, kSessionStackBytes);
    iRaopDevice = new RaopDevice(aDvStack, iRaopDiscoveryServer->Port(), aFriendlyNameObservable, iAdapter.Address(), aMacAddr);

    // Require 2 discovery sessions to run to allow a second to attempt to connect and be rejected rather than hanging.
    TUint nextSessionId = 1;
    iRaopDiscoverySession1 = new RaopDiscoverySession(iEnv, *this, *iRaopDevice, nextSessionId++, aVolume);
    iRaopDiscoveryServer->Add("RaopDiscovery1", iRaopDiscoverySession1);

    iRaopDiscoverySession2 = new RaopDiscoverySession(iEnv, *this, *iRaopDevice, nextSessionId++, aVolume);
    iRaopDiscoveryServer->Add("RaopDiscovery2", iRaopDiscoverySession2);

    TIpAddress ipAddr = iAdapter.Address();
    Endpoint::AddressBuf addrBuf;
    Endpoint ep(iRaopDiscoveryServer->Port(), ipAddr);
    ep.AppendAddress(addrBuf);
    LOG(kMedia, "RaopDiscoveryServer::RaopDiscoveryServer using network adapter %s\n", addrBuf.Ptr());
}

RaopDiscoveryServer::~RaopDiscoveryServer()
{
    iRaopDevice->Deregister();
    delete iRaopDiscoveryServer;    // Deletes iRaopDiscoverySessionX, which deactivates itself in destructor.
    delete iRaopDevice;
    iAdapter.RemoveRef(kAdapterCookie);
}

const NetworkAdapter& RaopDiscoveryServer::Adapter() const
{
    return iAdapter;
}

void RaopDiscoveryServer::AddObserver(IRaopServerObserver& aObserver)
{
    AutoMutex a(iObserversLock);
    iObservers.push_back(&aObserver);
}

void RaopDiscoveryServer::PowerDown()
{
    // called on power failure
    iRaopDevice->Deregister();
}

void RaopDiscoveryServer::NotifySessionStart(TUint aControlPort, TUint aTimingPort)
{
    AutoMutex a(iObserversLock);
    std::vector<IRaopServerObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionStart(iAdapter, aControlPort, aTimingPort);
        ++it;
    }
}

void RaopDiscoveryServer::NotifySessionEnd()
{
    AutoMutex a(iObserversLock);
    std::vector<IRaopServerObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionEnd(iAdapter);
        ++it;
    }
}

void RaopDiscoveryServer::NotifySessionWait(TUint aSeq, TUint aTime)
{
    AutoMutex a(iObserversLock);
    std::vector<IRaopServerObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionWait(iAdapter, aSeq, aTime);
        ++it;
    }
}

const Brx& RaopDiscoveryServer::Aeskey()
{
    return ActiveSession().Aeskey();
}

const Brx& RaopDiscoveryServer::Aesiv()
{
    return ActiveSession().Aesiv();
}

const Brx& RaopDiscoveryServer::Fmtp()
{
    return ActiveSession().Fmtp();
}

TBool RaopDiscoveryServer::Active()
{
    return (iRaopDiscoverySession1->Active() || iRaopDiscoverySession2->Active());
}

void RaopDiscoveryServer::Deactivate()
{
    LOG(kMedia, "RaopDiscoveryServer::Deactivate\n");
    // Deactivate RAOP source.
    iRaopDiscoverySession1->Deactivate();
    iRaopDiscoverySession2->Deactivate();
}

void RaopDiscoveryServer::Enable()
{
    iRaopDevice->Register();
}

void RaopDiscoveryServer::Disable()
{
    iRaopDevice->Deregister();
}

void RaopDiscoveryServer::KeepAlive()
{
    ActiveSession().KeepAlive();
}

TUint RaopDiscoveryServer::AesSid()
{
    return ActiveSession().AesSid();
}

void RaopDiscoveryServer::Close()
{
    LOG(kMedia, "RaopDiscoveryServer::Close\n");
    iRaopDiscoverySession1->Close();
    iRaopDiscoverySession2->Close();
}

void RaopDiscoveryServer::SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming)
{
    iRaopDiscoverySession1->SetListeningPorts(aAudio, aControl, aTiming);
    iRaopDiscoverySession2->SetListeningPorts(aAudio, aControl, aTiming);
}

RaopDiscoverySession& RaopDiscoveryServer::ActiveSession()
{
    if (iRaopDiscoverySession1->Active()) {
        return *iRaopDiscoverySession1;
    }
    else if (iRaopDiscoverySession2->Active()) {
        return *iRaopDiscoverySession2;
    }
    else {
        THROW(RaopError);
    }
}


// RaopDiscovery
RaopDiscovery::RaopDiscovery(Environment& aEnv, Net::DvStack& aDvStack, IPowerManager& aPowerManager, IFriendlyNameObservable& aFriendlyNameObservable, const Brx& aMacAddr, IVolumeReporter& aVolumeReporter, IVolumeSourceOffset& aVolumeOffset, TUint aVolumeMaxMilliDb)
    : iEnv(aEnv)
    , iDvStack(aDvStack)
    , iFriendlyNameObservable(aFriendlyNameObservable)
    , iMacAddr(aMacAddr)
    , iCurrent(nullptr)
    , iServersLock("RDSL")
    , iObserversLock("RDOL")
    , iVolume(aVolumeReporter, aVolumeOffset, aVolumeMaxMilliDb, kVolMaxScaled)
{
    // NOTE: iRaopDevice is not registered by default
    iPowerObserver = aPowerManager.RegisterPowerHandler(*this, kPowerPriorityLowest);
}

RaopDiscovery::~RaopDiscovery()
{
    delete iPowerObserver;

    AutoMutex a(iServersLock);
    iEnv.NetworkAdapterList().RemoveCurrentChangeListener(iCurrentAdapterChangeListenerId);
    iEnv.NetworkAdapterList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);

    std::vector<RaopDiscoveryServer*>::iterator it = iServers.begin();
    while (it != iServers.end()) {
        (*it)->Disable();
        delete (*it);
        ++it;
    }
}

void RaopDiscovery::AddObserver(IRaopObserver& aObserver)
{
    AutoMutex a(iObserversLock);
    iObservers.push_back(&aObserver);
}

TBool RaopDiscovery::Active()
{
    // If switching adapters while playing a track, this call may come in before
    // one of the newly-created sessions has been set active (iCurrent == nullptr).
    // So, return false in that case, as neither session is active.
    if (iCurrent != nullptr) {
        return iCurrent->Active();
    }
    return false;
}

TUint RaopDiscovery::AesSid()
{
    if (iCurrent == nullptr) {
        THROW(RaopError);
    }
    return iCurrent->AesSid();
}

const Brx& RaopDiscovery::Aeskey()
{
    if (iCurrent == nullptr) {
        THROW(RaopError);
    }
    return iCurrent->Aeskey();
}

const Brx& RaopDiscovery::Aesiv()
{
    if (iCurrent == nullptr) {
        THROW(RaopError);
    }
    return iCurrent->Aesiv();
}

const Brx& RaopDiscovery::Fmtp()
{
    if (iCurrent == nullptr) {
        THROW(RaopError);
    }
    return iCurrent->Fmtp();
}

void RaopDiscovery::KeepAlive()
{
    if (iCurrent == nullptr) {
        THROW(RaopError);
    }
    return iCurrent->KeepAlive();
}

void RaopDiscovery::Close()
{
    // Deactivate all servers, rather than just currently selected.
    AutoMutex a(iServersLock);
    std::vector<RaopDiscoveryServer*>::iterator it = iServers.begin();
    while (it != iServers.end()) {
        (*it)->Close();
        ++it;
    }
}

void RaopDiscovery::SetListeningPorts(TUint aAudio, TUint aControl, TUint aTiming)
{
    AutoMutex a(iServersLock);
    std::vector<RaopDiscoveryServer*>::iterator it = iServers.begin();
    while (it != iServers.end()) {
        (*it)->SetListeningPorts(aAudio, aControl, aTiming);
        ++it;
    }
}

void RaopDiscovery::NotifySessionStart(const NetworkAdapter& aNif, TUint aControlPort, TUint aTimingPort)
{
    AutoMutex mutexServers(iServersLock);
    AutoMutex mutexObservers(iObserversLock);
    if (iCurrent == nullptr || !NifsMatch(aNif, iCurrent->Adapter())) {
        // No server previously selected, or previously connected on different interface.
        // Find selected server and set it as iCurrent.
        std::vector<RaopDiscoveryServer*>::iterator it = iServers.begin();
        while (it != iServers.end()) {
            const NetworkAdapter& nif = (*it)->Adapter();
            if (NifsMatch(nif, aNif)) {
                iCurrent = (*it);
                break;
            }
            ++it;
        }

        // FIXME - should we also disable all other servers when one is
        // selected, and only re-enable on a subnet list/adapter change?

        ASSERT(it != iServers.end()); // NotifySessionStart should only come from a server owned by this.
    }
    std::vector<IRaopObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionStart(aControlPort, aTimingPort);
        ++it;
    }
}

void RaopDiscovery::NotifySessionEnd(const NetworkAdapter& /*aNif*/)
{
    AutoMutex mutexServers(iServersLock);
    AutoMutex mutexObservers(iObserversLock);
    //ASSERT((iCurrent == nullptr) || NifsMatch(aNif, iCurrent->Adapter()));
    iCurrent = nullptr;
    std::vector<IRaopObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionEnd();
        ++it;
    }
}

void RaopDiscovery::NotifySessionWait(const NetworkAdapter& /*aNif*/, TUint aSeq, TUint aTime)
{
    AutoMutex mutexServers(iServersLock);
    AutoMutex mutexObservers(iObserversLock);
    //ASSERT((iCurrent == nullptr) || NifsMatch(aNif, iCurrent->Adapter()));
    std::vector<IRaopObserver*>::iterator it = iObservers.begin();
    while (it != iObservers.end()) {
        (*it)->NotifySessionWait(aSeq, aTime);
        ++it;
    }
}

void RaopDiscovery::SetVolumeEnabled(TBool aEnabled)
{
    iVolume.SetVolumeEnabled(aEnabled);
}

void RaopDiscovery::PowerUp()
{
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    Functor functor = MakeFunctor(*this, &RaopDiscovery::HandleInterfaceChange);
    iCurrentAdapterChangeListenerId = nifList.AddCurrentChangeListener(functor, "RaopDiscovery-current");
    iSubnetListChangeListenerId = nifList.AddSubnetListChangeListener(functor, "RaopDiscovery-subnet");

    AutoNetworkAdapterRef ref(iEnv, "RaopDiscovery ctor");
    NetworkAdapter* current = ref.Adapter();

    iServersLock.Wait();
    if (current != nullptr) {
        // Single interface selected. Register only on this interface.
        AddAdapter(*current);
    }
    else {
        // No interface selected. Advertise on all interfaces.
        for (TUint i=0; i<subnetList->size(); i++) {
            NetworkAdapter* subnet = (*subnetList)[i];
            AddAdapter(*subnet);
        }
    }
    iServersLock.Signal();
    NetworkAdapterList::DestroySubnetList(subnetList);
}

void RaopDiscovery::PowerDown()
{
    AutoMutex a(iServersLock);
    std::vector<RaopDiscoveryServer*>::iterator it = iServers.begin();
    while (it != iServers.end()) {
        (*it)->PowerDown();
        ++it;
    }
}

void RaopDiscovery::HandleInterfaceChange()
{
    TBool currentRemoved = false;   // identify whether current active server
                                    // has been removed by interface change.
    NetworkAdapterList& nifList = iEnv.NetworkAdapterList();
    std::vector<NetworkAdapter*>* subnetList = nifList.CreateSubnetList();
    AutoNetworkAdapterRef ref(iEnv, "RaopDiscovery::HandleInterfaceChange");
    NetworkAdapter* current = ref.Adapter();

    // When we detect an interface change:
    // - determine if a single interface is selected; if so:
    // -- remove all subnets not matching the current interface
    // -- if no subnets remain that match the current interface, add the current interface
    // - otherwise (there is no single interface selected, so):
    // -- remove all subnets that no longer exist
    // -- add new subnets

    iServersLock.Wait();
    if (current != nullptr) {
        // Single interface selected. Register only on this interface.

        // First, remove any other interfaces.
        TUint i = 0;
        while (i<iServers.size()) {
            const NetworkAdapter& adapter = iServers[i]->Adapter();
            if (!NifsMatch(adapter, *current)) {
                if ((iCurrent != nullptr) && NifsMatch(adapter, iCurrent->Adapter())) {
                    // Clear current server if its interface has been removed.
                    currentRemoved = true;
                    iCurrent = nullptr;
                }
                iServers[i]->Disable();
                delete iServers[i];
                iServers.erase(iServers.begin()+i);
            }
            else {
                i++;
            }
        }

        // If this interface isn't registered, add it.
        if (iServers.size() == 0) {
            AddAdapter(*current);
        }
    }
    else {
        // No interface selected. Advertise on all interfaces.

        // First, remove any subnets that have disappeared from the new subnet list.
        TUint i = 0;
        while (i<iServers.size()) {
            const NetworkAdapter& adapter = iServers[i]->Adapter();
            if (InterfaceIndex(adapter, *subnetList) == -1) {
                if ((iCurrent != nullptr) && NifsMatch(adapter, iCurrent->Adapter())) {
                    // Clear current server if its interface has been removed.
                    currentRemoved = true;
                    iCurrent = nullptr;
                }
                iServers[i]->Disable();
                delete iServers[i];
                iServers.erase(iServers.begin()+i);
            }
            else {
                i++;
            }
        }

        // Then, add any new interfaces.
        for (TUint j=0; j<subnetList->size(); j++) {
            NetworkAdapter* subnet = (*subnetList)[j];
            if (InterfaceIndex(*subnet) == -1) {
                AddAdapter(*subnet);
           }
        }
    }
    iServersLock.Signal();
    NetworkAdapterList::DestroySubnetList(subnetList);

    if (currentRemoved) {
         // If current active server has been removed, notify observers.
        iObserversLock.Wait();
        std::vector<IRaopObserver*>::iterator it = iObservers.begin();
        while (it != iObservers.end()) {
            (*it)->NotifySessionEnd();
            ++it;
        }
        iObserversLock.Signal();
    }
}

void RaopDiscovery::AddAdapter(NetworkAdapter& aNif)
{
    RaopDiscoveryServer* server = new RaopDiscoveryServer(iEnv, iDvStack, aNif, iFriendlyNameObservable, iMacAddr, iVolume);
    iServers.push_back(server);
    server->Enable();
    server->AddObserver(*this);
}

TInt RaopDiscovery::InterfaceIndex(const NetworkAdapter& aNif)
{
    for (TUint i=0; i<(TUint)iServers.size(); i++) {
        if (NifsMatch(iServers[i]->Adapter(), aNif)) {
            return i;
        }
    }
    return -1;
}

TInt RaopDiscovery::InterfaceIndex(const NetworkAdapter& aNif, const std::vector<NetworkAdapter*>& aList)
{
    for (TUint i=0; i<(TUint)aList.size(); i++) {
        if (NifsMatch(*(aList[i]), aNif)) {
            return i;
        }
    }
    return -1;
}

TBool RaopDiscovery::NifsMatch(const NetworkAdapter& aNif1, const NetworkAdapter& aNif2)
{
    if (aNif1.Address() == aNif2.Address() && aNif1.Subnet() == aNif2.Subnet() && strcmp(aNif1.Name(), aNif2.Name()) == 0) {
        return true;
    }
    return false;
}


// HeaderCSeq

TBool HeaderCSeq::Received() const
{
    return (iReceived);
}

TUint HeaderCSeq::CSeq() const
{
    return (iCSeq);
}

TBool HeaderCSeq::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, Brn("CSeq")));
}

void HeaderCSeq::Reset()
{
    iReceived = false;
}

void HeaderCSeq::Process(const Brx& aValue)
{
    if (aValue.Bytes() > kMaxCSeqBytes) {
        THROW(HttpError);
    }

    Parser parser(aValue);
    Brn cseq = parser.Remaining();
    iCSeq = Ascii::Uint(cseq);
    iReceived = true;
}


// HeaderAppleChallenge

TBool HeaderAppleChallenge::Received() const
{
    return (iReceived);
}

const Brx& HeaderAppleChallenge::Challenge() const
{
    return (iChallenge);
}

TBool HeaderAppleChallenge::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, Brn("Apple-Challenge")));
}

void HeaderAppleChallenge::Reset()
{
    iReceived = false;
}

void HeaderAppleChallenge::Process(const Brx& aValue)
{
    if (aValue.Bytes() > kMaxChallengeBytes) {
        THROW(HttpError);
    }

    Parser parser(aValue);
    Brn challengeb64 = parser.Remaining();
    iChallenge.Replace(challengeb64);
    Converter::FromBase64(iChallenge);
    iReceived = true;
}


// HeaderRtspTransport

const Brn HeaderRtspTransport::kControlPortStr("control_port");
const Brn HeaderRtspTransport::kTimingPortStr("timing_port");

TUint HeaderRtspTransport::ControlPort() const
{
    return iControlPort;
}

TUint HeaderRtspTransport::TimingPort() const
{
    return iTimingPort;
}

TBool HeaderRtspTransport::Recognise(const Brx& aHeader)
{
    return (Ascii::CaseInsensitiveEquals(aHeader, Brn("Transport")));
}

void HeaderRtspTransport::Reset()
{
    HttpHeader::Reset();
    iControlPort = 0;
    iTimingPort = 0;
}

TUint HeaderRtspTransport::ParsePort(Brx& aData)
{
    Parser parser(aData);
    parser.Next('=');
    Brn val = parser.Next();

    return Ascii::Uint(val);
}

void HeaderRtspTransport::Process(const Brx& aValue)
{
    Parser parser(aValue);
    for (TUint i=0; i<6; i++) {
        Brn entry;

        if (i < 5) {
            entry = parser.Next(';');
        }
        else {
            entry = parser.Next();
        }

        if (Ascii::Contains(entry, kControlPortStr)) {
            iControlPort = ParsePort(entry);
        }
        else if (Ascii::Contains(entry, kTimingPortStr)) {
            iTimingPort = ParsePort(entry);
        }
    }
}


// HeaderRtpInfo

const Brn HeaderRtpInfo::kSeqStr("seq");
const Brn HeaderRtpInfo::kRtpTimeStr("rtptime");

TUint HeaderRtpInfo::Seq() const
{
    return iSeq;
}

TUint HeaderRtpInfo::RtpTime() const
{
    return iRtpTime;
}

void HeaderRtpInfo::Reset()
{
    HttpHeader::Reset();
    iSeq = 0;
    iRtpTime = 0;
}

TBool HeaderRtpInfo::Recognise(const Brx& aHeader)
{
    return Ascii::CaseInsensitiveEquals(aHeader, Brn("RTP-Info"));
}

void HeaderRtpInfo::Process(const Brx& aValue)
{
    Parser parser(aValue);
    Brn entry;
    do {
        entry = parser.Next(';');
        if (Ascii::Contains(entry, kSeqStr)) {
            Brn val = ParameterValue(entry);
            iSeq = Ascii::Uint(val);
        }
        else if (Ascii::Contains(entry, kRtpTimeStr)) {
            Brn val = ParameterValue(entry);
            iRtpTime = Ascii::Uint(val);
        }
    } while (entry != Brx::Empty());
}

Brn HeaderRtpInfo::ParameterValue(Brx& aData)
{
    Parser parser(aData);
    parser.Next('=');
    Brn val = parser.Next();
    return val;
}
