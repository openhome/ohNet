package org.openhome.net.core;

import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * (Service) Property.  Only intended for use by auto-generated proxies and providers.
 * 
 * <p>One Property will be created per Property (state variable) for the Service.
 */
public class Property
{
	private static native void ServicePropertyDestroy(long aProperty);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	protected long iHandle;
	private boolean iOwnsNativeProperty;
	private IPropertyChangeListener iValueChanged;
	
	protected Property()
	{
		iOwnsNativeProperty = false;
	}
	
	protected Property(boolean aOwnsNativeProperty)
	{
		iOwnsNativeProperty = aOwnsNativeProperty;
	}
	
	protected Property(IPropertyChangeListener aListener)
	{
		iValueChanged = aListener;
	}
	
	public long getHandle()
	{
		return iHandle;
	}
	
	public void destroy()
	{
		if (iOwnsNativeProperty)
		{
			ServicePropertyDestroy(iHandle);
		}
	}
}
