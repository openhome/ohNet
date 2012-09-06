package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderUpnpOrgSwitchPower1
{

    /**
     * Set the value of the Status property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyStatus(boolean aValue);

    /**
     * Get a copy of the value of the Status property
     *
     * @return value of the Status property.
     */
    public boolean getPropertyStatus();
        
}

/**
 * Provider for the upnp.org:SwitchPower:1 UPnP service.
 */
public class DvProviderUpnpOrgSwitchPower1 extends DvProvider implements IDvProviderUpnpOrgSwitchPower1
{

    private IDvInvocationListener iDelegateSetTarget;
    private IDvInvocationListener iDelegateGetTarget;
    private IDvInvocationListener iDelegateGetStatus;
    private PropertyBool iPropertyStatus;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderUpnpOrgSwitchPower1(DvDevice aDevice)
    {
        super(aDevice, "upnp.org", "SwitchPower", 1);
    }

    /**
     * Enable the Status property.
     */
    public void enablePropertyStatus()
    {
        iPropertyStatus = new PropertyBool(new ParameterBool("Status"));
        addProperty(iPropertyStatus);
    }

    /**
     * Set the value of the Status property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyStatus(boolean aValue)
    {
        return setPropertyBool(iPropertyStatus, aValue);
    }

    /**
     * Get a copy of the value of the Status property
     *
     * @return  value of the Status property.
     */
    public boolean getPropertyStatus()
    {
        return iPropertyStatus.getValue();
    }

    /**
     * Signal that the action SetTarget is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetTarget must be overridden if this is called.
     */      
    protected void enableActionSetTarget()
    {
        Action action = new Action("SetTarget");
        action.addInputParameter(new ParameterBool("newTargetValue"));
        iDelegateSetTarget = new DoSetTarget();
        enableAction(action, iDelegateSetTarget);
    }

    /**
     * Signal that the action GetTarget is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetTarget must be overridden if this is called.
     */      
    protected void enableActionGetTarget()
    {
        Action action = new Action("GetTarget");
        action.addOutputParameter(new ParameterBool("RetTargetValue"));
        iDelegateGetTarget = new DoGetTarget();
        enableAction(action, iDelegateGetTarget);
    }

    /**
     * Signal that the action GetStatus is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetStatus must be overridden if this is called.
     */      
    protected void enableActionGetStatus()
    {
        Action action = new Action("GetStatus");
        action.addOutputParameter(new ParameterRelated("ResultStatus", iPropertyStatus));
        iDelegateGetStatus = new DoGetStatus();
        enableAction(action, iDelegateGetStatus);
    }

    /**
     * SetTarget action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetTarget action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetTarget} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param anewTargetValue
     */
    protected void setTarget(IDvInvocation aInvocation, boolean anewTargetValue)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetTarget action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetTarget action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetTarget} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean getTarget(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetStatus action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetStatus action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetStatus} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean getStatus(IDvInvocation aInvocation)
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


    private class DoSetTarget implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean newTargetValue;
            try
            {
                invocation.readStart();
                newTargetValue = invocation.readBool("newTargetValue");
                invocation.readEnd();
                setTarget(invocation, newTargetValue);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetTarget");
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

    private class DoGetTarget implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean retTargetValue;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 retTargetValue = getTarget(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetTarget");
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
                invocation.writeBool("RetTargetValue", retTargetValue);
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

    private class DoGetStatus implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean resultStatus;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 resultStatus = getStatus(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetStatus");
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
                invocation.writeBool("ResultStatus", resultStatus);
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

