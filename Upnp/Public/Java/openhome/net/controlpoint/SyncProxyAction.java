package openhome.net.controlpoint;

import java.util.concurrent.Semaphore;

public abstract class SyncProxyAction {
	
	private class AsyncCompleteListener implements ICpProxyListener
	{

		public void callbackAsyncComplete(long aAsyncHandle) {
			{
				try
				{
					completeRequest(aAsyncHandle);
				}
				catch (ProxyError pe)
				{
					iError = true;
				}
				catch (Exception e)
				{
					System.out.println("ERROR: unexpected exception thrown: " + e.getMessage() + "\nStack trace: " + e.getStackTrace());
					System.out.println("       Only ProxyError can be thrown by action complete delegates");
				}
//				iSem.release();
				synchronized (iSem)
				{
					iSem.notify();
				}
			}
		}

		public void callbackActionComplete(long aPtr, long aAsyncHandle) {}
		public void callback(long aPtr) {}
	}
	
	private ICpProxyListener iAsyncComplete;
    private Semaphore iSem;
    private boolean iError;
    
    protected SyncProxyAction()
    {
        iAsyncComplete = new AsyncCompleteListener();
        iSem = new Semaphore(1);
    }
    
    public ICpProxyListener getListener()
    {
        return iAsyncComplete;
    }

    public void waitToComplete()
    {
        try {
			synchronized (iSem)
			{
				iSem.wait();
//	        	iSem.acquire();
//				Thread.sleep(5000);
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    }

    public void reportError()
    {
        if (iError)
        {
            throw new ProxyError();
        }
    }

    protected abstract void completeRequest(long aAsyncHandle) throws ProxyError;

}
