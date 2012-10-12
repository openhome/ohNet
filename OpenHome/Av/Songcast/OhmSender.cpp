#include "OhmSender.h"
#include <OpenHome/Net/Core/DvAvOpenhomeOrgSender1.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Arch.h>
#include <OpenHome/Private/Debug.h>

#include <stdio.h>

#ifdef _WIN32
# pragma warning(disable:4355) // use of 'this' in ctor lists safe in this case
#endif

namespace OpenHome {
namespace Av {

	class ProviderSender : public Net::DvProviderAvOpenhomeOrgSender1
	{
	    static const TUint kMaxMetadataBytes = 4096;
	    static const TUint kTimeoutAudioPresentMs = 1000;
	
	public:
	    ProviderSender(Net::DvDevice& aDevice);
	    
	    void SetMetadata(const Brx& aValue);
	    
	    void SetStatusEnabled();
	    void SetStatusDisabled();
        void SetStatusBlocked();
	    
	    void InformAudioPresent();
	    
	    ~ProviderSender() {}
	    
	private:
	    virtual void PresentationUrl(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
	    virtual void Metadata(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
	    virtual void Audio(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue);
	    virtual void Status(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
	    virtual void Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue);
	
	    void UpdateMetadata();
	    void TimerAudioPresentExpired();
	
	private:
	    Bws<kMaxMetadataBytes> iMetadata;
	    mutable Mutex iMutex;
	    Timer iTimerAudioPresent;
	};
} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::Av;

// ProviderSender

ProviderSender::ProviderSender(Net::DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgSender1(aDevice)
    , iMutex("PSND")
    , iTimerAudioPresent(MakeFunctor(*this, &ProviderSender::TimerAudioPresentExpired))
{
	EnablePropertyPresentationUrl();
	EnablePropertyMetadata();
	EnablePropertyAudio();
	EnablePropertyStatus();
	EnablePropertyAttributes();

	EnableActionPresentationUrl();
    EnableActionMetadata();
    EnableActionAudio();
    EnableActionStatus();
    EnableActionAttributes();
    
    SetPropertyPresentationUrl(Brx::Empty());
    SetPropertyMetadata(Brx::Empty());
    SetPropertyAudio(false);
    SetStatusDisabled();
    SetPropertyAttributes(Brx::Empty());
}

void ProviderSender::PresentationUrl(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyPresentationUrl(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Metadata(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyMetadata(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Audio(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseBool& aValue)
{
    TBool value;
    GetPropertyAudio(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aInvocation.EndResponse();
}

void ProviderSender::Status(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyStatus(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::Attributes(Net::IDvInvocation& aInvocation, Net::IDvInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyAttributes(value);
    aInvocation.StartResponse();
    aValue.Write(value);
    aValue.WriteFlush();
    aInvocation.EndResponse();
}

void ProviderSender::SetMetadata(const Brx& aValue)
{
	SetPropertyMetadata(aValue);
}

static const Brn kStatusEnabled("Enabled");
static const Brn kStatusDisabled("Disabled");
static const Brn kStatusBlocked("Blocked");

void ProviderSender::SetStatusEnabled()
{
    SetPropertyStatus(kStatusEnabled);
}

void ProviderSender::SetStatusDisabled()
{
    SetPropertyStatus(kStatusDisabled);
}

void ProviderSender::SetStatusBlocked()
{
    SetPropertyStatus(kStatusBlocked);
}

void ProviderSender::InformAudioPresent()
{
    SetPropertyAudio(true);
    iTimerAudioPresent.FireIn(kTimeoutAudioPresentMs);
}
    
void ProviderSender::TimerAudioPresentExpired()
{
    SetPropertyAudio(false);
}

// OhmSenderDriver

OhmSenderDriver::OhmSenderDriver()
    : iMutex("OHMD")
	, iEnabled(false)
    , iActive(false)
	, iSend(false)
    , iFrame(0)
    , iSamplesTotal(0)
    , iSampleStart(0)
	, iLatency(100)
	, iFactory(100, 10, 10)
{
}

void OhmSenderDriver::SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName)
{
    AutoMutex mutex(iMutex);

    iSampleRate = aSampleRate;
    iBitRate = aBitRate;
    iChannels = aChannels;
    iBitDepth = aBitDepth;
    iLossless = aLossless;
    iCodecName.Replace(aCodecName);
}

void OhmSenderDriver::SendAudio(const TByte* aData, TUint aBytes)
{
    AutoMutex mutex(iMutex);
    
    TUint samples = aBytes * 8 / iChannels / iBitDepth;

    if (!iSend) {
        iSampleStart += samples;
        return;
    }

	TUint multiplier = 48000 * 256;

	if ((iSampleRate % 441) == 0)
	{
		multiplier = 44100 * 256;
	}

	TUint latency = iLatency * multiplier / 1000;
    
	if (iFifoHistory.SlotsUsed() == kMaxHistoryFrames) {
		iFifoHistory.Read()->RemoveRef();
	}

	OhmMsgAudio& msg = iFactory.CreateAudio(
		false,  // halt
        iLossless,
		false,
		false,
        samples,
        iFrame,
		0, // network timestamp
		latency,
		0,
        iSampleStart,
        iSamplesTotal,
        iSampleRate,
        iBitRate,
        0, // volume offset
        iBitDepth,
        iChannels,
        iCodecName,
		Brn(aData, aBytes)
	);
    
	WriterBuffer writer(iBuffer);
	writer.Flush();
	msg.Externalise(writer);

	msg.SetResent(true);

	iFifoHistory.Write(&msg);

    try {
		iSocket.Send(iBuffer, iEndpoint);
    }
    catch (NetworkError&) {
    }
        
    iSampleStart += samples;

    iFrame++;
}

// IOhmSenderDriver

void OhmSenderDriver::SetEnabled(TBool aValue)
{
    AutoMutex mutex(iMutex);

	iEnabled = aValue;

	if (iSend) {
		if (!aValue) { // turning off
			ResetLocked();
		}
	}
	else {
		if (aValue && iActive) { // turning on
			iSend = true;
		}
	}
}

void OhmSenderDriver::SetActive(TBool aValue)
{
    AutoMutex mutex(iMutex);
	
	iActive = aValue;

	if (iSend) {
		if (!aValue) { // turning off
			ResetLocked();
		}
	}
	else {
		if (aValue && iEnabled) { // turning on
			iSend = true;
		}
	}
}

void OhmSenderDriver::SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter)
{
    AutoMutex mutex(iMutex);
    iEndpoint.Replace(aEndpoint);
	iAdapter = aAdapter;
}


void OhmSenderDriver::SetTtl(TUint aValue)
{
    AutoMutex mutex(iMutex);
    iSocket.SetTtl(aValue);
}

void OhmSenderDriver::SetLatency(TUint aValue)
{
    AutoMutex mutex(iMutex);
    iLatency = aValue;
}

void OhmSenderDriver::SetTrackPosition(TUint64 aSamplesTotal, TUint64 aSampleStart)
{
    AutoMutex mutex(iMutex);
    iSamplesTotal = aSamplesTotal;
    iSampleStart = aSampleStart;
}

void OhmSenderDriver::Resend(OhmMsgAudio& aMsg)
{
	WriterBuffer writer(iBuffer);

	writer.Flush();

	aMsg.Externalise(writer);

	try {
		iSocket.Send(iBuffer, iEndpoint);
	}
	catch (NetworkError&) {
	}

}

void OhmSenderDriver::Resend(const Brx& aFrames)
{
    AutoMutex mutex(iMutex);

	printf("RESEND");

	ReaderBuffer buffer(aFrames);
	ReaderBinary reader(buffer);

	TUint frames = aFrames.Bytes() / 4;

	TUint frame = reader.ReadUintBe(4);

	frames--;

	printf(" %d", frame);
	
	TBool found = false;

	TUint count = iFifoHistory.SlotsUsed();

	for (TUint i = 0; i < count; i++) {
		OhmMsgAudio* msg = iFifoHistory.Read();

		if (!found) {
			TInt diff = frame - msg->Frame();

			if (diff == 0) {
				Resend(*msg);
				if (frames-- > 0) {
					frame = reader.ReadUintBe(4);
				}
				else {
					found = true;
				}
			}
			else {
				while (diff < 0) {
					if (frames-- > 0) {
						frame = reader.ReadUintBe(4);
					}
					else {
						found = true;
						break;
					}

					diff = frame - msg->Frame();

					if (diff == 0) {
						Resend(*msg);

						if (frames-- > 0) {
							frame = reader.ReadUintBe(4);
						}
						else {
							found = true;
						}

						break;
					}
				}
			}
		}

		iFifoHistory.Write(msg);
	}

	printf("\n");
}

void OhmSenderDriver::ResetLocked()
{
	iSend = false;

	iFrame = 0;

	TUint count = iFifoHistory.SlotsUsed();

	for (TUint i = 0; i < count; i++) {
		iFifoHistory.Read()->RemoveRef();
	}
}

// OhmSender

OhmSender::OhmSender(Net::DvDevice& aDevice, IOhmSenderDriver& aDriver, const Brx& aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TUint aLatency, TBool aMulticast, TBool aEnabled, const Brx& aImage, const Brx& aMimeType, TUint aPreset)
    : iDevice(aDevice)
    , iDriver(aDriver)
    , iName(aName)
    , iChannel(aChannel)
    , iInterface(aInterface)
    , iTtl(aTtl)
	, iLatency(aLatency)
    , iMulticast(aMulticast)
	, iEnabled(false)
	, iImage(aImage)
	, iMimeType(aMimeType)
    , iRxBuffer(iSocketOhm)
	, iRxZone(iSocketOhz)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iMutexZone("OHMZ")
    , iNetworkDeactivated("OHDN", 0)
    , iZoneDeactivated("OHDZ", 0)
    , iStarted(false)
    , iActive(false)
    , iAliveJoined(false)
    , iAliveBlocked(false)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iTimerExpiry(MakeFunctor(*this, &OhmSender::TimerExpiryExpired))
    , iTimerZoneUri(MakeFunctor(*this, &OhmSender::TimerZoneUriExpired))
    , iTimerPresetInfo(MakeFunctor(*this, &OhmSender::TimerPresetInfoExpired))
    , iSequenceTrack(0)
    , iSequenceMetatext(0)
	, iClientControllingTrackMetadata(false)
    , iPreset(aPreset)
{
    iProvider = new ProviderSender(iDevice);
 
    iDriver.SetTtl(iTtl);

	LOG(kMedia, "OHM SENDER DRIVER TTL %d\n", iTtl);
       
	iDriver.SetLatency(iLatency);

	LOG(kMedia, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
       
    iThreadMulticast = new ThreadFunctor("MTXM", MakeFunctor(*this, &OhmSender::RunMulticast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadMulticast->Start();
    
    iThreadUnicast = new ThreadFunctor("MTXU", MakeFunctor(*this, &OhmSender::RunUnicast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadUnicast->Start();
    
    iThreadZone = new ThreadFunctor("MTXZ", MakeFunctor(*this, &OhmSender::RunZone), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadZone->Start();    

	iServer = new SocketTcpServer("OHMS", 0, iInterface);

	iServer->Add("OHMS", new OhmSenderSession(*this));

    // scope for AutoMutex
    {
    AutoMutex mutex(iMutexStartStop);
	StartZone();
    }

    UpdateChannel();

	SetEnabled(aEnabled);
	
	UpdateMetadata();
}

const Brx& OhmSender::Image() const
{
	return (iImage);
}

const Brx& OhmSender::MimeType() const
{
	return (iMimeType);
}

const Brx& OhmSender::SenderUri() const
{
	return (iSenderUri.AbsoluteUri());
}

const Brx& OhmSender::SenderMetadata() const
{
	return (iSenderMetadata);
}


void OhmSender::SetName(const Brx& aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
	if (iName != aValue) {
		iName.Replace(aValue);
		UpdateMetadata();
	}
}

void OhmSender::SetChannel(TUint aValue)
{
    AutoMutex mutex(iMutexStartStop);

	if (iChannel != aValue) {
		if (iMulticast) {
			if (iStarted) {
				Stop();
				iChannel = aValue;
				UpdateChannel();
				Start();
			}
			else {
				iChannel = aValue;
				UpdateChannel();
				UpdateUri();
			}
		}
		else {
			iChannel = aValue;
			UpdateChannel();
		}
	}
}

void OhmSender::SetInterface(TIpAddress aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
	if (iInterface != aValue) {
		if (iStarted) {
			Stop();
			StopZone();
			delete (iServer);
			iInterface = aValue;
			iServer = new SocketTcpServer("OHMS", 0, iInterface);
			iServer->Add("OHMS", new OhmSenderSession(*this));
            // recreate server before UpdateMetadata() as that function requires the server port
			UpdateMetadata();
			StartZone();
			Start();
		}
		else {
			StopZone();
			iInterface = aValue;
			StartZone();
		}
	}
}

void OhmSender::SetTtl(TUint aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
	if (iTtl != aValue) {
		if (iStarted) {
			Stop();
			iTtl = aValue;
			iDriver.SetTtl(iTtl);
			LOG(kMedia, "OHM SENDER DRIVER TTL %d\n", iTtl);
			Start();
		}
		else {
			iTtl = aValue;
			iDriver.SetTtl(iTtl);
			LOG(kMedia, "OHM SENDER DRIVER TTL %d\n", iTtl);
		}
	}
}

void OhmSender::SetLatency(TUint aValue)
{
    AutoMutex mutex(iMutexStartStop);
    
	if (iLatency != aValue) {
		if (iStarted) {
			Stop();
			iLatency = aValue;
			iDriver.SetLatency(iLatency);
			LOG(kMedia, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
			Start();
		}
		else {
			iLatency = aValue;
			iDriver.SetLatency(iLatency);
			LOG(kMedia, "OHM SENDER DRIVER LATENCY %d\n", iLatency);
		}
	}
}

void OhmSender::SetMulticast(TBool aValue)
{
    AutoMutex mutex(iMutexStartStop);

	if (iMulticast != aValue) {
		if (iStarted) {
			Stop();
			iMulticast = aValue;
			UpdateMetadata();
			Start();
		}
		else {
			iMulticast = aValue;
			UpdateMetadata();
		}
	}
}

void OhmSender::SetEnabled(TBool aValue)
{
    AutoMutex mutex(iMutexStartStop);

	if (iEnabled != aValue) {
		iEnabled = aValue;

		iDriver.SetEnabled(iEnabled);

		LOG(kMedia, "OHM SENDER DRIVER ENABLED %d\n", aValue);
    
		if (iEnabled) {
			iProvider->SetStatusEnabled();
			Start();
		}
		else {
			Stop();
			iProvider->SetStatusDisabled();
		}
	}
}

// Start always called with the start/stop mutex locked

void OhmSender::Start()
{
    if (!iStarted) {
        if (iMulticast) {
            iSocketOhm.OpenMulticast(iInterface, iTtl, iMulticastEndpoint);
            iTargetEndpoint.Replace(iMulticastEndpoint);
			iTargetInterface = iInterface;
            iThreadMulticast->Signal();
        }
        else {
            iSocketOhm.OpenUnicast(iInterface, iTtl);
			iTargetInterface = iInterface;
            iThreadUnicast->Signal();
        }
        iStarted = true;
        UpdateUri();
    }
}


// Stop always called with the start/stop mutex locked

void OhmSender::Stop()
{
    if (iStarted) {
		LOG(kMedia, "STOP INTERRUPT\n");
        iSocketOhm.ReadInterrupt();
		LOG(kMedia, "STOP WAIT\n");
        iNetworkDeactivated.Wait();
		LOG(kMedia, "STOP CLOSE\n");
        iSocketOhm.Close();
        iStarted = false;
		LOG(kMedia, "STOP UPDATE\n");
        UpdateUri();
		LOG(kMedia, "STOP DONE\n");
    }
}

void OhmSender::StopZone()
{
    iSocketOhz.ReadInterrupt();
    iZoneDeactivated.Wait();
	iTimerZoneUri.Cancel();
	iTimerPresetInfo.Cancel();
    iSocketOhz.Close();
}

void OhmSender::StartZone()
{
    iSocketOhz.Open(iInterface, iTtl);
	iThreadZone->Signal();
}

void OhmSender::SetTrack(const Brx& aUri, const Brx& aMetadata, TUint64 aSamplesTotal, TUint64 aSampleStart)
{
    AutoMutex mutex(iMutexActive);

	iClientControllingTrackMetadata = true;
    iDriver.SetTrackPosition(aSamplesTotal, aSampleStart);
    iSequenceTrack++;
    iSequenceMetatext = 0;
    iTrackUri.Replace(aUri);
    iTrackMetadata.Replace(aMetadata);
    iTrackMetatext.Replace(Brx::Empty());
    
    if (iActive) {
        SendTrack();
    }
}

void OhmSender::SetMetatext(const Brx& aValue)
{
    AutoMutex mutex(iMutexActive);

    iSequenceMetatext++;
    iTrackMetatext.Replace(aValue);
    
    if (iActive) {
        SendMetatext();
    }
}

void OhmSender::SetPreset(TUint aValue)
{
	AutoMutex mutex(iMutexZone);
	iPreset = aValue;
}
    
OhmSender::~OhmSender()
{
    LOG(kMedia, "OhmSender::~OhmSender\n");

	iEnabled = false;

	iDriver.SetEnabled(false);

	LOG(kMedia, "OhmSender::~OhmSender disabled driver\n");

    // scope for AutoMutex
    {
    AutoMutex mutex(iMutexStartStop);
    Stop();
	StopZone();
    }

    LOG(kMedia, "OhmSender::~OhmSender stopped\n");

	delete iThreadZone;

    LOG(kMedia, "OhmSender::~OhmSender deleted zone thread\n");

    delete iServer;

    LOG(kMedia, "OhmSender::~OhmSender deleted tcp server\n");

	delete iThreadUnicast;

    LOG(kMedia, "OhmSender::~OhmSender deleted unicast thread\n");

    delete iThreadMulticast;

    LOG(kMedia, "OhmSender::~OhmSender deleted multicast thread\n");

	delete iProvider;

	LOG(kMedia, "OhmSender::~OhmSender deleted provider\n");
}

//  This runs a little state machine where the current state is reflected by:
//
//  iAliveJoined: Indicates that someone is listening to us (we received a join recently)
//  iAliveBlocked: Indicates that someone else is sending on our channel (we received audio recently)
//
//  iActive, when true, causes pipeline audio to be sent out over the network
//
//  The state machine ensures that iActive is only true when iAliveJoined is true and iAliveBlocked is false
//

void OhmSender::RunMulticast()
{
    for (;;) {
        LOG(kMedia, "OhmSender::RunMulticast wait\n");
        
        iThreadMulticast->Wait();

        LOG(kMedia, "OhmSender::RunMulticast go\n");
        
		iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);

		LOG(kMedia, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());

        try {
            for (;;) {
                try {
                    OhmHeader header;
                    header.Internalise(iRxBuffer);
                    
                    if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                        LOG(kMedia, "OhmSender::RunMulticast join/listen received\n");
                        
                        AutoMutex mutex(iMutexActive);
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            SendTrack();
                            SendMetatext();
                        }
                        
						if (!iActive) {
							iActive = true;
	                        iDriver.SetActive(true);
							LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
						}
                        
						iAliveJoined = true;

                        iTimerAliveJoin.FireIn(kTimerAliveJoinTimeoutMs);
                    }
					else if (header.MsgType() == OhmHeader::kMsgTypeResend) {
                        LOG(kMedia, "OhmSender::RunMulticast resend received\n");

						OhmHeaderResend headerResend;
						headerResend.Internalise(iRxBuffer, header);

						TUint frames = headerResend.FramesCount();

						if (frames > 0) {
							iDriver.Resend(iRxBuffer.Read(frames * 4));
						}
					}
					else if (header.MsgType() == OhmHeader::kMsgTypeAudio) {
						// Check sender not us

						Endpoint sender = iSocketOhm.Sender();

						if (sender.Address() != iInterface) {
	                        LOG(kMedia, "OhmSender::RunMulticast audio received\n");

							// The following randomisation prevents two senders from both sending,
							// both seeing each other's audio, both backing off for the same amount of time,
							// then both sending again, then both seeing each other's audio again,
							// then both backing off for the same amount of time ...
                        
							TUint delay = Random(kTimerAliveAudioTimeoutMs, kTimerAliveAudioTimeoutMs >> 1);

                            // scope for AutoMutex
                            {
                            AutoMutex mutex(iMutexActive);
                        
							if (iActive) {
								iActive = false;
								iDriver.SetActive(false);
								LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
							} 

							iAliveBlocked = true;

							iTimerAliveAudio.FireIn(delay);
                            }

							LOG(kMedia, "OhmSender::RunMulticast blocked\n");

							iProvider->SetStatusBlocked();
						}
                    }
                }
                catch (OhmError&)
                {
                }
                
                iRxBuffer.ReadFlush();
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "OhmSender::RunMulticast reader error\n");
        }

        iRxBuffer.ReadFlush();

        iTimerAliveJoin.Cancel();
        iTimerAliveAudio.Cancel();
        
        // scope for AutoMutex
        {
        AutoMutex mutex(iMutexActive);

        if (iActive) {
            iActive = false;
            iDriver.SetActive(false);
			LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
        } 

        iAliveJoined = false;
        iAliveBlocked = false;
        }
        
        iNetworkDeactivated.Signal();

        LOG(kMedia, "OhmSender::RunMulticast stop\n");
    }
}

void OhmSender::RunUnicast()
{
    for (;;) {
        LOG(kMedia, "OhmSender::RunUnicast wait\n");
        
        iThreadUnicast->Wait();

        LOG(kMedia, "OhmSender::RunUnicast go\n");
        
        try {
            for (;;) {
                // wait for first receiver to join
                // if we receive a listen, it's probably from a temporarily physically disconnected receiver
                // so accept them as well
                            
                for (;;) {
                    try {
                        OhmHeader header;
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                            LOG(kMedia, "OhmSender::RunUnicast ready/join or listen\n");
                            break;                        
                        }
                    }
                    catch (OhmError&)
                    {
                    }
                    
                    iRxBuffer.ReadFlush();  
                }
    
                iRxBuffer.ReadFlush();

                iTargetEndpoint.Replace(iSocketOhm.Sender());

				iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);

				LOG(kMedia, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());
        
				SendTrack();
                SendMetatext();
            
                iSlaveCount = 0;
                
                // scope for AutoMutex
                {
                AutoMutex mutex(iMutexActive);

                iActive = true;
                iAliveJoined = true;

                iDriver.SetActive(true);

				LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", true);
                }
                
                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                
                for (;;) {
                    try {
                        OhmHeader header;
                        header.Internalise(iRxBuffer);
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/join\n");
                            
                            Endpoint sender(iSocketOhm.Sender());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave >= iSlaveCount) {
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;

                                        AutoMutex mutex(iMutexActive);
                                        SendListen(sender);
                                    }
                                }
                                else {
                                    iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                }
                            }

                            AutoMutex mutex(iMutexActive);
                            SendSlaveList();
                            SendTrack();
                            SendMetatext();
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeListen) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/listen\n");
                            
                            Endpoint sender(iSocketOhm.Sender());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                                if (CheckSlaveExpiry()) {
                                    AutoMutex mutex(iMutexActive);
                                    SendSlaveList();
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                }
                                else {
                                    // unknown slave, probably temporarily physically disconnected receiver
                                    if (slave < kMaxSlaveCount) {
                                        iSlaveList[slave].Replace(sender);
                                        iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                        iSlaveCount++;

                                        AutoMutex mutex(iMutexActive);
                                        SendListen(sender);
                                        SendSlaveList();
                                        SendTrack();
                                        SendMetatext();
                                    }
                                }
                            }
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeLeave) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/leave\n");
                            
                            Endpoint sender(iSocketOhm.Sender());

                            if (sender.Equals(iTargetEndpoint) || sender.Equals(iSocketOhm.This())) {
						        iTimerExpiry.Cancel();
                    			if (iSlaveCount == 0) {
                                    if (sender.Equals(iTargetEndpoint)) {
                                        AutoMutex mutex(iMutexActive);
                                        SendLeave(sender);
                                    }
                                    break;
                                }
                                else {
                                    AutoMutex mutex(iMutexActive);
                                    
									SendLeave(sender);
                                    
									iTargetEndpoint.Replace(iSlaveList[--iSlaveCount]);
                                    
									iTimerExpiry.FireAt(iSlaveExpiry[iSlaveCount]);
                                    
									if (iSlaveCount > 0) {
                                        SendSlaveList();
                                    }
                                    
									iDriver.SetEndpoint(iTargetEndpoint, iTargetInterface);

									LOG(kMedia, "OHM SENDER DRIVER ENDPOINT %x:%d\n", iTargetEndpoint.Address(), iTargetEndpoint.Port());
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    RemoveSlave(slave);

                                    AutoMutex mutex(iMutexActive);
                                    SendLeave(sender);
                                    SendSlaveList();
                                }
                            }
                        }
						else if (header.MsgType() == OhmHeader::kMsgTypeResend) {
							LOG(kMedia, "OhmSender::RunMulticast resend received\n");

							OhmHeaderResend headerResend;
							headerResend.Internalise(iRxBuffer, header);

							TUint frames = headerResend.FramesCount();

							if (frames > 0) {
								iDriver.Resend(iRxBuffer.Read(frames * 4));
							}
						}
                    }
                    catch (OhmError&)
                    {
                    }
                    
                    iRxBuffer.ReadFlush();
                }

                iRxBuffer.ReadFlush();

                AutoMutex mutex(iMutexActive);
                iActive = false;

				iAliveJoined = false;               

				iDriver.SetActive(false);

				LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "OhmSender::RunUnicast reader error\n");
        }

		iRxBuffer.ReadFlush();

		iTimerExpiry.Cancel();

        // scope for AutoMutex
        {
        AutoMutex mutex(iMutexActive);

        if (iActive) {
            iActive = false;

			iDriver.SetActive(false);
			
			LOG(kMedia, "OHM SENDER DRIVER ACTIVE %d\n", iActive);
        } 

        iAliveJoined = false;
        iAliveBlocked = false;
        }

		iNetworkDeactivated.Signal();
        
        LOG(kMedia, "OhmSender::RunUnicast stop\n");
    }
}

void OhmSender::TimerAliveJoinExpired()
{
    AutoMutex mutex(iMutexActive);
    iActive = false;
    iAliveJoined = false;
}

void OhmSender::TimerAliveAudioExpired()
{
    // scope for AutoMutex
    {
    AutoMutex mutex(iMutexActive);
    TBool joined = iAliveBlocked;
    iActive = joined;
    iAliveBlocked = false;
    }

    iProvider->SetStatusEnabled();
}

void OhmSender::TimerExpiryExpired()
{
    // Send a Leave to ourselves, which is interpreted as a Leave from the receiver

    LOG(kMedia, "OhmSender::TimerExpiryExpired TIMEOUT\n");

    Bws<OhmHeader::kHeaderBytes> buffer;
    WriterBuffer writer(buffer);

    OhmHeader leave(OhmHeader::kMsgTypeLeave, 0);
    
    leave.Externalise(writer);

    AutoMutex mutex(iMutexActive);

    try {
        iSocketOhm.Send(buffer, iSocketOhm.This());
    }
    catch (NetworkError&) {
    }
}

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    
    iMulticastEndpoint.SetAddress(Arch::BigEndian4(address));
    iMulticastEndpoint.SetPort(Ohm::kPort);
}

void OhmSender::UpdateUri()
{
	AutoMutex mutex(iMutexZone);

	if (iStarted) {
		if (iMulticast) {
			iUri.Replace("ohm://");
			iMulticastEndpoint.AppendEndpoint(iUri);
		}
		else {
			iUri.Replace("ohu://");
			iSocketOhm.This().AppendEndpoint(iUri);
		}
	}
	else {
			iUri.Replace("ohu://0.0.0.0:0");
	}

	SendZoneUri(3);
}

void OhmSender::UpdateMetadata()
{
    iSenderMetadata.Replace("<DIDL-Lite xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:upnp=\"urn:schemas-upnp-org:metadata-1-0/upnp/\" xmlns=\"urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/\">");
    iSenderMetadata.Append("<item id=\"0\" restricted=\"True\">");
    iSenderMetadata.Append("<dc:title>");
    iSenderMetadata.Append(iName);
    iSenderMetadata.Append("</dc:title>");
    
    if (iMulticast) {
	    iSenderMetadata.Append("<res protocolInfo=\"ohz:*:*:m\">");
	}
	else {
	    iSenderMetadata.Append("<res protocolInfo=\"ohz:*:*:u\">");
	}

	iSenderUri.Replace(Brn("ohz://239.255.255.250:51972/"), iDevice.Udn());

	iSenderMetadata.Append(iSenderUri.AbsoluteUri());
    iSenderMetadata.Append("</res>");
    
	if (iImage.Bytes() > 0)
	{
		iSenderMetadata.Append("<upnp:albumArtURI>");
		iSenderMetadata.Append("http://");
		Endpoint(iServer->Port(), iInterface).AppendEndpoint(iSenderMetadata);
		iSenderMetadata.Append("/icon");
		iSenderMetadata.Append("</upnp:albumArtURI>");
	}
		
	iSenderMetadata.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iSenderMetadata.Append("</item>");
    iSenderMetadata.Append("</DIDL-Lite>");

	if (!iClientControllingTrackMetadata) {
		AutoMutex mutex(iMutexActive);
	
		iTrackMetadata.Replace(iSenderMetadata);
		
		iSequenceTrack++;
		iSequenceMetatext = 0;
    
		if (iActive) {
			SendTrack();
		}
	}

	iProvider->SetMetadata(iSenderMetadata);
}

void OhmSender::Send()
{
    try {
        iSocketOhm.Send(iTxBuffer, iTargetEndpoint);
    }
    catch (NetworkError&) {
    }
}

// SendTrack called with alive mutex locked;

void OhmSender::SendTrack()
{
    OhmHeaderTrack headerTrack(iSequenceTrack, iTrackUri, iTrackMetadata);
    OhmHeader header(OhmHeader::kMsgTypeTrack, headerTrack.MsgBytes());
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerTrack.Externalise(writer);
    writer.Write(iTrackUri);
    writer.Write(iTrackMetadata);

    Send();    
}

// SendMetatext called with alive mutex locked;

void OhmSender::SendMetatext()
{
    OhmHeaderMetatext headerMetatext(iSequenceMetatext, iTrackMetatext);
    OhmHeader header(OhmHeader::kMsgTypeMetatext, headerMetatext.MsgBytes());
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerMetatext.Externalise(writer);
    writer.Write(iTrackMetatext);
    
    Send();    
}

// SendSlaveList called with alive mutex locked;

void OhmSender::SendSlaveList()
{
    OhmHeaderSlave headerSlave(iSlaveCount);
    OhmHeader header(OhmHeader::kMsgTypeSlave, headerSlave.MsgBytes());
    
    WriterBuffer writer(iTxBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerSlave.Externalise(writer);
    
    WriterBinary binary(writer);
    
    for (TUint i = 0; i < iSlaveCount; i++) {
        binary.WriteUint32Be(Arch::BigEndian4(iSlaveList[i].Address()));
        binary.WriteUint16Be(iSlaveList[i].Port());
    }
    
    Send();    
}


// SendListen called with alive mutex locked;

// Listen message is ignored by slaves, but this is sent to populate my arp tables
// in case the slave needs to be quickly changed to master receiver.

void OhmSender::SendListen(const Endpoint& aEndpoint)
{
    OhmHeader header(OhmHeader::kMsgTypeListen, 0);

    WriterBuffer writer(iTxBuffer);

    writer.Flush();
    header.Externalise(writer);

    try {
        iSocketOhm.Send(iTxBuffer, aEndpoint);
    }
    catch (NetworkError&) {
    }
}

// Leave message is sent to acknowledge a Leave sent from a receiver or slave

void OhmSender::SendLeave(const Endpoint& aEndpoint)
{
    OhmHeader header(OhmHeader::kMsgTypeLeave, 0);

    WriterBuffer writer(iTxBuffer);

    writer.Flush();
    header.Externalise(writer);

    try {
        iSocketOhm.Send(iTxBuffer, aEndpoint);
    }
    catch (NetworkError&) {
    }
}

TBool OhmSender::CheckSlaveExpiry()
{
    TBool changed = false;

    for (TUint i = 0; i < iSlaveCount;) {
        if (Time::IsInPastOrNow(iSlaveExpiry[i])) {
            RemoveSlave(i);
            changed = true;
            continue;
        }
        i++;
    }
    
    return (changed);
}

void OhmSender::RemoveSlave(TUint aIndex)
{
    iSlaveCount--;
    for (TUint i = aIndex; i < iSlaveCount; i++) {
        iSlaveList[i].Replace(iSlaveList[i + 1]);
        iSlaveExpiry[i] = iSlaveExpiry[i + 1];
    }
}

// Returns index of supplied endpoint, or index of empty slot if not found
// distinguish between the two by comparing returned value with iSlaveCount
  
TUint OhmSender::FindSlave(const Endpoint& aEndpoint)
{
    for (TUint i = 0; i < iSlaveCount; i++) {
        if (aEndpoint.Equals(iSlaveList[i])) {
            return (i);
        }
    }
    
    return (iSlaveCount);
}

// Zone handling

void OhmSender::RunZone()
{
    for (;;) {
        LOG(kMedia, "OhmSender::RunZone wait\n");
        
        iThreadZone->Wait();

        LOG(kMedia, "OhmSender::RunZone go\n");
        
		try {
			for (;;) {
				OhzHeader header;
	        
        		try {
					header.Internalise(iRxZone);
				}
				catch (OhzError&) {
			        LOG(kMedia, "OhmSender::RunZone received error\n");
					iRxZone.ReadFlush();
	           		continue;
				}

				if (header.MsgType() == OhzHeader::kMsgTypeZoneQuery) {
					OhzHeaderZoneQuery headerZoneQuery;
					headerZoneQuery.Internalise(iRxZone, header);

					Brn zone = iRxZone.Read(headerZoneQuery.ZoneBytes());

			        LOG(kMedia, "OhmSender::RunZone received zone query for ");
					LOG(kMedia, zone);
					LOG(kMedia, "\n");
                
					if (zone == iDevice.Udn())
					{
	                    AutoMutex mutex(iMutexZone);
						SendZoneUri(1);
					}
				}
				else if (header.MsgType() == OhzHeader::kMsgTypePresetQuery) {
			        LOG(kMedia, "OhmSender::RunZone received preset query\n");
					OhzHeaderPresetQuery headerPresetQuery;
					headerPresetQuery.Internalise(iRxZone, header);
					TUint preset = headerPresetQuery.Preset();

					if (preset > 0) {
	                    AutoMutex mutex(iMutexZone);
						if (preset == iPreset) {
							SendPresetInfo(1);
						}
					}
				}

				else {
					LOG(kMedia, "OhmSender::RunZone received message type %d\n", header.MsgType());
				}

				iRxZone.ReadFlush();
			}
		}
		catch (ReaderError&) { // ReaderError is thrown when shutdown is called to close the thread
		}

        iZoneDeactivated.Signal();
        
        LOG(kMedia, "OhmSender::RunZone stop\n");
	}
}

// called with zone mutex locked

void OhmSender::SendZoneUri(TUint aCount)
{
    iSendZoneUriCount = aCount;
	iTimerZoneUri.FireIn(0);
}

void OhmSender::SendZoneUri()
{
	ASSERT(iSendZoneUriCount <= 3);

    try
    {
        OhzHeaderZoneUri headerZoneUri(iDevice.Udn(), iUri);
        OhzHeader header(OhzHeader::kMsgTypeZoneUri, headerZoneUri.MsgBytes());
        
        WriterBuffer writer(iTxZone);
        
        writer.Flush();
        header.Externalise(writer);
        headerZoneUri.Externalise(writer);
        writer.Write(iDevice.Udn());
        writer.Write(iUri);
        
        LOG(kMedia, "OhmSender::SendZoneUri %d\n", iSendZoneUriCount);

		iSocketOhz.Send(iTxZone);
        
        iSendZoneUriCount--;
    }
    catch (OhzError&)
    {
        LOG(kMedia, "OhmSender::SendZoneUri OhzError\n");
    }
    catch (WriterError&)
    {
        LOG(kMedia, "OhmSender::SendZoneUri WriterError\n");
    }
    catch (NetworkError&)
    {
        LOG(kMedia, "OhmSender::SendZoneUri NetworkError\n");
    }

    if (iSendZoneUriCount > 0) {
        iTimerZoneUri.FireIn(kTimerZoneUriDelayMs);
    }
}

void OhmSender::SendPresetInfo(TUint aCount)
{
	iSendPresetInfoCount = aCount;

    SendPresetInfo();
}

void OhmSender::SendPresetInfo()
{
    try
    {
    	OhzHeaderPresetInfo headerPresetInfo(iPreset, iSenderMetadata);
        OhzHeader header(OhzHeader::kMsgTypePresetInfo, headerPresetInfo.MsgBytes());

        WriterBuffer writer(iTxZone);

        writer.Flush();
        header.Externalise(writer);
        headerPresetInfo.Externalise(writer);
        writer.Write(iSenderMetadata);

        iSocketOhz.Send(iTxZone);

        iSendPresetInfoCount--;
    }
    catch (OhzError&)
    {
    }
    catch (WriterError&)
    {
    }

    if (iSendPresetInfoCount > 0) {
        iTimerPresetInfo.FireIn(kTimerPresetInfoDelayMs);
    }
}

void OhmSender::TimerZoneUriExpired()
{
    AutoMutex mutex(iMutexZone);
    SendZoneUri();
}

void OhmSender::TimerPresetInfoExpired()
{
    AutoMutex mutex(iMutexZone);
    SendPresetInfo();
}
    

// OhmSenderSession

// OhmSender must run an http server just to serve up the image that it is constructed with and that is reported in its metadata

OhmSenderSession::OhmSenderSession(const OhmSender& aSender)
	: iSender(aSender)
    , iSemaphore("OHMS", 1)
{
    iReadBuffer = new Srs<kMaxRequestBytes>(*this);
    iReaderRequest = new ReaderHttpRequest(*iReadBuffer);
    iWriterBuffer = new Sws<kMaxResponseBytes>(*this);
    iWriterResponse = new WriterHttpResponse(*iWriterBuffer);
    iReaderRequest->AddMethod(Http::kMethodGet);
    iReaderRequest->AddMethod(Http::kMethodHead);
    iReaderRequest->AddHeader(iHeaderHost);
}

OhmSenderSession::~OhmSenderSession()
{
    Interrupt(true);
    iSemaphore.Wait();
    delete iWriterResponse;
    delete iWriterBuffer;
    delete iReaderRequest;
    delete iReadBuffer;
}

void OhmSenderSession::Run()
{
    iSemaphore.Wait();
    iErrorStatus = &HttpStatus::kOk;
    iReaderRequest->Flush();
    
	try {
        try {
            iReaderRequest->Read();
        }
        catch (HttpError&) {
            Error(HttpStatus::kBadRequest);
        }
        if (iReaderRequest->MethodNotAllowed()) {
            Error(HttpStatus::kMethodNotAllowed);
        }
        const Brx& method = iReaderRequest->Method();
        iResponseStarted = false;
        iResponseEnded = false;
        if (method == Http::kMethodGet) {
            Get(true);
        }
		else {
			Get(false);
		}
    }
    catch (HttpError&) {
        iErrorStatus = &HttpStatus::kMethodNotAllowed;
    }
    catch (ReaderError&) {
        iErrorStatus = &HttpStatus::kBadRequest;
    }
    catch (WriterError&) {
    }
    
	try {
        if (!iResponseStarted) {
            if (iErrorStatus == &HttpStatus::kOk) {
                iErrorStatus = &HttpStatus::kNotFound;
            }
            iWriterResponse->WriteStatus(*iErrorStatus, Http::eHttp11);
            Http::WriteHeaderConnectionClose(*iWriterResponse);
            iWriterResponse->WriteFlush();
        }
        else if (!iResponseEnded) {
            iWriterResponse->WriteFlush();
        }
    }
    catch (WriterError&) {
	}

    iSemaphore.Signal();
}

void OhmSenderSession::Error(const HttpStatus& aStatus)
{
    iErrorStatus = &aStatus;
    THROW(HttpError);
}

void OhmSenderSession::Get(TBool aWriteEntity)
{
    if (iReaderRequest->Version() == Http::eHttp11) {
        if (!iHeaderHost.Received()) {
            Error(HttpStatus::kBadRequest);
        }
    }

	if (iHeaderExpect.Continue()) {
        iWriterResponse->WriteStatus(HttpStatus::kContinue, Http::eHttp11);
        iWriterResponse->WriteFlush();
    }

    iWriterResponse->WriteStatus(HttpStatus::kOk, Http::eHttp11);

    Http::WriteHeaderContentLength(*iWriterResponse, iSender.Image().Bytes());

	IWriterAscii& writer = iWriterResponse->WriteHeaderField(Http::kHeaderContentType);
	writer.Write(iSender.MimeType());
	writer.Write(Brn("; charset=\"utf-8\""));
	writer.WriteFlush();

	Http::WriteHeaderConnectionClose(*iWriterResponse);

    iWriterResponse->WriteFlush();

    iResponseStarted = true;

	if (aWriteEntity) {
		iWriterBuffer->Write(iSender.Image());
	}

    iWriterBuffer->WriteFlush();
}

