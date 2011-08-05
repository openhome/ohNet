package org.openhome.net.controlpoint;


/**
 * Base interface for all proxies.
 */
public interface ICpProxy
{
	/**
	 * Subscribe to notification of changes in state variables.
	 * Use {@link CpProxy#setPropertyChanged} to register a callback which runs
	 * after each group of 1..n changes is processed.
	 */
	public void subscribe();
	
	/**
	 * Unsubscribe to notification of changes in state variables.
	 * No further notifications will be published until Subscribe() is called again.
	 */
	public void unsubscribe();
	
	/**
	 * Register a {@link IPropertyChangeListener} which will run after each
	 * group of 1..n changes to state variable is processed.
	 * 
	 * @param aPropertyChanged	the property change listener to be called.
	 */
	public void setPropertyChanged(IPropertyChangeListener aPropertyChanged);
	
	/**
	 * Register a listener object which will be called when the state of all
	 * properties becomes available.
	 * This is often the first point at which UI elements can be fully initialised.
	 * 
	 * @param aInitialEvent	the listener to be called.
	 */
	public void setPropertyInitialEvent(IPropertyChangeListener aInitialEvent);
}
