package org.openhome.net.controlpoint.tests;

import java.util.Arrays;
import java.util.concurrent.Semaphore;

import org.openhome.net.controlpoint.CpDevice;
import org.openhome.net.controlpoint.IPropertyChangeListener;
import org.openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgTestBasic1;


public class TestBasicCp implements IPropertyChangeListener
{
	private Semaphore iUpdatesComplete;
	private CpDevice iDevice;
	private static final int TEST_ITERATIONS = 10;
	
	public TestBasicCp(CpDevice aDevice)
	{
		iDevice = aDevice;
		iUpdatesComplete = new Semaphore(Integer.MAX_VALUE);
		iUpdatesComplete.acquireUninterruptibly(Integer.MAX_VALUE);
	}
	
	public void testActions()
	{
		System.out.println("  Actions");
		CpProxyOpenhomeOrgTestBasic1 proxy = new CpProxyOpenhomeOrgTestBasic1(iDevice);
		int i;
		
		System.out.println("    Unsigned integer arguments...");
		long valUint = 15;
		for (i = 0; i < TEST_ITERATIONS; i++)
		{
			long result = proxy.syncIncrement(valUint);
			assert(result == valUint+1);
			valUint = result;
		}
		
		System.out.println("    Integer arguments...");
		int valInt = 3;
		for (i = 0; i < TEST_ITERATIONS; i++)
		{
			int result = proxy.syncDecrement(valInt);
			assert(result == valInt-1);
			valInt = result;
		}
		
		System.out.println("    Boolean arguments...");
		boolean valBool = true;
		for (i = 0; i < TEST_ITERATIONS; i++)
		{
			boolean result = proxy.syncToggle(valBool);
			assert(result != valBool);
			valBool = result;
		}
		
		System.out.println("    String arguments...");
		String valStr = "<&'tag\">";
		for (i = 0; i < TEST_ITERATIONS; i++)
		{
			String result = proxy.syncEchoString(valStr);
			assert(result.equals(valStr));
		}
		
		System.out.println("    Binary arguments...");
		byte[] bin = new byte[128];
		for (i = 0; i < 127; i++)
		{
			bin[i] = (byte)(i+1);
		}
		bin[127] = 0;
		for (i = 0; i < TEST_ITERATIONS; i++)
		{
			byte[] result = proxy.syncEchoBinary(bin);
			assert(Arrays.equals(result, bin));
		}

		proxy.dispose();
	}
	
	public void testSubscriptions()
	{
		System.out.println("  Subscriptions");
		CpProxyOpenhomeOrgTestBasic1 proxy = new CpProxyOpenhomeOrgTestBasic1(iDevice);
		proxy.setPropertyChanged(this);
		proxy.subscribe();
		iUpdatesComplete.acquireUninterruptibly();
		
		/*
		 * For each property,
		 * 		call it's setter action
		 * 		wait on a property being updated
		 * 		check that the property matches the value set
		 * 		check that the getter action matches the property
		 */
		
		System.out.println("    Uint...");
		proxy.syncSetUint(1);
		iUpdatesComplete.acquireUninterruptibly();
		long propUint = proxy.getPropertyVarUint();
		assert(propUint == 1);
		long valUint = proxy.syncGetUint();
		assert(propUint == valUint);
		
		System.out.println("    Int...");
		proxy.syncSetInt(-99);
		iUpdatesComplete.acquireUninterruptibly();
		int propInt = proxy.getPropertyVarInt();
		assert(propInt == -99);
		int valInt = proxy.syncGetInt();
		assert(propInt == -99);
		
		System.out.println("    Bool...");
		proxy.syncSetBool(true);
		iUpdatesComplete.acquireUninterruptibly();
		boolean propBool = proxy.getPropertyVarBool();
		assert(propBool);
		boolean valBool = proxy.syncGetBool();
		assert(valBool);
		
		System.out.println("    String...");
		String str = "<&'tag\">";
		proxy.syncSetString(str);
		iUpdatesComplete.acquireUninterruptibly();
		String propStr = proxy.getPropertyVarStr();
		assert(propStr.equals(str));
		// Test again to check that getPropertyVarStr didn't transfer to the property.
		propStr = proxy.getPropertyVarStr();
		assert(propStr.equals(str));
		String valStr = proxy.syncGetString();
		assert(propStr.equals(valStr));
		
		System.out.println("    Binary...");
		byte[] bin = new byte[128];
		for (int i = 0; i < 127; i++)
		{
			bin[i] = (byte)(i+1);
		}
		bin[127] = 0;
		proxy.syncSetBinary(bin);
		iUpdatesComplete.acquireUninterruptibly();
		byte[] propBin = proxy.getPropertyVarBin();
		assert(Arrays.equals(propBin, bin));
		// Test again to check that getPropertyVarBin didn't transfer to the property.
		propBin = proxy.getPropertyVarBin();
		assert(Arrays.equals(propBin, bin));
		byte[] valBin = proxy.syncGetBinary();
		assert(Arrays.equals(propBin, valBin));
		
		System.out.println("    Multiple...");
		proxy.syncSetMultiple(15, 658, false);
		iUpdatesComplete.acquireUninterruptibly();
		propUint = proxy.getPropertyVarUint();
		assert(propUint == 15);
		valUint = proxy.syncGetUint();
		assert(propUint == valUint);
		propInt = proxy.getPropertyVarInt();
		assert(propInt == 658);
		valInt = proxy.syncGetInt();
		assert(propInt == valInt);
		propBool = proxy.getPropertyVarBool();
		assert(!propBool);
		valBool = proxy.syncGetBool();
		assert(!valBool);
		
		proxy.dispose(); // Automatically unsubscribes.
	}
	
	public void notifyChange()
	{
		iUpdatesComplete.release();
	}
}
