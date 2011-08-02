package org.openhome.net.core;

/**
 * Class representing an exception in the OhNet library.
 */
public class LibraryException extends RuntimeException {
	
	/**
	 * Create a default library exception.
	 */
	public LibraryException() { }
	
	/**
	 * Create a library exception with the given message.
	 * 
	 * @param aMessage	Message indicating the nature of the exception.
	 */
	public LibraryException(String aMessage)
	{
		super(aMessage);
	}

}
