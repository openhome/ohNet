package org.openhome.net.device;

/**
 * Interface passed to implementors of DvDevice allowing them to serve UI files to Control Points.
 */
public interface IResourceWriter
{

	/**
	 * Must be called before writing any file data.
	 * 
	 * @param aTotalBytes	size in bytes of the file. Can be 0 if size is unknown.
	 * @param aMimeType		MIME type of the file. May be NULL if this is unknown.
	 */
	public void writeResourceBegin(int aTotalBytes, String aMimeType);

	/**
	 * Called to write a block of file data.
	 * Will be called 0..n times after {@link #writeResourceBegin} and before
	 * {@link #writeResourceEnd}.
	 * @param aData		file data to write.
	 * @param aBytes	size in bytes of aData.
	 */
	public void writeResource(byte[] aData, int aBytes);
	
	/**
	 * Called when serving of a file is complete.
	 * Must only be called after a call to {@link #writeResourceBegin}.
	 * 
	 * An error writing the file can be inferred if {@link #writeResource} has
	 * not been called or if {@code aTotalBytes} was non-zero in the
	 * {@link #writeResourceBegin} callback and the sum of {@code aBytes}
	 * values in the {@link #writeResource} callbacks does not match
	 * {@code aTotalBytes}.
	 */
	public void writeResourceEnd();
}
