package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgInfo1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgInfo1 extends ICpProxy
{
    public Counters syncCounters();
    public void beginCounters(ICpProxyListener aCallback);
    public Counters endCounters(long aAsyncHandle);
    public Track syncTrack();
    public void beginTrack(ICpProxyListener aCallback);
    public Track endTrack(long aAsyncHandle);
    public Details syncDetails();
    public void beginDetails(ICpProxyListener aCallback);
    public Details endDetails(long aAsyncHandle);
    public String syncMetatext();
    public void beginMetatext(ICpProxyListener aCallback);
    public String endMetatext(long aAsyncHandle);
    public void setPropertyTrackCountChanged(IPropertyChangeListener aTrackCountChanged);
    public long getPropertyTrackCount();
    public void setPropertyDetailsCountChanged(IPropertyChangeListener aDetailsCountChanged);
    public long getPropertyDetailsCount();
    public void setPropertyMetatextCountChanged(IPropertyChangeListener aMetatextCountChanged);
    public long getPropertyMetatextCount();
    public void setPropertyUriChanged(IPropertyChangeListener aUriChanged);
    public String getPropertyUri();
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged);
    public String getPropertyMetadata();
    public void setPropertyDurationChanged(IPropertyChangeListener aDurationChanged);
    public long getPropertyDuration();
    public void setPropertyBitRateChanged(IPropertyChangeListener aBitRateChanged);
    public long getPropertyBitRate();
    public void setPropertyBitDepthChanged(IPropertyChangeListener aBitDepthChanged);
    public long getPropertyBitDepth();
    public void setPropertySampleRateChanged(IPropertyChangeListener aSampleRateChanged);
    public long getPropertySampleRate();
    public void setPropertyLosslessChanged(IPropertyChangeListener aLosslessChanged);
    public boolean getPropertyLossless();
    public void setPropertyCodecNameChanged(IPropertyChangeListener aCodecNameChanged);
    public String getPropertyCodecName();
    public void setPropertyMetatextChanged(IPropertyChangeListener aMetatextChanged);
    public String getPropertyMetatext();
}

class SyncCountersAvOpenhomeOrgInfo1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgInfo1 iService;
    private long iTrackCount;
    private long iDetailsCount;
    private long iMetatextCount;

    public SyncCountersAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        Counters result = iService.endCounters(aAsyncHandle);
        
        iTrackCount = result.getTrackCount();
        iDetailsCount = result.getDetailsCount();
        iMetatextCount = result.getMetatextCount();
    }
}

class SyncTrackAvOpenhomeOrgInfo1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgInfo1 iService;
    private String iUri;
    private String iMetadata;

    public SyncTrackAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
    {
        iService = aProxy;
    }
    public String getUri()
    {
        return iUri;
    }
    public String getMetadata()
    {
        return iMetadata;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Track result = iService.endTrack(aAsyncHandle);
        
        iUri = result.getUri();
        iMetadata = result.getMetadata();
    }
}

class SyncDetailsAvOpenhomeOrgInfo1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgInfo1 iService;
    private long iDuration;
    private long iBitRate;
    private long iBitDepth;
    private long iSampleRate;
    private boolean iLossless;
    private String iCodecName;

    public SyncDetailsAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        Details result = iService.endDetails(aAsyncHandle);
        
        iDuration = result.getDuration();
        iBitRate = result.getBitRate();
        iBitDepth = result.getBitDepth();
        iSampleRate = result.getSampleRate();
        iLossless = result.getLossless();
        iCodecName = result.getCodecName();
    }
}

class SyncMetatextAvOpenhomeOrgInfo1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgInfo1 iService;
    private String iValue;

    public SyncMetatextAvOpenhomeOrgInfo1(CpProxyAvOpenhomeOrgInfo1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endMetatext(aAsyncHandle);
        
        iValue = result;
    }
}

