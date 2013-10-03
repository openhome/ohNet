#include <OpenHome/Av/Songcast/ProviderReceiver.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Private/Thread.h>
#include <Generated/DvAvOpenhomeOrgReceiver1.h>
#include <OpenHome/Net/Core/DvInvocationResponse.h>

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

ProviderReceiver::ProviderReceiver(Net::DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgReceiver1(aDevice)
{
    EnablePropertyUri();
    EnablePropertyMetadata();
    EnablePropertyTransportState();
    EnablePropertyProtocolInfo();

    EnableActionPlay();
    EnableActionStop();
    EnableActionSetSender();
    EnableActionSender();
    EnableActionProtocolInfo();
    EnableActionTransportState();
}

void ProviderReceiver::Play(IDvInvocation& /*aInvocation*/)
{
}

void ProviderReceiver::Stop(IDvInvocation& /*aInvocation*/)
{
}

void ProviderReceiver::SetSender(IDvInvocation& /*aInvocation*/, const Brx& /*aUri*/, const Brx& /*aMetadata*/)
{
}

void ProviderReceiver::Sender(IDvInvocation& /*aInvocation*/, IDvInvocationResponseString& /*aUri*/, IDvInvocationResponseString& /*aMetadata*/)
{
}

void ProviderReceiver::ProtocolInfo(IDvInvocation& /*aInvocation*/, IDvInvocationResponseString& /*aValue*/)
{
}

void ProviderReceiver::TransportState(IDvInvocation& /*aInvocation*/, IDvInvocationResponseString& /*aValue*/)
{
}
