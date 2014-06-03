package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyUpnpOrgConnectionManager1.*;
import org.openhome.net.core.*;

    
interface ICpProxyUpnpOrgConnectionManager1 extends ICpProxy
{
    public GetProtocolInfo syncGetProtocolInfo();
    public void beginGetProtocolInfo(ICpProxyListener aCallback);
    public GetProtocolInfo endGetProtocolInfo(long aAsyncHandle);
    public PrepareForConnection syncPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection);
    public void beginPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, ICpProxyListener aCallback);
    public PrepareForConnection endPrepareForConnection(long aAsyncHandle);
    public void syncConnectionComplete(int aConnectionID);
    public void beginConnectionComplete(int aConnectionID, ICpProxyListener aCallback);
    public void endConnectionComplete(long aAsyncHandle);
    public String syncGetCurrentConnectionIDs();
    public void beginGetCurrentConnectionIDs(ICpProxyListener aCallback);
    public String endGetCurrentConnectionIDs(long aAsyncHandle);
    public GetCurrentConnectionInfo syncGetCurrentConnectionInfo(int aConnectionID);
    public void beginGetCurrentConnectionInfo(int aConnectionID, ICpProxyListener aCallback);
    public GetCurrentConnectionInfo endGetCurrentConnectionInfo(long aAsyncHandle);
    public void setPropertySourceProtocolInfoChanged(IPropertyChangeListener aSourceProtocolInfoChanged);
    public String getPropertySourceProtocolInfo();
    public void setPropertySinkProtocolInfoChanged(IPropertyChangeListener aSinkProtocolInfoChanged);
    public String getPropertySinkProtocolInfo();
    public void setPropertyCurrentConnectionIDsChanged(IPropertyChangeListener aCurrentConnectionIDsChanged);
    public String getPropertyCurrentConnectionIDs();
}

class SyncGetProtocolInfoUpnpOrgConnectionManager1 extends SyncProxyAction
{
    private CpProxyUpnpOrgConnectionManager1 iService;
    private String iSource;
    private String iSink;

    public SyncGetProtocolInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
    {
        iService = aProxy;
    }
    public String getSource()
    {
        return iSource;
    }
    public String getSink()
    {
        return iSink;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetProtocolInfo result = iService.endGetProtocolInfo(aAsyncHandle);
        
        iSource = result.getSource();
        iSink = result.getSink();
    }
}

class SyncPrepareForConnectionUpnpOrgConnectionManager1 extends SyncProxyAction
{
    private CpProxyUpnpOrgConnectionManager1 iService;
    private int iConnectionID;
    private int iAVTransportID;
    private int iRcsID;

    public SyncPrepareForConnectionUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
    {
        iService = aProxy;
    }
    public int getConnectionID()
    {
        return iConnectionID;
    }
    public int getAVTransportID()
    {
        return iAVTransportID;
    }
    public int getRcsID()
    {
        return iRcsID;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        PrepareForConnection result = iService.endPrepareForConnection(aAsyncHandle);
        
        iConnectionID = result.getConnectionID();
        iAVTransportID = result.getAVTransportID();
        iRcsID = result.getRcsID();
    }
}

class SyncConnectionCompleteUpnpOrgConnectionManager1 extends SyncProxyAction
{
    private CpProxyUpnpOrgConnectionManager1 iService;

    public SyncConnectionCompleteUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endConnectionComplete(aAsyncHandle);
        
    }
}

class SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 extends SyncProxyAction
{
    private CpProxyUpnpOrgConnectionManager1 iService;
    private String iConnectionIDs;

    public SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
    {
        iService = aProxy;
    }
    public String getConnectionIDs()
    {
        return iConnectionIDs;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetCurrentConnectionIDs(aAsyncHandle);
        
        iConnectionIDs = result;
    }
}

class SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 extends SyncProxyAction
{
    private CpProxyUpnpOrgConnectionManager1 iService;
    private int iRcsID;
    private int iAVTransportID;
    private String iProtocolInfo;
    private String iPeerConnectionManager;
    private int iPeerConnectionID;
    private String iDirection;
    private String iStatus;

