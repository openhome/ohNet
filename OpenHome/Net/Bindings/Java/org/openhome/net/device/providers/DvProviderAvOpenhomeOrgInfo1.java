package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgInfo1
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
     * Set the value of the DetailsCount property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyDetailsCount(long aValue);

    /**
     * Get a copy of the value of the DetailsCount property
     *
     * @return value of the DetailsCount property.
     */
    public long getPropertyDetailsCount();

    /**
     * Set the value of the MetatextCount property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyMetatextCount(long aValue);

    /**
     * Get a copy of the value of the MetatextCount property
     *
     * @return value of the MetatextCount property.
     */
    public long getPropertyMetatextCount();

    /**
     * Set the value of the Uri property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyUri(String aValue);

    /**
     * Get a copy of the value of the Uri property
     *
     * @return value of the Uri property.
     */
    public String getPropertyUri();

    /**
     * Set the value of the Metadata property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyMetadata(String aValue);

    /**
     * Get a copy of the value of the Metadata property
     *
     * @return value of the Metadata property.
     */
    public String getPropertyMetadata();

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
     * Set the value of the BitRate property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyBitRate(long aValue);

    /**
     * Get a copy of the value of the BitRate property
     *
     * @return value of the BitRate property.
     */
    public long getPropertyBitRate();

    /**
     * Set the value of the BitDepth property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyBitDepth(long aValue);

    /**
     * Get a copy of the value of the BitDepth property
     *
     * @return value of the BitDepth property.
     */
    public long getPropertyBitDepth();

    /**
     * Set the value of the SampleRate property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySampleRate(long aValue);

    /**
     * Get a copy of the value of the SampleRate property
     *
     * @return value of the SampleRate property.
     */
    public long getPropertySampleRate();

    /**
     * Set the value of the Lossless property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyLossless(boolean aValue);

    /**
     * Get a copy of the value of the Lossless property
     *
     * @return value of the Lossless property.
     */
    public boolean getPropertyLossless();

    /**
     * Set the value of the CodecName property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyCodecName(String aValue);

    /**
     * Get a copy of the value of the CodecName property
     *
     * @return value of the CodecName property.
     */
    public String getPropertyCodecName();

    /**
     * Set the value of the Metatext property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyMetatext(String aValue);

    /**
     * Get a copy of the value of the Metatext property
     *
     * @return value of the Metatext property.
     */
    public String getPropertyMetatext();
        
}

