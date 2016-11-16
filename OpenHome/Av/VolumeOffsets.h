#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>

#include <functional>
#include <vector>

EXCEPTION(ChannelInvalid);
EXCEPTION(VolumeOffsetOutOfRange);

namespace OpenHome {
namespace Av {

/**
 * Interface that allows implementors to visit each volume offset in a
 * collection, in turn.
 */
class IVolumeOffsetterVisitor
{
public:
    virtual void Visit(const Brx& aChannel, TInt aOffsetBinaryMilliDb) = 0;
    virtual ~IVolumeOffsetterVisitor() {}
};

/**
 * Interface that provides access to a collection of volume offsets.
 */
class IVolumeOffsetterVisitable
{
public:
    virtual void AcceptVolumeOffsetterVisitor(IVolumeOffsetterVisitor& aVisitor) = 0;
    virtual ~IVolumeOffsetterVisitable() {}
};

/**
 * Interface that allows implementors to be notified when a collection of
 * volume offsets changes.
 */
class IVolumeOffsetterObserver
{
public:
    virtual void VolumeOffsetsChanged(IVolumeOffsetterVisitable& aVisitable) = 0;
    virtual ~IVolumeOffsetterObserver() {}
};

///**
// * Interface that provides notification to registered observers when a
// * collection of volume offsets changes.
// *
// * Should perform immediate callback on the observer to share current state.
// */
//class IVolumeOffsetterObservable
//{
//public:
//    virtual void AddVolumeOffsetterObserver(IVolumeOffsetterObserver& aObserver) = 0;
//    virtual ~IVolumeOffsetterObservable() {}
//};

class IVolumeOffsetter
{
public:
    /*
     * THROWS:
     *      ChannelInvalid,
     *      VolumeOffsetOutOfRange
     */
    virtual void SetVolumeOffset(const Brx& aChannel, TInt aOffsetBinaryMilliDb) = 0;
    /*
     * THROWS:
     *      ChannelInvalid
     */
    virtual TInt GetVolumeOffset(const Brx& aChannel) = 0;
    /*
     * Interface that provides notification to registered observers when a
     * collection of volume offsets changes.
     *
     * Should perform immediate callback on the observer to share current state.
     */
    virtual void AddVolumeOffsetterObserver(IVolumeOffsetterObserver& aObserver) = 0;
    virtual ~IVolumeOffsetter() {}
};

} // namespace Av
} // namespace OpenHome
