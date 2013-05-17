#include <OpenHome/Av/UpnpAv/ProviderConnectionManager.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <Generated/DvUpnpOrgConnectionManager1.h>
#include <OpenHome/Private/Ascii.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

static const TUint kInvalidConnectionIdCode = 706;
static const Brn kInvalidConnectionIdMsg("Invalid connection reference");
static const Brn kDirectionInput("Input");
static const Brn kStatusUnknown("Unknown");

ProviderConnectionManager::ProviderConnectionManager(Net::DvDevice& aDevice, const TChar* aSinkProtocolInfo)
    : DvProviderUpnpOrgConnectionManager1(aDevice)
    , iSinkProtocolInfo(aSinkProtocolInfo)
{
    EnablePropertySourceProtocolInfo();
    EnablePropertySinkProtocolInfo();
    EnablePropertyCurrentConnectionIDs();

    EnableActionGetProtocolInfo();
    EnableActionGetCurrentConnectionIDs();
    EnableActionGetCurrentConnectionInfo();

    (void)SetPropertySourceProtocolInfo(Brx::Empty());
    (void)SetPropertySinkProtocolInfo(iSinkProtocolInfo);
    Bws<Ascii::kMaxIntStringBytes> connectionId;
    Ascii::AppendDec(connectionId, kConnectionId);
    (void)SetPropertyCurrentConnectionIDs(connectionId);
}

ProviderConnectionManager::~ProviderConnectionManager()
{
}

void ProviderConnectionManager::GetProtocolInfo(IDvInvocation& aInvocation, IDvInvocationResponseString& aSource, IDvInvocationResponseString& aSink)
{
    aInvocation.StartResponse();
    aSource.Write(Brx::Empty());
    aSource.WriteFlush();
    aSink.Write(iSinkProtocolInfo);
    aSink.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderConnectionManager::GetCurrentConnectionIDs(IDvInvocation& aInvocation, IDvInvocationResponseString& aConnectionIDs)
{
    aInvocation.StartResponse();
    Bws<Ascii::kMaxIntStringBytes> connectionId;
    Ascii::AppendDec(connectionId, kConnectionId);
    aConnectionIDs.Write(connectionId);
    aConnectionIDs.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderConnectionManager::GetCurrentConnectionInfo(IDvInvocation& aInvocation, TInt aConnectionID, IDvInvocationResponseInt& aRcsID,
                                                         IDvInvocationResponseInt& aAVTransportID, IDvInvocationResponseString& aProtocolInfo,
                                                         IDvInvocationResponseString& aPeerConnectionManager, IDvInvocationResponseInt& aPeerConnectionID,
                                                         IDvInvocationResponseString& aDirection, IDvInvocationResponseString& aStatus)
{
    if (aConnectionID != 0) {
        aInvocation.Error(kInvalidConnectionIdCode, kInvalidConnectionIdMsg);
    }
    aInvocation.StartResponse();
    aRcsID.Write(kConnectionId);
    aAVTransportID.Write(kConnectionId);
    aProtocolInfo.Write(iSinkProtocolInfo);
    aProtocolInfo.WriteFlush();
    aPeerConnectionManager.Write(Brx::Empty());
    aPeerConnectionManager.WriteFlush();
    aPeerConnectionID.Write(-1);
    aDirection.Write(kDirectionInput);
    aDirection.WriteFlush();
    aStatus.Write(kStatusUnknown);
    aStatus.WriteFlush();
    aInvocation.EndResponse();
}
