package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgTime1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgTime1 extends ICpProxy
{
    public Time syncTime();
    public void beginTime(ICpProxyListener aCallback);
    public Time endTime(long aAsyncHandle);
    public void setPropertyTrackCountChanged(IPropertyChangeListener aTrackCountChanged);
    public long getPropertyTrackCount();
    public void setPropertyDurationChanged(IPropertyChangeListener aDurationChanged);
    public long getPropertyDuration();
    public void setPropertySecondsChanged(IPropertyChangeListener aSecondsChanged);
    public long getPropertySeconds();
}

class SyncTimeAvOpenhomeOrgTime1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgTime1 iService;
    private long iTrackCount;
    private long iDuration;
    private long iSeconds;

    public SyncTimeAvOpenhomeOrgTime1(CpProxyAvOpenhomeOrgTime1 aProxy)
    {
        iService = aProxy;
    }
    public long getTrackCount()
    {
        return iTrackCount;
    }
    public long getDuration()
    {
        return iDuration;
    }
    public long getSeconds()
    {
        return iSeconds;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Time result = iService.endTime(aAsyncHandle);
        
        iTrackCount = result.getTrackCount();
        iDuration = result.getDuration();
        iSeconds = result.getSeconds();
    }
}

/**
 * Proxy for the av.openhome.org:Time:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgTime1 extends CpProxy implements ICpProxyAvOpenhomeOrgTime1
{

    public class Time
    {
        private long iTrackCount;
        private long iDuration;
        private long iSeconds;

        public Time(
            long aTrackCount,
            long aDuration,
            long aSeconds
        )
        {
            iTrackCount = aTrackCount;
            iDuration = aDuration;
            iSeconds = aSeconds;
        }
        public long getTrackCount()
        {
            return iTrackCount;
        }
        public long getDuration()
        {
            return iDuration;
        }
        public long getSeconds()
        {
            return iSeconds;
        }
    }

    private Action iActionTime;
    private PropertyUint iTrackCount;
    private PropertyUint iDuration;
    private PropertyUint iSeconds;
    private IPropertyChangeListener iTrackCountChanged;
    private IPropertyChangeListener iDurationChanged;
    private IPropertyChangeListener iSecondsChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgTime1(CpDevice aDevice)
    {
        super("av-openhome-org", "Time", 1, aDevice);
        Parameter param;
        

        iActionTime = new Action("Time");
        param = new ParameterUint("TrackCount");
        iActionTime.addOutputParameter(param);
        param = new ParameterUint("Duration");
        iActionTime.addOutputParameter(param);
        param = new ParameterUint("Seconds");
        iActionTime.addOutputParameter(param);

        iTrackCountChanged = new PropertyChangeListener();
        iTrackCount = new PropertyUint("TrackCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    trackCountPropertyChanged();
                }
            }
        );
        addProperty(iTrackCount);
        iDurationChanged = new PropertyChangeListener();
        iDuration = new PropertyUint("Duration",
            new PropertyChangeListener() {
                public void notifyChange() {
                    durationPropertyChanged();
                }
            }
        );
        addProperty(iDuration);
        iSecondsChanged = new PropertyChangeListener();
        iSeconds = new PropertyUint("Seconds",
            new PropertyChangeListener() {
                public void notifyChange() {
                    secondsPropertyChanged();
                }
            }
        );
        addProperty(iSeconds);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Time syncTime()
    {
        SyncTimeAvOpenhomeOrgTime1 sync = new SyncTimeAvOpenhomeOrgTime1(this);
        beginTime(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Time(
            sync.getTrackCount(),
            sync.getDuration(),
            sync.getSeconds()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endTime}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginTime(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionTime, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionTime.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionTime.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionTime.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginTime} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginTime} method.
     * @return the result of the previously invoked action.
     */
    public Time endTime(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long trackCount = Invocation.getOutputUint(aAsyncHandle, index++);
        long duration = Invocation.getOutputUint(aAsyncHandle, index++);
        long seconds = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Time(
            trackCount,
            duration,
            seconds
        );
    }
        
    /**
     * Set a delegate to be run when the TrackCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param aTrackCountChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyTrackCountChanged(IPropertyChangeListener aTrackCountChanged)
    {
        synchronized (iPropertyLock)
        {
            iTrackCountChanged = aTrackCountChanged;
        }
    }

    private void trackCountPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iTrackCountChanged);
        }
    }
    /**
     * Set a delegate to be run when the Duration state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param aDurationChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyDurationChanged(IPropertyChangeListener aDurationChanged)
    {
        synchronized (iPropertyLock)
        {
            iDurationChanged = aDurationChanged;
        }
    }

    private void durationPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iDurationChanged);
        }
    }
    /**
     * Set a delegate to be run when the Seconds state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgTime1 instance will not overlap.
     *
     * @param aSecondsChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySecondsChanged(IPropertyChangeListener aSecondsChanged)
    {
        synchronized (iPropertyLock)
        {
            iSecondsChanged = aSecondsChanged;
        }
    }

    private void secondsPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSecondsChanged);
        }
    }

    /**
     * Query the value of the TrackCount property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the TrackCount property.
     */
    public long getPropertyTrackCount()
    {
        propertyReadLock();
        long val = iTrackCount.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Duration property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Duration property.
     */
    public long getPropertyDuration()
    {
        propertyReadLock();
        long val = iDuration.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Seconds property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Seconds property.
     */
    public long getPropertySeconds()
    {
        propertyReadLock();
        long val = iSeconds.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.
     * Must be called before <tt>Library.close()</tt>.
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            disposeProxy();
            iHandle = 0;
            iActionTime.destroy();
            iTrackCount.destroy();
            iDuration.destroy();
            iSeconds.destroy();
        }
    }
}

