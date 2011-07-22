package ohnet;


public class PropertyUint extends Property
{
	
	public PropertyUint(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyBinaryCp(aName, aListener);
	}
	
	public PropertyUint(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyBinaryDv(aParameter, aOwnsNativeProperty);
	}
	
	public long getValue()
	{
		return getValueUint();
	}
	
	public boolean setValue(long aValue)
	{
		return setValueUint(aValue);
	}
}