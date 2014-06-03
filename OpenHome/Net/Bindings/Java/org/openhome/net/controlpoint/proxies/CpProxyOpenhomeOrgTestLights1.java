package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyOpenhomeOrgTestLights1.*;
import org.openhome.net.core.*;

    
interface ICpProxyOpenhomeOrgTestLights1 extends ICpProxy
{
    public long syncGetCount();
    public void beginGetCount(ICpProxyListener aCallback);
    public long endGetCount(long aAsyncHandle);
    public String syncGetRoom(long aIndex);
    public void beginGetRoom(long aIndex, ICpProxyListener aCallback);
    public String endGetRoom(long aAsyncHandle);
    public String syncGetName(long aIndex);
    public void beginGetName(long aIndex, ICpProxyListener aCallback);
    public String endGetName(long aAsyncHandle);
    public GetPosition syncGetPosition(long aIndex);
    public void beginGetPosition(long aIndex, ICpProxyListener aCallback);
    public GetPosition endGetPosition(long aAsyncHandle);
    public void syncSetColor(long aIndex, long aColor);
    public void beginSetColor(long aIndex, long aColor, ICpProxyListener aCallback);
    public void endSetColor(long aAsyncHandle);
    public long syncGetColor(long aIndex);
    public void beginGetColor(long aIndex, ICpProxyListener aCallback);
    public long endGetColor(long aAsyncHandle);
    public GetColorComponents syncGetColorComponents(long aColor);
    public void beginGetColorComponents(long aColor, ICpProxyListener aCallback);
    public GetColorComponents endGetColorComponents(long aAsyncHandle);
}

class SyncGetCountOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private long iCount;

    public SyncGetCountOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public long getCount()
    {
        return iCount;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetCount(aAsyncHandle);
        
        iCount = result;
    }
}

class SyncGetRoomOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private String iRoomName;

    public SyncGetRoomOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public String getRoomName()
    {
        return iRoomName;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetRoom(aAsyncHandle);
        
        iRoomName = result;
    }
}

class SyncGetNameOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private String iFriendlyName;

    public SyncGetNameOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public String getFriendlyName()
    {
        return iFriendlyName;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endGetName(aAsyncHandle);
        
        iFriendlyName = result;
    }
}

class SyncGetPositionOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private long iX;
    private long iY;
    private long iZ;

    public SyncGetPositionOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public long getX()
    {
        return iX;
    }
    public long getY()
    {
        return iY;
    }
    public long getZ()
    {
        return iZ;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetPosition result = iService.endGetPosition(aAsyncHandle);
        
        iX = result.getX();
        iY = result.getY();
        iZ = result.getZ();
    }
}

class SyncSetColorOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;

    public SyncSetColorOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetColor(aAsyncHandle);
        
    }
}

class SyncGetColorOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private long iColor;

    public SyncGetColorOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public long getColor()
    {
        return iColor;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endGetColor(aAsyncHandle);
        
        iColor = result;
    }
}

class SyncGetColorComponentsOpenhomeOrgTestLights1 extends SyncProxyAction
{
    private CpProxyOpenhomeOrgTestLights1 iService;
    private long iBrightness;
    private long iRed;
    private long iGreen;
    private long iBlue;

    public SyncGetColorComponentsOpenhomeOrgTestLights1(CpProxyOpenhomeOrgTestLights1 aProxy)
    {
        iService = aProxy;
    }
    public long getBrightness()
    {
        return iBrightness;
    }
    public long getRed()
    {
        return iRed;
    }
    public long getGreen()
    {
        return iGreen;
    }
    public long getBlue()
    {
        return iBlue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        GetColorComponents result = iService.endGetColorComponents(aAsyncHandle);
        
        iBrightness = result.getBrightness();
        iRed = result.getRed();
        iGreen = result.getGreen();
        iBlue = result.getBlue();
    }
}

/**
 * Proxy for the openhome.org:TestLights:1 UPnP service
 */
public class CpProxyOpenhomeOrgTestLights1 extends CpProxy implements ICpProxyOpenhomeOrgTestLights1
{

    public class GetPosition
    {
        private long iX;
        private long iY;
        private long iZ;

