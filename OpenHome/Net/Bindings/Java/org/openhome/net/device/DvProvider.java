package org.openhome.net.device;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.Action;
import org.openhome.net.core.Property;
import org.openhome.net.core.PropertyBinary;
import org.openhome.net.core.PropertyBool;
import org.openhome.net.core.PropertyInt;
import org.openhome.net.core.PropertyString;
import org.openhome.net.core.PropertyUint;


public class DvProvider
{
	private class PropertySetStatus
	{
		private boolean iChanged;
		private boolean iSucceeded;
		
		public PropertySetStatus(int aChanged, int aSucceeded)
		{
			iChanged = (aChanged != 0);
			iSucceeded = (aSucceeded == 0);
		}
		
		public boolean changed()
		{
			return iChanged;
		}
		
		public boolean succeeded()
		{
			return iSucceeded;
		}
	}
	
	private static native long DvProviderCreate(long aDevice, String aDomain, String aType, int aVersion);
	private static native void DvProviderDestroy(long aProvider, long[] aCallbacks, int aLen);
	private static native long DvProviderAddAction(long aProvider, long aAction, IDvInvocationListener aCallback);
	private static native void DvProviderPropertiesLock(long aProvider);
	private static native void DvProviderPropertiesUnlock(long aProvider);
	private static native void DvProviderAddProperty(long aProvider, long aProperty);
	private native PropertySetStatus DvProviderSetPropertyInt(long aProvider, long aProperty, int aValue);
	private native PropertySetStatus DvProviderSetPropertyUint(long aProvider, long aProperty, long aValue);
	private native PropertySetStatus DvProviderSetPropertyBool(long aProvider, long aProperty, int aValue);
	private native PropertySetStatus DvProviderSetPropertyString(long aProvider, long aProperty, String aValue);
	private native PropertySetStatus DvProviderSetPropertyBinary(long aProvider, long aProperty, byte[] aData, int aLen);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	protected long iHandle;
	private List<Long> iCallbacks;
    private List<Action> iActions;
    private List<Property> iProperties;
    
    /**
     * Create a {@link #DvProvider}.
     * 
     * @param aDevice	device the service is being added to and will be offered by.
     * @param aDomain	domain of the vendor who defined the service.
     * @param aType		name of the service.
     * @param aVersion	version number of the service.
     */
    protected DvProvider(DvDevice aDevice, String aDomain, String aType, int aVersion)
    {
    	iHandle = DvProviderCreate(aDevice.getHandle(), aDomain, aType, aVersion);
    	iCallbacks = new ArrayList<Long>();
    	iActions = new LinkedList<Action>();
    	iProperties = new LinkedList<Property>();
    }
    
    /**
     * Register an action as available. The action will be published as part
     * of the owning device's service XML.
     * 
     * @param aAction		action being registered as available.
     * @param aDelegate		listener to notify when the action is invoked.
     */
    protected void enableAction(Action aAction, IDvInvocationListener aDelegate)
    {
        iActions.add(aAction);
        long callback = DvProviderAddAction(iHandle, aAction.getHandle(), aDelegate);
        iCallbacks.add(callback);
    }
    
    /**
     * Add a property to this provider.
     * 
     * <p>Any later updates to the value of the property will be automatically
     * published to any subscribers.
     * 
     * @param aProperty	property being added.
     */
    protected void addProperty(Property aProperty)
    {
        iProperties.add(aProperty);
        DvProviderAddProperty(iHandle, aProperty.getHandle());
    }
    
    /**
     * Utility function which updates the value of a PropertyInt.
     * (Not intended for external use).
     * 
     * <p>If the property value has changed and the properties are not locked
     * (<tt>propertiesLock()</tt> called more recently than {@code
     * propertiesUnlock()}), publication of an update is scheduled.
     * 
     * @param aProperty	property to be updated.
     * @param aValue	new value for the property.
     * @return			<tt>true</tt> if the property's value has changed ({@code
     * 					aValue} was different to the previous value).
     * @throws 			<tt>PropertyUpdateError</tt> if the property has a range
     * 					of allowed values and the new value is not in this range.
     */
    protected boolean setPropertyInt(PropertyInt aProperty, int aValue)
    {
        PropertySetStatus status = DvProviderSetPropertyInt(iHandle, aProperty.getHandle(), aValue);
        if (!status.succeeded())
        {
            throw new PropertyUpdateError();
        }
        return status.changed();
    }
    