/**
 * Provider for the av.openhome.org:Info:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgInfo1 extends DvProvider implements IDvProviderAvOpenhomeOrgInfo1
{

    public class Counters
    {
        private long iTrackCount;
        private long iDetailsCount;
        private long iMetatextCount;

        public Counters(
            long aTrackCount,
            long aDetailsCount,
            long aMetatextCount
        )
        {
            iTrackCount = aTrackCount;
            iDetailsCount = aDetailsCount;
            iMetatextCount = aMetatextCount;
        }
        public long getTrackCount()
        {
            return iTrackCount;
        }
        public long getDetailsCount()
        {
            return iDetailsCount;
        }
        public long getMetatextCount()
        {
            return iMetatextCount;
        }
    }

    public class Track
    {
        private String iUri;
        private String iMetadata;

        public Track(
            String aUri,
            String aMetadata
        )
        {
            iUri = aUri;
            iMetadata = aMetadata;
        }
        public String getUri()
        {
            return iUri;
        }
        public String getMetadata()
        {
            return iMetadata;
        }
    }

    public class Details
    {
        private long iDuration;
        private long iBitRate;
        private long iBitDepth;
        private long iSampleRate;
        private boolean iLossless;
        private String iCodecName;

        public Details(
            long aDuration,
            long aBitRate,
            long aBitDepth,
            long aSampleRate,
            boolean aLossless,
            String aCodecName
        )
        {
            iDuration = aDuration;
            iBitRate = aBitRate;
            iBitDepth = aBitDepth;
            iSampleRate = aSampleRate;
            iLossless = aLossless;
            iCodecName = aCodecName;
        }
        public long getDuration()
        {
            return iDuration;
        }
        public long getBitRate()
        {
            return iBitRate;
        }
        public long getBitDepth()
        {
            return iBitDepth;
        }
        public long getSampleRate()
        {
            return iSampleRate;
        }
        public boolean getLossless()
        {
            return iLossless;
        }
        public String getCodecName()
        {
            return iCodecName;
        }
    }

    private IDvInvocationListener iDelegateCounters;
    private IDvInvocationListener iDelegateTrack;
    private IDvInvocationListener iDelegateDetails;
    private IDvInvocationListener iDelegateMetatext;
    private PropertyUint iPropertyTrackCount;
    private PropertyUint iPropertyDetailsCount;
    private PropertyUint iPropertyMetatextCount;
    private PropertyString iPropertyUri;
    private PropertyString iPropertyMetadata;
    private PropertyUint iPropertyDuration;
    private PropertyUint iPropertyBitRate;
    private PropertyUint iPropertyBitDepth;
    private PropertyUint iPropertySampleRate;
    private PropertyBool iPropertyLossless;
    private PropertyString iPropertyCodecName;
    private PropertyString iPropertyMetatext;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgInfo1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "Info", 1);
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
     * Enable the DetailsCount property.
     */
    public void enablePropertyDetailsCount()
    {
        iPropertyDetailsCount = new PropertyUint(new ParameterUint("DetailsCount"));
        addProperty(iPropertyDetailsCount);
    }

    /**
     * Enable the MetatextCount property.
     */
    public void enablePropertyMetatextCount()
    {
        iPropertyMetatextCount = new PropertyUint(new ParameterUint("MetatextCount"));
        addProperty(iPropertyMetatextCount);
    }

    /**
     * Enable the Uri property.
     */
    public void enablePropertyUri()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyUri = new PropertyString(new ParameterString("Uri", allowedValues));
        addProperty(iPropertyUri);
    }

    /**
     * Enable the Metadata property.
     */
    public void enablePropertyMetadata()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyMetadata = new PropertyString(new ParameterString("Metadata", allowedValues));
        addProperty(iPropertyMetadata);
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
     * Enable the BitRate property.
     */
    public void enablePropertyBitRate()
    {
        iPropertyBitRate = new PropertyUint(new ParameterUint("BitRate"));
        addProperty(iPropertyBitRate);
    }

    /**
     * Enable the BitDepth property.
     */
    public void enablePropertyBitDepth()
    {
        iPropertyBitDepth = new PropertyUint(new ParameterUint("BitDepth"));
        addProperty(iPropertyBitDepth);
    }

    /**
     * Enable the SampleRate property.
     */
    public void enablePropertySampleRate()
    {
        iPropertySampleRate = new PropertyUint(new ParameterUint("SampleRate"));
        addProperty(iPropertySampleRate);
    }

    /**
     * Enable the Lossless property.
     */
    public void enablePropertyLossless()
    {
        iPropertyLossless = new PropertyBool(new ParameterBool("Lossless"));
        addProperty(iPropertyLossless);
    }

    /**
     * Enable the CodecName property.
     */
    public void enablePropertyCodecName()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyCodecName = new PropertyString(new ParameterString("CodecName", allowedValues));
        addProperty(iPropertyCodecName);
    }

    /**
     * Enable the Metatext property.
     */
    public void enablePropertyMetatext()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyMetatext = new PropertyString(new ParameterString("Metatext", allowedValues));
        addProperty(iPropertyMetatext);
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
     * Set the value of the DetailsCount property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyDetailsCount(long aValue)
    {
        return setPropertyUint(iPropertyDetailsCount, aValue);
    }

    /**
     * Get a copy of the value of the DetailsCount property
     *
     * @return  value of the DetailsCount property.
     */
    public long getPropertyDetailsCount()
    {
        return iPropertyDetailsCount.getValue();
    }

    /**
     * Set the value of the MetatextCount property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyMetatextCount(long aValue)
    {
        return setPropertyUint(iPropertyMetatextCount, aValue);
    }

    /**
     * Get a copy of the value of the MetatextCount property
     *
     * @return  value of the MetatextCount property.
     */
    public long getPropertyMetatextCount()
    {
        return iPropertyMetatextCount.getValue();
    }

    /**
     * Set the value of the Uri property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyUri(String aValue)
    {
        return setPropertyString(iPropertyUri, aValue);
    }

    /**
     * Get a copy of the value of the Uri property
     *
     * @return  value of the Uri property.
     */
    public String getPropertyUri()
    {
        return iPropertyUri.getValue();
    }

    /**
     * Set the value of the Metadata property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyMetadata(String aValue)
    {
        return setPropertyString(iPropertyMetadata, aValue);
    }

    /**
     * Get a copy of the value of the Metadata property
     *
     * @return  value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        return iPropertyMetadata.getValue();
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
     * Set the value of the BitRate property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyBitRate(long aValue)
    {
        return setPropertyUint(iPropertyBitRate, aValue);
    }

    /**
     * Get a copy of the value of the BitRate property
     *
     * @return  value of the BitRate property.
     */
    public long getPropertyBitRate()
    {
        return iPropertyBitRate.getValue();
    }

    /**
     * Set the value of the BitDepth property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyBitDepth(long aValue)
    {
        return setPropertyUint(iPropertyBitDepth, aValue);
    }

    /**
     * Get a copy of the value of the BitDepth property
     *
     * @return  value of the BitDepth property.
     */
    public long getPropertyBitDepth()
    {
        return iPropertyBitDepth.getValue();
    }

    /**
     * Set the value of the SampleRate property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySampleRate(long aValue)
    {
        return setPropertyUint(iPropertySampleRate, aValue);
    }

    /**
     * Get a copy of the value of the SampleRate property
     *
     * @return  value of the SampleRate property.
     */
    public long getPropertySampleRate()
    {
        return iPropertySampleRate.getValue();
    }

    /**
     * Set the value of the Lossless property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyLossless(boolean aValue)
    {
        return setPropertyBool(iPropertyLossless, aValue);
    }

    /**
     * Get a copy of the value of the Lossless property
     *
     * @return  value of the Lossless property.
     */
    public boolean getPropertyLossless()
    {
        return iPropertyLossless.getValue();
    }

    /**
     * Set the value of the CodecName property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyCodecName(String aValue)
    {
        return setPropertyString(iPropertyCodecName, aValue);
    }

    /**
     * Get a copy of the value of the CodecName property
     *
     * @return  value of the CodecName property.
     */
    public String getPropertyCodecName()
    {
        return iPropertyCodecName.getValue();
    }

    /**
     * Set the value of the Metatext property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyMetatext(String aValue)
    {
        return setPropertyString(iPropertyMetatext, aValue);
    }

    /**
     * Get a copy of the value of the Metatext property
     *
     * @return  value of the Metatext property.
     */
    public String getPropertyMetatext()
    {
        return iPropertyMetatext.getValue();
    }

    /**
     * Signal that the action Counters is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Counters must be overridden if this is called.
     */      
    protected void enableActionCounters()
    {
        Action action = new Action("Counters");
        action.addOutputParameter(new ParameterRelated("TrackCount", iPropertyTrackCount));
        action.addOutputParameter(new ParameterRelated("DetailsCount", iPropertyDetailsCount));
        action.addOutputParameter(new ParameterRelated("MetatextCount", iPropertyMetatextCount));
        iDelegateCounters = new DoCounters();
        enableAction(action, iDelegateCounters);
    }

    /**
     * Signal that the action Track is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Track must be overridden if this is called.
     */      
    protected void enableActionTrack()
    {
        Action action = new Action("Track");
        action.addOutputParameter(new ParameterRelated("Uri", iPropertyUri));
        action.addOutputParameter(new ParameterRelated("Metadata", iPropertyMetadata));
        iDelegateTrack = new DoTrack();
        enableAction(action, iDelegateTrack);
    }

    /**
     * Signal that the action Details is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Details must be overridden if this is called.
     */      
    protected void enableActionDetails()
    {
        Action action = new Action("Details");
        action.addOutputParameter(new ParameterRelated("Duration", iPropertyDuration));
        action.addOutputParameter(new ParameterRelated("BitRate", iPropertyBitRate));
        action.addOutputParameter(new ParameterRelated("BitDepth", iPropertyBitDepth));
        action.addOutputParameter(new ParameterRelated("SampleRate", iPropertySampleRate));
        action.addOutputParameter(new ParameterRelated("Lossless", iPropertyLossless));
        action.addOutputParameter(new ParameterRelated("CodecName", iPropertyCodecName));
        iDelegateDetails = new DoDetails();
        enableAction(action, iDelegateDetails);
    }

    /**
     * Signal that the action Metatext is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Metatext must be overridden if this is called.
     */      
    protected void enableActionMetatext()
    {
        Action action = new Action("Metatext");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyMetatext));
        iDelegateMetatext = new DoMetatext();
        enableAction(action, iDelegateMetatext);
    }

    /**
     * Counters action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Counters action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionCounters} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Counters counters(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Track action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Track action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionTrack} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Track track(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Details action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Details action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionDetails} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Details details(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Metatext action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Metatext action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionMetatext} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String metatext(IDvInvocation aInvocation)
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


    private class DoCounters implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long trackCount;
            long detailsCount;
            long metatextCount;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Counters outArgs = counters(invocation);
            trackCount = outArgs.getTrackCount();
            detailsCount = outArgs.getDetailsCount();
            metatextCount = outArgs.getMetatextCount();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Counters");
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
                invocation.writeUint("DetailsCount", detailsCount);
                invocation.writeUint("MetatextCount", metatextCount);
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

    private class DoTrack implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String uri;
            String metadata;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Track outArgs = track(invocation);
            uri = outArgs.getUri();
            metadata = outArgs.getMetadata();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Track");
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
                invocation.writeString("Uri", uri);
                invocation.writeString("Metadata", metadata);
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

    private class DoDetails implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long duration;
            long bitRate;
            long bitDepth;
            long sampleRate;
            boolean lossless;
            String codecName;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Details outArgs = details(invocation);
            duration = outArgs.getDuration();
            bitRate = outArgs.getBitRate();
            bitDepth = outArgs.getBitDepth();
            sampleRate = outArgs.getSampleRate();
            lossless = outArgs.getLossless();
            codecName = outArgs.getCodecName();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Details");
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
                invocation.writeUint("Duration", duration);
                invocation.writeUint("BitRate", bitRate);
                invocation.writeUint("BitDepth", bitDepth);
                invocation.writeUint("SampleRate", sampleRate);
                invocation.writeBool("Lossless", lossless);
                invocation.writeString("CodecName", codecName);
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

    private class DoMetatext implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = metatext(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Metatext");
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
                invocation.writeString("Value", value);
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

