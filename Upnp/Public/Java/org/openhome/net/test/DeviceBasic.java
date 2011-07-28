package org.openhome.net.test;

import java.util.Random;

import org.openhome.net.device.ActionDisabledError;
import org.openhome.net.device.DvDevice;
import org.openhome.net.device.DvDeviceStandard;
import org.openhome.net.device.providers.DvProviderOpenhomeOrgTestBasic1;

public class DeviceBasic
{
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

	public static final String DEVICE_NAME_STUB = "device";
	private String iUdn;
	private DvDeviceStandard iDevice;
	private DvProviderOpenhomeOrgTestBasic1 iTestBasic;

	public DeviceBasic()
	{
		iUdn = randomiseUdn();
		iDevice = new DvDeviceStandard(iUdn);
		iDevice.setAttribute("Upnp.Domain", "openhome.org");
		iDevice.setAttribute("Upnp.Type", "Test");
		iDevice.setAttribute("Upnp.Version", "1");
		iDevice.setAttribute("Upnp.FriendlyName", "ohNetTestDevice");
		iDevice.setAttribute("Upnp.Manufacturer", "None");
		iDevice.setAttribute("Upnp.ModelName", "ohNet test device");
		iTestBasic = new TestBasicDv(iDevice);
		iDevice.setEnabled();
	}

	public DvDevice getDevice()
	{
		return iDevice;
	}

	public void dispose()
	{
		iTestBasic.dispose();
		iDevice.destroy();
	}
	
	public String getUdn()
	{
		return iUdn;
	}

	private String randomiseUdn()
	{
		String aUdn = DEVICE_NAME_STUB;
		aUdn += "-";
		Random rnd = new Random();
		aUdn += rnd.nextInt();

		return aUdn;
	}
}
