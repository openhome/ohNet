package org.openhome.net.controlpoint;

/**
 * Class representing the result of attempting to get a value for a CpAttribute.
 */
public class CpAttribute
{
	private String iAttribute;
	private boolean iAvailable;
	private String iValue;
	
	/**
	 * Construct a <tt>CpAttribute</tt>. Only intended for native code
	 * responding to an attribute retrieval request.
	 *
	 * @param aAttribute	name of the attribute requested.
	 * @param aAvailable	<tt>true</tt> if attribute was available; <tt>false</tt> otherwise;
	 * @param aValue		value of the attribute; <tt>null</tt> if unavailable. 
	 */
	public CpAttribute(String aAttribute, boolean aAvailable, String aValue)
	{
		iAttribute = aAttribute;
		iAvailable = aAvailable;
		iValue = aValue;
	}
	
	/**
	 * Name of the attribute that was requested.
	 *
	 * @return	name of the attribute.
	 */
	public String getName()
	{
		return iAttribute;
	}
	
	/**
	 * Whether the named attribute was available.
	 *
	 * @return	<tt>true</tt> if attribute was available; <tt>false</tt> otherwise;
	 */
	public boolean isAvailable()
	{
		return iAvailable;
	}
	
	/**
	 * The value of the named attribute that was requested.
	 *
	 * @return	value of the attribute requested; <tt>null</tt> if unavailable;
	 */
	public String getValue()
	{
		return iValue;
	}
}