    /**
     * Utility function which updates the value of a PropertyUint.
     * (Not intended for external use).
     * 
     * <p>If the property value has changed and the properties are not locked
     * (<tt>propertiesLock()</tt> called more recently than {@code
     * propertiesUnlock()}), publication of an update is scheduled.
     * 
     * @throws 			<tt>PropertyUpdateError</tt> if the property has a range
     * 					of allowed values and the new value is not in this range.
     * @param aProperty	property to be updated.
     * @param aValue	new value for the property.
     * @return			<tt>true</tt> if the property's value has changed ({@code
     * 					aValue} was different to the previous value).
     */
    protected boolean setPropertyUint(PropertyUint aProperty, long aValue)
    {
        PropertySetStatus status = DvProviderSetPropertyUint(iHandle, aProperty.getHandle(), aValue);
        if (!status.succeeded())
        {
            throw new PropertyUpdateError();
        }
        return status.changed();
    }
    
    /**
     * Utility function which updates the value of a PropertyBool.
     * (Not intended for external use).
     * 
     * <p>If the property value has changed and the properties are not locked
     * (<tt>propertiesLock()</tt> called more recently than {@code
     * propertiesUnlock()}), publication of an update is scheduled.
     * 
     * @throws 			<tt>PropertyUpdateError</tt> if the property has a range
     * 					of allowed values and the new value is not in this range.
     * @param aProperty	property to be updated.
     * @param aValue	new value for the property.
     * @return			<tt>true</tt> if the property's value has changed ({@code
     * 					aValue} was different to the previous value).
     */
    protected boolean setPropertyBool(PropertyBool aProperty, boolean aValue)
    {
    	int val = (aValue ? 1 : 0);
        PropertySetStatus status = DvProviderSetPropertyBool(iHandle, aProperty.getHandle(), val);
        if (!status.succeeded())
        {
            throw new PropertyUpdateError();
        }
        return status.changed();
    }
    
    /**
     * Utility function which updates the value of a PropertyString.
     * (Not intended for external use).
     * 
     * <p>If the property value has changed and the properties are not locked
     * (<tt>propertiesLock()</tt> called more recently than {@code
     * propertiesUnlock()}), publication of an update is scheduled.
     * 
     * @throws 			<tt>PropertyUpdateError</tt> if the property has a range
     * 					of allowed values and the new value is not in this range.
     * @param aProperty	property to be updated.
     * @param aValue	new value for the property
     * @return			<tt>true</tt> if the property's value has changed ({@code
     * 					aValue} was different to the previous value)
     */
    protected boolean setPropertyString(PropertyString aProperty, String aValue)
    {
        PropertySetStatus status = DvProviderSetPropertyString(iHandle, aProperty.getHandle(), aValue);
        if (!status.succeeded())
        {
            throw new PropertyUpdateError();
        }
        return status.changed();
    }
    
    /**
     * Utility function which updates the value of a PropertyString.
     * (Not intended for external use).
     * 
     * <p>If the property value has changed and the properties are not locked
     * (<tt>propertiesLock()</tt> called more recently than {@code
     *  propertiesUnlock()}),
     * publication of an update is scheduled.
     * 
     * @throws 			<tt>PropertyUpdateError</tt> if the property has a range
     * 					of allowed values and the new value is not in this range.
     * @param aProperty	property to be updated.
     * @param aValue	new value for the property
     * @return			<tt>true</tt> if the property's value has changed ({@code
     * 					aValue} was different to the previous value)
     */
    protected boolean setPropertyBinary(PropertyBinary aProperty, byte[] aValue)
    {
        PropertySetStatus status = DvProviderSetPropertyBinary(iHandle, aProperty.getHandle(), aValue, aValue.length);
        if (!status.succeeded())
        {
            throw new PropertyUpdateError();
        }
        return status.changed();
    }
    
    /**
     * Dispose of the underlying native provider.
     * Must be called by each sub-class.
     */
    protected void dispose()
    {
    	long[] callbackArray = new long[iCallbacks.size()];
    	for (int i = 0; i < callbackArray.length; i++)
    	{
    		callbackArray[i] = iCallbacks.get(i);
    	}
        DvProviderDestroy(iHandle, callbackArray, callbackArray.length);
        iHandle = 0;
        for (Action a : iActions)
        {
        	a.destroy();
        }
        for (Property p : iProperties)
        {
        	p.destroy();
        }
    }
    
    /**
     * Lock the provider's properties, blocking publication of updates.
     * 
     * <p>This is not necessary when updating a single property but is used by
     * providers that have >1 properties whose values are related. Without
     * locking, updates to some properties may be published, leaving related
     * properties in their old (now incompatible) states.
     * 
     * <p>Every call to this must be followed by (exactly) one call to {@link
     * #propertiesUnlock}.
     */
    public void propertiesLock()
    {
        DvProviderPropertiesLock(iHandle);
    }
    
    /**
     * Unlock the provider's properties, allowing publication of updates.
     * 
     * <p>Any pending updates will automatically be scheduled.
     * 
     * <p>This must only be called following a call to {@link #propertiesLock}.
     */
    public void propertiesUnlock()
    {
        DvProviderPropertiesUnlock(iHandle);
    }
}
