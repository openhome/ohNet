package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgConnectionManager2
{

    /**
     * Set the value of the SourceProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySourceProtocolInfo(String aValue);

    /**
     * Get a copy of the value of the SourceProtocolInfo property
     *
     * @return value of the SourceProtocolInfo property.
     */
    public String getPropertySourceProtocolInfo();

    /**
     * Set the value of the SinkProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySinkProtocolInfo(String aValue);

    /**
     * Get a copy of the value of the SinkProtocolInfo property
     *
     * @return value of the SinkProtocolInfo property.
     */
    public String getPropertySinkProtocolInfo();

    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyCurrentConnectionIDs(String aValue);

    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     *
     * @return value of the CurrentConnectionIDs property.
     */
    public String getPropertyCurrentConnectionIDs();
        
}

/**
 * Provider for the upnp.org:ConnectionManager:2 UPnP service.
 */
public class DvProviderUpnpOrgConnectionManager2 extends DvProvider implements IDvProviderUpnpOrgConnectionManager2
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

    private IDvInvocationListener iDelegateGetProtocolInfo;
    private IDvInvocationListener iDelegatePrepareForConnection;
    private IDvInvocationListener iDelegateConnectionComplete;
    private IDvInvocationListener iDelegateGetCurrentConnectionIDs;
    private IDvInvocationListener iDelegateGetCurrentConnectionInfo;
    private PropertyString iPropertySourceProtocolInfo;
    private PropertyString iPropertySinkProtocolInfo;
    private PropertyString iPropertyCurrentConnectionIDs;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgConnectionManager2(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "ConnectionManager", 2);
    }

    /**
     * Enable the SourceProtocolInfo property.
     */
    public void enablePropertySourceProtocolInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertySourceProtocolInfo = new PropertyString(new ParameterString("SourceProtocolInfo", allowedValues));
        addProperty(iPropertySourceProtocolInfo);
    }

    /**
     * Enable the SinkProtocolInfo property.
     */
    public void enablePropertySinkProtocolInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertySinkProtocolInfo = new PropertyString(new ParameterString("SinkProtocolInfo", allowedValues));
        addProperty(iPropertySinkProtocolInfo);
    }

    /**
     * Enable the CurrentConnectionIDs property.
     */
    public void enablePropertyCurrentConnectionIDs()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyCurrentConnectionIDs = new PropertyString(new ParameterString("CurrentConnectionIDs", allowedValues));
        addProperty(iPropertyCurrentConnectionIDs);
    }

    /**
     * Set the value of the SourceProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySourceProtocolInfo(String aValue)
    {
        return setPropertyString(iPropertySourceProtocolInfo, aValue);
    }

    /**
     * Get a copy of the value of the SourceProtocolInfo property
     *
     * @return  value of the SourceProtocolInfo property.
     */
    public String getPropertySourceProtocolInfo()
    {
        return iPropertySourceProtocolInfo.getValue();
    }

    /**
     * Set the value of the SinkProtocolInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySinkProtocolInfo(String aValue)
    {
        return setPropertyString(iPropertySinkProtocolInfo, aValue);
    }

    /**
     * Get a copy of the value of the SinkProtocolInfo property
     *
     * @return  value of the SinkProtocolInfo property.
     */
    public String getPropertySinkProtocolInfo()
    {
        return iPropertySinkProtocolInfo.getValue();
    }

    /**
     * Set the value of the CurrentConnectionIDs property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyCurrentConnectionIDs(String aValue)
    {
        return setPropertyString(iPropertyCurrentConnectionIDs, aValue);
    }

    /**
     * Get a copy of the value of the CurrentConnectionIDs property
     *
     * @return  value of the CurrentConnectionIDs property.
     */
    public String getPropertyCurrentConnectionIDs()
    {
        return iPropertyCurrentConnectionIDs.getValue();
    }

    /**
     * Signal that the action GetProtocolInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetProtocolInfo must be overridden if this is called.
     */      
    protected void enableActionGetProtocolInfo()
    {
        Action action = new Action("GetProtocolInfo");
        action.addOutputParameter(new ParameterRelated("Source", iPropertySourceProtocolInfo));
        action.addOutputParameter(new ParameterRelated("Sink", iPropertySinkProtocolInfo));
        iDelegateGetProtocolInfo = new DoGetProtocolInfo();
        enableAction(action, iDelegateGetProtocolInfo);
    }

    /**
     * Signal that the action PrepareForConnection is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PrepareForConnection must be overridden if this is called.
     */      
    protected void enableActionPrepareForConnection()
    {
        Action action = new Action("PrepareForConnection");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("RemoteProtocolInfo", allowedValues));
        action.addInputParameter(new ParameterString("PeerConnectionManager", allowedValues));
        action.addInputParameter(new ParameterInt("PeerConnectionID"));
        allowedValues.add("Input");
        allowedValues.add("Output");
        action.addInputParameter(new ParameterString("Direction", allowedValues));
        allowedValues.clear();
        action.addOutputParameter(new ParameterInt("ConnectionID"));
        action.addOutputParameter(new ParameterInt("AVTransportID"));
        action.addOutputParameter(new ParameterInt("RcsID"));
        iDelegatePrepareForConnection = new DoPrepareForConnection();
        enableAction(action, iDelegatePrepareForConnection);
    }

    /**
     * Signal that the action ConnectionComplete is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * ConnectionComplete must be overridden if this is called.
     */      
    protected void enableActionConnectionComplete()
    {
        Action action = new Action("ConnectionComplete");
        action.addInputParameter(new ParameterInt("ConnectionID"));
        iDelegateConnectionComplete = new DoConnectionComplete();
        enableAction(action, iDelegateConnectionComplete);
    }

    /**
     * Signal that the action GetCurrentConnectionIDs is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetCurrentConnectionIDs must be overridden if this is called.
     */      
    protected void enableActionGetCurrentConnectionIDs()
    {
        Action action = new Action("GetCurrentConnectionIDs");
        action.addOutputParameter(new ParameterRelated("ConnectionIDs", iPropertyCurrentConnectionIDs));
        iDelegateGetCurrentConnectionIDs = new DoGetCurrentConnectionIDs();
        enableAction(action, iDelegateGetCurrentConnectionIDs);
    }

    /**
     * Signal that the action GetCurrentConnectionInfo is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetCurrentConnectionInfo must be overridden if this is called.
     */      
    protected void enableActionGetCurrentConnectionInfo()
    {
        Action action = new Action("GetCurrentConnectionInfo");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterInt("ConnectionID"));
        action.addOutputParameter(new ParameterInt("RcsID"));
        action.addOutputParameter(new ParameterInt("AVTransportID"));
        action.addOutputParameter(new ParameterString("ProtocolInfo", allowedValues));
        action.addOutputParameter(new ParameterString("PeerConnectionManager", allowedValues));
        action.addOutputParameter(new ParameterInt("PeerConnectionID"));
        allowedValues.add("Input");
        allowedValues.add("Output");
        action.addOutputParameter(new ParameterString("Direction", allowedValues));
        allowedValues.clear();
        allowedValues.add("OK");
        allowedValues.add("ContentFormatMismatch");
        allowedValues.add("InsufficientBandwidth");
        allowedValues.add("UnreliableChannel");
        allowedValues.add("Unknown");
        action.addOutputParameter(new ParameterString("Status", allowedValues));
        allowedValues.clear();
        iDelegateGetCurrentConnectionInfo = new DoGetCurrentConnectionInfo();
        enableAction(action, iDelegateGetCurrentConnectionInfo);
    }

    /**
     * GetProtocolInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetProtocolInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetProtocolInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected GetProtocolInfo getProtocolInfo(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * PrepareForConnection action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PrepareForConnection action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPrepareForConnection} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRemoteProtocolInfo
     * @param aPeerConnectionManager
     * @param aPeerConnectionID
     * @param aDirection
     */
    protected PrepareForConnection prepareForConnection(IDvInvocation aInvocation, String aRemoteProtocolInfo, String aPeerConnectionManager, int aPeerConnectionID, String aDirection)
    {
        throw (new ActionDisabledError());
    }

    /**
     * ConnectionComplete action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * ConnectionComplete action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionConnectionComplete} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aConnectionID
     */
    protected void connectionComplete(IDvInvocation aInvocation, int aConnectionID)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetCurrentConnectionIDs action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionIDs action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetCurrentConnectionIDs} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String getCurrentConnectionIDs(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetCurrentConnectionInfo action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetCurrentConnectionInfo action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetCurrentConnectionInfo} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aConnectionID
     */
    protected GetCurrentConnectionInfo getCurrentConnectionInfo(IDvInvocation aInvocation, int aConnectionID)
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


    private class DoGetProtocolInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String source;
            String sink;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            GetProtocolInfo outArgs = getProtocolInfo(invocation);
            source = outArgs.getSource();
            sink = outArgs.getSink();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetProtocolInfo");
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
                invocation.writeString("Source", source);
                invocation.writeString("Sink", sink);
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

    private class DoPrepareForConnection implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String remoteProtocolInfo;
            String peerConnectionManager;
            int peerConnectionID;
            String direction;
            int connectionID;
            int aVTransportID;
            int rcsID;
            try
            {
                invocation.readStart();
                remoteProtocolInfo = invocation.readString("RemoteProtocolInfo");
                peerConnectionManager = invocation.readString("PeerConnectionManager");
                peerConnectionID = invocation.readInt("PeerConnectionID");
                direction = invocation.readString("Direction");
                invocation.readEnd();

            PrepareForConnection outArgs = prepareForConnection(invocation, remoteProtocolInfo, peerConnectionManager, peerConnectionID, direction);
            connectionID = outArgs.getConnectionID();
            aVTransportID = outArgs.getAVTransportID();
            rcsID = outArgs.getRcsID();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "PrepareForConnection");
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
                invocation.writeInt("ConnectionID", connectionID);
                invocation.writeInt("AVTransportID", aVTransportID);
                invocation.writeInt("RcsID", rcsID);
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

    private class DoConnectionComplete implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            int connectionID;
            try
            {
                invocation.readStart();
                connectionID = invocation.readInt("ConnectionID");
                invocation.readEnd();
                connectionComplete(invocation, connectionID);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "ConnectionComplete");
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

    private class DoGetCurrentConnectionIDs implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String connectionIDs;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 connectionIDs = getCurrentConnectionIDs(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetCurrentConnectionIDs");
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
                invocation.writeString("ConnectionIDs", connectionIDs);
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

    private class DoGetCurrentConnectionInfo implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            int connectionID;
            int rcsID;
            int aVTransportID;
            String protocolInfo;
            String peerConnectionManager;
            int peerConnectionID;
            String direction;
            String status;
            try
            {
                invocation.readStart();
                connectionID = invocation.readInt("ConnectionID");
                invocation.readEnd();

            GetCurrentConnectionInfo outArgs = getCurrentConnectionInfo(invocation, connectionID);
            rcsID = outArgs.getRcsID();
            aVTransportID = outArgs.getAVTransportID();
            protocolInfo = outArgs.getProtocolInfo();
            peerConnectionManager = outArgs.getPeerConnectionManager();
            peerConnectionID = outArgs.getPeerConnectionID();
            direction = outArgs.getDirection();
            status = outArgs.getStatus();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetCurrentConnectionInfo");
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
                invocation.writeInt("RcsID", rcsID);
                invocation.writeInt("AVTransportID", aVTransportID);
                invocation.writeString("ProtocolInfo", protocolInfo);
                invocation.writeString("PeerConnectionManager", peerConnectionManager);
                invocation.writeInt("PeerConnectionID", peerConnectionID);
                invocation.writeString("Direction", direction);
                invocation.writeString("Status", status);
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