/**
 * Proxy for the av.openhome.org:Info:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgInfo1 extends CpProxy implements ICpProxyAvOpenhomeOrgInfo1
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

    private Action iActionCounters;
    private Action iActionTrack;
    private Action iActionDetails;
    private Action iActionMetatext;
    private PropertyUint iTrackCount;
    private PropertyUint iDetailsCount;
    private PropertyUint iMetatextCount;
    private PropertyString iUri;
    private PropertyString iMetadata;
    private PropertyUint iDuration;
    private PropertyUint iBitRate;
    private PropertyUint iBitDepth;
    private PropertyUint iSampleRate;
    private PropertyBool iLossless;
    private PropertyString iCodecName;
    private PropertyString iMetatext;
    private IPropertyChangeListener iTrackCountChanged;
    private IPropertyChangeListener iDetailsCountChanged;
    private IPropertyChangeListener iMetatextCountChanged;
    private IPropertyChangeListener iUriChanged;
    private IPropertyChangeListener iMetadataChanged;
    private IPropertyChangeListener iDurationChanged;
    private IPropertyChangeListener iBitRateChanged;
    private IPropertyChangeListener iBitDepthChanged;
    private IPropertyChangeListener iSampleRateChanged;
    private IPropertyChangeListener iLosslessChanged;
    private IPropertyChangeListener iCodecNameChanged;
    private IPropertyChangeListener iMetatextChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgInfo1(CpDevice aDevice)
    {
        super("av-openhome-org", "Info", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionCounters = new Action("Counters");
        param = new ParameterUint("TrackCount");
        iActionCounters.addOutputParameter(param);
        param = new ParameterUint("DetailsCount");
        iActionCounters.addOutputParameter(param);
        param = new ParameterUint("MetatextCount");
        iActionCounters.addOutputParameter(param);

        iActionTrack = new Action("Track");
        param = new ParameterString("Uri", allowedValues);
        iActionTrack.addOutputParameter(param);
        param = new ParameterString("Metadata", allowedValues);
        iActionTrack.addOutputParameter(param);

        iActionDetails = new Action("Details");
        param = new ParameterUint("Duration");
        iActionDetails.addOutputParameter(param);
        param = new ParameterUint("BitRate");
        iActionDetails.addOutputParameter(param);
        param = new ParameterUint("BitDepth");
        iActionDetails.addOutputParameter(param);
        param = new ParameterUint("SampleRate");
        iActionDetails.addOutputParameter(param);
        param = new ParameterBool("Lossless");
        iActionDetails.addOutputParameter(param);
        param = new ParameterString("CodecName", allowedValues);
        iActionDetails.addOutputParameter(param);

        iActionMetatext = new Action("Metatext");
        param = new ParameterString("Value", allowedValues);
        iActionMetatext.addOutputParameter(param);

        iTrackCountChanged = new PropertyChangeListener();
        iTrackCount = new PropertyUint("TrackCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    trackCountPropertyChanged();
                }
            }
        );
        addProperty(iTrackCount);
        iDetailsCountChanged = new PropertyChangeListener();
        iDetailsCount = new PropertyUint("DetailsCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    detailsCountPropertyChanged();
                }
            }
        );
        addProperty(iDetailsCount);
        iMetatextCountChanged = new PropertyChangeListener();
        iMetatextCount = new PropertyUint("MetatextCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    metatextCountPropertyChanged();
                }
            }
        );
        addProperty(iMetatextCount);
        iUriChanged = new PropertyChangeListener();
        iUri = new PropertyString("Uri",
            new PropertyChangeListener() {
                public void notifyChange() {
                    uriPropertyChanged();
                }
            }
        );
        addProperty(iUri);
        iMetadataChanged = new PropertyChangeListener();
        iMetadata = new PropertyString("Metadata",
            new PropertyChangeListener() {
                public void notifyChange() {
                    metadataPropertyChanged();
                }
            }
        );
        addProperty(iMetadata);
        iDurationChanged = new PropertyChangeListener();
        iDuration = new PropertyUint("Duration",
            new PropertyChangeListener() {
                public void notifyChange() {
                    durationPropertyChanged();
                }
            }
        );
        addProperty(iDuration);
        iBitRateChanged = new PropertyChangeListener();
        iBitRate = new PropertyUint("BitRate",
            new PropertyChangeListener() {
                public void notifyChange() {
                    bitRatePropertyChanged();
                }
            }
        );
        addProperty(iBitRate);
        iBitDepthChanged = new PropertyChangeListener();
        iBitDepth = new PropertyUint("BitDepth",
            new PropertyChangeListener() {
                public void notifyChange() {
                    bitDepthPropertyChanged();
                }
            }
        );
        addProperty(iBitDepth);
        iSampleRateChanged = new PropertyChangeListener();
        iSampleRate = new PropertyUint("SampleRate",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sampleRatePropertyChanged();
                }
            }
        );
        addProperty(iSampleRate);
        iLosslessChanged = new PropertyChangeListener();
        iLossless = new PropertyBool("Lossless",
            new PropertyChangeListener() {
                public void notifyChange() {
                    losslessPropertyChanged();
                }
            }
        );
        addProperty(iLossless);
        iCodecNameChanged = new PropertyChangeListener();
        iCodecName = new PropertyString("CodecName",
            new PropertyChangeListener() {
                public void notifyChange() {
                    codecNamePropertyChanged();
                }
            }
        );
        addProperty(iCodecName);
        iMetatextChanged = new PropertyChangeListener();
        iMetatext = new PropertyString("Metatext",
            new PropertyChangeListener() {
                public void notifyChange() {
                    metatextPropertyChanged();
                }
            }
        );
        addProperty(iMetatext);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Counters syncCounters()
    {
        SyncCountersAvOpenhomeOrgInfo1 sync = new SyncCountersAvOpenhomeOrgInfo1(this);
        beginCounters(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Counters(
            sync.getTrackCount(),
            sync.getDetailsCount(),
            sync.getMetatextCount()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endCounters}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginCounters(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionCounters, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionCounters.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionCounters.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionCounters.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginCounters} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginCounters} method.
     * @return the result of the previously invoked action.
     */
    public Counters endCounters(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long trackCount = Invocation.getOutputUint(aAsyncHandle, index++);
        long detailsCount = Invocation.getOutputUint(aAsyncHandle, index++);
        long metatextCount = Invocation.getOutputUint(aAsyncHandle, index++);
        return new Counters(
            trackCount,
            detailsCount,
            metatextCount
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Track syncTrack()
    {
        SyncTrackAvOpenhomeOrgInfo1 sync = new SyncTrackAvOpenhomeOrgInfo1(this);
        beginTrack(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Track(
            sync.getUri(),
            sync.getMetadata()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endTrack}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginTrack(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionTrack, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionTrack.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionTrack.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginTrack} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginTrack} method.
     * @return the result of the previously invoked action.
     */
    public Track endTrack(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String uri = Invocation.getOutputString(aAsyncHandle, index++);
        String metadata = Invocation.getOutputString(aAsyncHandle, index++);
        return new Track(
            uri,
            metadata
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Details syncDetails()
    {
        SyncDetailsAvOpenhomeOrgInfo1 sync = new SyncDetailsAvOpenhomeOrgInfo1(this);
        beginDetails(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Details(
            sync.getDuration(),
            sync.getBitRate(),
            sync.getBitDepth(),
            sync.getSampleRate(),
            sync.getLossless(),
            sync.getCodecName()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endDetails}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginDetails(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionDetails, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionDetails.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionDetails.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionDetails.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionDetails.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionDetails.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionDetails.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginDetails} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginDetails} method.
     * @return the result of the previously invoked action.
     */
    public Details endDetails(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long duration = Invocation.getOutputUint(aAsyncHandle, index++);
        long bitRate = Invocation.getOutputUint(aAsyncHandle, index++);
        long bitDepth = Invocation.getOutputUint(aAsyncHandle, index++);
        long sampleRate = Invocation.getOutputUint(aAsyncHandle, index++);
        boolean lossless = Invocation.getOutputBool(aAsyncHandle, index++);
        String codecName = Invocation.getOutputString(aAsyncHandle, index++);
        return new Details(
            duration,
            bitRate,
            bitDepth,
            sampleRate,
            lossless,
            codecName
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncMetatext()
    {
        SyncMetatextAvOpenhomeOrgInfo1 sync = new SyncMetatextAvOpenhomeOrgInfo1(this);
        beginMetatext(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endMetatext}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginMetatext(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionMetatext, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionMetatext.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginMetatext} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginMetatext} method.
     * @return the result of the previously invoked action.
     */
    public String endMetatext(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String value = Invocation.getOutputString(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Set a delegate to be run when the TrackCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
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
     * Set a delegate to be run when the DetailsCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aDetailsCountChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyDetailsCountChanged(IPropertyChangeListener aDetailsCountChanged)
    {
        synchronized (iPropertyLock)
        {
            iDetailsCountChanged = aDetailsCountChanged;
        }
    }

    private void detailsCountPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iDetailsCountChanged);
        }
    }
    /**
     * Set a delegate to be run when the MetatextCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aMetatextCountChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyMetatextCountChanged(IPropertyChangeListener aMetatextCountChanged)
    {
        synchronized (iPropertyLock)
        {
            iMetatextCountChanged = aMetatextCountChanged;
        }
    }

    private void metatextCountPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iMetatextCountChanged);
        }
    }
    /**
     * Set a delegate to be run when the Uri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aUriChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyUriChanged(IPropertyChangeListener aUriChanged)
    {
        synchronized (iPropertyLock)
        {
            iUriChanged = aUriChanged;
        }
    }

    private void uriPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iUriChanged);
        }
    }
    /**
     * Set a delegate to be run when the Metadata state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aMetadataChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyMetadataChanged(IPropertyChangeListener aMetadataChanged)
    {
        synchronized (iPropertyLock)
        {
            iMetadataChanged = aMetadataChanged;
        }
    }

    private void metadataPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iMetadataChanged);
        }
    }
    /**
     * Set a delegate to be run when the Duration state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
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
     * Set a delegate to be run when the BitRate state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aBitRateChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyBitRateChanged(IPropertyChangeListener aBitRateChanged)
    {
        synchronized (iPropertyLock)
        {
            iBitRateChanged = aBitRateChanged;
        }
    }

    private void bitRatePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iBitRateChanged);
        }
    }
    /**
     * Set a delegate to be run when the BitDepth state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aBitDepthChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyBitDepthChanged(IPropertyChangeListener aBitDepthChanged)
    {
        synchronized (iPropertyLock)
        {
            iBitDepthChanged = aBitDepthChanged;
        }
    }

    private void bitDepthPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iBitDepthChanged);
        }
    }
    /**
     * Set a delegate to be run when the SampleRate state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aSampleRateChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySampleRateChanged(IPropertyChangeListener aSampleRateChanged)
    {
        synchronized (iPropertyLock)
        {
            iSampleRateChanged = aSampleRateChanged;
        }
    }

    private void sampleRatePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSampleRateChanged);
        }
    }
    /**
     * Set a delegate to be run when the Lossless state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aLosslessChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyLosslessChanged(IPropertyChangeListener aLosslessChanged)
    {
        synchronized (iPropertyLock)
        {
            iLosslessChanged = aLosslessChanged;
        }
    }

    private void losslessPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iLosslessChanged);
        }
    }
    /**
     * Set a delegate to be run when the CodecName state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aCodecNameChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyCodecNameChanged(IPropertyChangeListener aCodecNameChanged)
    {
        synchronized (iPropertyLock)
        {
            iCodecNameChanged = aCodecNameChanged;
        }
    }

    private void codecNamePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iCodecNameChanged);
        }
    }
    /**
     * Set a delegate to be run when the Metatext state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgInfo1 instance will not overlap.
     *
     * @param aMetatextChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyMetatextChanged(IPropertyChangeListener aMetatextChanged)
    {
        synchronized (iPropertyLock)
        {
            iMetatextChanged = aMetatextChanged;
        }
    }

    private void metatextPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iMetatextChanged);
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
     * Query the value of the DetailsCount property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the DetailsCount property.
     */
    public long getPropertyDetailsCount()
    {
        propertyReadLock();
        long val = iDetailsCount.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the MetatextCount property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the MetatextCount property.
     */
    public long getPropertyMetatextCount()
    {
        propertyReadLock();
        long val = iMetatextCount.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Uri property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Uri property.
     */
    public String getPropertyUri()
    {
        propertyReadLock();
        String val = iUri.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Metadata property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Metadata property.
     */
    public String getPropertyMetadata()
    {
        propertyReadLock();
        String val = iMetadata.getValue();
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
     * Query the value of the BitRate property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the BitRate property.
     */
    public long getPropertyBitRate()
    {
        propertyReadLock();
        long val = iBitRate.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the BitDepth property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the BitDepth property.
     */
    public long getPropertyBitDepth()
    {
        propertyReadLock();
        long val = iBitDepth.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the SampleRate property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SampleRate property.
     */
    public long getPropertySampleRate()
    {
        propertyReadLock();
        long val = iSampleRate.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Lossless property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Lossless property.
     */
    public boolean getPropertyLossless()
    {
        propertyReadLock();
        boolean val = iLossless.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the CodecName property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the CodecName property.
     */
    public String getPropertyCodecName()
    {
        propertyReadLock();
        String val = iCodecName.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Metatext property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Metatext property.
     */
    public String getPropertyMetatext()
    {
        propertyReadLock();
        String val = iMetatext.getValue();
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
            iActionCounters.destroy();
            iActionTrack.destroy();
            iActionDetails.destroy();
            iActionMetatext.destroy();
            iTrackCount.destroy();
            iDetailsCount.destroy();
            iMetatextCount.destroy();
            iUri.destroy();
            iMetadata.destroy();
            iDuration.destroy();
            iBitRate.destroy();
            iBitDepth.destroy();
            iSampleRate.destroy();
            iLossless.destroy();
            iCodecName.destroy();
            iMetatext.destroy();
        }
    }
}

