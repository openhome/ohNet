package ohnet;


public class PropertyBinary extends Property
{
	
	public PropertyBinary(String aName, IPropertyChangeListener aListener)
	{
		initialiseServicePropertyBinaryCp(aName, aListener);
	}
	
	public PropertyBinary(Parameter aParameter)
	{
		initialiseServicePropertyBinaryDv(aParameter, false);
	}
	
	
	public PropertyBinary(Parameter aParameter, boolean aOwnsNativeProperty)
	{
		initialiseServicePropertyBinaryDv(aParameter, aOwnsNativeProperty);
	}
	
	public byte[] getValue()
	{
		return getValueBinary();
	}
	
	public boolean setValue(byte[] aValue)
	{
		return setValueBinary(aValue);
	}
}