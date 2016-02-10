#pragma once

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>

#include <vector>

namespace OpenHome {
namespace Media {

class IMuteObserver
{
public:
    virtual void MuteChanged(TBool aValue) = 0;
    virtual ~IMuteObserver() { /*NOP*/ }
};

// element interface
class IMute
{
public:
    virtual void Mute() = 0;
    virtual void Unmute() = 0;
    virtual ~IMute() {}
};

class MuteClient : public IMute, private INonCopyable
{
public:
    MuteClient(IMute& aMute);
private: // from IMute
    void Mute() override;
    void Unmute() override;
private:
    IMute& iMute;
    Mutex iLock;
    TBool iMuted;
};

class MuteCounted : public IMute, public INonCopyable
{
public:
    MuteCounted(IMute& aMute);
private:  // from IMute
    void Mute() override;
    void Unmute() override;
private:
    IMute& iMute;
    Mutex iLock;
    TUint iCount;
};

} // namespace Media
} // namespace OpenHome

