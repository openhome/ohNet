package org.openhome.net.device.tests;

import org.openhome.net.device.DvDevice;
import org.openhome.net.device.IDvInvocation;
import org.openhome.net.device.providers.DvProviderOpenhomeOrgTestBasic1;

public class TestBasicDv extends DvProviderOpenhomeOrgTestBasic1
{
	public TestBasicDv(DvDevice aDevice) {
		super(aDevice);

        enablePropertyVarUint();
        enablePropertyVarInt();
        enablePropertyVarBool();
        enablePropertyVarStr();
        enablePropertyVarBin();
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
	
	protected long increment(IDvInvocation aInvocation, long aValue)
	{
		return aValue + 1;
	}
	
	protected int decrement(IDvInvocation aInvocation, int aValue)
	{
		return aValue - 1;
	}
	
	protected boolean toggle(IDvInvocation aInvocation, boolean aValue)
	{
		return !aValue;
	}
	
	protected String echoString(IDvInvocation aInvocation, String aValue)
	{
		return aValue;
	}
	
	protected byte[] echoBinary(IDvInvocation aInvocation, byte[] aValue)
	{
		return aValue;
	}
	
	protected void setUint(IDvInvocation aInvocation, long aValueUint)
	{
		setPropertyVarUint(aValueUint);
	}
	
	protected long getUint(IDvInvocation aInvocation)
	{
		return getPropertyVarUint();
	}
	
	protected void setInt(IDvInvocation aInvocation, int aValueInt)
	{
		setPropertyVarInt(aValueInt);
	}
	
	protected int getInt(IDvInvocation aInvocation)
	{
		return getPropertyVarInt();
	}
	
	protected void setBool(IDvInvocation aInvocation, boolean aValueBool)
	{
		setPropertyVarBool(aValueBool);
	}
	
	protected boolean getBool(IDvInvocation aInvocation)
	{
		return getPropertyVarBool();
	}
	
	protected void setString(IDvInvocation aInvocation, String aValueStr)
	{
		setPropertyVarStr(aValueStr);
	}
	
	protected String getString(IDvInvocation aInvocation)
	{
		return getPropertyVarStr();
	}
	
	protected void setBinary(IDvInvocation aInvocation, byte[] aValueBin)
	{
		setPropertyVarBin(aValueBin);
	}
	
	protected byte[] getBinary(IDvInvocation aInvocation)
	{
		return getPropertyVarBin();
	}
	
	protected void setMultiple(IDvInvocation aInvocation, long aValueUint, int aValueInt, boolean aValueBool)
	{
		propertiesLock();
		setPropertyVarUint(aValueUint);
		setPropertyVarInt(aValueInt);
		setPropertyVarBool(aValueBool);
		propertiesUnlock();
	}
}