    public SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(CpProxyUpnpOrgConnectionManager1 aProxy)
    {
        iService = aProxy;
    }
    public int getRcsID()
    {
        return iRcsID;
    }
    public int getAVTransportID()
    {
        return iAVTransportID;
    }
    public String getProtocolInfo()
    {
        return iProtocolInfo;
    }
    public String getPeerConnectionManager()
    {
        return iPeerConnectionManager;
    }
    public int getPeerConnectionID()
    {
        return iPeerConnectionID;
    }
    public String getDirection()
    {
        return iDirection;
    }
    public String getStatus()
    {
        return iStatus;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetCurrentConnectionInfo result = iService.endGetCurrentConnectionInfo(aAsyncHandle);
        
        iRcsID = result.getRcsID();
        iAVTransportID = result.getAVTransportID();
        iProtocolInfo = result.getProtocolInfo();
        iPeerConnectionManager = result.getPeerConnectionManager();
        iPeerConnectionID = result.getPeerConnectionID();
        iDirection = result.getDirection();
        iStatus = result.getStatus();
    }
}

/**
 * Proxy for the upnp.org:ConnectionManager:1 UPnP service
 */
public class CpProxyUpnpOrgConnectionManager1 extends CpProxy implements ICpProxyUpnpOrgConnectionManager1
{

    public class GetProtocolInfo
    {
        private String iSource;
        private String iSink;

        public GetProtocolInfo(
            String aSource,
            String aSink
        )
        {
            iSource = aSource;
            iSink = aSink;
        }
        public String getSource()
        {
            return iSource;
        }
        public String getSink()
        {
            return iSink;
        }
    }

    public class PrepareForConnection
    {
        private int iConnectionID;
        private int iAVTransportID;
        private int iRcsID;

        public PrepareForConnection(
            int aConnectionID,
            int aAVTransportID,
            int aRcsID
        )
        {
            iConnectionID = aConnectionID;
            iAVTransportID = aAVTransportID;
            iRcsID = aRcsID;
        }
        public int getConnectionID()
        {
            return iConnectionID;
        }
        public int getAVTransportID()
        {
            return iAVTransportID;
        }
        public int getRcsID()
        {
            return iRcsID;
        }
    }

    public class GetCurrentConnectionInfo
    {
        private int iRcsID;
        private int iAVTransportID;
        private String iProtocolInfo;
        private String iPeerConnectionManager;
        private int iPeerConnectionID;
        private String iDirection;
        private String iStatus;

        public GetCurrentConnectionInfo(
            int aRcsID,
            int aAVTransportID,
            String aProtocolInfo,
            String aPeerConnectionManager,
            int aPeerConnectionID,
            String aDirection,
            String aStatus
        )
        {
            iRcsID = aRcsID;
            iAVTransportID = aAVTransportID;
            iProtocolInfo = aProtocolInfo;
            iPeerConnectionManager = aPeerConnectionManager;
            iPeerConnectionID = aPeerConnectionID;
            iDirection = aDirection;
            iStatus = aStatus;
        }
        public int getRcsID()
        {
            return iRcsID;
        }
        public int getAVTransportID()
        {
            return iAVTransportID;
        }
        public String getProtocolInfo()
        {
            return iProtocolInfo;
        }
        public String getPeerConnectionManager()
        {
            return iPeerConnectionManager;
        }
        public int getPeerConnectionID()
        {
            return iPeerConnectionID;
        }
        public String getDirection()
        {
            return iDirection;
        }
        public String getStatus()
        {
            return iStatus;
        }
    }

