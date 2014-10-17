/**
 * Ssdp utilities which depend on the device stack
 * Placed in a separate file to encourage the linker to drop dv code for cp builds
 */

#include <OpenHome/Net/Private/Ssdp.h>
#include <OpenHome/Private/Http.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Stream.h>
#include <OpenHome/Net/Private/DviStack.h>
#include <OpenHome/Private/Env.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// Ssdp (fragments)

void Ssdp::WriteBootId(DvStack& aDvStack, IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderBootId);
    stream.WriteUint(aDvStack.BootId());
    stream.WriteFlush();
}

void Ssdp::WriteNextBootId(DvStack& aDvStack, IWriterHttpHeader& aWriter)
{
    IWriterAscii& stream = aWriter.WriteHeaderField(Ssdp::kHeaderNextBootId);
    stream.WriteUint(aDvStack.NextBootId());
    stream.WriteFlush();
}


// SsdpNotifier

SsdpNotifier::SsdpNotifier(DvStack& aDvStack)
    : iDvStack(aDvStack)
    , iSocket(aDvStack.Env())
    , iSocketWriter(iSocket, Endpoint(Ssdp::kMulticastPort, Ssdp::kMulticastAddress))
    , iBuffer(iSocketWriter)
    , iWriter(iBuffer)
    , iConfigId(0)
{
}

void SsdpNotifier::Start(TIpAddress aInterface, TUint aConfigId)
{
    iSocket.SetMulticastIf(aInterface);
    iSocket.ReBind(0, aInterface);
    iSocket.SetTtl(iDvStack.Env().InitParams()->MsearchTtl()); 
    iConfigId = aConfigId;
}

void SsdpNotifier::SsdpNotify(const Brx& aUri, ENotificationType aNotificationType)
{
    Ssdp::WriteMethodNotify(iWriter);
    Ssdp::WriteHost(iWriter);
    Ssdp::WriteBootId(iDvStack, iWriter);
    Ssdp::WriteConfigId(iWriter, iConfigId);
    switch (aNotificationType)
    {
    case EAlive:
        Ssdp::WriteServer(iDvStack.Env(), iWriter);
        Ssdp::WriteMaxAge(iDvStack.Env(), iWriter);
        Ssdp::WriteLocation(iWriter, aUri);
        Ssdp::WriteSubTypeAlive(iWriter);
        // !!!! Ssdp::WriteSearchPort(iWriter, ????);
        break;
    case EByeBye:
        Ssdp::WriteSubTypeByeBye(iWriter);
        break;
    case EUpdate:
        Ssdp::WriteNextBootId(iDvStack, iWriter);
        break;
    }
}

void SsdpNotifier::SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType)
{
    SsdpNotify(aUri, aNotificationType);
    Ssdp::WriteNotificationTypeRoot(iWriter);
    Ssdp::WriteUsnRoot(iWriter, aUuid);
    iWriter.WriteFlush();
}

void SsdpNotifier::SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType)
{
    SsdpNotify(aUri, aNotificationType);
    Ssdp::WriteNotificationTypeUuid(iWriter, aUuid);
    Ssdp::WriteUsnUuid(iWriter, aUuid);
    iWriter.WriteFlush();
}

void SsdpNotifier::SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType)
{
    SsdpNotify(aUri, aNotificationType);
    Ssdp::WriteNotificationTypeDeviceType(iWriter, aDomain, aType, aVersion);
    Ssdp::WriteUsnDeviceType(iWriter, aDomain, aType, aVersion, aUuid);
    iWriter.WriteFlush();
}

void SsdpNotifier::SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri, ENotificationType aNotificationType)
{
    SsdpNotify(aUri, aNotificationType);
    Ssdp::WriteNotificationTypeServiceType(iWriter, aDomain, aType, aVersion);
    Ssdp::WriteUsnServiceType(iWriter, aDomain, aType, aVersion, aUuid);
    iWriter.WriteFlush();
}


// SsdpNotifierAlive

SsdpNotifierAlive::SsdpNotifierAlive(SsdpNotifier& aNotifier)
    : iNotifier(aNotifier)
{
}

void SsdpNotifierAlive::SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyRoot(aUuid, aUri, SsdpNotifier::EAlive);
}

void SsdpNotifierAlive::SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyUuid(aUuid, aUri, SsdpNotifier::EAlive);
}

