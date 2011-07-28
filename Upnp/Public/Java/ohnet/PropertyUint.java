package ohnet;


public class PropertyUint extends Property
{
	
	public PropertyUint(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyUintCp(aName, aListener);
	}
	
	public PropertyUint(Parameter aParameter)
	{
		initialiseServicePropertyUintDv(aParameter, false);
	}
	
	public PropertyUint(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyUintDv(aParameter, aOwnsNativeProperty);
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