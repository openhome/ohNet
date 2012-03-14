package org.openhome.net.device.providers;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.core.*;
import org.openhome.net.device.*;

interface IDvProviderAvOpenhomeOrgMediaServer1
{

    /**
     * Set the value of the ManufacturerName property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyManufacturerName(String aValue);

    /**
     * Get a copy of the value of the ManufacturerName property
     *
     * @return value of the ManufacturerName property.
     */
    public String getPropertyManufacturerName();

    /**
     * Set the value of the ManufacturerInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyManufacturerInfo(String aValue);

    /**
     * Get a copy of the value of the ManufacturerInfo property
     *
     * @return value of the ManufacturerInfo property.
     */
    public String getPropertyManufacturerInfo();

    /**
     * Set the value of the ManufacturerUrl property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyManufacturerUrl(String aValue);

    /**
     * Get a copy of the value of the ManufacturerUrl property
     *
     * @return value of the ManufacturerUrl property.
     */
    public String getPropertyManufacturerUrl();

    /**
     * Set the value of the ManufacturerImageUri property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyManufacturerImageUri(String aValue);

    /**
     * Get a copy of the value of the ManufacturerImageUri property
     *
     * @return value of the ManufacturerImageUri property.
     */
    public String getPropertyManufacturerImageUri();

    /**
     * Set the value of the ModelName property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyModelName(String aValue);

    /**
     * Get a copy of the value of the ModelName property
     *
     * @return value of the ModelName property.
     */
    public String getPropertyModelName();

    /**
     * Set the value of the ModelInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyModelInfo(String aValue);

    /**
     * Get a copy of the value of the ModelInfo property
     *
     * @return value of the ModelInfo property.
     */
    public String getPropertyModelInfo();

    /**
     * Set the value of the ModelUrl property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyModelUrl(String aValue);

    /**
     * Get a copy of the value of the ModelUrl property
     *
     * @return value of the ModelUrl property.
     */
    public String getPropertyModelUrl();

    /**
     * Set the value of the ModelImageUri property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyModelImageUri(String aValue);

    /**
     * Get a copy of the value of the ModelImageUri property
     *
     * @return value of the ModelImageUri property.
     */
    public String getPropertyModelImageUri();

    /**
     * Set the value of the ProductName property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyProductName(String aValue);

    /**
     * Get a copy of the value of the ProductName property
     *
     * @return value of the ProductName property.
     */
    public String getPropertyProductName();

    /**
     * Set the value of the ProductInfo property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyProductInfo(String aValue);

    /**
     * Get a copy of the value of the ProductInfo property
     *
     * @return value of the ProductInfo property.
     */
    public String getPropertyProductInfo();

    /**
     * Set the value of the ProductUrl property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyProductUrl(String aValue);

    /**
     * Get a copy of the value of the ProductUrl property
     *
     * @return value of the ProductUrl property.
     */
    public String getPropertyProductUrl();

    /**
     * Set the value of the ProductImageUri property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyProductImageUri(String aValue);

    /**
     * Get a copy of the value of the ProductImageUri property
     *
     * @return value of the ProductImageUri property.
     */
    public String getPropertyProductImageUri();

    /**
     * Set the value of the Attributes property
     *
     * @param aValue    new value for the property.
     * @return      <tt>true</tt> if the value has been updated; <tt>false</tt> if <tt>aValue</tt> was the same as the previous value.
     *
     */
    public boolean setPropertyAttributes(String aValue);

    /**
     * Get a copy of the value of the Attributes property
     *
     * @return value of the Attributes property.
     */
    public String getPropertyAttributes();
        
}

/**
 * Provider for the av.openhome.org:MediaServer:1 UPnP service.
 */
public class DvProviderAvOpenhomeOrgMediaServer1 extends DvProvider implements IDvProviderAvOpenhomeOrgMediaServer1
{

    public class Manufacturer
    {
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public Manufacturer(
            String aName,
            String aInfo,
            String aUrl,
            String aImageUri
        )
        {
            iName = aName;
            iInfo = aInfo;
            iUrl = aUrl;
            iImageUri = aImageUri;
        }
        public String getName()
        {
            return iName;
        }
        public String getInfo()
        {
            return iInfo;
        }
        public String getUrl()
        {
            return iUrl;
        }
        public String getImageUri()
        {
            return iImageUri;
        }
    }

