package org.openhome.net.device;

/**
 * Thrown when an invoked action fails.  Will not be visible to external code.
 */
public class ActionError extends RuntimeException
{
    private int iErrorCode;

    public ActionError()
    {
        super();
    }

    public ActionError(String aMessage)
    {
        super(aMessage);
    }

    public ActionError(String aMessage, int aErrorCode)
    {
        super(aMessage);
        iErrorCode = aErrorCode;
    }

    /**
     * Return the error code.
     * 
     * @return  the error code.
     */
    public int getErrorCode()
    {
        return iErrorCode;
    }
}
