package org.openhome.net.device;

import java.util.List;

/**
 * Helper class for writing resources (files) to native code
 */
public class ResourceWriter implements IResourceWriter
{
	private static native void CallbackWriteResourceBegin(long aWriteBegin, long aWriterData, int aTotalBytes, String aMimeType);
	private static native void CallbackWriteResource(long aWriteResource, long aWriterData, byte[] aData, int aBytes);
	private static native void CallbackWriteResourceEnd(long aWriteEnd, long aWriterData);
	
	static
    {
        System.loadLibrary("ohNet");
        System.loadLibrary("ohNetJni");
    }
	
	private long iWriterData;
	private long iWriteBegin;
	private long iWriteResource;
	private long iWriteEnd;
	
	/**
	 * Create a resource writer.
	 * 
	 * @param aWriterData
	 * @param aWriteBegin
	 * @param aWriteResource
	 * @param aWriteEnd
	 */
	public ResourceWriter(long aWriterData, long aWriteBegin,
			long aWriteResource, long aWriteEnd)
	{
		iWriterData = aWriterData;
		iWriteBegin = aWriteBegin;
		iWriteResource = aWriteResource;
		iWriteEnd = aWriteEnd;
	}
	
	/**
	 * Write resources.
	 * 
	 * @param aManager			resource manager to control writing of resource.
	 * @param aUriTail			file being requested
	 * @param aInterface		network interface the file request was made on.
	 * @param aLanguageList		prioritised list of the languages accepted in
	 * 							the resources to be written. 
	 */
	public void write(IResourceManager aManager, String aUriTail, int aInterface, List<String> aLanguageList)
	{
		aManager.writeResource(aUriTail, aInterface, aLanguageList, this);
	}
	
	/**
	 * Must be called before writing any file data.
	 * 
	 * @param aTotalBytes	size in bytes of the file. Can be 0 if size is unknown.
	 * @param aMimeType		MIME type of the file. May be NULL if this is unknown.
	 */
	public void writeResourceBegin(int aTotalBytes, String aMimeType) {
		CallbackWriteResourceBegin(iWriteBegin, iWriterData, aTotalBytes, aMimeType);
	}

	/**
	 * Called to write a block of file data.
	 * Will be called 0..n times after {@link #writeResourceBegin} and before
	 * <tt>writeResourceEnd()</tt>.
	 * @param aData		file data to write.
	 * @param aBytes	size in bytes of aData.
	 */
	public void writeResource(byte[] aData, int aBytes) {
		CallbackWriteResource(iWriteResource, iWriterData, aData, aBytes);
	}

	/**
	 * Called when serving of a file is complete.
	 * Must only be called after a call to {@link #writeResourceBegin}.
	 * 
	 * An error writing the file can be inferred if {@link #writeResource} has
	 * not been called or if <tt>aTotalBytes</tt> was non-zero in the
	 * {@link #writeResourceBegin} callback and the sum of <tt>aBytes</tt>
	 * values in the {@link #writeResource} callbacks does not match
	 * <tt>aTotalBytes</tt>.
	 */
	public void writeResourceEnd() {
		CallbackWriteResourceEnd(iWriteEnd, iWriterData);
	}

}