void SsdpNotifierAlive::SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyDeviceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EAlive);
}

void SsdpNotifierAlive::SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyServiceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EAlive);
}


// SsdpNotifierByeBye

SsdpNotifierByeBye::SsdpNotifierByeBye(SsdpNotifier& aNotifier)
    : iNotifier(aNotifier)
{
}

void SsdpNotifierByeBye::SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyRoot(aUuid, aUri, SsdpNotifier::EByeBye);
}

void SsdpNotifierByeBye::SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyUuid(aUuid, aUri, SsdpNotifier::EByeBye);
}

void SsdpNotifierByeBye::SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyDeviceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EByeBye);
}

void SsdpNotifierByeBye::SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyServiceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EByeBye);
}


// SsdpNotifierUpdate

SsdpNotifierUpdate::SsdpNotifierUpdate(SsdpNotifier& aNotifier)
    : iNotifier(aNotifier)
{
}

void SsdpNotifierUpdate::SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyRoot(aUuid, aUri, SsdpNotifier::EUpdate);
}

void SsdpNotifierUpdate::SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyUuid(aUuid, aUri, SsdpNotifier::EUpdate);
}

void SsdpNotifierUpdate::SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyDeviceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EUpdate);
}

void SsdpNotifierUpdate::SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    iNotifier.SsdpNotifyServiceType(aDomain, aType, aVersion, aUuid, aUri, SsdpNotifier::EUpdate);
}


// SsdpMsearchResponder

SsdpMsearchResponder::SsdpMsearchResponder(DvStack& aDvStack)
    : iDvStack(aDvStack)
    , iBuffer(iResponse)
    , iWriter(iBuffer)
    , iConfigId(0)
{
}

void SsdpMsearchResponder::SetRemote(const Endpoint& aEndpoint, TUint aConfigId, TIpAddress aAdapter)
{
    iRemote.Replace(aEndpoint);
    iConfigId = aConfigId;
    iAdapter = aAdapter;
}

void SsdpMsearchResponder::SsdpNotify(const Brx& aUri)
{
    iBuffer.Flush(); // clear any data left over from a previous failed notification
    Ssdp::WriteStatus(iWriter);
    Ssdp::WriteServer(iDvStack.Env(), iWriter);
    Ssdp::WriteMaxAge(iDvStack.Env(), iWriter);
    Ssdp::WriteExt(iWriter);
    Ssdp::WriteLocation(iWriter, aUri);
    Ssdp::WriteBootId(iDvStack, iWriter);
    Ssdp::WriteConfigId(iWriter, iConfigId);
    // !!!! Ssdp::WriteSearchPort(iWriter, ????);
}

void SsdpMsearchResponder::Flush()
{
    iWriter.WriteFlush();
    SocketUdp socket(iDvStack.Env(), 0, iAdapter);
    socket.Send(iResponse, iRemote);
    iBuffer.Flush();
}

void SsdpMsearchResponder::SsdpNotifyRoot(const Brx& aUuid, const Brx& aUri)
{
    SsdpNotify(aUri);
    Ssdp::WriteSearchTypeRoot(iWriter);
    Ssdp::WriteUsnRoot(iWriter, aUuid);
    Flush();
}

void SsdpMsearchResponder::SsdpNotifyUuid(const Brx& aUuid, const Brx& aUri)
{
    SsdpNotify(aUri);
    Ssdp::WriteSearchTypeUuid(iWriter, aUuid);
    Ssdp::WriteUsnUuid(iWriter, aUuid);
    Flush();
}

void SsdpMsearchResponder::SsdpNotifyDeviceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    SsdpNotify(aUri);
    Ssdp::WriteSearchTypeDeviceType(iWriter, aDomain, aType, aVersion);
    Ssdp::WriteUsnDeviceType(iWriter, aDomain, aType, aVersion, aUuid);
    Flush();
}

void SsdpMsearchResponder::SsdpNotifyServiceType(const Brx& aDomain, const Brx& aType, TUint aVersion, const Brx& aUuid, const Brx& aUri)
{
    SsdpNotify(aUri);
    Ssdp::WriteSearchTypeServiceType(iWriter, aDomain, aType, aVersion);
    Ssdp::WriteUsnServiceType(iWriter, aDomain, aType, aVersion, aUuid);
    Flush();
}