    private Action iActionGetProtocolInfo;
    private Action iActionPrepareForConnection;
    private Action iActionConnectionComplete;
    private Action iActionGetCurrentConnectionIDs;
    private Action iActionGetCurrentConnectionInfo;
    private PropertyString iSourceProtocolInfo;
    private PropertyString iSinkProtocolInfo;
    private PropertyString iCurrentConnectionIDs;
    private IPropertyChangeListener iSourceProtocolInfoChanged;
    private IPropertyChangeListener iSinkProtocolInfoChanged;
    private IPropertyChangeListener iCurrentConnectionIDsChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyUpnpOrgConnectionManager1(CpDevice aDevice)
    {
        super("schemas-upnp-org", "ConnectionManager", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionGetProtocolInfo = new Action("GetProtocolInfo");
        param = new ParameterString("Source", allowedValues);
        iActionGetProtocolInfo.addOutputParameter(param);
        param = new ParameterString("Sink", allowedValues);
        iActionGetProtocolInfo.addOutputParameter(param);

        iActionPrepareForConnection = new Action("PrepareForConnection");
        param = new ParameterString("RemoteProtocolInfo", allowedValues);
        iActionPrepareForConnection.addInputParameter(param);
        param = new ParameterString("PeerConnectionManager", allowedValues);
        iActionPrepareForConnection.addInputParameter(param);
        param = new ParameterInt("PeerConnectionID");
        iActionPrepareForConnection.addInputParameter(param);
        allowedValues.add("Input");
        allowedValues.add("Output");
        param = new ParameterString("Direction", allowedValues);
        iActionPrepareForConnection.addInputParameter(param);
        allowedValues.clear();
        param = new ParameterInt("ConnectionID");
        iActionPrepareForConnection.addOutputParameter(param);
        param = new ParameterInt("AVTransportID");
        iActionPrepareForConnection.addOutputParameter(param);
        param = new ParameterInt("RcsID");
        iActionPrepareForConnection.addOutputParameter(param);

        iActionConnectionComplete = new Action("ConnectionComplete");
        param = new ParameterInt("ConnectionID");
        iActionConnectionComplete.addInputParameter(param);

        iActionGetCurrentConnectionIDs = new Action("GetCurrentConnectionIDs");
        param = new ParameterString("ConnectionIDs", allowedValues);
        iActionGetCurrentConnectionIDs.addOutputParameter(param);

        iActionGetCurrentConnectionInfo = new Action("GetCurrentConnectionInfo");
        param = new ParameterInt("ConnectionID");
        iActionGetCurrentConnectionInfo.addInputParameter(param);
        param = new ParameterInt("RcsID");
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        param = new ParameterInt("AVTransportID");
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        param = new ParameterString("ProtocolInfo", allowedValues);
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        param = new ParameterString("PeerConnectionManager", allowedValues);
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        param = new ParameterInt("PeerConnectionID");
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        allowedValues.add("Input");
        allowedValues.add("Output");
        param = new ParameterString("Direction", allowedValues);
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        allowedValues.clear();
        allowedValues.add("OK");
        allowedValues.add("ContentFormatMismatch");
        allowedValues.add("InsufficientBandwidth");
        allowedValues.add("UnreliableChannel");
        allowedValues.add("Unknown");
        param = new ParameterString("Status", allowedValues);
        iActionGetCurrentConnectionInfo.addOutputParameter(param);
        allowedValues.clear();

        iSourceProtocolInfoChanged = new PropertyChangeListener();
        iSourceProtocolInfo = new PropertyString("SourceProtocolInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sourceProtocolInfoPropertyChanged();
                }
            }
        );
        addProperty(iSourceProtocolInfo);
        iSinkProtocolInfoChanged = new PropertyChangeListener();
        iSinkProtocolInfo = new PropertyString("SinkProtocolInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sinkProtocolInfoPropertyChanged();
                }
            }
        );
        addProperty(iSinkProtocolInfo);
        iCurrentConnectionIDsChanged = new PropertyChangeListener();
        iCurrentConnectionIDs = new PropertyString("CurrentConnectionIDs",
            new PropertyChangeListener() {
                public void notifyChange() {
                    currentConnectionIDsPropertyChanged();
                }
            }
        );
        addProperty(iCurrentConnectionIDs);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetProtocolInfo syncGetProtocolInfo()
    {
        SyncGetProtocolInfoUpnpOrgConnectionManager1 sync = new SyncGetProtocolInfoUpnpOrgConnectionManager1(this);
        beginGetProtocolInfo(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetProtocolInfo(
            sync.getSource(),
            sync.getSink()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetProtocolInfo}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetProtocolInfo(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetProtocolInfo, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetProtocolInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetProtocolInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetProtocolInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetProtocolInfo} method.
     * @return the result of the previously invoked action.
     */
    public GetProtocolInfo endGetProtocolInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String source = Invocation.getOutputString(aAsyncHandle, index++);
        String sink = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetProtocolInfo(
            source,
            sink
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public PrepareForConnection syncPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection)
    {
        SyncPrepareForConnectionUpnpOrgConnectionManager1 sync = new SyncPrepareForConnectionUpnpOrgConnectionManager1(this);
        beginPrepareForConnection(aRemoteProtocolInfo, aPeerConnectionManager, aPeerConnectionID, aDirection, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new PrepareForConnection(
            sync.getConnectionID(),
            sync.getAVTransportID(),
            sync.getRcsID()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endPrepareForConnection}.
     * 
     * @param aRemoteProtocolInfo
     * @param aPeerConnectionManager
     * @param aPeerConnectionID
     * @param aDirection
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginPrepareForConnection(String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionPrepareForConnection, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionPrepareForConnection.getInputParameter(inIndex++), aRemoteProtocolInfo));
        invocation.addInput(new ArgumentString((ParameterString)iActionPrepareForConnection.getInputParameter(inIndex++), aPeerConnectionManager));
        invocation.addInput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.getInputParameter(inIndex++), aPeerConnectionID));
        invocation.addInput(new ArgumentString((ParameterString)iActionPrepareForConnection.getInputParameter(inIndex++), aDirection));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionPrepareForConnection.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginPrepareForConnection} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginPrepareForConnection} method.
     * @return the result of the previously invoked action.
     */
    public PrepareForConnection endPrepareForConnection(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int connectionID = Invocation.getOutputInt(aAsyncHandle, index++);
        int aVTransportID = Invocation.getOutputInt(aAsyncHandle, index++);
        int rcsID = Invocation.getOutputInt(aAsyncHandle, index++);
        return new PrepareForConnection(
            connectionID,
            aVTransportID,
            rcsID
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncConnectionComplete(int aConnectionID)
    {
        SyncConnectionCompleteUpnpOrgConnectionManager1 sync = new SyncConnectionCompleteUpnpOrgConnectionManager1(this);
        beginConnectionComplete(aConnectionID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endConnectionComplete}.
     * 
     * @param aConnectionID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginConnectionComplete(int aConnectionID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionConnectionComplete, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentInt((ParameterInt)iActionConnectionComplete.getInputParameter(inIndex++), aConnectionID));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginConnectionComplete} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginConnectionComplete} method.
     */
    public void endConnectionComplete(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetCurrentConnectionIDs()
    {
        SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1 sync = new SyncGetCurrentConnectionIDsUpnpOrgConnectionManager1(this);
        beginGetCurrentConnectionIDs(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getConnectionIDs();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetCurrentConnectionIDs}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetCurrentConnectionIDs(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetCurrentConnectionIDs, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionIDs.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetCurrentConnectionIDs} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetCurrentConnectionIDs} method.
     * @return the result of the previously invoked action.
     */
    public String endGetCurrentConnectionIDs(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String connectionIDs = Invocation.getOutputString(aAsyncHandle, index++);
        return connectionIDs;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetCurrentConnectionInfo syncGetCurrentConnectionInfo(int aConnectionID)
    {
        SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1 sync = new SyncGetCurrentConnectionInfoUpnpOrgConnectionManager1(this);
        beginGetCurrentConnectionInfo(aConnectionID, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetCurrentConnectionInfo(
            sync.getRcsID(),
            sync.getAVTransportID(),
            sync.getProtocolInfo(),
            sync.getPeerConnectionManager(),
            sync.getPeerConnectionID(),
            sync.getDirection(),
            sync.getStatus()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetCurrentConnectionInfo}.
     * 
     * @param aConnectionID
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetCurrentConnectionInfo(int aConnectionID, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetCurrentConnectionInfo, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.getInputParameter(inIndex++), aConnectionID));
        int outIndex = 0;
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentInt((ParameterInt)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetCurrentConnectionInfo.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetCurrentConnectionInfo} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetCurrentConnectionInfo} method.
     * @return the result of the previously invoked action.
     */
    public GetCurrentConnectionInfo endGetCurrentConnectionInfo(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        int rcsID = Invocation.getOutputInt(aAsyncHandle, index++);
        int aVTransportID = Invocation.getOutputInt(aAsyncHandle, index++);
        String protocolInfo = Invocation.getOutputString(aAsyncHandle, index++);
        String peerConnectionManager = Invocation.getOutputString(aAsyncHandle, index++);
        int peerConnectionID = Invocation.getOutputInt(aAsyncHandle, index++);
        String direction = Invocation.getOutputString(aAsyncHandle, index++);
        String status = Invocation.getOutputString(aAsyncHandle, index++);
        return new GetCurrentConnectionInfo(
            rcsID,
            aVTransportID,
            protocolInfo,
            peerConnectionManager,
            peerConnectionID,
            direction,
            status
        );
    }
        
    /**
     * Set a delegate to be run when the SourceProtocolInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param aSourceProtocolInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySourceProtocolInfoChanged(IPropertyChangeListener aSourceProtocolInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iSourceProtocolInfoChanged = aSourceProtocolInfoChanged;
        }
    }

    private void sourceProtocolInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSourceProtocolInfoChanged);
        }
    }
    /**
     * Set a delegate to be run when the SinkProtocolInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param aSinkProtocolInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySinkProtocolInfoChanged(IPropertyChangeListener aSinkProtocolInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iSinkProtocolInfoChanged = aSinkProtocolInfoChanged;
        }
    }

    private void sinkProtocolInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSinkProtocolInfoChanged);
        }
    }
    /**
     * Set a delegate to be run when the CurrentConnectionIDs state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyUpnpOrgConnectionManager1 instance will not overlap.
     *
     * @param aCurrentConnectionIDsChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyCurrentConnectionIDsChanged(IPropertyChangeListener aCurrentConnectionIDsChanged)
    {
        synchronized (iPropertyLock)
        {
            iCurrentConnectionIDsChanged = aCurrentConnectionIDsChanged;
        }
    }

    private void currentConnectionIDsPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iCurrentConnectionIDsChanged);
        }
    }

    /**
     * Query the value of the SourceProtocolInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SourceProtocolInfo property.
     */
    public String getPropertySourceProtocolInfo()
    {
        propertyReadLock();
        String val = iSourceProtocolInfo.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the SinkProtocolInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SinkProtocolInfo property.
     */
    public String getPropertySinkProtocolInfo()
    {
        propertyReadLock();
        String val = iSinkProtocolInfo.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the CurrentConnectionIDs property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the CurrentConnectionIDs property.
     */
    public String getPropertyCurrentConnectionIDs()
    {
        propertyReadLock();
        String val = iCurrentConnectionIDs.getValue();
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
            iActionGetProtocolInfo.destroy();
            iActionPrepareForConnection.destroy();
            iActionConnectionComplete.destroy();
            iActionGetCurrentConnectionIDs.destroy();
            iActionGetCurrentConnectionInfo.destroy();
            iSourceProtocolInfo.destroy();
            iSinkProtocolInfo.destroy();
            iCurrentConnectionIDs.destroy();
        }
    }
}

