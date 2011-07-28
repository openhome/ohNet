package ohnet;


public class PropertyBool extends Property
{
	
	public PropertyBool(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyBoolCp(aName, aListener);
	}
	
	public PropertyBool(Parameter aParameter)
	{
		initialiseServicePropertyBoolDv(aParameter, false);
	}
	
	public PropertyBool(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyBoolDv(aParameter, aOwnsNativeProperty);
	}
	
	public boolean getValue()
	{
		return getValueBool();
	}
	
	public boolean setValue(boolean aValue)
	{
		return setValueBool(aValue);
	}
}