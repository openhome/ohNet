package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderOpenhomeOrgTestLights1
{
        
}

/**
 * Provider for the openhome.org:TestLights:1 UPnP service.
 */
public class DvProviderOpenhomeOrgTestLights1 extends DvProvider implements IDvProviderOpenhomeOrgTestLights1
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

    private IDvInvocationListener iDelegateGetCount;
    private IDvInvocationListener iDelegateGetRoom;
    private IDvInvocationListener iDelegateGetName;
    private IDvInvocationListener iDelegateGetPosition;
    private IDvInvocationListener iDelegateSetColor;
    private IDvInvocationListener iDelegateGetColor;
    private IDvInvocationListener iDelegateGetColorComponents;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderOpenhomeOrgTestLights1(DvDevice aDevice)
    {
        super(aDevice, "openhome.org", "TestLights", 1);
    }

    /**
     * Signal that the action GetCount is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetCount must be overridden if this is called.
     */      
    protected void enableActionGetCount()
    {
        Action action = new Action("GetCount");
        action.addOutputParameter(new ParameterUint("Count"));
        iDelegateGetCount = new DoGetCount();
        enableAction(action, iDelegateGetCount);
    }

    /**
     * Signal that the action GetRoom is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetRoom must be overridden if this is called.
     */      
    protected void enableActionGetRoom()
    {
        Action action = new Action("GetRoom");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("Index"));
        action.addOutputParameter(new ParameterString("RoomName", allowedValues));
        iDelegateGetRoom = new DoGetRoom();
        enableAction(action, iDelegateGetRoom);
    }

    /**
     * Signal that the action GetName is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetName must be overridden if this is called.
     */      
    protected void enableActionGetName()
    {
        Action action = new Action("GetName");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterUint("Index"));
        action.addOutputParameter(new ParameterString("FriendlyName", allowedValues));
        iDelegateGetName = new DoGetName();
        enableAction(action, iDelegateGetName);
    }

    /**
     * Signal that the action GetPosition is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetPosition must be overridden if this is called.
     */      
    protected void enableActionGetPosition()
    {
        Action action = new Action("GetPosition");
        action.addInputParameter(new ParameterUint("Index"));
        action.addOutputParameter(new ParameterUint("X"));
        action.addOutputParameter(new ParameterUint("Y"));
        action.addOutputParameter(new ParameterUint("Z"));
        iDelegateGetPosition = new DoGetPosition();
        enableAction(action, iDelegateGetPosition);
    }

    /**
     * Signal that the action SetColor is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * SetColor must be overridden if this is called.
     */      
    protected void enableActionSetColor()
    {
        Action action = new Action("SetColor");
        action.addInputParameter(new ParameterUint("Index"));
        action.addInputParameter(new ParameterUint("Color"));
        iDelegateSetColor = new DoSetColor();
        enableAction(action, iDelegateSetColor);
    }

    /**
     * Signal that the action GetColor is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetColor must be overridden if this is called.
     */      
    protected void enableActionGetColor()
    {
        Action action = new Action("GetColor");
        action.addInputParameter(new ParameterUint("Index"));
        action.addOutputParameter(new ParameterUint("Color"));
        iDelegateGetColor = new DoGetColor();
        enableAction(action, iDelegateGetColor);
    }

    /**
     * Signal that the action GetColorComponents is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * GetColorComponents must be overridden if this is called.
     */      
    protected void enableActionGetColorComponents()
    {
        Action action = new Action("GetColorComponents");
        action.addInputParameter(new ParameterUint("Color"));
        action.addOutputParameter(new ParameterUint("Brightness"));
        action.addOutputParameter(new ParameterUint("Red"));
        action.addOutputParameter(new ParameterUint("Green"));
        action.addOutputParameter(new ParameterUint("Blue"));
        iDelegateGetColorComponents = new DoGetColorComponents();
        enableAction(action, iDelegateGetColorComponents);
    }

    /**
     * GetCount action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetCount action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetCount} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected long getCount(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetRoom action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetRoom action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetRoom} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIndex
     */
    protected String getRoom(IDvInvocation aInvocation, long aIndex)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetName action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetName action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetName} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIndex
     */
    protected String getName(IDvInvocation aInvocation, long aIndex)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetPosition action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetPosition action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetPosition} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIndex
     */
    protected GetPosition getPosition(IDvInvocation aInvocation, long aIndex)
    {
        throw (new ActionDisabledError());
    }

    /**
     * SetColor action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * SetColor action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionSetColor} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIndex
     * @param aColor
     */
    protected void setColor(IDvInvocation aInvocation, long aIndex, long aColor)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetColor action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetColor action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetColor} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aIndex
     */
    protected long getColor(IDvInvocation aInvocation, long aIndex)
    {
        throw (new ActionDisabledError());
    }

    /**
     * GetColorComponents action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * GetColorComponents action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionGetColorComponents} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aColor
     */
    protected GetColorComponents getColorComponents(IDvInvocation aInvocation, long aColor)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Must be called for each class instance.  Must be called before Core.Library.Close().
     */
    public void dispose()
    {
        synchronized (this)
        {
            if (iHandle == 0)
            {
                return;
            }
            super.dispose();
            iHandle = 0;
        }
    }


    private class DoGetCount implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long count;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 count = getCount(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetCount");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("Count", count);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetRoom implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long index;
            String roomName;
            try
            {
                invocation.readStart();
                index = invocation.readUint("Index");
                invocation.readEnd();
                 roomName = getRoom(invocation, index);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetRoom");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("RoomName", roomName);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetName implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long index;
            String friendlyName;
            try
            {
                invocation.readStart();
                index = invocation.readUint("Index");
                invocation.readEnd();
                 friendlyName = getName(invocation, index);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetName");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeString("FriendlyName", friendlyName);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetPosition implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long index;
            long x;
            long y;
            long z;
            try
            {
                invocation.readStart();
                index = invocation.readUint("Index");
                invocation.readEnd();

            GetPosition outArgs = getPosition(invocation, index);
            x = outArgs.getX();
            y = outArgs.getY();
            z = outArgs.getZ();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetPosition");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("X", x);
                invocation.writeUint("Y", y);
                invocation.writeUint("Z", z);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoSetColor implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long index;
            long color;
            try
            {
                invocation.readStart();
                index = invocation.readUint("Index");
                color = invocation.readUint("Color");
                invocation.readEnd();
                setColor(invocation, index, color);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "SetColor");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetColor implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long index;
            long color;
            try
            {
                invocation.readStart();
                index = invocation.readUint("Index");
                invocation.readEnd();
                 color = getColor(invocation, index);
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetColor");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("Color", color);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }

    private class DoGetColorComponents implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            long color;
            long brightness;
            long red;
            long green;
            long blue;
            try
            {
                invocation.readStart();
                color = invocation.readUint("Color");
                invocation.readEnd();

            GetColorComponents outArgs = getColorComponents(invocation, color);
            brightness = outArgs.getBrightness();
            red = outArgs.getRed();
            green = outArgs.getGreen();
            blue = outArgs.getBlue();
            }
            catch (ActionError ae)
            {
                invocation.reportActionError(ae, "GetColorComponents");
                return;
            }
            catch (PropertyUpdateError pue)
            {
                invocation.reportError(501, "Invalid XML");
                return;
            }
            catch (Exception e)
            {
                System.out.println("WARNING: unexpected exception: " + e.getMessage());
                System.out.println("         Only ActionError or PropertyUpdateError can be thrown by actions");
                e.printStackTrace();
                return;
            }
            try
            {
                invocation.writeStart();
                invocation.writeUint("Brightness", brightness);
                invocation.writeUint("Red", red);
                invocation.writeUint("Green", green);
                invocation.writeUint("Blue", blue);
                invocation.writeEnd();
            }
            catch (ActionError ae)
            {
                return;
            }
            catch (Exception e)
            {
                System.out.println("ERROR: unexpected exception: " + e.getMessage());
                System.out.println("       Only ActionError can be thrown by action response writer");
                e.printStackTrace();
            }
        }
    }
}

