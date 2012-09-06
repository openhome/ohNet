package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderOpenhomeOrgSubscriptionLongPoll1
{
        
}

/**
 * Provider for the openhome.org:SubscriptionLongPoll:1 UPnP service.
 */
public class DvProviderOpenhomeOrgSubscriptionLongPoll1 extends DvProvider implements IDvProviderOpenhomeOrgSubscriptionLongPoll1
{

    public class Subscribe
    {
        private String iSid;
        private long iDuration;

        public Subscribe(
            String aSid,
            long aDuration
        )
        {
            iSid = aSid;
            iDuration = aDuration;
        }
        public String getSid()
        {
            return iSid;
        }
        public long getDuration()
        {
            return iDuration;
        }
    }

    private IDvInvocationListener iDelegateSubscribe;
    private IDvInvocationListener iDelegateUnsubscribe;
    private IDvInvocationListener iDelegateRenew;
    private IDvInvocationListener iDelegateGetPropertyUpdates;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderOpenhomeOrgSubscriptionLongPoll1(DvDevice aDevice)
    {
        super(aDevice, "openhome.org", "SubscriptionLongPoll", 1);
    }

    /**
     * Signal that the action Subscribe is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Subscribe must be overridden if this is called.
     */      
    protected void enableActionSubscribe()
    {
        Action action = new Action("Subscribe");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ClientId", allowedValues));
        action.addInputParameter(new ParameterString("Udn", allowedValues));
        action.addInputParameter(new ParameterString("Service", allowedValues));
        action.addInputParameter(new ParameterUint("RequestedDuration"));
        action.addOutputParameter(new ParameterString("Sid", allowedValues));
        action.addOutputParameter(new ParameterUint("Duration"));
        iDelegateSubscribe = new DoSubscribe();
        enableAction(action, iDelegateSubscribe);
    }

    /**
     * Signal that the action Unsubscribe is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Unsubscribe must be overridden if this is called.
     */      
    protected void enableActionUnsubscribe()
    {
        Action action = new Action("Unsubscribe");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("Sid", allowedValues));
        iDelegateUnsubscribe = new DoUnsubscribe();
        enableAction(action, iDelegateUnsubscribe);
    }

    /**
     * Signal that the action Renew is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Renew must be overridden if this is called.
     */      
    protected void enableActionRenew()
    {
        Action action = new Action("Renew");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("Sid", allowedValues));
        action.addInputParameter(new ParameterUint("RequestedDuration"));
        action.addOutputParameter(new ParameterUint("Duration"));
        iDelegateRenew = new DoRenew();
        enableAction(action, iDelegateRenew);
    }

    /**
     * Signal that the action GetPropertyUpdates is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetPropertyUpdates must be overridden if this is called.
     */      
    protected void enableActionGetPropertyUpdates()
    {
        Action action = new Action("GetPropertyUpdates");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("ClientId", allowedValues));
        action.addOutputParameter(new ParameterString("Updates", allowedValues));
        iDelegateGetPropertyUpdates = new DoGetPropertyUpdates();
        enableAction(action, iDelegateGetPropertyUpdates);
    }

    /**
     * Subscribe action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Subscribe action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSubscribe} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aClientId
     * @param aUdn
     * @param aService
     * @param aRequestedDuration
     */
    protected Subscribe subscribe(IDvInvocation aInvocation, String aClientId, String aUdn, String aService, long aRequestedDuration)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Unsubscribe action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Unsubscribe action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionUnsubscribe} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aSid
     */
    protected void unsubscribe(IDvInvocation aInvocation, String aSid)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Renew action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Renew action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionRenew} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aSid
     * @param aRequestedDuration
     */
    protected long renew(IDvInvocation aInvocation, String aSid, long aRequestedDuration)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetPropertyUpdates action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetPropertyUpdates action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetPropertyUpdates} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aClientId
     */
    protected String getPropertyUpdates(IDvInvocation aInvocation, String aClientId)
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


    private class DoSubscribe implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String clientId;
            String udn;
            String service;
            long requestedDuration;
            String sid;
            long duration;
            try
            {
                invocation.readStart();
                clientId = invocation.readString("ClientId");
                udn = invocation.readString("Udn");
                service = invocation.readString("Service");
                requestedDuration = invocation.readUint("RequestedDuration");
                invocation.readEnd();

            Subscribe outArgs = subscribe(invocation, clientId, udn, service, requestedDuration);
            sid = outArgs.getSid();
            duration = outArgs.getDuration();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Subscribe");
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
                invocation.writeString("Sid", sid);
                invocation.writeUint("Duration", duration);
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

    private class DoUnsubscribe implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sid;
            try
            {
                invocation.readStart();
                sid = invocation.readString("Sid");
                invocation.readEnd();
                unsubscribe(invocation, sid);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Unsubscribe");
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

    private class DoRenew implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String sid;
            long requestedDuration;
            long duration;
            try
            {
                invocation.readStart();
                sid = invocation.readString("Sid");
                requestedDuration = invocation.readUint("RequestedDuration");
                invocation.readEnd();
                 duration = renew(invocation, sid, requestedDuration);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Renew");
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

    private class DoGetPropertyUpdates implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String clientId;
            String updates;
            try
            {
                invocation.readStart();
                clientId = invocation.readString("ClientId");
                invocation.readEnd();
                 updates = getPropertyUpdates(invocation, clientId);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetPropertyUpdates");
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
                invocation.writeString("Updates", updates);
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

