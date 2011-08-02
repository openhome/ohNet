package org.openhome.net.device.tests;

import java.util.Random;

import org.openhome.net.device.DvDevice;
import org.openhome.net.device.DvDeviceStandard;
import org.openhome.net.device.providers.DvProviderOpenhomeOrgTestBasic1;

public class DeviceBasic
{
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
