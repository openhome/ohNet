package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgSender1
{

    /**
     * Set the value of the PresentationUrl property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyPresentationUrl(String aValue);

    /**
     * Get a copy of the value of the PresentationUrl property
     *
     * @return value of the PresentationUrl property.
     */
    public String getPropertyPresentationUrl();

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
     * Set the value of the Audio property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyAudio(boolean aValue);

    /**
     * Get a copy of the value of the Audio property
     *
     * @return value of the Audio property.
     */
    public boolean getPropertyAudio();

    /**
     * Set the value of the Status property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyStatus(String aValue);

    /**
     * Get a copy of the value of the Status property
     *
     * @return value of the Status property.
     */
    public String getPropertyStatus();

    /**
     * Set the value of the Attributes property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyAttributes(String aValue);

    /**
     * Get a copy of the value of the Attributes property
     *
     * @return value of the Attributes property.
     */
    public String getPropertyAttributes();
        
}

/**
 * Provider for the av.openhome.org:Sender:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgSender1 extends DvProvider implements IDvProviderAvOpenhomeOrgSender1
{

    private IDvInvocationListener iDelegatePresentationUrl;
    private IDvInvocationListener iDelegateMetadata;
    private IDvInvocationListener iDelegateAudio;
    private IDvInvocationListener iDelegateStatus;
    private IDvInvocationListener iDelegateAttributes;
    private PropertyString iPropertyPresentationUrl;
    private PropertyString iPropertyMetadata;
    private PropertyBool iPropertyAudio;
    private PropertyString iPropertyStatus;
    private PropertyString iPropertyAttributes;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgSender1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "Sender", 1);
    }

    /**
     * Enable the PresentationUrl property.
     */
    public void enablePropertyPresentationUrl()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyPresentationUrl = new PropertyString(new ParameterString("PresentationUrl", allowedValues));
        addProperty(iPropertyPresentationUrl);
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
     * Enable the Audio property.
     */
    public void enablePropertyAudio()
    {
        iPropertyAudio = new PropertyBool(new ParameterBool("Audio"));
        addProperty(iPropertyAudio);
    }

    /**
     * Enable the Status property.
     */
    public void enablePropertyStatus()
    {
        List<String> allowedValues = new LinkedList<String>();
        allowedValues.add("Enabled");
        allowedValues.add("Disabled");
        allowedValues.add("Blocked");
        iPropertyStatus = new PropertyString(new ParameterString("Status", allowedValues));
        addProperty(iPropertyStatus);
            allowedValues.clear();
    }

    /**
     * Enable the Attributes property.
     */
    public void enablePropertyAttributes()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyAttributes = new PropertyString(new ParameterString("Attributes", allowedValues));
        addProperty(iPropertyAttributes);
    }

    /**
     * Set the value of the PresentationUrl property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyPresentationUrl(String aValue)
    {
        return setPropertyString(iPropertyPresentationUrl, aValue);
    }

    /**
     * Get a copy of the value of the PresentationUrl property
     *
     * @return  value of the PresentationUrl property.
     */
    public String getPropertyPresentationUrl()
    {
        return iPropertyPresentationUrl.getValue();
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
     * Set the value of the Audio property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyAudio(boolean aValue)
    {
        return setPropertyBool(iPropertyAudio, aValue);
    }

    /**
     * Get a copy of the value of the Audio property
     *
     * @return  value of the Audio property.
     */
    public boolean getPropertyAudio()
    {
        return iPropertyAudio.getValue();
    }

    /**
     * Set the value of the Status property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyStatus(String aValue)
    {
        return setPropertyString(iPropertyStatus, aValue);
    }

    /**
     * Get a copy of the value of the Status property
     *
     * @return  value of the Status property.
     */
    public String getPropertyStatus()
    {
        return iPropertyStatus.getValue();
    }

    /**
     * Set the value of the Attributes property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyAttributes(String aValue)
    {
        return setPropertyString(iPropertyAttributes, aValue);
    }

    /**
     * Get a copy of the value of the Attributes property
     *
     * @return  value of the Attributes property.
     */
    public String getPropertyAttributes()
    {
        return iPropertyAttributes.getValue();
    }

    /**
     * Signal that the action PresentationUrl is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * PresentationUrl must be overridden if this is called.
     */      
    protected void enableActionPresentationUrl()
    {
        Action action = new Action("PresentationUrl");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyPresentationUrl));
        iDelegatePresentationUrl = new DoPresentationUrl();
        enableAction(action, iDelegatePresentationUrl);
    }

    /**
     * Signal that the action Metadata is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Metadata must be overridden if this is called.
     */      
    protected void enableActionMetadata()
    {
        Action action = new Action("Metadata");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyMetadata));
        iDelegateMetadata = new DoMetadata();
        enableAction(action, iDelegateMetadata);
    }

    /**
     * Signal that the action Audio is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Audio must be overridden if this is called.
     */      
    protected void enableActionAudio()
    {
        Action action = new Action("Audio");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyAudio));
        iDelegateAudio = new DoAudio();
        enableAction(action, iDelegateAudio);
    }

    /**
     * Signal that the action Status is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Status must be overridden if this is called.
     */      
    protected void enableActionStatus()
    {
        Action action = new Action("Status");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyStatus));
        iDelegateStatus = new DoStatus();
        enableAction(action, iDelegateStatus);
    }

    /**
     * Signal that the action Attributes is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Attributes must be overridden if this is called.
     */      
    protected void enableActionAttributes()
    {
        Action action = new Action("Attributes");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyAttributes));
        iDelegateAttributes = new DoAttributes();
        enableAction(action, iDelegateAttributes);
    }

    /**
     * PresentationUrl action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * PresentationUrl action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionPresentationUrl} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String presentationUrl(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Metadata action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Metadata action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionMetadata} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String metadata(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Audio action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Audio action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionAudio} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected boolean audio(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Status action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Status action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionStatus} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String status(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Attributes action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionAttributes} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String attributes(IDvInvocation aInvocation)
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


    private class DoPresentationUrl implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = presentationUrl(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "PresentationUrl");
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

    private class DoMetadata implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = metadata(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Metadata");
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

    private class DoAudio implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            boolean value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = audio(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Audio");
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
                invocation.writeBool("Value", value);
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

    private class DoStatus implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = status(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Status");
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

    private class DoAttributes implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = attributes(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "Attributes");
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

