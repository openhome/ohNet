package org.openhome.net.core;

/**
 * Thrown when getValue() is called on a Property whose value has never been set.
 */
public class PropertyError extends RuntimeException
{
    /**
     * Create a default property error object.
     */
    public PropertyError() { }

    /**
     * Create a property error object with the given message.
     *
     * @param aMessage  Message indicating the nature of the error.
     */
    public PropertyError(String aMessage)
    {
        super(aMessage);
    }
}
