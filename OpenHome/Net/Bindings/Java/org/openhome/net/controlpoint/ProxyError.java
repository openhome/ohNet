package org.openhome.net.controlpoint;

public class ProxyError extends RuntimeException
{
    private int iErrorCode;

    public ProxyError()
    {
        super();
    }

    public ProxyError(int aErrorCode)
    {
        super();
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
