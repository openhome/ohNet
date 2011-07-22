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
namespace Net {

	class ProviderSender : public DvProviderAvOpenhomeOrgSender1
	{
	    static const TUint kMaxMetadataBytes = 4096;
	    static const TUint kTimeoutAudioPresentMs = 1000;
	
	public:
	    ProviderSender(DvDevice& aDevice);
	    
	    void SetMetadata(const Brx& aValue);
	    
	    void SetStatusEnabled();
	    void SetStatusDisabled();
        void SetStatusBlocked();
	    
	    void InformAudioPresent();
	    
	    ~ProviderSender() {}
	    
	private:
	    virtual void PresentationUrl(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Metadata(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Audio(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseBool& aValue);
	    virtual void Status(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	    virtual void Attributes(IInvocationResponse& aResponse, TUint aVersion, IInvocationResponseString& aValue);
	
	    void UpdateMetadata();
	    void TimerAudioPresentExpired();
	
	private:
	    Bws<kMaxMetadataBytes> iMetadata;
	    mutable Mutex iMutex;
	    Timer iTimerAudioPresent;
	};
} // namespace Net
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;

// ProviderSender

ProviderSender::ProviderSender(DvDevice& aDevice)
    : DvProviderAvOpenhomeOrgSender1(aDevice)
    , iMutex("PSND")
    , iTimerAudioPresent(MakeFunctor(*this, &ProviderSender::TimerAudioPresentExpired))
{
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

void ProviderSender::PresentationUrl(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyPresentationUrl(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::Metadata(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValue)
{
	Brhz value;
    GetPropertyMetadata(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::Audio(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseBool& aValue)
{
    TBool value;
    GetPropertyAudio(value);
    aResponse.Start();
    aValue.Write(value);
    aResponse.End();
}

void ProviderSender::Status(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyStatus(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
}

void ProviderSender::Attributes(IInvocationResponse& aResponse, TUint /*aVersion*/, IInvocationResponseString& aValue)
{
    Brhz value;
    GetPropertyAttributes(value);
    aResponse.Start();
    aValue.Write(value);
    aValue.WriteFlush();
    aResponse.End();
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
{
}

void OhmSenderDriver::SetEnabled(TBool aValue)
{
	iMutex.Wait();

	iEnabled = aValue;

	if (iSend) {
		if (!aValue) { // turning off
			iSend = false;
			iFrame = 0;
		}
	}
	else {
		if (aValue && iActive) { // turning on
			iSend = true;
		}
	}

	iMutex.Signal();
}

void OhmSenderDriver::SetActive(TBool aValue)
{
	iMutex.Wait();
	
	iActive = aValue;

	if (iSend) {
		if (!aValue) { // turning off
			iSend = false;
			iFrame = 0;
		}
	}
	else {
		if (aValue && iEnabled) { // turning on
			iSend = true;
		}
	}

	iMutex.Signal();
}

void OhmSenderDriver::SetEndpoint(const Endpoint& aEndpoint)
{
    iMutex.Wait();
    iEndpoint.Replace(aEndpoint);
    iMutex.Signal();
}


void OhmSenderDriver::SetTtl(TUint aValue)
{
    iMutex.Wait();
    iSocket.SetTtl(aValue);
    iMutex.Signal();
}

void OhmSenderDriver::SetTrackPosition(TUint64 aSamplesTotal, TUint64 aSampleStart)
{
    iMutex.Wait();
    iSamplesTotal = aSamplesTotal;
    iSampleStart = aSampleStart;
    iMutex.Signal();
}

void OhmSenderDriver::SetAudioFormat(TUint aSampleRate, TUint aBitRate, TUint aChannels, TUint aBitDepth, TBool aLossless, const Brx& aCodecName)
{
    iMutex.Wait();
    iSampleRate = aSampleRate;
    iBitRate = aBitRate;
    iChannels = aChannels;
    iBitDepth = aBitDepth;
    iLossless = aLossless;
    iCodecName.Replace(aCodecName);
    iMutex.Signal();
}

void OhmSenderDriver::SendAudio(const TByte* aData, TUint aBytes)
{
    iMutex.Wait();
    
    TUint samples = aBytes * 8 / iChannels / iBitDepth;

    if (!iSend) {
        iSampleStart += samples;
        iMutex.Signal();
        return;
    }
    
    OhmHeaderAudio headerAudio(false,  // halt
                               iLossless,
                               samples,
                               iFrame,
                               iSampleStart,
                               iSamplesTotal,
                               iSampleRate,
                               iBitRate,
                               0, // volume offset
                               iBitDepth,
                               iChannels,
                               iCodecName);
    
    OhmHeader header(OhmHeader::kMsgTypeAudio, headerAudio.MsgBytes());

    WriterBuffer writer(iBuffer);
    
    writer.Flush();
    header.Externalise(writer);
    headerAudio.Externalise(writer);
    
    writer.Write(Brn(aData, aBytes));

    try {
        iSocket.Send(iBuffer, iEndpoint);
    }
    catch (NetworkError&) {
        ASSERTS();
    }
        
    iSampleStart += samples;

    iFrame++;
    
    iMutex.Signal();
}

// OhmSender

OhmSender::OhmSender(DvDevice& aDevice, IOhmSenderDriver& aDriver, const Brx& aName, TUint aChannel, TIpAddress aInterface, TUint aTtl, TBool aMulticast, TBool aEnabled, const Brx& aImage, const Brx& aMimeType, TUint aPreset)
    : iDevice(aDevice)
    , iDriver(aDriver)
    , iName(aName)
    , iChannel(aChannel)
    , iInterface(aInterface)
    , iTtl(aTtl)
    , iMulticast(aMulticast)
	, iImage(aImage)
	, iMimeType(aMimeType)
    , iRxBuffer(iSocketOhm)
	, iRxZone(iSocketOhz)
    , iMutexStartStop("OHMS")
    , iMutexActive("OHMA")
    , iMutexZone("OHMZ")
    , iNetworkDeactivated("OHDN", 0)
    , iZoneDeactivated("OHDZ", 0)
    , iTimerAliveJoin(MakeFunctor(*this, &OhmSender::TimerAliveJoinExpired))
    , iTimerAliveAudio(MakeFunctor(*this, &OhmSender::TimerAliveAudioExpired))
    , iTimerExpiry(MakeFunctor(*this, &OhmSender::TimerExpiryExpired))
    , iTimerZoneUri(MakeFunctor(*this, &OhmSender::TimerZoneUriExpired))
    , iTimerPresetInfo(MakeFunctor(*this, &OhmSender::TimerPresetInfoExpired))
    , iStarted(false)
    , iActive(false)
    , iAliveJoined(false)
    , iAliveBlocked(false)
    , iSequenceTrack(0)
    , iSequenceMetatext(0)
	, iClientControllingTrackMetadata(false)
    , iPreset(aPreset)
{
    iProvider = new ProviderSender(iDevice);
 
    iDriver.SetTtl(iTtl);
       
    iThreadMulticast = new ThreadFunctor("MTXM", MakeFunctor(*this, &OhmSender::RunMulticast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadMulticast->Start();
    
    iThreadUnicast = new ThreadFunctor("MTXU", MakeFunctor(*this, &OhmSender::RunUnicast), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadUnicast->Start();
    
    iThreadZone = new ThreadFunctor("MTXZ", MakeFunctor(*this, &OhmSender::RunZone), kThreadPriorityNetwork, kThreadStackBytesNetwork);
    iThreadZone->Start();    

	iServer = new SocketTcpServer("OHMS", 0, iInterface);

	iServer->Add("OHMS", new OhmSenderSession(*this));

	iMutexStartStop.Wait();

	StartZone();
    
	iMutexStartStop.Signal();

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
	return (iSenderUri);
}

const Brx& OhmSender::SenderMetadata() const
{
	return (iSenderMetadata);
}


void OhmSender::SetName(const Brx& aValue)
{
    iMutexStartStop.Wait();
    
	if (iName != aValue) {
		iName.Replace(aValue);
		UpdateMetadata();
	}

    iMutexStartStop.Signal();
}

void OhmSender::SetChannel(TUint aValue)
{
    iMutexStartStop.Wait();

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
    
    iMutexStartStop.Signal();
}

void OhmSender::SetInterface(TIpAddress aValue)
{
    iMutexStartStop.Wait();
    
	if (iInterface != aValue) {
		if (iStarted) {
			Stop();
			StopZone();
			iInterface = aValue;
			delete (iServer);
			iServer = new SocketTcpServer("OHMS", 0, iInterface);
			iServer->Add("OHMS", new OhmSenderSession(*this));
			StartZone();
			Start();
		}
		else {
			StopZone();
			iInterface = aValue;
			StartZone();
		}
	}
    
    iMutexStartStop.Signal();
}

void OhmSender::SetTtl(TUint aValue)
{
    iMutexStartStop.Wait();
    
	if (iTtl != aValue) {
		if (iStarted) {
			Stop();
			iTtl = aValue;
			iDriver.SetTtl(iTtl);
			Start();
		}
		else {
			iTtl = aValue;
			iDriver.SetTtl(iTtl);
		}
	}
    
    iMutexStartStop.Signal();
}

void OhmSender::SetMulticast(TBool aValue)
{
    iMutexStartStop.Wait();

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
    
    iMutexStartStop.Signal();
}

void OhmSender::SetEnabled(TBool aValue)
{
    iMutexStartStop.Wait();

	if (iEnabled != aValue) {
		iEnabled = aValue;

		iDriver.SetEnabled(aValue);
    
		if (iEnabled) {
			iProvider->SetStatusEnabled();
			Start();
		}
		else {
			Stop();
			iProvider->SetStatusDisabled();
		}
	}

    iMutexStartStop.Signal();
}

// Start always called with the start/stop mutex locked

void OhmSender::Start()
{
    if (!iStarted) {
        if (iMulticast) {
            iSocketOhm.OpenMulticast(iInterface, iTtl, iMulticastEndpoint);
            iTargetEndpoint.Replace(iMulticastEndpoint);
            iThreadMulticast->Signal();
        }
        else {
            iSocketOhm.OpenUnicast(iInterface, iTtl);
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
        iSocketOhm.ReadInterrupt();
        iNetworkDeactivated.Wait();
        iSocketOhm.Close();
        iStarted = false;
        UpdateUri();
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
    iMutexActive.Wait();
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
    
    iMutexActive.Signal();
}

void OhmSender::SetMetatext(const Brx& aValue)
{
    iMutexActive.Wait();
    iSequenceMetatext++;
    iTrackMetatext.Replace(aValue);
    
    if (iActive) {
        SendMetatext();
    }
    
    iMutexActive.Signal();
}

void OhmSender::SetPreset(TUint aValue)
{
	iMutexZone.Wait();
	iPreset = aValue;
	iMutexZone.Signal();
}
    
OhmSender::~OhmSender()
{
    LOG(kMedia, "OhmSender::~OhmSender\n");
    iMutexStartStop.Wait();
    Stop();
	StopZone();
    iMutexStartStop.Signal();

    LOG(kMedia, "OhmSender::~OhmSender stopped\n");

	iDriver.SetEnabled(false);

    LOG(kMedia, "OhmSender::~OhmSender driver disabled\n");

	delete iThreadZone;

    LOG(kMedia, "OhmSender::~OhmSender deleted zone thread\n");


	delete iThreadUnicast;

    LOG(kMedia, "OhmSender::~OhmSender deleted unicast thread\n");

    delete iThreadMulticast;

    LOG(kMedia, "OhmSender::~OhmSender deleted multicast thread\n");
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
        
		iDriver.SetEndpoint(iTargetEndpoint);

        try {
            for (;;) {
                try {
                    OhmHeader header;
                    header.Internalise(iRxBuffer);
                    
                    if (header.MsgType() <= OhmHeader::kMsgTypeListen) {
                        LOG(kMedia, "OhmSender::RunMulticast join/listen received\n");
                        
                        iMutexActive.Wait();
                        
                        if (header.MsgType() == OhmHeader::kMsgTypeJoin) {
                            SendTrack();
                            SendMetatext();
                        }
                        
						if (!iActive) {
							iActive = true;
	                        iDriver.SetActive(true);
						}
                        
						iAliveJoined = true;

                        iTimerAliveJoin.FireIn(kTimerAliveJoinTimeoutMs);

                        iMutexActive.Signal();
                    }
                    else {
						// Check sender not us

						Endpoint sender = iSocketOhm.Sender();

						if (sender.Address() != iInterface) {
	                        LOG(kMedia, "OhmSender::RunMulticast audio received\n");

							// The following randomisation prevents two senders from both sending,
							// both seeing each other's audio, both backing off for the same amount of time,
							// then both sending again, then both seeing each other's audio again,
							// then both backing off for the same amount of time ...
                        
							TUint delay = Random(kTimerAliveAudioTimeoutMs, kTimerAliveAudioTimeoutMs >> 1);

							iMutexActive.Wait();
                        
							if (iActive) {
								iActive = false;
								iDriver.SetActive(false);
							} 

							iAliveBlocked = true;

							iTimerAliveAudio.FireIn(delay);

							iMutexActive.Signal();

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
            LOG(kMedia, "OPhmSender::RunMulticast reader error\n");
        }

        iRxBuffer.ReadFlush();

        iTimerAliveJoin.Cancel();
        iTimerAliveAudio.Cancel();
        
        iMutexActive.Wait();

        if (iActive) {
            iActive = false;
            iDriver.SetActive(false);
        } 

        iAliveJoined = false;
        iAliveBlocked = false;

        iMutexActive.Signal();
        
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

				iDriver.SetEndpoint(iTargetEndpoint);
        
				SendTrack();
                SendMetatext();
            
                iSlaveCount = 0;
                
                iMutexActive.Wait();

                iActive = true;
                iAliveJoined = true;

                iDriver.SetActive(true);

                iMutexActive.Signal();
                
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
                                        iMutexActive.Wait();
                                        SendListen(sender);
                                        iMutexActive.Signal();
                                    }
                                }
                                else {
                                    iSlaveExpiry[slave] = Time::Now() + kTimerExpiryTimeoutMs;
                                }
                            }
                            iMutexActive.Wait();
                            SendSlaveList();
                            SendTrack();
                            SendMetatext();
                            iMutexActive.Signal();
                        }
                        else if (header.MsgType() == OhmHeader::kMsgTypeListen) {
                            LOG(kMedia, "OhmSender::RunUnicast sending/listen\n");
                            
                            Endpoint sender(iSocketOhm.Sender());

                            if (sender.Equals(iTargetEndpoint)) {
                                iTimerExpiry.FireIn(kTimerExpiryTimeoutMs);
                                if (CheckSlaveExpiry()) {
                                    iMutexActive.Wait();
                                    SendSlaveList();
                                    iMutexActive.Signal();
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
                                        iMutexActive.Wait();
                                        SendListen(sender);
                                        SendSlaveList();
                                        SendTrack();
                                        SendMetatext();
                                        iMutexActive.Signal();
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
                                        iMutexActive.Wait();
                                        SendLeave(sender);
                                        iMutexActive.Signal();
                                    }
                                    break;
                                }
                                else {
                                    iMutexActive.Wait();
                                    SendLeave(sender);
                                    iTargetEndpoint.Replace(iSlaveList[--iSlaveCount]);
                                    iTimerExpiry.FireAt(iSlaveExpiry[iSlaveCount]);
                                    if (iSlaveCount > 0) {
                                        SendSlaveList();
                                    }
                                    iDriver.SetEndpoint(iTargetEndpoint);
                                    iMutexActive.Signal();
                                }
                            }
                            else {
                                TUint slave = FindSlave(sender);
                                if (slave < iSlaveCount) {
                                    RemoveSlave(slave);
                                    iMutexActive.Wait();
                                    SendLeave(sender);
                                    SendSlaveList();
                                    iMutexActive.Signal();
                                }
                            }
                        }
                    }
                    catch (OhmError&)
                    {
                    }
                    
                    iRxBuffer.ReadFlush();
                }

                iRxBuffer.ReadFlush();

                iMutexActive.Wait();
                iActive = false;
                iAliveJoined = false;               
                iDriver.SetActive(false);
                iMutexActive.Signal();
            }
        }
        catch (ReaderError&) {
            LOG(kMedia, "OhmSender::RunUnicast reader error\n");
        }

        iRxBuffer.ReadFlush();

        iTimerExpiry.Cancel();

        iMutexActive.Wait();

        if (iActive) {
            iActive = false;
            iDriver.SetActive(false);
        } 

        iAliveJoined = false;
        iAliveBlocked = false;

        iMutexActive.Signal();
        
        iNetworkDeactivated.Signal();
        
        LOG(kMedia, "OhmSender::RunUnicast stop\n");
    }
}

void OhmSender::TimerAliveJoinExpired()
{
    iMutexActive.Wait();
    iActive = false;
    iAliveJoined = false;
    iMutexActive.Signal();
}

void OhmSender::TimerAliveAudioExpired()
{
    iMutexActive.Wait();
    TBool joined = iAliveBlocked;
    iActive = joined;
    iAliveBlocked = false;
    iMutexActive.Signal();
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

    iMutexActive.Wait();

    try {
        iSocketOhm.Send(buffer, iSocketOhm.This());
    }
    catch (NetworkError&) {
        ASSERTS();
    }

    iMutexActive.Signal();
}

void OhmSender::UpdateChannel()
{
    TUint address = (iChannel & 0xffff) | 0xeffd0000; // 239.253.x.x
    
    iMulticastEndpoint.SetAddress(Arch::BigEndian4(address));
    iMulticastEndpoint.SetPort(Ohm::kPort);
}

void OhmSender::UpdateUri()
{
	iMutexZone.Wait();

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

	iMutexZone.Signal();
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

	iSenderUri.Replace("ohz://239.255.255.250:51972/");
    iSenderUri.Append(iDevice.Udn());

	iSenderMetadata.Append(iSenderUri);
    iSenderMetadata.Append("</res>");
    
	iSenderMetadata.Append("<upnp:albumArtURI>");
	iSenderMetadata.Append("http://");

	Endpoint(iServer->Port(), iInterface).AppendEndpoint(iSenderMetadata);

	iSenderMetadata.Append("/icon");
	iSenderMetadata.Append("</upnp:albumArtURI>");
		
	iSenderMetadata.Append("<upnp:class>object.item.audioItem</upnp:class>");
    iSenderMetadata.Append("</item>");
    iSenderMetadata.Append("</DIDL-Lite>");

	if (!iClientControllingTrackMetadata) {
		iMutexActive.Wait();
	
		iTrackMetadata.Replace(iSenderMetadata);
		
		iSequenceTrack++;
		iSequenceMetatext = 0;
    
		if (iActive) {
			SendTrack();
		}
    
		iMutexActive.Signal();
	}

	iProvider->SetMetadata(iSenderMetadata);
}

void OhmSender::Send()
{
    try {
        iSocketOhm.Send(iTxBuffer, iTargetEndpoint);
    }
    catch (NetworkError&) {
        ASSERTS();
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
        ASSERTS();
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
        ASSERTS();
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
						iMutexZone.Wait();
						SendZoneUri(1);
						iMutexZone.Signal();
					}
				}
				else if (header.MsgType() == OhzHeader::kMsgTypePresetQuery) {
			        LOG(kMedia, "OhmSender::RunZone received preset query\n");
					OhzHeaderPresetQuery headerPresetQuery;
					headerPresetQuery.Internalise(iRxZone, header);
					TUint preset = headerPresetQuery.Preset();

					if (preset > 0) {
						iMutexZone.Wait();
						if (preset == iPreset) {
							SendPresetInfo(1);
						}
						iMutexZone.Signal();
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
    iMutexZone.Wait();
    SendZoneUri();
    iMutexZone.Signal();
}

void OhmSender::TimerPresetInfoExpired()
{
    iMutexZone.Wait();
    SendPresetInfo();
    iMutexZone.Signal();
}
    

// OhmSenderSession

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

