#pragma once

#include <OpenHome/Media/Protocol/Protocol.h>
#include <OpenHome/Private/Env.h>
#include <OpenHome/Private/Network.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Timer.h>
#include <OpenHome/Media/SupplyAggregator.h>
#include <OpenHome/Media/Debug.h>

#include  <openssl/rsa.h>
#include  <openssl/aes.h>

EXCEPTION(InvalidRaopPacket)
EXCEPTION(RepairerBufferFull)
EXCEPTION(RepairerStreamRestarted)

namespace OpenHome {
    class Timer;
namespace Av {

class SocketUdpServer;
class UdpServerManager;
class IRaopDiscovery;

/**
 * RAOP appears to use a version of the RTP header that does not conform to
 * RFC 3350: https://www.ietf.org/rfc/rfc3550.txt.
 *
 * It uses only the first 4 bytes of the fixed-size header and the extension
 * bit can be set without providing an extension header.
 */
class RtpHeaderRaop : private INonCopyable
{
public:
    static const TUint kBytes = 4;
    static const TUint kVersion = 2;
public:
    RtpHeaderRaop(TBool aPadding, TBool aExtension, TUint aCsrcCount, TBool aMarker, TUint aPayloadType, TUint aSeqNumber);
    RtpHeaderRaop(const Brx& aRtpHeader);
    void Write(IWriter& aWriter) const;
    TBool Padding() const;
    TBool Extension() const;
    TUint CsrcCount() const;
    TBool Marker() const;
    TUint Type() const;
    TUint Seq() const;
private:
    TBool iPadding;
    TBool iExtension;
    TUint iCsrcCount;
    TBool iMarker;
    TUint iPayloadType;
    TUint iSequenceNumber;
};

class RtpPacketRaop
{
public:
    // Assume the following:
    // Max Ethernet frame size: 1500 bytes.
    // IPv4 header:             20 bytes.
    // UDP header:              8 bytes.
    // So, 1500-20-8 = 1472 RTP bytes max.
    static const TUint kMaxPacketBytes = 1472;
public:
    RtpPacketRaop(const Brx& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
private:
    const RtpHeaderRaop iHeader;
    const Brn iPayload;
};

class RaopPacketAudio : private INonCopyable
{
public:
    static const TUint kType = 0x60;
private:
    static const TUint kAudioSpecificHeaderBytes = 8;
public:
    RaopPacketAudio(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
    TUint Timestamp() const;
    TUint Ssrc() const;
private:
    const RtpPacketRaop& iPacket;
    const Brn iPayload;
    TUint iTimestamp;
    TUint iSsrc;
};

class RaopPacketSync : private INonCopyable
{
public:
    static const TUint kType = 0x54;
private:
    static const TUint kSyncSpecificHeaderBytes = 16;
public:
    RaopPacketSync(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const Brx& Payload() const;
    TUint RtpTimestampMinusLatency() const;
    TUint NtpTimestampSecs() const;
    TUint NtpTimestampFract() const;
    TUint RtpTimestamp() const;
private:
    const RtpPacketRaop& iPacket;
    const Brn iPayload;
    TUint iRtpTimestampMinusLatency;
    TUint iNtpTimestampSecs;
    TUint iNtpTimestampFract;
    TUint iRtpTimestamp;
};

class RaopPacketResendResponse
{
public:
    static const TUint kType = 0x56;
public:
    RaopPacketResendResponse(const RtpPacketRaop& aRtpPacket);
    const RtpHeaderRaop& Header() const;
    const RaopPacketAudio& AudioPacket() const;
private:
    const RtpPacketRaop& iPacketOuter;
    const RtpPacketRaop iPacketInner;
    const RaopPacketAudio iAudioPacket;
};

class RaopPacketResendRequest
{
public:
    static const TUint kType = 0x55;
    static const TUint kBytes = 8;
public:
    RaopPacketResendRequest(TUint aSeqStart, TUint aCount);
    void Write(IWriter& aWriter) const;
private:
    const RtpHeaderRaop iHeader;
    const TUint iSeqStart;
    const TUint iCount;
};

class RaopAudioServer : private INonCopyable
{
public:
    RaopAudioServer(SocketUdpServer& aServer);
    ~RaopAudioServer();
    void Open();
    void Close();
    void ReadPacket(Bwx& aBuf);
    void DoInterrupt();
    void Reset();
private:
    SocketUdpServer& iServer;
    TBool iInterrupted;
    Mutex iLock;
    TBool iOpen;
};

// FIXME - this class currently writes out the packet length at the start of decoded audio.
// That shouldn't be a responsibility of a generic decryptor.
// Maybe have a chain of elements that write into the same buffer (i.e., one element to write the packet length at the start, then pass onto decryptor to decrypt the audio into the buffer).
class RaopAudioDecryptor
{
private:
    static const TUint kAesKeyBytes = sizeof(AES_KEY);
    static const TUint kAesInitVectorBytes = 16;
    static const TUint kPacketSizeBytes = sizeof(TUint);
public:
    void Init(const Brx& aAesKey, const Brx& aAesInitVector);
    void Decrypt(const Brx& aEncryptedIn, Bwx& aAudioOut) const;
private:
    Bws<kAesKeyBytes> iKey;
    Bws<kAesInitVectorBytes> iInitVector;
};

class IRaopResendReceiver
{
public:
    virtual void ResendReceive(const RaopPacketAudio& aPacket) = 0;
    virtual ~IRaopResendReceiver() {}
};

class IRaopResendRequester
{
public:
    virtual void RequestResend(TUint aSeqStart, TUint aCount) = 0;
    virtual ~IRaopResendRequester() {}
};

class RaopControlServer : public IRaopResendRequester
{
private:
    static const TUint kMaxReadBufferBytes = 1500;
    static const TUint kPriority = kPriorityNormal-1;
    static const TUint kSessionStackBytes = 10 * 1024;
    static const TUint kInvalidServerPort = 0;
private:
    enum EType {
        ESync = 0x54,
        EResendRequest = 0x55,
        EResendResponse = 0x56,
    };
public:
    RaopControlServer(SocketUdpServer& aServer, IRaopResendReceiver& aResendReceiver);
    ~RaopControlServer();
    void Open();
    void Close();
    void DoInterrupt();
    void Reset(TUint aClientPort);
    TUint Latency() const;  // Returns latency in samples.
public: // from IRaopResendRequester
    void RequestResend(TUint aSeqStart, TUint aCount) override;
private:
    void Run();
private:
    Endpoint iEndpoint;
    TUint iClientPort;
    SocketUdpServer& iServer;
    IRaopResendReceiver& iResendReceiver;
    Bws<kMaxReadBufferBytes> iPacket;
    ThreadFunctor* iThread;
    TUint iLatency;
    mutable Mutex iLock;
    TBool iOpen;
    TBool iExit;
};

class IAudioSupply
{
public:
    virtual void OutputAudio(const Brx& aAudio) = 0;
    virtual ~IAudioSupply() {}
};

class IRepairable
{
public:
    virtual TUint Frame() const = 0;
    virtual TBool Resend() const = 0;
    virtual const Brx& Data() const = 0;
    virtual void Destroy() = 0;
    virtual ~IRepairable() {}
};

class IRepairableAllocatable : public IRepairable
{
public: // from IRepairable
    virtual TUint Frame() const = 0;
    virtual TBool Resend() const = 0;
    virtual const Brx& Data() const = 0;
    virtual void Destroy() = 0;
public:
    virtual void Set(TUint aFrame, TBool aResend, const Brx& aData) = 0;
    virtual ~IRepairableAllocatable() {}
};

class IRaopRepairableDeallocator
{
public:
    virtual void Deallocate(IRepairableAllocatable* aRepairable) = 0;
    virtual ~IRaopRepairableDeallocator() {}
};

template <TUint S> class Repairable : public IRepairableAllocatable
{
public:
    Repairable(IRaopRepairableDeallocator& aDeallocator)
        : iDeallocator(aDeallocator), iFrame(0), iResend(0) {}

public: // from IRepairableAllocatable
    TUint Frame() const override { return iFrame; }
    TBool Resend() const override { return iResend; }
    const Brx& Data() const override { return iData; }
    void Destroy() override { iDeallocator.Deallocate(this); }
    void Set(TUint aFrame, TBool aResend, const Brx& aData) override
    {
        iFrame = aFrame;
        iResend = aResend;
        iData.Replace(aData);
    }
private:
    IRaopRepairableDeallocator& iDeallocator;
    TUint iFrame;
    TBool iResend;
    Bws<S> iData;
};


template <TUint RepairableCount,TUint DataBytes> class RaopRepairableAllocator : IRaopRepairableDeallocator
{
public:
    RaopRepairableAllocator();
    ~RaopRepairableAllocator();
    IRepairable* Allocate(const RaopPacketAudio& aPacket);
    IRepairable* Allocate(const RaopPacketResendResponse& aPacket);
public: // fromIRaopRepairableDeallocator
    void Deallocate(IRepairableAllocatable* aRepairable) override;
private:
    FifoLite<IRepairableAllocatable*, RepairableCount> iFifo;
    Mutex iLock;
};

template <TUint RepairableCount, TUint DataBytes> RaopRepairableAllocator<RepairableCount,DataBytes>::RaopRepairableAllocator()
    : iLock("RRAL")
{
    AutoMutex a(iLock);
    for (TUint i=0; i<RepairableCount; i++) {
        iFifo.Write(new Repairable<DataBytes>(*this));
    }
}

template <TUint RepairableCount, TUint DataBytes> RaopRepairableAllocator<RepairableCount,DataBytes>::~RaopRepairableAllocator()
{
    AutoMutex a(iLock);
    ASSERT(iFifo.SlotsFree() == 0);
    while (iFifo.SlotsUsed() > 0) {
        IRepairable* repairable = iFifo.Read();
        delete repairable;
    }
}

template <TUint RepairableCount, TUint DataBytes> IRepairable*  RaopRepairableAllocator<RepairableCount,DataBytes>::Allocate(const RaopPacketAudio& aPacket)
{
    AutoMutex a(iLock);
    IRepairableAllocatable* repairable = iFifo.Read();
    repairable->Set(aPacket.Header().Seq(), false, aPacket.Payload());
    return repairable;
}

template <TUint RepairableCount, TUint DataBytes> IRepairable* RaopRepairableAllocator<RepairableCount,DataBytes>::Allocate(const RaopPacketResendResponse& aPacket)
{
    AutoMutex a(iLock);
    IRepairableAllocatable* repairable = iFifo.Read();
    repairable->Set(aPacket.Header().Seq(), true, aPacket.AudioPacket().Payload());
    return repairable;
}

template <TUint RepairableCount, TUint DataBytes> void RaopRepairableAllocator<RepairableCount,DataBytes>::Deallocate(IRepairableAllocatable* aRepairable)
{
    AutoMutex a(iLock);
    aRepairable->Set(0, false, Brx::Empty());
    iFifo.Write(aRepairable);
}


/**
 * Resend ranges are inclusive.
 */
class IResendRange
{
public:
    virtual TUint Start() const = 0;
    virtual TUint End() const = 0;
    virtual ~IResendRange() {}
};

class IResendRangeRequester
{
public:
    virtual void RequestResendSequences(const std::vector<const IResendRange*> aRanges) = 0;
    virtual ~IResendRangeRequester() {}
};

class RaopResendRangeRequester : public IResendRangeRequester, private INonCopyable
{
public:
    RaopResendRangeRequester(IRaopResendRequester& aResendRequester);
public: // from IResendRangeRequester
    void RequestResendSequences(const std::vector<const IResendRange*> aRanges) override;
private:
    IRaopResendRequester& iResendRequester;
};

class IRepairerTimer
{
public:
    virtual void Start(Functor aFunctor, TUint aFireInMs) = 0;
    virtual void Cancel() = 0;
    virtual ~IRepairerTimer() {}
};

class RepairerTimer : public IRepairerTimer
{
public:
    RepairerTimer(Environment& aEnv, const TChar* aId);
    ~RepairerTimer();
public: // from IRepairerTimer
    void Start(Functor aFunctor, TUint aFireInMs) override;
    void Cancel() override;
private:
    void TimerFired();
private:
    Timer iTimer;
    Functor iFunctor;
};

class ResendRange : public IResendRange
{
public:
    ResendRange();
    void Set(TUint aStart, TUint aEnd);
public: // from IResendRange
    TUint Start() const override;
    TUint End() const override;
private:
    TUint iStart;
    TUint iEnd;
};

template <TUint MaxFrames> class Repairer
{
private:
    static const TUint kMaxMissedRanges = MaxFrames/2;
    static const TUint kInitialRepairTimeoutMs = 10;
    static const TUint kSubsequentRepairTimeoutMs = 30;
public:
    Repairer(Environment& aEnv, IResendRangeRequester& aResendRequester, IAudioSupply& aAudioSupply, IRepairerTimer& aTimer);
    ~Repairer();
    void OutputAudio(IRepairable& aRepairable);  // THROWS RepairerBufferFull, RepairerStreamRestarted
    void DropAudio();
private:
    TBool RepairBegin(IRepairable& aRepairable);
    void RepairReset();
    TBool Repair(IRepairable& aRepairable);
    void TimerRepairExpired();
private:
    Environment& iEnv;
    IResendRangeRequester& iResendRequester;
    IAudioSupply& iAudioSupply;
    IRepairerTimer& iTimer;
    IRepairable* iRepairFirst;
    std::vector<IRepairable*> iRepairFrames;
    std::vector<IRepairable*> iOutput;
    std::vector<ResendRange*> iResend;              // Ranges to be requested.
    std::vector<const IResendRange*> iResendConst;  // Populated at same time as iResend, and used to pass immutable resend list to resend requester.
    FifoLite<ResendRange*, kMaxMissedRanges> iFifoResend;
    TBool iRunning;
    TBool iRepairing;
    TUint16 iFrame;     // RAOP seq no is 16-bit uint.
    Mutex iMutexTransport;
    Mutex iMutexAudioOutput;
};

// Repairer

template <TUint MaxFrames> Repairer<MaxFrames>::Repairer(Environment& aEnv, IResendRangeRequester& aResendRequester, IAudioSupply& aAudioSupply, IRepairerTimer& aTimer)
    : iEnv(aEnv)
    , iResendRequester(aResendRequester)
    , iAudioSupply(aAudioSupply)
    , iTimer(aTimer)
    , iRepairFirst(nullptr)
    , iRunning(false)
    , iRepairing(false)
    , iFrame(0)
    , iMutexTransport("REPL")
    , iMutexAudioOutput("REAO")
{
    for (TUint i=0; i<kMaxMissedRanges; i++) {
        iFifoResend.Write(new ResendRange());
    }
}

template <TUint MaxFrames> Repairer<MaxFrames>::~Repairer()
{
    iTimer.Cancel();
    ASSERT(iFifoResend.SlotsFree() == 0);
    while (iFifoResend.SlotsUsed() > 0) {
        auto resend = iFifoResend.Read();
        delete resend;
    }
}

template <TUint MaxFrames> void Repairer<MaxFrames>::OutputAudio(IRepairable& aRepairable)
{
    // Must only be held by this method to protect iOutput.
    AutoMutex ao(iMutexAudioOutput);

    {
        AutoMutex a(iMutexTransport);
        if (!iRunning) {
            iFrame = static_cast<TUint16>(aRepairable.Frame());
            iRunning = true;
            iOutput.push_back(&aRepairable);
        }
        if (iRepairing) {
            iRepairing = Repair(aRepairable);
        }

        // The above code may result in audio being pushed into iOutput.
        // If that's the case, aRepairable was incorporated into messages to be
        // output, so don't want to enter the code blocks below.
        if (!iRepairing && iOutput.size() == 0) {
            const TInt16 diff = static_cast<TUint16>(aRepairable.Frame()) - iFrame;
            if (diff == 1) {
                iFrame++;
                iOutput.push_back(&aRepairable);
            }
            else if (diff < 1) {
                if (!aRepairable.Resend()) {
                    // A frame in the past that is not a resend implies that the sender has reset their frame count
                    aRepairable.Destroy();
                    // accept the next received frame as the start of a new stream
                    iRunning = false;
                    THROW(RepairerStreamRestarted);
                }
                aRepairable.Destroy();
            }
            else {
                iRepairing = RepairBegin(aRepairable);
            }
        }
    }

    // Must NOT hold iMutexTransport while calling iAudioSupply.OutputAudio()
    // in case this class receives an interrupt of some form (such as DropAudio()).
    if (iOutput.size() > 0) {
        for (auto* repairable : iOutput) {
            iAudioSupply.OutputAudio(repairable->Data());
            repairable->Destroy();
        }
        iOutput.clear();
    }
}

template <TUint MaxFrames> void Repairer<MaxFrames>::DropAudio()
{
    AutoMutex a(iMutexTransport);
    RepairReset();
}

template <TUint MaxFrames> TBool Repairer<MaxFrames>::RepairBegin(IRepairable& aRepairable)
{
    LOG(kMedia, "Repairer::RepairBegin BEGIN ON %d\n", aRepairable.Frame());
    iRepairFirst = &aRepairable;
    iTimer.Start(MakeFunctor(*this, &Repairer<MaxFrames>::TimerRepairExpired), iEnv.Random(kInitialRepairTimeoutMs));
    return true;
}

template <TUint MaxFrames> void Repairer<MaxFrames>::RepairReset()
{
    LOG(kMedia, "Repairer::RepairReset RESET\n");
    /* TimerRepairExpired() claims iMutexTransport.  Release it briefly to avoid possible deadlock.
    TimerManager guarantees that TimerRepairExpired() won't be called once Cancel() returns... */
    iMutexTransport.Signal();
    iTimer.Cancel();
    iMutexTransport.Wait();
    if (iRepairFirst != nullptr) {
        iRepairFirst->Destroy();
        iRepairFirst = nullptr;
    }
    for (TUint i=0; i<iRepairFrames.size(); i++) {
        iRepairFrames[i]->Destroy();
    }
    iRepairFrames.clear();
    iRunning = false;
    iRepairing = false;
}

template <TUint MaxFrames> TBool Repairer<MaxFrames>::Repair(IRepairable& aRepairable)
{
    // get the incoming frame number
    const TUint16 frame = static_cast<TUint16>(aRepairable.Frame());
    LOG(kMedia, "Repairer::Repair GOT %d\n", frame);

    // get difference between this and the last frame sent down the pipeline
    TInt16 diff = frame - iFrame;
    if (diff < 1) {
        TBool repairing = true;
        if (!aRepairable.Resend()) {
            // A frame in the past that is not a resend implies that the sender has reset their frame count
            RepairReset();
            repairing = false;
            aRepairable.Destroy();
            THROW(RepairerStreamRestarted);
        }
        // incoming frames is equal to or earlier than the last frame sent down the pipeline
        // in other words, it's a duplicate, so discard it and continue
        aRepairable.Destroy();
        return repairing;
    }
    if (diff == 1) {
        // incoming frame is one greater than the last frame sent down the pipeline, so send this ...
        iFrame++;
        iOutput.push_back(&aRepairable);
        // ... and see if the current first waiting frame is now also ready to be sent
        while (static_cast<TUint16>(iRepairFirst->Frame()) == static_cast<TUint16>(iFrame + 1)) {
            // ... yes, it is, so send it
            iFrame++;
            iOutput.push_back(iRepairFirst);
            // ... and see if there are further messages waiting
            if (iRepairFrames.size() == 0) {
                // ... no, so we have completed the repair
                iRepairFirst = nullptr;
                LOG(kMedia, "END\n");
                return false;
            }
            // ... yes, so update the current first waiting frame and continue testing to see if this can also be sent
            iRepairFirst = iRepairFrames[0];
            iRepairFrames.erase(iRepairFrames.begin());
        }
        // ... we're done
        return true;
    }

    // Ok, its a frame that needs to be put into the backlog, but where?
    // compare it to the current first waiting frame
    diff = frame - static_cast<TUint16>(iRepairFirst->Frame());
    if (diff == 0) {
        // it's equal to the currently first waiting frame, so discard it - it's a duplicate
        aRepairable.Destroy();
        return true;
    }
    if (diff < 0) {
        // it's earlier than the current first waiting message, so it should become the new current first waiting frame
        // and the old first waiting frame needs to be injected into the start of the backlog, so inject it into the end
        // and rotate the others (if there is space to add another frame)
        if (iRepairFrames.size() == MaxFrames) {
            // can't fit another frame into the backlog
            RepairReset();
            aRepairable.Destroy();
            THROW(RepairerBufferFull);
        }
        iRepairFrames.insert(iRepairFrames.begin(), iRepairFirst);
        iRepairFirst = &aRepairable;
        return true;
    }
    // ok, it's after the currently first waiting frame, so it needs to go into the backlog
    // first check if the backlog is empty
    if (iRepairFrames.size() == 0) {
        // ... yes, so just inject it
        iRepairFrames.insert(iRepairFrames.begin(), &aRepairable);
        return true;
    }
    // ok, so the backlog is not empty
    // is it a duplicate of the last frame in the backlog?
    diff = frame - static_cast<TUint16>(iRepairFrames[iRepairFrames.size()-1]->Frame());
    if (diff == 0) {
        // ... yes, so discard
        aRepairable.Destroy();
        return true;
    }
    // is the incoming frame later than the last one currently in the backlog?
    if (diff > 0) {
        // ... yes, so, again, just inject it (if there is space)
        if (iRepairFrames.size() == MaxFrames) {
            // can't fit another frame into the backlog
            RepairReset();
            aRepairable.Destroy();
            THROW(RepairerBufferFull);
        }
        iRepairFrames.push_back(&aRepairable);
        return true;
    }
    // ... no, so it has to go somewhere in the middle of the backlog, so iterate through and inject it at the right place (if there is space)
    TUint count = iRepairFrames.size();
    for (auto it = iRepairFrames.begin(); it != iRepairFrames.end(); ++it) {
        diff = frame - static_cast<TUint16>((*it)->Frame());
        if (diff > 0) {
            continue;
        }
        if (diff == 0) {
            aRepairable.Destroy();
        }
        else {
            if (count == MaxFrames) {
                // can't fit another frame into the backlog
                aRepairable.Destroy();
                RepairReset();
                THROW(RepairerBufferFull);
            }
            iRepairFrames.insert(it, &aRepairable);
        }
        break;
    }

    return true;
}

template <TUint MaxFrames> void Repairer<MaxFrames>::TimerRepairExpired()
{
    AutoMutex a(iMutexTransport);
    if (iRepairing) {
        LOG(kMedia, ">Repairer::TimerRepairExpired REQUEST RESEND");

        TUint rangeCount = 0;
        TUint16 start = iFrame + 1;
        TUint16 end = static_cast<TUint16>(iRepairFirst->Frame());

        // phase 1 - request the frames between the last sent down the pipeline and the first waiting frame
        ResendRange* range = iFifoResend.Read();
        range->Set(start, end-1);
        iResend.push_back(range);
        iResendConst.push_back(range);
        rangeCount++;


        // phase 2 - if there is room add the missing frames in the backlog
        for (TUint i=0; rangeCount < kMaxMissedRanges && i < iRepairFrames.size(); i++) {
            IRepairable* repairable = iRepairFrames[i];
            start = end + 1;
            end = static_cast<TUint16>(repairable->Frame());

            if (end-start > 0) {
                ResendRange* range = iFifoResend.Read();
                range->Set(start, end-1);
                iResend.push_back(range);
                iResendConst.push_back(range);

                LOG(kMedia, " %d-%d", start, end);
                if (++rangeCount == kMaxMissedRanges) {
                    break;
                }
            }

        }
        LOG(kMedia, "\n");

        iResendRequester.RequestResendSequences(iResendConst);

        for (auto repairable : iResend) {
            repairable->Set(0, 0);
            iFifoResend.Write(repairable);
        }
        iResend.clear();
        iResendConst.clear();

        iTimer.Start(MakeFunctor(*this, &Repairer<MaxFrames>::TimerRepairExpired), kSubsequentRepairTimeoutMs);
    }
}

class IVolumeScalerEnabler;

// NOTE: there are three channels to monitor:
// - Audio
// - Control
// - Timing
// However, the timing channel was never monitored in the previous codebase,
// so no RaopTiming class exists here.
class ProtocolRaop : public Media::Protocol, public IRaopResendReceiver, public IAudioSupply
{
private:
    static const TUint kSampleRate = 44100;     // Always 44.1KHz. Can get this from fmtp field.
    static const TUint kMaxFrameBytes = 2048;
    static const TUint kMaxRepairFrames = 50;
public:
    ProtocolRaop(Environment& aEnv, Media::TrackFactory& aTrackFactory, IVolumeScalerEnabler& aVolume, IRaopDiscovery& aDiscovery, UdpServerManager& aServerManager, TUint aAudioId, TUint aControlId);
    ~ProtocolRaop();
    TUint SendFlush(TUint aSeq, TUint aTime);
private: // from Protocol
    void Interrupt(TBool aInterrupt) override;
    void Initialise(Media::MsgFactory& aMsgFactory, Media::IPipelineElementDownstream& aDownstream) override;
    Media::ProtocolStreamResult Stream(const Brx& aUri) override;
    Media::ProtocolGetResult Get(IWriter& aWriter, const Brx& aUri, TUint64 aOffset, TUint aBytes) override;
private: // from IStreamHandler
    TUint TryStop(TUint aStreamId) override;
    void NotifyStarving(const Brx& aMode, TUint aStreamId, TBool aStarving) override;
private: // from IRaopResendReceiver
    void ResendReceive(const RaopPacketAudio& aPacket) override;
private: // from IAudioSupply
    void OutputAudio(const Brx& aAudio) override;
private:
    void Reset();
    void Start();
    void StartStream();
    void UpdateSessionId(TUint aSessionId);
    TBool IsValidSession(TUint aSessionId) const;
    TBool ShouldFlush(TUint aSeq, TUint aTimestamp) const;
    //void OutputAudio(const Brx& aAudio);
    void OutputDiscontinuity();
    void OutputContainer(const Brx& aFmtp);
    void DoInterrupt();
    void WaitForDrain();
    void InputChanged();
    void ResendTimerFired();
    static TUint Delay(TUint aSamples);
private:
    Media::TrackFactory& iTrackFactory;
    TBool iVolumeEnabled;
    IVolumeScalerEnabler& iVolume;
    IRaopDiscovery& iDiscovery;
    UdpServerManager& iServerManager;
    Bws<RtpPacketRaop::kMaxPacketBytes> iPacketBuf;
    Bws<RtpPacketRaop::kMaxPacketBytes> iAudioDecrypted;
    RaopAudioDecryptor iAudioDecryptor;
    RaopAudioServer iAudioServer;
    RaopControlServer iControlServer;
    Media::SupplyAggregatorBytes* iSupply;
    Uri iUri;

    TUint iSessionId;
    TUint iStreamId;
    TUint iLatency;
    TUint iFlushSeq;
    TUint iFlushTime;
    TUint iNextFlushId;
    TBool iActive;
    TBool iWaiting;
    TBool iResumePending;
    TBool iStopped;
    TBool iInterrupted;
    TBool iDiscontinuity;
    mutable Mutex iLockRaop;
    Semaphore iSemDrain;

    // +3 as must be able to cause repairer to overflow (which requires kMaxRepairFrames+2), plus could be sending from normal audio channel and control channel simultaneously.
    RaopRepairableAllocator<kMaxRepairFrames+3,kMaxFrameBytes> iRepairableAllocator;
    RaopResendRangeRequester iResendRangeRequester;
    RepairerTimer iRepairerTimer;
    Repairer<kMaxRepairFrames> iRepairer;
};

};  // namespace Av
};  // namespace OpenHome

