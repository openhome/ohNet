package ohnet;


public class PropertyInt extends Property
{
	
	public PropertyInt(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyIntCp(aName, aListener);
	}
	
	public PropertyInt(Parameter aParameter)
	{
		initialiseServicePropertyIntDv(aParameter, false);
	}
	
	public PropertyInt(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyIntDv(aParameter, aOwnsNativeProperty);
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
