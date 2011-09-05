package org.openhome.net.device;

import java.util.LinkedList;
import java.util.List;

public class DvDeviceStandard extends DvDevice
{
	private static native long DvDeviceStandardCreateNoResources(String aUdn);
	private native DvDeviceStandardInitialised DvDeviceStandardCreate(String aUdn);
	private static native void DvDeviceDestroy(long aDevice, long aCallback);
	private static native int DvResourceWriterLanguageCount(long aLanguageList);
	private static native String DvResourceWriterLanguage(long aLanguageList, int aIndex);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private class DvDeviceStandardInitialised
	{
		private long iHandle;
		private long iCallback;
		
		public DvDeviceStandardInitialised(long aHandle, long aCallback)
		{
			iHandle = aHandle;
			iCallback = aCallback;
		}
		public long getHandle()
		{
			return iHandle;
		}
		public long getCallback()
		{
			return iCallback;
		}
	}
	
	private IResourceManager iResourceManager;
	private long iCallback;
	
	/**
	 * Creates a device capable of operating on any of the protocols the device
	 * stack supports as standard but with no services or attributes as yet.
	 * 
	 * @param aUdn	universally unique identifier.  The caller is responsible
	 * 				for calculating/assigning this
	 */
	public DvDeviceStandard(String aUdn)
	{
		super();
		iResourceManager = null;
		iCallback = 0;
		iHandle = DvDeviceStandardCreateNoResources(aUdn);
	}
	
	/**
	 * Creates a device capable of serving UI files and of operating on any of
	 * the protocols the device stack supports as standard but with no services
	 * or attributes as yet.
	 * 
	 * @param aUdn				universally unique identifier. The caller is
	 * 							responsible for calculating/assigning this.
	 * @param aResourceManager	allows the owner of a device to serve UI files.
	 */
	public DvDeviceStandard(String aUdn, IResourceManager aResourceManager)
    {
        iResourceManager = aResourceManager;
        DvDeviceStandardInitialised init = DvDeviceStandardCreate(aUdn);
        iHandle = init.getHandle();
        iCallback = init.getCallback();
    }
	
	/**
	 * Destroy the underlying native instance. Must be called for each class instance.
	 * Must be called before <tt>Library.close()</tt>.
	 */
	public void destroy()
	{
		DvDeviceDestroy(iHandle, iCallback);
	}
	
	
	/**
	 * Method which will be called back by native code when a device is asked
	 * to serve an unknown file.
	 * 
	 * @param aUserData			'aPtr' passed to DvDeviceCreate.
	 * @param aUriTail			file being requested.
	 * @param aInterface		network interface the file request was made on.
	 * @param aLanguageList		handle to a prioritised list of the languages
	 * 							accepted in the resources to be written. This
	 * 							should be passed to {@link #DvResourceWriterLanguage}.
	 * @param aWriterData		pointer to be passed to all 3 <tt>writeResource</tt> callbacks.
	 * @param aWriteBegin		callback to run at the start of serving the file.
	 * 							Should not be run if the file cannot be supplied.
	 * @param aWriteResource	callback to run to write file data. Must be called
	 * 							at least once to successfully serve a file. Can be
	 *							called repeatedly to allow the file to be written
	 * 							in chunks (avoiding the need to read a large file
	 * 							fully into memory).
	 * @param aWriteEnd			callback to be run at the end of serving a file.
	 * 							Must be called if <tt>aWriteBegin</tt> is called.
	 */
	private void writeResource(long aUserData, String aUriTail, int aInterface, long aLanguageList, long aWriterData,
			long aWriteBegin,
			long aWriteResource,
			long aWriteEnd)
	{
		List<String> languageList = new LinkedList<String>();
		int count = DvResourceWriterLanguageCount(aLanguageList);
		for (int i = 0; i < count; i++)
		{
			languageList.add(DvResourceWriterLanguage(aLanguageList, i));
		}
		ResourceWriter writer = new ResourceWriter(aWriterData, aWriteBegin, aWriteResource, aWriteEnd);
		writer.write(iResourceManager, aUriTail, aInterface, languageList);
	}

}