    public class Model
    {
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public Model(
            String aName,
            String aInfo,
            String aUrl,
            String aImageUri
        )
        {
            iName = aName;
            iInfo = aInfo;
            iUrl = aUrl;
            iImageUri = aImageUri;
        }
        public String getName()
        {
            return iName;
        }
        public String getInfo()
        {
            return iInfo;
        }
        public String getUrl()
        {
            return iUrl;
        }
        public String getImageUri()
        {
            return iImageUri;
        }
    }

    public class Product
    {
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public Product(
            String aName,
            String aInfo,
            String aUrl,
            String aImageUri
        )
        {
            iName = aName;
            iInfo = aInfo;
            iUrl = aUrl;
            iImageUri = aImageUri;
        }
        public String getName()
        {
            return iName;
        }
        public String getInfo()
        {
            return iInfo;
        }
        public String getUrl()
        {
            return iUrl;
        }
        public String getImageUri()
        {
            return iImageUri;
        }
    }

    private IDvInvocationListener iDelegateManufacturer;
    private IDvInvocationListener iDelegateModel;
    private IDvInvocationListener iDelegateProduct;
    private IDvInvocationListener iDelegateAttributes;
    private IDvInvocationListener iDelegateQuery;
    private PropertyString iPropertyManufacturerName;
    private PropertyString iPropertyManufacturerInfo;
    private PropertyString iPropertyManufacturerUrl;
    private PropertyString iPropertyManufacturerImageUri;
    private PropertyString iPropertyModelName;
    private PropertyString iPropertyModelInfo;
    private PropertyString iPropertyModelUrl;
    private PropertyString iPropertyModelImageUri;
    private PropertyString iPropertyProductName;
    private PropertyString iPropertyProductInfo;
    private PropertyString iPropertyProductUrl;
    private PropertyString iPropertyProductImageUri;
    private PropertyString iPropertyAttributes;

    /**
     * Constructor
     *
     * @param aDevice   device which owns this provider.
     */
    protected DvProviderAvOpenhomeOrgMediaServer1(DvDevice aDevice)
    {
        super(aDevice, "av.openhome.org", "MediaServer", 1);
    }

