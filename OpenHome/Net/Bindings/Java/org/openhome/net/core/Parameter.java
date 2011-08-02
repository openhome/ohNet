package org.openhome.net.core;

/**
 * Description of the type plus any bounds of action arguments plus properties.
 * Only intended for use by auto-generated proxies and providers.
 * 
 * <p>Each action owns {@code 0..n} parameters; each property owns exactly {@code 1}.
 */
public class Parameter
{
	protected long iHandle = 0;
	
	protected Parameter() {};

	public long getHandle()
	{
		return iHandle;
	}
}
