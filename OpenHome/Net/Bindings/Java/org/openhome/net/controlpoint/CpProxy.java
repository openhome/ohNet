package org.openhome.net.controlpoint;


import org.openhome.net.core.Property;

/**
 * Base class for all proxies
 */
public class CpProxy implements ICpProxy
{	
	/**
	 * Class representing subscription status within a proxy.
	 */
	enum SubscriptionStatus
    {
        E_NOT_SUBSCRIBED,
        E_SUBSCRIBING,
        E_SUBSCRIBED
    }
	
	private static native long CpProxyCreate(String aDomain, String aName, int aVersion, long aDevice);
	private static native void CpProxyDestroy(long aProxy, long aCallbackPropertyChanged, long aCallbackInitialEvent);
	private static native long CpProxyService(long aProxy);
	private static native void CpProxySubscribe(long aHandle);
	private static native void CpProxyUnsubscribe(long aHandle);
	private static native long CpProxySetPropertyChanged(long aHandle, IPropertyChangeListener aCallback);
	private static native long CpProxySetPropertyInitialEvent(long aHandle, IPropertyChangeListener aCallback);
    private static native long CpProxyVersion(long aHandle);
	private static native void CpProxyPropertyReadLock(long aHandle);
	private static native void CpProxyPropertyReadUnlock(long aHandle);
	private static native void CpProxyAddProperty(long aHandle, long aProperty);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	protected long iHandle;
	protected CpService iService;
	private long iCallbackNativePropertyChanged;
	private long iCallbackNativeInitialEvent;
	private IPropertyChangeListener iCallbackPropertyChanged;
	private IPropertyChangeListener iCallbackInitialEvent;
	private SubscriptionStatus iSubscriptionStatus = SubscriptionStatus.E_NOT_SUBSCRIBED;
	private Object iSubscriptionStatusLock;
	
	/**
	 * Create a proxy that will be manually populated with actions/properties.
	 * In most cases, clients should create proxy instances for specific services instead.
	 * 
	 * @param aDomain	the domain (vendor) name.
	 * @param aName		the service name.
	 * @param aVersion	the version number.
	 * @param aDevice	a handle to the device the proxy will communicate with / operate on.
	 */
	protected CpProxy(String aDomain, String aName, int aVersion, CpDevice aDevice)
    {
        iHandle = CpProxyCreate(aDomain, aName, aVersion, aDevice.getHandle());
        long serviceHandle = CpProxyService(iHandle);
        iService = new CpService(serviceHandle);
        iSubscriptionStatusLock = new Object();
    }
	
	/**
	 * Destroy this proxy.
	 */
	protected void disposeProxy()
    {
        boolean unsubscribe;
        synchronized (iSubscriptionStatusLock)
        {
            unsubscribe = (iSubscriptionStatus != SubscriptionStatus.E_NOT_SUBSCRIBED);
        }
        if (unsubscribe)
            unsubscribe();
        CpProxyDestroy(iHandle, iCallbackNativePropertyChanged, iCallbackNativeInitialEvent);
    }
	
	/**
	 * Subscribe to notification of changes in state variables.
	 * Use {@link CpProxy#setPropertyChanged} to register a callback which runs
	 * after each group of 1..n changes is processed.
	 */
	public void subscribe()
    {
        synchronized (iSubscriptionStatusLock)
        {
            iSubscriptionStatus = SubscriptionStatus.E_SUBSCRIBING;
        }
        CpProxySubscribe(iHandle);
    }
	
	/**
	 * Unsubscribe to notification of changes in state variables.
	 * No further notifications will be published until Subscribe() is called again.
	 */
	public void unsubscribe()
    {
        synchronized (iSubscriptionStatusLock)
        {
            iSubscriptionStatus = SubscriptionStatus.E_NOT_SUBSCRIBED;
        }
        CpProxyUnsubscribe(iHandle);
    }
	
	/**
	 * Register a {@link IPropertyChangeListener} which will run after each
	 * group of 1..n changes to state variable is processed.
	 * 
	 * @param aPropertyChanged	the property change listener to be called.
	 */
	public void setPropertyChanged(IPropertyChangeListener aPropertyChanged)
    {
		if (iCallbackPropertyChanged == null)
		{
			iCallbackPropertyChanged = aPropertyChanged;
			iCallbackNativePropertyChanged = CpProxySetPropertyChanged(iHandle, iCallbackPropertyChanged);
		}
    }

	/**
	 * Register a {@link IPropertyChangeListener} which will run after an
	 * initial event for a state variable.
	 * 
	 * @param aInitialEvent	the initial event listener to be called.
	 */
    public void setPropertyInitialEvent(IPropertyChangeListener aInitialEvent)
    {
    	if (iCallbackInitialEvent == null)
    	{
    		iCallbackInitialEvent = aInitialEvent;
    		iCallbackNativeInitialEvent = CpProxySetPropertyInitialEvent(iHandle, iCallbackInitialEvent);
    	}
    }

    /**
     * Query service version implemented by the remote device
     */
    public long version()
    {
        return CpProxyVersion(iHandle);
    }

    /**
     * Acquire a lock to read the value of a property.
     * Must be called before reading the value of a property.
     */
	protected void propertyReadLock()
    {
        CpProxyPropertyReadLock(iHandle);
    }

	/**
	 * Release the read lock after reading the value of a property.
	 * Must be called once for each call to {@link #propertyReadLock}.
	 */
    protected void propertyReadUnlock()
    {
        CpProxyPropertyReadUnlock(iHandle);
    }
    
    /**
     * Report an even to a property change listener.
     * @param aCallback	the property change listener to notify.
     */
    protected void reportEvent(IPropertyChangeListener aCallback)
    {
        synchronized (iSubscriptionStatusLock)
        {
            if (iSubscriptionStatus == SubscriptionStatus.E_SUBSCRIBING)
            {
                iSubscriptionStatus = SubscriptionStatus.E_SUBSCRIBED;
            }
            if (iSubscriptionStatus == SubscriptionStatus.E_SUBSCRIBED && aCallback != null)
            {
                aCallback.notifyChange();
            }
        }
    }
    
    /**
     * Add a property to a service.
     * Will normally only be called by auto-generated code.
     * 
     * @param aProperty the property to be added to the service.
     */
    protected void addProperty(Property aProperty)
    {
        CpProxyAddProperty(iHandle, aProperty.getHandle());
    }
	
}