    /**
     * Enable the ManufacturerName property.
     */
    public void enablePropertyManufacturerName()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyManufacturerName = new PropertyString(new ParameterString("ManufacturerName", allowedValues));
        addProperty(iPropertyManufacturerName);
    }

    /**
     * Enable the ManufacturerInfo property.
     */
    public void enablePropertyManufacturerInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyManufacturerInfo = new PropertyString(new ParameterString("ManufacturerInfo", allowedValues));
        addProperty(iPropertyManufacturerInfo);
    }

    /**
     * Enable the ManufacturerUrl property.
     */
    public void enablePropertyManufacturerUrl()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyManufacturerUrl = new PropertyString(new ParameterString("ManufacturerUrl", allowedValues));
        addProperty(iPropertyManufacturerUrl);
    }

    /**
     * Enable the ManufacturerImageUri property.
     */
    public void enablePropertyManufacturerImageUri()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyManufacturerImageUri = new PropertyString(new ParameterString("ManufacturerImageUri", allowedValues));
        addProperty(iPropertyManufacturerImageUri);
    }

    /**
     * Enable the ModelName property.
     */
    public void enablePropertyModelName()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyModelName = new PropertyString(new ParameterString("ModelName", allowedValues));
        addProperty(iPropertyModelName);
    }

    /**
     * Enable the ModelInfo property.
     */
    public void enablePropertyModelInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyModelInfo = new PropertyString(new ParameterString("ModelInfo", allowedValues));
        addProperty(iPropertyModelInfo);
    }

    /**
     * Enable the ModelUrl property.
     */
    public void enablePropertyModelUrl()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyModelUrl = new PropertyString(new ParameterString("ModelUrl", allowedValues));
        addProperty(iPropertyModelUrl);
    }

    /**
     * Enable the ModelImageUri property.
     */
    public void enablePropertyModelImageUri()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyModelImageUri = new PropertyString(new ParameterString("ModelImageUri", allowedValues));
        addProperty(iPropertyModelImageUri);
    }

    /**
     * Enable the ProductName property.
     */
    public void enablePropertyProductName()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyProductName = new PropertyString(new ParameterString("ProductName", allowedValues));
        addProperty(iPropertyProductName);
    }

    /**
     * Enable the ProductInfo property.
     */
    public void enablePropertyProductInfo()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyProductInfo = new PropertyString(new ParameterString("ProductInfo", allowedValues));
        addProperty(iPropertyProductInfo);
    }

    /**
     * Enable the ProductUrl property.
     */
    public void enablePropertyProductUrl()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyProductUrl = new PropertyString(new ParameterString("ProductUrl", allowedValues));
        addProperty(iPropertyProductUrl);
    }

    /**
     * Enable the ProductImageUri property.
     */
    public void enablePropertyProductImageUri()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyProductImageUri = new PropertyString(new ParameterString("ProductImageUri", allowedValues));
        addProperty(iPropertyProductImageUri);
    }

    /**
     * Enable the Attributes property.
     */
    public void enablePropertyAttributes()
    {
        List<String> allowedValues = new LinkedList<String>();
        iPropertyAttributes = new PropertyString(new ParameterString("Attributes", allowedValues));
        addProperty(iPropertyAttributes);
    }

    /**
     * Set the value of the ManufacturerName property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyManufacturerName(String aValue)
    {
        return setPropertyString(iPropertyManufacturerName, aValue);
    }

    /**
     * Get a copy of the value of the ManufacturerName property
     *
     * @return  value of the ManufacturerName property.
     */
    public String getPropertyManufacturerName()
    {
        return iPropertyManufacturerName.getValue();
    }

    /**
     * Set the value of the ManufacturerInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyManufacturerInfo(String aValue)
    {
        return setPropertyString(iPropertyManufacturerInfo, aValue);
    }

    /**
     * Get a copy of the value of the ManufacturerInfo property
     *
     * @return  value of the ManufacturerInfo property.
     */
    public String getPropertyManufacturerInfo()
    {
        return iPropertyManufacturerInfo.getValue();
    }

    /**
     * Set the value of the ManufacturerUrl property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyManufacturerUrl(String aValue)
    {
        return setPropertyString(iPropertyManufacturerUrl, aValue);
    }

    /**
     * Get a copy of the value of the ManufacturerUrl property
     *
     * @return  value of the ManufacturerUrl property.
     */
    public String getPropertyManufacturerUrl()
    {
        return iPropertyManufacturerUrl.getValue();
    }

    /**
     * Set the value of the ManufacturerImageUri property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyManufacturerImageUri(String aValue)
    {
        return setPropertyString(iPropertyManufacturerImageUri, aValue);
    }

    /**
     * Get a copy of the value of the ManufacturerImageUri property
     *
     * @return  value of the ManufacturerImageUri property.
     */
    public String getPropertyManufacturerImageUri()
    {
        return iPropertyManufacturerImageUri.getValue();
    }

    /**
     * Set the value of the ModelName property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyModelName(String aValue)
    {
        return setPropertyString(iPropertyModelName, aValue);
    }

    /**
     * Get a copy of the value of the ModelName property
     *
     * @return  value of the ModelName property.
     */
    public String getPropertyModelName()
    {
        return iPropertyModelName.getValue();
    }

    /**
     * Set the value of the ModelInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyModelInfo(String aValue)
    {
        return setPropertyString(iPropertyModelInfo, aValue);
    }

    /**
     * Get a copy of the value of the ModelInfo property
     *
     * @return  value of the ModelInfo property.
     */
    public String getPropertyModelInfo()
    {
        return iPropertyModelInfo.getValue();
    }

    /**
     * Set the value of the ModelUrl property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyModelUrl(String aValue)
    {
        return setPropertyString(iPropertyModelUrl, aValue);
    }

    /**
     * Get a copy of the value of the ModelUrl property
     *
     * @return  value of the ModelUrl property.
     */
    public String getPropertyModelUrl()
    {
        return iPropertyModelUrl.getValue();
    }

    /**
     * Set the value of the ModelImageUri property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyModelImageUri(String aValue)
    {
        return setPropertyString(iPropertyModelImageUri, aValue);
    }

    /**
     * Get a copy of the value of the ModelImageUri property
     *
     * @return  value of the ModelImageUri property.
     */
    public String getPropertyModelImageUri()
    {
        return iPropertyModelImageUri.getValue();
    }

    /**
     * Set the value of the ProductName property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyProductName(String aValue)
    {
        return setPropertyString(iPropertyProductName, aValue);
    }

    /**
     * Get a copy of the value of the ProductName property
     *
     * @return  value of the ProductName property.
     */
    public String getPropertyProductName()
    {
        return iPropertyProductName.getValue();
    }

    /**
     * Set the value of the ProductInfo property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyProductInfo(String aValue)
    {
        return setPropertyString(iPropertyProductInfo, aValue);
    }

    /**
     * Get a copy of the value of the ProductInfo property
     *
     * @return  value of the ProductInfo property.
     */
    public String getPropertyProductInfo()
    {
        return iPropertyProductInfo.getValue();
    }

    /**
     * Set the value of the ProductUrl property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyProductUrl(String aValue)
    {
        return setPropertyString(iPropertyProductUrl, aValue);
    }

    /**
     * Get a copy of the value of the ProductUrl property
     *
     * @return  value of the ProductUrl property.
     */
    public String getPropertyProductUrl()
    {
        return iPropertyProductUrl.getValue();
    }

    /**
     * Set the value of the ProductImageUri property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyProductImageUri(String aValue)
    {
        return setPropertyString(iPropertyProductImageUri, aValue);
    }

    /**
     * Get a copy of the value of the ProductImageUri property
     *
     * @return  value of the ProductImageUri property.
     */
    public String getPropertyProductImageUri()
    {
        return iPropertyProductImageUri.getValue();
    }

    /**
     * Set the value of the Attributes property
     *
     * @param aValue    new value for the property.
     * @return <tt>true</tt> if the value has been updated; <tt>false</tt>
     * if <tt>aValue</tt> was the same as the previous value.
     */
    public boolean setPropertyAttributes(String aValue)
    {
        return setPropertyString(iPropertyAttributes, aValue);
    }

    /**
     * Get a copy of the value of the Attributes property
     *
     * @return  value of the Attributes property.
     */
    public String getPropertyAttributes()
    {
        return iPropertyAttributes.getValue();
    }

    /**
     * Signal that the action Manufacturer is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Manufacturer must be overridden if this is called.
     */      
    protected void enableActionManufacturer()
    {
        Action action = new Action("Manufacturer");
        action.addOutputParameter(new ParameterRelated("Name", iPropertyManufacturerName));
        action.addOutputParameter(new ParameterRelated("Info", iPropertyManufacturerInfo));
        action.addOutputParameter(new ParameterRelated("Url", iPropertyManufacturerUrl));
        action.addOutputParameter(new ParameterRelated("ImageUri", iPropertyManufacturerImageUri));
        iDelegateManufacturer = new DoManufacturer();
        enableAction(action, iDelegateManufacturer);
    }

    /**
     * Signal that the action Model is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Model must be overridden if this is called.
     */      
    protected void enableActionModel()
    {
        Action action = new Action("Model");
        action.addOutputParameter(new ParameterRelated("Name", iPropertyModelName));
        action.addOutputParameter(new ParameterRelated("Info", iPropertyModelInfo));
        action.addOutputParameter(new ParameterRelated("Url", iPropertyModelUrl));
        action.addOutputParameter(new ParameterRelated("ImageUri", iPropertyModelImageUri));
        iDelegateModel = new DoModel();
        enableAction(action, iDelegateModel);
    }

    /**
     * Signal that the action Product is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Product must be overridden if this is called.
     */      
    protected void enableActionProduct()
    {
        Action action = new Action("Product");
        action.addOutputParameter(new ParameterRelated("Name", iPropertyProductName));
        action.addOutputParameter(new ParameterRelated("Info", iPropertyProductInfo));
        action.addOutputParameter(new ParameterRelated("Url", iPropertyProductUrl));
        action.addOutputParameter(new ParameterRelated("ImageUri", iPropertyProductImageUri));
        iDelegateProduct = new DoProduct();
        enableAction(action, iDelegateProduct);
    }

    /**
     * Signal that the action Attributes is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Attributes must be overridden if this is called.
     */      
    protected void enableActionAttributes()
    {
        Action action = new Action("Attributes");
        action.addOutputParameter(new ParameterRelated("Value", iPropertyAttributes));
        iDelegateAttributes = new DoAttributes();
        enableAction(action, iDelegateAttributes);
    }

    /**
     * Signal that the action Query is supported.
     *
     * <p>The action's availability will be published in the device's service.xml.
     * Query must be overridden if this is called.
     */      
    protected void enableActionQuery()
    {
        Action action = new Action("Query");        List<String> allowedValues = new LinkedList<String>();
        action.addInputParameter(new ParameterString("Request", allowedValues));
        action.addOutputParameter(new ParameterString("Result", allowedValues));
        iDelegateQuery = new DoQuery();
        enableAction(action, iDelegateQuery);
    }

    /**
     * Manufacturer action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Manufacturer action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionManufacturer} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Manufacturer manufacturer(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Model action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Model action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionModel} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Model model(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Product action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Product action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionProduct} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected Product product(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Attributes action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Attributes action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionAttributes} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     */
    protected String attributes(IDvInvocation aInvocation)
    {
        throw (new ActionDisabledError());
    }

    /**
     * Query action.
     *
     * <p>Will be called when the device stack receives an invocation of the
     * Query action for the owning device.
     *
     * <p>Must be implemented iff {@link #enableActionQuery} was called.</remarks>
     *
     * @param aInvocation   Interface allowing querying of aspects of this particular action invocation.</param>
     * @param aRequest
     */
    protected String query(IDvInvocation aInvocation, String aRequest)
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


    private class DoManufacturer implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String name;
            String info;
            String url;
            String imageUri;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Manufacturer outArgs = manufacturer(invocation);
            name = outArgs.getName();
            info = outArgs.getInfo();
            url = outArgs.getUrl();
            imageUri = outArgs.getImageUri();
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Name", name);
                invocation.writeString("Info", info);
                invocation.writeString("Url", url);
                invocation.writeString("ImageUri", imageUri);
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

    private class DoModel implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String name;
            String info;
            String url;
            String imageUri;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Model outArgs = model(invocation);
            name = outArgs.getName();
            info = outArgs.getInfo();
            url = outArgs.getUrl();
            imageUri = outArgs.getImageUri();
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Name", name);
                invocation.writeString("Info", info);
                invocation.writeString("Url", url);
                invocation.writeString("ImageUri", imageUri);
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

    private class DoProduct implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String name;
            String info;
            String url;
            String imageUri;
            try
            {
                invocation.readStart();
                invocation.readEnd();

            Product outArgs = product(invocation);
            name = outArgs.getName();
            info = outArgs.getInfo();
            url = outArgs.getUrl();
            imageUri = outArgs.getImageUri();
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Name", name);
                invocation.writeString("Info", info);
                invocation.writeString("Url", url);
                invocation.writeString("ImageUri", imageUri);
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

    private class DoAttributes implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String value;
            try
            {
                invocation.readStart();
                invocation.readEnd();
                 value = attributes(invocation);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Value", value);
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

    private class DoQuery implements IDvInvocationListener
    {
        public void actionInvoked(long aInvocation)
        {
            DvInvocation invocation = new DvInvocation(aInvocation);
            String request;
            String result;
            try
            {
                invocation.readStart();
                request = invocation.readString("Request");
                invocation.readEnd();
                 result = query(invocation, request);
            }
            catch (ActionError ae)
            {
                invocation.reportError(501, "Invalid XML");
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
                invocation.writeString("Result", result);
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

