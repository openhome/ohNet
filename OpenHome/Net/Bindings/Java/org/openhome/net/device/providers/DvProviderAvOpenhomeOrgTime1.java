package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgTime1
{

    /**
     * Set the value of the TrackCount property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyTrackCount(long aValue);

    /**
     * Get a copy of the value of the TrackCount property
     *
     * @return value of the TrackCount property.
     */
    public long getPropertyTrackCount();

    /**
     * Set the value of the Duration property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyDuration(long aValue);

    /**
     * Get a copy of the value of the Duration property
     *
     * @return value of the Duration property.
     */
    public long getPropertyDuration();

    /**
     * Set the value of the Seconds property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySeconds(long aValue);

    /**
     * Get a copy of the value of the Seconds property
     *
     * @return value of the Seconds property.
     */
    public long getPropertySeconds();
        
}

/**
 * Provider for the av.openhome.org:Time:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgTime1 extends DvProvider implements IDvProviderAvOpenhomeOrgTime1
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

    private IDvInvocationListener iDelegateTime;
    private PropertyUint iPropertyTrackCount;
    private PropertyUint iPropertyDuration;
    private PropertyUint iPropertySeconds;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgTime1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "Time", 1);
    }

    /**
     * Enable the TrackCount property.
     */
    public void enablePropertyTrackCount()
    {
        iPropertyTrackCount = new PropertyUint(new ParameterUint("TrackCount"));
        addProperty(iPropertyTrackCount);
    }

    /**
     * Enable the Duration property.
     */
    public void enablePropertyDuration()
    {
        iPropertyDuration = new PropertyUint(new ParameterUint("Duration"));
        addProperty(iPropertyDuration);
    }

    /**
     * Enable the Seconds property.
     */
    public void enablePropertySeconds()
    {
        iPropertySeconds = new PropertyUint(new ParameterUint("Seconds"));
        addProperty(iPropertySeconds);
    }

    /**
     * Set the value of the TrackCount property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyTrackCount(long aValue)
    {
        return setPropertyUint(iPropertyTrackCount, aValue);
    }

    /**
     * Get a copy of the value of the TrackCount property
     *
     * @return  value of the TrackCount property.
     */
    public long getPropertyTrackCount()
    {
        return iPropertyTrackCount.getValue();
    }

    /**
     * Set the value of the Duration property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyDuration(long aValue)
    {
        return setPropertyUint(iPropertyDuration, aValue);
    }

    /**
     * Get a copy of the value of the Duration property
     *
     * @return  value of the Duration property.
     */
    public long getPropertyDuration()
    {
        return iPropertyDuration.getValue();
    }

    /**
     * Set the value of the Seconds property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySeconds(long aValue)
    {
        return setPropertyUint(iPropertySeconds, aValue);
    }

    /**
     * Get a copy of the value of the Seconds property
     *
     * @return  value of the Seconds property.
     */
    public long getPropertySeconds()
    {
        return iPropertySeconds.getValue();
    }

    /**
     * Signal that the action Time is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Time must be overridden if this is called.
     */      
    protected void enableActionTime()
    {
        Action action = new Action("Time");
        action.addOutputParameter(new ParameterRelated("TrackCount", iPropertyTrackCount));
        action.addOutputParameter(new ParameterRelated("Duration", iPropertyDuration));
        action.addOutputParameter(new ParameterRelated("Seconds", iPropertySeconds));
        iDelegateTime = new DoTime();
        enableAction(action, iDelegateTime);
    }

    /**
     * Time action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Time action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionTime} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Time time(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Must be called for each class instance.  Must be called before Core.Library.Close().
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            super.dispose();
            iHandle = 0;
        }
    }


    private class DoTime implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long trackCount;
            long duration;
            long seconds;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Time outArgs = time(invocation);
            trackCount = outArgs.getTrackCount();
            duration = outArgs.getDuration();
            seconds = outArgs.getSeconds();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Time");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("TrackCount", trackCount);
                invocation.writeUint("Duration", duration);
                invocation.writeUint("Seconds", seconds);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }
}

