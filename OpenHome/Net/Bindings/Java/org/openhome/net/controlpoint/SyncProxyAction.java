package org.openhome.net.controlpoint;

import java.util.concurrent.Semaphore;


public abstract class SyncProxyAction {
	
	private class AsyncCompleteListener implements ICpProxyListener
	{

		public void callbackAsyncComplete(long aAsyncHandle)
		{
			try
			{
				completeRequest(aAsyncHandle);
			}
			catch (ProxyError pe)
			{
				iProxyError = pe;
			}
			catch (Throwable e)
			{
                iProxyError = new ProxyError();
				System.err.println("ERROR: unexpected exception thrown: " + e);
				System.err.println("       Only ProxyError can be thrown by action complete delegates");
				e.printStackTrace();
			}
			iSem.release();
//			synchronized (iSem)
//			{
//				iSem.notify();
//			}
		}

		public void callbackActionComplete(long aPtr, long aAsyncHandle) {}
		public void callback(long aPtr) {}
	}
	
	private ICpProxyListener iAsyncComplete;
    private Semaphore iSem;
    private ProxyError iProxyError;
    
    protected SyncProxyAction()
    {
        iAsyncComplete = new AsyncCompleteListener();
        iSem = new Semaphore(1, true);
        try {
			iSem.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    }
    
    public ICpProxyListener getListener()
    {
        return iAsyncComplete;
    }

    public void waitToComplete()
    {
    	try {
    		iSem.acquire();
    	}
    	catch (InterruptedException e)
    	{
    		e.printStackTrace();
    	}
    }

    public void reportError()
    {
        if (iProxyError != null)
        {
			// create a new ProxyError with a meaningful stack trace
			throw new ProxyError(iProxyError.getErrorCode(), iProxyError.getErrorDescription());
        }
    }

    protected abstract void completeRequest(long aAsyncHandle) throws ProxyError;

}
