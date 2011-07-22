package ohnet;


public class PropertyString extends Property
{
	
	public PropertyString(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyStringCp(aName, aListener);
	}
	
	public PropertyString(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyStringDv(aParameter, aOwnsNativeProperty);
	}
	
	public String getValue()
	{
		return getValueString();
	}
	
	public boolean setValue(String aValue)
	{
		return setValueString(aValue);
	}
}