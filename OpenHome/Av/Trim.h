#pragma once

#include <OpenHome/Buffer.h>
#include <OpenHome/Types.h>
#include <OpenHome/Exception.h>
#include <OpenHome/Private/Standard.h>

#include <functional>
#include <vector>

EXCEPTION(TrimChannelInvalid);
EXCEPTION(TrimOutOfRange);

namespace OpenHome {
namespace Av {

/**
 * Interface that allows implementors to visit each trim in a collection, in
 * turn.
 */
class ITrimVisitor
{
public:
    virtual void Visit(const Brx& aChannel, TInt aMinBinaryMilliDb, TInt aMaxBinaryMilliDb, TInt aTrimBinaryMilliDb) = 0;
    virtual ~ITrimVisitor() {}
};

/**
 * Interface that provides access to a collection of trims.
 */
class ITrimVisitable
{
public:
    virtual void AcceptTrimVisitor(ITrimVisitor& aVisitor) = 0;
    virtual ~ITrimVisitable() {}
};

/**
 * Interface that allows implementors to be notified when a collection of
 * trims changes.
 */
class ITrimObserver
{
public:
    virtual void TrimsChanged(ITrimVisitable& aVisitable) = 0;
    virtual ~ITrimObserver() {}
};

class ITrim
{
public:
    virtual TUint TrimChannelCount() const = 0;
    /*
     * THROWS:
     *      TrimChannelInvalid,
     *      TrimOutOfRange
     */
    virtual void SetTrim(const Brx& aChannel, TInt aTrimBinaryMilliDb) = 0;
    /*
     * THROWS:
     *      TrimChannelInvalid
     */
    virtual TInt GetTrim(const Brx& aChannel) = 0;
    /*
     * Interface that provides notification to registered observers when a
     * collection of trims changes.
     *
     * Should perform immediate callback on the observer to share current state.
     */
    virtual void AddTrimObserver(ITrimObserver& aObserver) = 0;
    virtual ~ITrim() {}
};

} // namespace Av
} // namespace OpenHome
