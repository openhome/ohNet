package ohnet;


public class PropertyInt extends Property
{
	
	public PropertyInt(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyBinaryCp(aName, aListener);
	}
	
	public PropertyInt(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyBinaryDv(aParameter, aOwnsNativeProperty);
	}
	
	public int getValue()
	{
		return getValueInt();
	}
	
	public boolean setValue(int aValue)
	{
		return setValueInt(aValue);
	}
}
