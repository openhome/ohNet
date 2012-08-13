package org.openhome.net.controlpoint;

public class ProxyError extends RuntimeException
{
    private int iErrorCode;
    private String iErrorDesc;

    public ProxyError()
    {
        super();
    }

    public ProxyError(String aMessage)
    {
        super(aMessage);
    }

    public ProxyError(int aErrorCode, String aErrorDesc)
    {
        super(String.format("%d: %s", aErrorCode, aErrorDesc));
        iErrorCode = aErrorCode;
        iErrorDesc = aErrorDesc;
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

    /**
     * Return the error description.
     * 
     * @return  the error description.
     */
    public String getErrorDescription()
    {
        return iErrorDesc;
    }
}
