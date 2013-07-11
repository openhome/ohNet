package org.openhome.net.core;

import org.openhome.net.controlpoint.IPropertyChangeListener;

/**
 * (Service) Property.  Only intended for use by auto-generated proxies and providers.
 * 
 * <p>One Property will be created per Property (state variable) for the Service.
 */
public class Property
{
    private static native void ServicePropertyDestroyProperty(long aProperty);
    private static native void ServicePropertyDestroyCallback(long aCallback);
    
    static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
    
    protected class PropertyInitialised
    {
        private long iHandle;
        private long iCallback;
        
        public PropertyInitialised(long aHandle, long aCallback)
        {
            iHandle = aHandle;
            iCallback = aCallback;
        }
        public long getHandle()
        {
            return iHandle;
        }
        public long getCallback()
        {
            return iCallback;
        }
    }
    
    protected long iHandle;
    protected long iCallback;
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
            // This is a device property object with a native property object (iHandle)
            // and no callback object (iCallback).
            ServicePropertyDestroyProperty(iHandle);
        }
        if (iCallback != 0)
        {
            // This is a control point property object with a callback object (iCallback).
            // The native property object (iHandle) is freed by the CpProxy.disposeProxy()
            // method, which is called by the dispose() method of the generated Java proxy
            // before it calls this method.
            ServicePropertyDestroyCallback(iCallback);
        }
    }
}
