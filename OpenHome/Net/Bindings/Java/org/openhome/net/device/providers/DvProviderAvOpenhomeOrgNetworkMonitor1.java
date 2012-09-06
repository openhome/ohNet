package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgNetworkMonitor1
{

    /**
     * Set the value of the Name property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyName(String aValue);

    /**
     * Get a copy of the value of the Name property
     *
     * @return value of the Name property.
     */
    public String getPropertyName();

    /**
     * Set the value of the Sender property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertySender(long aValue);

    /**
     * Get a copy of the value of the Sender property
     *
     * @return value of the Sender property.
     */
    public long getPropertySender();

    /**
     * Set the value of the Receiver property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyReceiver(long aValue);

    /**
     * Get a copy of the value of the Receiver property
     *
     * @return value of the Receiver property.
     */
    public long getPropertyReceiver();

    /**
     * Set the value of the Results property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyResults(long aValue);

    /**
     * Get a copy of the value of the Results property
     *
     * @return value of the Results property.
     */
    public long getPropertyResults();
        
}

/**
 * Provider for the av.openhome.org:NetworkMonitor:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgNetworkMonitor1 extends DvProvider implements IDvProviderAvOpenhomeOrgNetworkMonitor1
{

    public class Ports
    {
        private long iSender;
        private long iReceiver;
        private long iResults;

        public Ports(
            long aSender,
            long aReceiver,
            long aResults
        )
        {
            iSender = aSender;
            iReceiver = aReceiver;
            iResults = aResults;
        }
        public long getSender()
        {
            return iSender;
        }
        public long getReceiver()
        {
            return iReceiver;
        }
        public long getResults()
        {
            return iResults;
        }
    }

    private IDvInvocationListener iDelegateName;
    private IDvInvocationListener iDelegatePorts;
    private PropertyString iPropertyName;
    private PropertyUint iPropertySender;
    private PropertyUint iPropertyReceiver;
    private PropertyUint iPropertyResults;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgNetworkMonitor1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "NetworkMonitor", 1);
    }

    /**
     * Enable the Name property.
     */
    public void enablePropertyName()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyName = new PropertyString(new ParameterString("Name", allowedValues));
        addProperty(iPropertyName);
    }

    /**
     * Enable the Sender property.
     */
    public void enablePropertySender()
    {
        iPropertySender = new PropertyUint(new ParameterUint("Sender"));
        addProperty(iPropertySender);
    }

    /**
     * Enable the Receiver property.
     */
    public void enablePropertyReceiver()
    {
        iPropertyReceiver = new PropertyUint(new ParameterUint("Receiver"));
        addProperty(iPropertyReceiver);
    }

    /**
     * Enable the Results property.
     */
    public void enablePropertyResults()
    {
        iPropertyResults = new PropertyUint(new ParameterUint("Results"));
        addProperty(iPropertyResults);
    }

    /**
     * Set the value of the Name property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyName(String aValue)
    {
        return setPropertyString(iPropertyName, aValue);
    }

    /**
     * Get a copy of the value of the Name property
     *
     * @return  value of the Name property.
     */
    public String getPropertyName()
    {
        return iPropertyName.getValue();
    }

    /**
     * Set the value of the Sender property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertySender(long aValue)
    {
        return setPropertyUint(iPropertySender, aValue);
    }

    /**
     * Get a copy of the value of the Sender property
     *
     * @return  value of the Sender property.
     */
    public long getPropertySender()
    {
        return iPropertySender.getValue();
    }

    /**
     * Set the value of the Receiver property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyReceiver(long aValue)
    {
        return setPropertyUint(iPropertyReceiver, aValue);
    }

    /**
     * Get a copy of the value of the Receiver property
     *
     * @return  value of the Receiver property.
     */
    public long getPropertyReceiver()
    {
        return iPropertyReceiver.getValue();
    }

    /**
     * Set the value of the Results property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyResults(long aValue)
    {
        return setPropertyUint(iPropertyResults, aValue);
    }

    /**
     * Get a copy of the value of the Results property
     *
     * @return  value of the Results property.
     */
    public long getPropertyResults()
    {
        return iPropertyResults.getValue();
    }

    /**
     * Signal that the action Name is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Name must be overridden if this is called.
     */      
    protected void enableActionName()
    {
        Action action = new Action("Name");
        action.addOutputParameter(new ParameterRelated("Name", iPropertyName));
        iDelegateName = new DoName();
        enableAction(action, iDelegateName);
    }

    /**
     * Signal that the action Ports is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Ports must be overridden if this is called.
     */      
    protected void enableActionPorts()
    {
        Action action = new Action("Ports");
        action.addOutputParameter(new ParameterRelated("Sender", iPropertySender));
        action.addOutputParameter(new ParameterRelated("Receiver", iPropertyReceiver));
        action.addOutputParameter(new ParameterRelated("Results", iPropertyResults));
        iDelegatePorts = new DoPorts();
        enableAction(action, iDelegatePorts);
    }

    /**
     * Name action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Name action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionName} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String name(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Ports action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Ports action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPorts} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Ports ports(IDvInvocation aInvocation)
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


    private class DoName implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String name;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 name = name(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Name");
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
                invocation.writeString("Name", name);
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

    private class DoPorts implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long sender;
            long receiver;
            long results;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Ports outArgs = ports(invocation);
            sender = outArgs.getSender();
            receiver = outArgs.getReceiver();
            results = outArgs.getResults();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Ports");
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
                invocation.writeUint("Sender", sender);
                invocation.writeUint("Receiver", receiver);
                invocation.writeUint("Results", results);
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

