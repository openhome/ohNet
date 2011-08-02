package org.openhome.net.device.tests;

import org.openhome.net.device.DvDevice;
import org.openhome.net.device.providers.DvProviderOpenhomeOrgTestBasic1;

public class TestBasicDv extends DvProviderOpenhomeOrgTestBasic1
{
	public TestBasicDv(DvDevice aDevice) {
		super(aDevice);

		setPropertyVarUint(0);
		setPropertyVarInt(0);
		setPropertyVarBool(false);
		String empty = "";
		byte[] emptyBinary = new byte[0];
		setPropertyVarStr(empty);
		setPropertyVarBin(emptyBinary);

		enableActionIncrement();
		enableActionDecrement();
		enableActionToggle();
		enableActionEchoString();
		enableActionEchoBinary();
		enableActionSetUint();
		enableActionGetUint();
		enableActionSetInt();
		enableActionGetInt();
		enableActionSetBool();
		enableActionGetBool();
		enableActionSetString();
		enableActionGetString();
		enableActionSetBinary();
		enableActionGetBinary();
		enableActionSetMultiple();
	}
	
	protected long increment(int aVersion, long aValue)
	{
		return aValue + 1;
	}
	
	protected int decrement(int aVersion, int aValue)
	{
		return aValue - 1;
	}
	
	protected boolean toggle(int aVersion, boolean aValue)
	{
		return !aValue;
	}
	
	protected String echoString(int aVersion, String aValue)
	{
		return aValue;
	}
	
	protected byte[] echoBinary(int aVersion, byte[] aValue)
	{
		return aValue;
	}
	
	protected void setUint(int aVersion, long aValueUint)
	{
		setPropertyVarUint(aValueUint);
	}
	
	protected long getUint(int aVersion)
	{
		return getPropertyVarUint();
	}
	
	protected void setInt(int aVersion, int aValueInt)
	{
		setPropertyVarInt(aValueInt);
	}
	
	protected int getInt(int aVersion)
	{
		return getPropertyVarInt();
	}
	
	protected void setBool(int aVersion, boolean aValueBool)
	{
		setPropertyVarBool(aValueBool);
	}
	
	protected boolean getBool(int aVersion)
	{
		return getPropertyVarBool();
	}
	
	protected void setString(int aVersion, String aValueStr)
	{
		setPropertyVarStr(aValueStr);
	}
	
	protected String getString(int aVersion)
	{
		return getPropertyVarStr();
	}
	
	protected void setBinary(int aVersion, byte[] aValueBin)
	{
		setPropertyVarBin(aValueBin);
	}
	
	protected byte[] getBinary(int aVersion)
	{
		return getPropertyVarBin();
	}
	
	protected void setMultiple(int aVersion, long aValueUint, int aValueInt, boolean aValueBool)
	{
		propertiesLock();
		setPropertyVarUint(aValueUint);
		setPropertyVarInt(aValueInt);
		setPropertyVarBool(aValueBool);
		propertiesUnlock();
	}
}