        public GetPosition(
            long aX,
            long aY,
            long aZ
        )
        {
            iX = aX;
            iY = aY;
            iZ = aZ;
        }
        public long getX()
        {
            return iX;
        }
        public long getY()
        {
            return iY;
        }
        public long getZ()
        {
            return iZ;
        }
    }

    public class GetColorComponents
    {
        private long iBrightness;
        private long iRed;
        private long iGreen;
        private long iBlue;

        public GetColorComponents(
            long aBrightness,
            long aRed,
            long aGreen,
            long aBlue
        )
        {
            iBrightness = aBrightness;
            iRed = aRed;
            iGreen = aGreen;
            iBlue = aBlue;
        }
        public long getBrightness()
        {
            return iBrightness;
        }
        public long getRed()
        {
            return iRed;
        }
        public long getGreen()
        {
            return iGreen;
        }
        public long getBlue()
        {
            return iBlue;
        }
    }

    private Action iActionGetCount;
    private Action iActionGetRoom;
    private Action iActionGetName;
    private Action iActionGetPosition;
    private Action iActionSetColor;
    private Action iActionGetColor;
    private Action iActionGetColorComponents;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyOpenhomeOrgTestLights1(CpDevice aDevice)
    {
        super("openhome-org", "TestLights", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionGetCount = new Action("GetCount");
        param = new ParameterUint("Count");
        iActionGetCount.addOutputParameter(param);

        iActionGetRoom = new Action("GetRoom");
        param = new ParameterUint("Index");
        iActionGetRoom.addInputParameter(param);
        param = new ParameterString("RoomName", allowedValues);
        iActionGetRoom.addOutputParameter(param);

        iActionGetName = new Action("GetName");
        param = new ParameterUint("Index");
        iActionGetName.addInputParameter(param);
        param = new ParameterString("FriendlyName", allowedValues);
        iActionGetName.addOutputParameter(param);

        iActionGetPosition = new Action("GetPosition");
        param = new ParameterUint("Index");
        iActionGetPosition.addInputParameter(param);
        param = new ParameterUint("X");
        iActionGetPosition.addOutputParameter(param);
        param = new ParameterUint("Y");
        iActionGetPosition.addOutputParameter(param);
        param = new ParameterUint("Z");
        iActionGetPosition.addOutputParameter(param);

        iActionSetColor = new Action("SetColor");
        param = new ParameterUint("Index");
        iActionSetColor.addInputParameter(param);
        param = new ParameterUint("Color");
        iActionSetColor.addInputParameter(param);

        iActionGetColor = new Action("GetColor");
        param = new ParameterUint("Index");
        iActionGetColor.addInputParameter(param);
        param = new ParameterUint("Color");
        iActionGetColor.addOutputParameter(param);

        iActionGetColorComponents = new Action("GetColorComponents");
        param = new ParameterUint("Color");
        iActionGetColorComponents.addInputParameter(param);
        param = new ParameterUint("Brightness");
        iActionGetColorComponents.addOutputParameter(param);
        param = new ParameterUint("Red");
        iActionGetColorComponents.addOutputParameter(param);
        param = new ParameterUint("Green");
        iActionGetColorComponents.addOutputParameter(param);
        param = new ParameterUint("Blue");
        iActionGetColorComponents.addOutputParameter(param);
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetCount()
    {
        SyncGetCountOpenhomeOrgTestLights1 sync = new SyncGetCountOpenhomeOrgTestLights1(this);
        beginGetCount(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getCount();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetCount}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetCount(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetCount, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetCount.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetCount} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetCount} method.
     * @return the result of the previously invoked action.
     */
    public long endGetCount(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long count = Invocation.getOutputUint(aAsyncHandle, index++);
        return count;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetRoom(long aIndex)
    {
        SyncGetRoomOpenhomeOrgTestLights1 sync = new SyncGetRoomOpenhomeOrgTestLights1(this);
        beginGetRoom(aIndex, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getRoomName();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetRoom}.
     * 
     * @param aIndex
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetRoom(long aIndex, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetRoom, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetRoom.getInputParameter(inIndex++), aIndex));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetRoom.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetRoom} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetRoom} method.
     * @return the result of the previously invoked action.
     */
    public String endGetRoom(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String roomName = Invocation.getOutputString(aAsyncHandle, index++);
        return roomName;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncGetName(long aIndex)
    {
        SyncGetNameOpenhomeOrgTestLights1 sync = new SyncGetNameOpenhomeOrgTestLights1(this);
        beginGetName(aIndex, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getFriendlyName();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetName}.
     * 
     * @param aIndex
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetName(long aIndex, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetName, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetName.getInputParameter(inIndex++), aIndex));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionGetName.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetName} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetName} method.
     * @return the result of the previously invoked action.
     */
    public String endGetName(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String friendlyName = Invocation.getOutputString(aAsyncHandle, index++);
        return friendlyName;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetPosition syncGetPosition(long aIndex)
    {
        SyncGetPositionOpenhomeOrgTestLights1 sync = new SyncGetPositionOpenhomeOrgTestLights1(this);
        beginGetPosition(aIndex, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetPosition(
            sync.getX(),
            sync.getY(),
            sync.getZ()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetPosition}.
     * 
     * @param aIndex
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetPosition(long aIndex, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetPosition, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetPosition.getInputParameter(inIndex++), aIndex));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetPosition.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetPosition.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetPosition.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetPosition} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetPosition} method.
     * @return the result of the previously invoked action.
     */
    public GetPosition endGetPosition(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long x = Invocation.getOutputUint(aAsyncHandle, index++);
        long y = Invocation.getOutputUint(aAsyncHandle, index++);
        long z = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetPosition(
            x,
            y,
            z
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetColor(long aIndex, long aColor)
    {
        SyncSetColorOpenhomeOrgTestLights1 sync = new SyncSetColorOpenhomeOrgTestLights1(this);
        beginSetColor(aIndex, aColor, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetColor}.
     * 
     * @param aIndex
     * @param aColor
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetColor(long aIndex, long aColor, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetColor, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetColor.getInputParameter(inIndex++), aIndex));
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetColor.getInputParameter(inIndex++), aColor));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetColor} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetColor} method.
     */
    public void endSetColor(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncGetColor(long aIndex)
    {
        SyncGetColorOpenhomeOrgTestLights1 sync = new SyncGetColorOpenhomeOrgTestLights1(this);
        beginGetColor(aIndex, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getColor();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetColor}.
     * 
     * @param aIndex
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetColor(long aIndex, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetColor, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetColor.getInputParameter(inIndex++), aIndex));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColor.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetColor} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetColor} method.
     * @return the result of the previously invoked action.
     */
    public long endGetColor(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long color = Invocation.getOutputUint(aAsyncHandle, index++);
        return color;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public GetColorComponents syncGetColorComponents(long aColor)
    {
        SyncGetColorComponentsOpenhomeOrgTestLights1 sync = new SyncGetColorComponentsOpenhomeOrgTestLights1(this);
        beginGetColorComponents(aColor, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new GetColorComponents(
            sync.getBrightness(),
            sync.getRed(),
            sync.getGreen(),
            sync.getBlue()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endGetColorComponents}.
     * 
     * @param aColor
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginGetColorComponents(long aColor, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionGetColorComponents, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionGetColorComponents.getInputParameter(inIndex++), aColor));
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionGetColorComponents.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginGetColorComponents} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginGetColorComponents} method.
     * @return the result of the previously invoked action.
     */
    public GetColorComponents endGetColorComponents(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long brightness = Invocation.getOutputUint(aAsyncHandle, index++);
        long red = Invocation.getOutputUint(aAsyncHandle, index++);
        long green = Invocation.getOutputUint(aAsyncHandle, index++);
        long blue = Invocation.getOutputUint(aAsyncHandle, index++);
        return new GetColorComponents(
            brightness,
            red,
            green,
            blue
        );
    }
        

    /**
     * Dispose of this control point proxy.
     * Must be called for each class instance.
     * Must be called before <tt>Library.close()</tt>.
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            disposeProxy();
            iHandle = 0;
            iActionGetCount.destroy();
            iActionGetRoom.destroy();
            iActionGetName.destroy();
            iActionGetPosition.destroy();
            iActionSetColor.destroy();
            iActionGetColor.destroy();
            iActionGetColorComponents.destroy();
        }
    }
}

