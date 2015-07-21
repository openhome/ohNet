#ifndef HEADER_PIPELINE_ELEMENT_EVENT
#define HEADER_PIPELINE_ELEMENT_EVENT

#include <OpenHome/Types.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/Standard.h>
#include <OpenHome/Functor.h>

#include <atomic>
#include <vector>

namespace OpenHome {
namespace Media {

/*
    Runs callbacks from any pipeline element in a dedicated thread.
    (i.e. Ensures callbacks don't block flow of pipeline msgs)
    Effect of calling Schedule while a previous callback is pending is slightly
    unpredictable - the callback is guaranteed to be called at least once.
*/

class IPipelineElementCallback
{
public:
    virtual ~IPipelineElementCallback() {}
    virtual void Schedule(TUint aId) = 0;
};

class IPipelineElementObserverThread
{
public:
    virtual ~IPipelineElementObserverThread() {}
    virtual TUint Register(Functor aCallback) = 0;
    virtual void Schedule(TUint aId) = 0;
};

class PipelineElementObserverThread : public IPipelineElementObserverThread, private INonCopyable
{
public:
    PipelineElementObserverThread(TUint aPriority);
    ~PipelineElementObserverThread();
private:
    void PipelineEventThread();
private: // from IPipelineElementObserverThread
    TUint Register(Functor aCallback) override;
    void Schedule(TUint aId) override;
private:
    class Callback : private INonCopyable
    {
    public:
        Callback(TUint aId, Functor aCallback);
        TUint Id() const { return iId; }
        void SetPending();
        void RunIfPending();
    private:
        TUint iId;
        Functor iCallback;
        std::atomic<bool> iPending;
    };
private:
    ThreadFunctor* iThread;
    Mutex iLock;
    std::vector<Callback*> iCallbacks;
    TUint iNextId;
};

// Test helper - supports a single callback and runs it synchronously, inside calls to Schedule()
class ElementObserverSync : public IPipelineElementObserverThread
{
    static const TUint kId;
private: // from IPipelineElementObserverThread
    TUint Register(Functor aCallback) override;
    void Schedule(TUint aId) override;
private:
    Functor iCallback;
};

} // namespace Media
} // namespace OpenHome

#endif // HEADER_PIPELINE_ELEMENT_EVENT
