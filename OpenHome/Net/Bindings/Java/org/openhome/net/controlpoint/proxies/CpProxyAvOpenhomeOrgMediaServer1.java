package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgMediaServer1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgMediaServer1 extends ICpProxy
{
    public Manufacturer syncManufacturer();
    public void beginManufacturer(ICpProxyListener aCallback);
    public Manufacturer endManufacturer(long aAsyncHandle);
    public Model syncModel();
    public void beginModel(ICpProxyListener aCallback);
    public Model endModel(long aAsyncHandle);
    public Product syncProduct();
    public void beginProduct(ICpProxyListener aCallback);
    public Product endProduct(long aAsyncHandle);
    public String syncAttributes();
    public void beginAttributes(ICpProxyListener aCallback);
    public String endAttributes(long aAsyncHandle);
    public long syncQueryPort();
    public void beginQueryPort(ICpProxyListener aCallback);
    public long endQueryPort(long aAsyncHandle);
    public long syncBrowsePort();
    public void beginBrowsePort(ICpProxyListener aCallback);
    public long endBrowsePort(long aAsyncHandle);
    public long syncUpdateCount();
    public void beginUpdateCount(ICpProxyListener aCallback);
    public long endUpdateCount(long aAsyncHandle);
    public void setPropertyManufacturerNameChanged(IPropertyChangeListener aManufacturerNameChanged);
    public String getPropertyManufacturerName();
    public void setPropertyManufacturerInfoChanged(IPropertyChangeListener aManufacturerInfoChanged);
    public String getPropertyManufacturerInfo();
    public void setPropertyManufacturerUrlChanged(IPropertyChangeListener aManufacturerUrlChanged);
    public String getPropertyManufacturerUrl();
    public void setPropertyManufacturerImageUriChanged(IPropertyChangeListener aManufacturerImageUriChanged);
    public String getPropertyManufacturerImageUri();
    public void setPropertyModelNameChanged(IPropertyChangeListener aModelNameChanged);
    public String getPropertyModelName();
    public void setPropertyModelInfoChanged(IPropertyChangeListener aModelInfoChanged);
    public String getPropertyModelInfo();
    public void setPropertyModelUrlChanged(IPropertyChangeListener aModelUrlChanged);
    public String getPropertyModelUrl();
    public void setPropertyModelImageUriChanged(IPropertyChangeListener aModelImageUriChanged);
    public String getPropertyModelImageUri();
    public void setPropertyProductNameChanged(IPropertyChangeListener aProductNameChanged);
    public String getPropertyProductName();
    public void setPropertyProductInfoChanged(IPropertyChangeListener aProductInfoChanged);
    public String getPropertyProductInfo();
    public void setPropertyProductUrlChanged(IPropertyChangeListener aProductUrlChanged);
    public String getPropertyProductUrl();
    public void setPropertyProductImageUriChanged(IPropertyChangeListener aProductImageUriChanged);
    public String getPropertyProductImageUri();
    public void setPropertyAttributesChanged(IPropertyChangeListener aAttributesChanged);
    public String getPropertyAttributes();
    public void setPropertyQueryPortChanged(IPropertyChangeListener aQueryPortChanged);
    public long getPropertyQueryPort();
    public void setPropertyBrowsePortChanged(IPropertyChangeListener aBrowsePortChanged);
    public long getPropertyBrowsePort();
    public void setPropertyUpdateCountChanged(IPropertyChangeListener aUpdateCountChanged);
    public long getPropertyUpdateCount();
}

class SyncManufacturerAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncManufacturerAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        Manufacturer result = iService.endManufacturer(aAsyncHandle);
        
        iName = result.getName();
        iInfo = result.getInfo();
        iUrl = result.getUrl();
        iImageUri = result.getImageUri();
    }
}

class SyncModelAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncModelAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        Model result = iService.endModel(aAsyncHandle);
        
        iName = result.getName();
        iInfo = result.getInfo();
        iUrl = result.getUrl();
        iImageUri = result.getImageUri();
    }
}

class SyncProductAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncProductAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
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
    protected void completeRequest(long aAsyncHandle)
    {
        Product result = iService.endProduct(aAsyncHandle);
        
        iName = result.getName();
        iInfo = result.getInfo();
        iUrl = result.getUrl();
        iImageUri = result.getImageUri();
    }
}

class SyncAttributesAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private String iValue;

    public SyncAttributesAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endAttributes(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncQueryPortAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private long iValue;

    public SyncQueryPortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endQueryPort(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncBrowsePortAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private long iValue;

    public SyncBrowsePortAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endBrowsePort(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncUpdateCountAvOpenhomeOrgMediaServer1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgMediaServer1 iService;
    private long iValue;

    public SyncUpdateCountAvOpenhomeOrgMediaServer1(CpProxyAvOpenhomeOrgMediaServer1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endUpdateCount(aAsyncHandle);
        
        iValue = result;
    }
}

/**
 * Proxy for the av.openhome.org:MediaServer:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgMediaServer1 extends CpProxy implements ICpProxyAvOpenhomeOrgMediaServer1
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

    private Action iActionManufacturer;
    private Action iActionModel;
    private Action iActionProduct;
    private Action iActionAttributes;
    private Action iActionQueryPort;
    private Action iActionBrowsePort;
    private Action iActionUpdateCount;
    private PropertyString iManufacturerName;
    private PropertyString iManufacturerInfo;
    private PropertyString iManufacturerUrl;
    private PropertyString iManufacturerImageUri;
    private PropertyString iModelName;
    private PropertyString iModelInfo;
    private PropertyString iModelUrl;
    private PropertyString iModelImageUri;
    private PropertyString iProductName;
    private PropertyString iProductInfo;
    private PropertyString iProductUrl;
    private PropertyString iProductImageUri;
    private PropertyString iAttributes;
    private PropertyUint iQueryPort;
    private PropertyUint iBrowsePort;
    private PropertyUint iUpdateCount;
    private IPropertyChangeListener iManufacturerNameChanged;
    private IPropertyChangeListener iManufacturerInfoChanged;
    private IPropertyChangeListener iManufacturerUrlChanged;
    private IPropertyChangeListener iManufacturerImageUriChanged;
    private IPropertyChangeListener iModelNameChanged;
    private IPropertyChangeListener iModelInfoChanged;
    private IPropertyChangeListener iModelUrlChanged;
    private IPropertyChangeListener iModelImageUriChanged;
    private IPropertyChangeListener iProductNameChanged;
    private IPropertyChangeListener iProductInfoChanged;
    private IPropertyChangeListener iProductUrlChanged;
    private IPropertyChangeListener iProductImageUriChanged;
    private IPropertyChangeListener iAttributesChanged;
    private IPropertyChangeListener iQueryPortChanged;
    private IPropertyChangeListener iBrowsePortChanged;
    private IPropertyChangeListener iUpdateCountChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgMediaServer1(CpDevice aDevice)
    {
        super("av-openhome-org", "MediaServer", 1, aDevice);
        Parameter param;
        List<String> allowedValues = new LinkedList<String>();

        iActionManufacturer = new Action("Manufacturer");
        param = new ParameterString("Name", allowedValues);
        iActionManufacturer.addOutputParameter(param);
        param = new ParameterString("Info", allowedValues);
        iActionManufacturer.addOutputParameter(param);
        param = new ParameterString("Url", allowedValues);
        iActionManufacturer.addOutputParameter(param);
        param = new ParameterString("ImageUri", allowedValues);
        iActionManufacturer.addOutputParameter(param);

        iActionModel = new Action("Model");
        param = new ParameterString("Name", allowedValues);
        iActionModel.addOutputParameter(param);
        param = new ParameterString("Info", allowedValues);
        iActionModel.addOutputParameter(param);
        param = new ParameterString("Url", allowedValues);
        iActionModel.addOutputParameter(param);
        param = new ParameterString("ImageUri", allowedValues);
        iActionModel.addOutputParameter(param);

        iActionProduct = new Action("Product");
        param = new ParameterString("Name", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("Info", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("Url", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("ImageUri", allowedValues);
        iActionProduct.addOutputParameter(param);

        iActionAttributes = new Action("Attributes");
        param = new ParameterString("Value", allowedValues);
        iActionAttributes.addOutputParameter(param);

        iActionQueryPort = new Action("QueryPort");
        param = new ParameterUint("Value");
        iActionQueryPort.addOutputParameter(param);

        iActionBrowsePort = new Action("BrowsePort");
        param = new ParameterUint("Value");
        iActionBrowsePort.addOutputParameter(param);

        iActionUpdateCount = new Action("UpdateCount");
        param = new ParameterUint("Value");
        iActionUpdateCount.addOutputParameter(param);

        iManufacturerNameChanged = new PropertyChangeListener();
        iManufacturerName = new PropertyString("ManufacturerName",
            new PropertyChangeListener() {
                public void notifyChange() {
                    manufacturerNamePropertyChanged();
                }
            }
        );
        addProperty(iManufacturerName);
        iManufacturerInfoChanged = new PropertyChangeListener();
        iManufacturerInfo = new PropertyString("ManufacturerInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    manufacturerInfoPropertyChanged();
                }
            }
        );
        addProperty(iManufacturerInfo);
        iManufacturerUrlChanged = new PropertyChangeListener();
        iManufacturerUrl = new PropertyString("ManufacturerUrl",
            new PropertyChangeListener() {
                public void notifyChange() {
                    manufacturerUrlPropertyChanged();
                }
            }
        );
        addProperty(iManufacturerUrl);
        iManufacturerImageUriChanged = new PropertyChangeListener();
        iManufacturerImageUri = new PropertyString("ManufacturerImageUri",
            new PropertyChangeListener() {
                public void notifyChange() {
                    manufacturerImageUriPropertyChanged();
                }
            }
        );
        addProperty(iManufacturerImageUri);
        iModelNameChanged = new PropertyChangeListener();
        iModelName = new PropertyString("ModelName",
            new PropertyChangeListener() {
                public void notifyChange() {
                    modelNamePropertyChanged();
                }
            }
        );
        addProperty(iModelName);
        iModelInfoChanged = new PropertyChangeListener();
        iModelInfo = new PropertyString("ModelInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    modelInfoPropertyChanged();
                }
            }
        );
        addProperty(iModelInfo);
        iModelUrlChanged = new PropertyChangeListener();
        iModelUrl = new PropertyString("ModelUrl",
            new PropertyChangeListener() {
                public void notifyChange() {
                    modelUrlPropertyChanged();
                }
            }
        );
        addProperty(iModelUrl);
        iModelImageUriChanged = new PropertyChangeListener();
        iModelImageUri = new PropertyString("ModelImageUri",
            new PropertyChangeListener() {
                public void notifyChange() {
                    modelImageUriPropertyChanged();
                }
            }
        );
        addProperty(iModelImageUri);
        iProductNameChanged = new PropertyChangeListener();
        iProductName = new PropertyString("ProductName",
            new PropertyChangeListener() {
                public void notifyChange() {
                    productNamePropertyChanged();
                }
            }
        );
        addProperty(iProductName);
        iProductInfoChanged = new PropertyChangeListener();
        iProductInfo = new PropertyString("ProductInfo",
            new PropertyChangeListener() {
                public void notifyChange() {
                    productInfoPropertyChanged();
                }
            }
        );
        addProperty(iProductInfo);
        iProductUrlChanged = new PropertyChangeListener();
        iProductUrl = new PropertyString("ProductUrl",
            new PropertyChangeListener() {
                public void notifyChange() {
                    productUrlPropertyChanged();
                }
            }
        );
        addProperty(iProductUrl);
        iProductImageUriChanged = new PropertyChangeListener();
        iProductImageUri = new PropertyString("ProductImageUri",
            new PropertyChangeListener() {
                public void notifyChange() {
                    productImageUriPropertyChanged();
                }
            }
        );
        addProperty(iProductImageUri);
        iAttributesChanged = new PropertyChangeListener();
        iAttributes = new PropertyString("Attributes",
            new PropertyChangeListener() {
                public void notifyChange() {
                    attributesPropertyChanged();
                }
            }
        );
        addProperty(iAttributes);
        iQueryPortChanged = new PropertyChangeListener();
        iQueryPort = new PropertyUint("QueryPort",
            new PropertyChangeListener() {
                public void notifyChange() {
                    queryPortPropertyChanged();
                }
            }
        );
        addProperty(iQueryPort);
        iBrowsePortChanged = new PropertyChangeListener();
        iBrowsePort = new PropertyUint("BrowsePort",
            new PropertyChangeListener() {
                public void notifyChange() {
                    browsePortPropertyChanged();
                }
            }
        );
        addProperty(iBrowsePort);
        iUpdateCountChanged = new PropertyChangeListener();
        iUpdateCount = new PropertyUint("UpdateCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    updateCountPropertyChanged();
                }
            }
        );
        addProperty(iUpdateCount);
        iPropertyLock = new Object();
    }
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Manufacturer syncManufacturer()
    {
        SyncManufacturerAvOpenhomeOrgMediaServer1 sync = new SyncManufacturerAvOpenhomeOrgMediaServer1(this);
        beginManufacturer(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Manufacturer(
            sync.getName(),
            sync.getInfo(),
            sync.getUrl(),
            sync.getImageUri()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endManufacturer}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginManufacturer(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionManufacturer, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionManufacturer.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionManufacturer.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionManufacturer.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionManufacturer.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginManufacturer} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginManufacturer} method.
     * @return the result of the previously invoked action.
     */
    public Manufacturer endManufacturer(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        String info = Invocation.getOutputString(aAsyncHandle, index++);
        String url = Invocation.getOutputString(aAsyncHandle, index++);
        String imageUri = Invocation.getOutputString(aAsyncHandle, index++);
        return new Manufacturer(
            name,
            info,
            url,
            imageUri
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Model syncModel()
    {
        SyncModelAvOpenhomeOrgMediaServer1 sync = new SyncModelAvOpenhomeOrgMediaServer1(this);
        beginModel(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Model(
            sync.getName(),
            sync.getInfo(),
            sync.getUrl(),
            sync.getImageUri()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endModel}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginModel(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionModel, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionModel.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionModel.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionModel.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionModel.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginModel} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginModel} method.
     * @return the result of the previously invoked action.
     */
    public Model endModel(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        String info = Invocation.getOutputString(aAsyncHandle, index++);
        String url = Invocation.getOutputString(aAsyncHandle, index++);
        String imageUri = Invocation.getOutputString(aAsyncHandle, index++);
        return new Model(
            name,
            info,
            url,
            imageUri
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public Product syncProduct()
    {
        SyncProductAvOpenhomeOrgMediaServer1 sync = new SyncProductAvOpenhomeOrgMediaServer1(this);
        beginProduct(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Product(
            sync.getName(),
            sync.getInfo(),
            sync.getUrl(),
            sync.getImageUri()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endProduct}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginProduct(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionProduct, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionProduct.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionProduct.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionProduct.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionProduct.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginProduct} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginProduct} method.
     * @return the result of the previously invoked action.
     */
    public Product endProduct(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        String info = Invocation.getOutputString(aAsyncHandle, index++);
        String url = Invocation.getOutputString(aAsyncHandle, index++);
        String imageUri = Invocation.getOutputString(aAsyncHandle, index++);
        return new Product(
            name,
            info,
            url,
            imageUri
        );
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public String syncAttributes()
    {
        SyncAttributesAvOpenhomeOrgMediaServer1 sync = new SyncAttributesAvOpenhomeOrgMediaServer1(this);
        beginAttributes(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endAttributes}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginAttributes(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionAttributes, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionAttributes.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginAttributes} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginAttributes} method.
     * @return the result of the previously invoked action.
     */
    public String endAttributes(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String value = Invocation.getOutputString(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncQueryPort()
    {
        SyncQueryPortAvOpenhomeOrgMediaServer1 sync = new SyncQueryPortAvOpenhomeOrgMediaServer1(this);
        beginQueryPort(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endQueryPort}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginQueryPort(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionQueryPort, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionQueryPort.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginQueryPort} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginQueryPort} method.
     * @return the result of the previously invoked action.
     */
    public long endQueryPort(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long value = Invocation.getOutputUint(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncBrowsePort()
    {
        SyncBrowsePortAvOpenhomeOrgMediaServer1 sync = new SyncBrowsePortAvOpenhomeOrgMediaServer1(this);
        beginBrowsePort(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endBrowsePort}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginBrowsePort(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionBrowsePort, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionBrowsePort.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginBrowsePort} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginBrowsePort} method.
     * @return the result of the previously invoked action.
     */
    public long endBrowsePort(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long value = Invocation.getOutputUint(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     *
     * @return the result of the invoked action.
     */
    public long syncUpdateCount()
    {
        SyncUpdateCountAvOpenhomeOrgMediaServer1 sync = new SyncUpdateCountAvOpenhomeOrgMediaServer1(this);
        beginUpdateCount(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endUpdateCount}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginUpdateCount(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionUpdateCount, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionUpdateCount.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginUpdateCount} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginUpdateCount} method.
     * @return the result of the previously invoked action.
     */
    public long endUpdateCount(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        long value = Invocation.getOutputUint(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Set a delegate to be run when the ManufacturerName state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aManufacturerNameChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyManufacturerNameChanged(IPropertyChangeListener aManufacturerNameChanged)
    {
        synchronized (iPropertyLock)
        {
            iManufacturerNameChanged = aManufacturerNameChanged;
        }
    }

    private void manufacturerNamePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iManufacturerNameChanged);
        }
    }
    /**
     * Set a delegate to be run when the ManufacturerInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aManufacturerInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyManufacturerInfoChanged(IPropertyChangeListener aManufacturerInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iManufacturerInfoChanged = aManufacturerInfoChanged;
        }
    }

    private void manufacturerInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iManufacturerInfoChanged);
        }
    }
    /**
     * Set a delegate to be run when the ManufacturerUrl state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aManufacturerUrlChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyManufacturerUrlChanged(IPropertyChangeListener aManufacturerUrlChanged)
    {
        synchronized (iPropertyLock)
        {
            iManufacturerUrlChanged = aManufacturerUrlChanged;
        }
    }

    private void manufacturerUrlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iManufacturerUrlChanged);
        }
    }
    /**
     * Set a delegate to be run when the ManufacturerImageUri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aManufacturerImageUriChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyManufacturerImageUriChanged(IPropertyChangeListener aManufacturerImageUriChanged)
    {
        synchronized (iPropertyLock)
        {
            iManufacturerImageUriChanged = aManufacturerImageUriChanged;
        }
    }

    private void manufacturerImageUriPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iManufacturerImageUriChanged);
        }
    }
    /**
     * Set a delegate to be run when the ModelName state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aModelNameChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyModelNameChanged(IPropertyChangeListener aModelNameChanged)
    {
        synchronized (iPropertyLock)
        {
            iModelNameChanged = aModelNameChanged;
        }
    }

    private void modelNamePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iModelNameChanged);
        }
    }
    /**
     * Set a delegate to be run when the ModelInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aModelInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyModelInfoChanged(IPropertyChangeListener aModelInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iModelInfoChanged = aModelInfoChanged;
        }
    }

    private void modelInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iModelInfoChanged);
        }
    }
    /**
     * Set a delegate to be run when the ModelUrl state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aModelUrlChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyModelUrlChanged(IPropertyChangeListener aModelUrlChanged)
    {
        synchronized (iPropertyLock)
        {
            iModelUrlChanged = aModelUrlChanged;
        }
    }

    private void modelUrlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iModelUrlChanged);
        }
    }
    /**
     * Set a delegate to be run when the ModelImageUri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aModelImageUriChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyModelImageUriChanged(IPropertyChangeListener aModelImageUriChanged)
    {
        synchronized (iPropertyLock)
        {
            iModelImageUriChanged = aModelImageUriChanged;
        }
    }

    private void modelImageUriPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iModelImageUriChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProductName state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aProductNameChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProductNameChanged(IPropertyChangeListener aProductNameChanged)
    {
        synchronized (iPropertyLock)
        {
            iProductNameChanged = aProductNameChanged;
        }
    }

    private void productNamePropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProductNameChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProductInfo state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aProductInfoChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProductInfoChanged(IPropertyChangeListener aProductInfoChanged)
    {
        synchronized (iPropertyLock)
        {
            iProductInfoChanged = aProductInfoChanged;
        }
    }

    private void productInfoPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProductInfoChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProductUrl state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aProductUrlChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProductUrlChanged(IPropertyChangeListener aProductUrlChanged)
    {
        synchronized (iPropertyLock)
        {
            iProductUrlChanged = aProductUrlChanged;
        }
    }

    private void productUrlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProductUrlChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProductImageUri state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aProductImageUriChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProductImageUriChanged(IPropertyChangeListener aProductImageUriChanged)
    {
        synchronized (iPropertyLock)
        {
            iProductImageUriChanged = aProductImageUriChanged;
        }
    }

    private void productImageUriPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProductImageUriChanged);
        }
    }
    /**
     * Set a delegate to be run when the Attributes state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aAttributesChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyAttributesChanged(IPropertyChangeListener aAttributesChanged)
    {
        synchronized (iPropertyLock)
        {
            iAttributesChanged = aAttributesChanged;
        }
    }

    private void attributesPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iAttributesChanged);
        }
    }
    /**
     * Set a delegate to be run when the QueryPort state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aQueryPortChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyQueryPortChanged(IPropertyChangeListener aQueryPortChanged)
    {
        synchronized (iPropertyLock)
        {
            iQueryPortChanged = aQueryPortChanged;
        }
    }

    private void queryPortPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iQueryPortChanged);
        }
    }
    /**
     * Set a delegate to be run when the BrowsePort state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aBrowsePortChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyBrowsePortChanged(IPropertyChangeListener aBrowsePortChanged)
    {
        synchronized (iPropertyLock)
        {
            iBrowsePortChanged = aBrowsePortChanged;
        }
    }

    private void browsePortPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iBrowsePortChanged);
        }
    }
    /**
     * Set a delegate to be run when the UpdateCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgMediaServer1 instance will not overlap.
     *
     * @param aUpdateCountChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyUpdateCountChanged(IPropertyChangeListener aUpdateCountChanged)
    {
        synchronized (iPropertyLock)
        {
            iUpdateCountChanged = aUpdateCountChanged;
        }
    }

    private void updateCountPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iUpdateCountChanged);
        }
    }

    /**
     * Query the value of the ManufacturerName property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ManufacturerName property.
     */
    public String getPropertyManufacturerName()
    {
        propertyReadLock();
        String val = iManufacturerName.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ManufacturerInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ManufacturerInfo property.
     */
    public String getPropertyManufacturerInfo()
    {
        propertyReadLock();
        String val = iManufacturerInfo.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ManufacturerUrl property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ManufacturerUrl property.
     */
    public String getPropertyManufacturerUrl()
    {
        propertyReadLock();
        String val = iManufacturerUrl.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ManufacturerImageUri property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ManufacturerImageUri property.
     */
    public String getPropertyManufacturerImageUri()
    {
        propertyReadLock();
        String val = iManufacturerImageUri.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ModelName property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ModelName property.
     */
    public String getPropertyModelName()
    {
        propertyReadLock();
        String val = iModelName.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ModelInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ModelInfo property.
     */
    public String getPropertyModelInfo()
    {
        propertyReadLock();
        String val = iModelInfo.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ModelUrl property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ModelUrl property.
     */
    public String getPropertyModelUrl()
    {
        propertyReadLock();
        String val = iModelUrl.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ModelImageUri property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ModelImageUri property.
     */
    public String getPropertyModelImageUri()
    {
        propertyReadLock();
        String val = iModelImageUri.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ProductName property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProductName property.
     */
    public String getPropertyProductName()
    {
        propertyReadLock();
        String val = iProductName.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ProductInfo property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProductInfo property.
     */
    public String getPropertyProductInfo()
    {
        propertyReadLock();
        String val = iProductInfo.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ProductUrl property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProductUrl property.
     */
    public String getPropertyProductUrl()
    {
        propertyReadLock();
        String val = iProductUrl.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the ProductImageUri property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProductImageUri property.
     */
    public String getPropertyProductImageUri()
    {
        propertyReadLock();
        String val = iProductImageUri.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the Attributes property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Attributes property.
     */
    public String getPropertyAttributes()
    {
        propertyReadLock();
        String val = iAttributes.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the QueryPort property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the QueryPort property.
     */
    public long getPropertyQueryPort()
    {
        propertyReadLock();
        long val = iQueryPort.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the BrowsePort property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the BrowsePort property.
     */
    public long getPropertyBrowsePort()
    {
        propertyReadLock();
        long val = iBrowsePort.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the UpdateCount property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the UpdateCount property.
     */
    public long getPropertyUpdateCount()
    {
        propertyReadLock();
        long val = iUpdateCount.getValue();
        propertyReadUnlock();
        return val;
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
            iActionManufacturer.destroy();
            iActionModel.destroy();
            iActionProduct.destroy();
            iActionAttributes.destroy();
            iActionQueryPort.destroy();
            iActionBrowsePort.destroy();
            iActionUpdateCount.destroy();
            iManufacturerName.destroy();
            iManufacturerInfo.destroy();
            iManufacturerUrl.destroy();
            iManufacturerImageUri.destroy();
            iModelName.destroy();
            iModelInfo.destroy();
            iModelUrl.destroy();
            iModelImageUri.destroy();
            iProductName.destroy();
            iProductInfo.destroy();
            iProductUrl.destroy();
            iProductImageUri.destroy();
            iAttributes.destroy();
            iQueryPort.destroy();
            iBrowsePort.destroy();
            iUpdateCount.destroy();
        }
    }
}

