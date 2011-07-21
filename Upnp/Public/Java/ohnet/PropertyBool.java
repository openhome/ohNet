package ohnet;


public class PropertyBool extends Property
{
	
	public PropertyBool(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyBinaryCp(aName, aListener);
	}
	
	public PropertyBool(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyBinaryDv(aParameter, aOwnsNativeProperty);
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