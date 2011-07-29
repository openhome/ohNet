package ohnet;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.IPropertyChangeListener;


public class Property
{
	private native void ServicePropertyDestroy(long propPtr);
	private native long ServicePropertyCreateIntCp(String aName);
	private native long ServicePropertyCreateIntDv(long aParameterHandle);
	private native long ServicePropertyCreateUintCp(String aName);
	private native long ServicePropertyCreateUintDv(long aParameterHandle);
	private native long ServicePropertyCreateBoolCp(String aName);
	private native long ServicePropertyCreateBoolDv(long aParameterHandle);
	private native long ServicePropertyCreateStringCp(String aName);
	private native long ServicePropertyCreateStringDv(long aParameterHandle);
	private native long ServicePropertyCreateBinaryCp(String aName);
	private native long ServicePropertyCreateBinaryDv(long aParameterHandle);
	
	private native int ServicePropertyValueInt(long propPtr);
	private native long ServicePropertyValueUint(long propPtr);
	private native int ServicePropertyValueBool(long propPtr);
	private native String ServicePropertyValueString(long propPtr);
	private native byte[] ServicePropertyGetValueBinary(long propPtr);
	
	private native int ServicePropertySetValueInt(long propPtr, int aValue);
	private native int ServicePropertySetValueUint(long propPtr, long aValue);
	private native int ServicePropertySetValueBool(long propPtr, long aValue);
	private native int ServicePropertySetValueString(long propPtr, String aValue);
	private native int ServicePropertySetValueBinary(long propPtr, byte[] aValue, int aLen);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iHandle = 0;
	private boolean iOwnsNativeProp = false;
	private List<IPropertyChangeListener> iListeners = null;
	
	protected Property()
	{
		iOwnsNativeProp = false;
		iListeners = new LinkedList<IPropertyChangeListener>();
	}
	
//	protected Property(PropertyChangeListener l) {
//		listeners = new LinkedList<PropertyChangeListener>();
//		addListener(l);
//	}
//	
//	protected Property(boolean aOwnsNativeProperty) {
//		ownsNativeProp = aOwnsNativeProperty;
//	}
	
	public long getHandle() {
		return iHandle;
	}
	
	public void destroy() {
		if (iHandle == 0)
		{
			ServicePropertyDestroy(iHandle);
		}
	}
	
	// Function to be called back by native code when a property changes.
	public void changed()
	{
		for (IPropertyChangeListener p : iListeners) 
		{
			p.notifyChange();
		}
	}
	
	public void addListener(IPropertyChangeListener l)
	{
		iListeners.add(l);
	}
	
	protected void initialiseServicePropertyIntCp(String aName, IPropertyChangeListener aListener)
	{
		iHandle = ServicePropertyCreateIntCp(aName);
		iListeners.add(aListener);
	}
	
	protected void initialiseServicePropertyIntDv(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		iHandle = ServicePropertyCreateIntDv(aParameter.getHandle());
		iOwnsNativeProp = aOwnsNativeProperty;
	}
	
	protected void initialiseServicePropertyUintCp(String aName, IPropertyChangeListener aListener)
	{
		iHandle = ServicePropertyCreateUintCp(aName);
		iListeners.add(aListener);
	}
	
	protected void initialiseServicePropertyUintDv(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		iHandle = ServicePropertyCreateUintDv(aParameter.getHandle());
		iOwnsNativeProp = aOwnsNativeProperty;
	}
	
	protected void initialiseServicePropertyBoolCp(String aName, IPropertyChangeListener aListener)
	{
		iHandle = ServicePropertyCreateBoolCp(aName);
		iListeners.add(aListener);
	}
	
	protected void initialiseServicePropertyBoolDv(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		iHandle = ServicePropertyCreateBoolDv(aParameter.getHandle());
		iOwnsNativeProp = aOwnsNativeProperty;
	}
	
	protected void initialiseServicePropertyStringCp(String aName, IPropertyChangeListener aListener)
	{
		iHandle = ServicePropertyCreateStringCp(aName);
		iListeners.add(aListener);
	}
	
	protected void initialiseServicePropertyStringDv(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		iHandle = ServicePropertyCreateStringDv(aParameter.getHandle());
		iOwnsNativeProp = aOwnsNativeProperty;
	}
	
	protected void initialiseServicePropertyBinaryCp(String aName, IPropertyChangeListener aListener)
	{
		iHandle = ServicePropertyCreateBinaryCp(aName);
		iListeners.add(aListener);
	}
	
	protected void initialiseServicePropertyBinaryDv(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		iHandle = ServicePropertyCreateBinaryDv(aParameter.getHandle());
		iOwnsNativeProp = aOwnsNativeProperty;
	}
	
	protected int getValueInt()
	{
		return ServicePropertyValueInt(iHandle);
	}
	
	protected long getValueUint()
	{
		return ServicePropertyValueUint(iHandle);
	}
	
	protected boolean getValueBool()
	{
		int result = ServicePropertyValueBool(iHandle);
		
		return (result != 0);
	}
	
	protected String getValueString()
	{
		return ServicePropertyValueString(iHandle);
	}
	
	protected byte[] getValueBinary()
	{
		return ServicePropertyGetValueBinary(iHandle);
	}
	
	protected boolean setValueInt(int aValue)
	{
		int result = ServicePropertySetValueInt(iHandle, aValue);
		
		return (result != 0);
	}
	
	protected boolean setValueUint(long aValue)
	{
		int result = ServicePropertySetValueUint(iHandle, aValue);
		
		return (result != 0);
	}
	
	protected boolean setValueBool(boolean aValue)
	{
		int value = (aValue ? 1 : 0);
		int result = ServicePropertySetValueBool(iHandle, value);
		
		return (result != 0);
	}
	
	protected boolean setValueString(String aValue)
	{
		int result = ServicePropertySetValueString(iHandle, aValue);
		
		return (result != 0);
	}
	
	protected boolean setValueBinary(byte[] aValue)
	{
		int result = ServicePropertySetValueBinary(iHandle, aValue, aValue.length);
		
		return (result != 0);
	}
}
