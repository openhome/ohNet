package org.openhome.net.controlpoint.proxies;

import java.util.LinkedList;
import java.util.List;

import org.openhome.net.controlpoint.*;
import org.openhome.net.controlpoint.proxies.CpProxyAvOpenhomeOrgProduct1.*;
import org.openhome.net.core.*;

    
interface ICpProxyAvOpenhomeOrgProduct1 extends ICpProxy
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
    public boolean syncStandby();
    public void beginStandby(ICpProxyListener aCallback);
    public boolean endStandby(long aAsyncHandle);
    public void syncSetStandby(boolean aValue);
    public void beginSetStandby(boolean aValue, ICpProxyListener aCallback);
    public void endSetStandby(long aAsyncHandle);
    public long syncSourceCount();
    public void beginSourceCount(ICpProxyListener aCallback);
    public long endSourceCount(long aAsyncHandle);
    public String syncSourceXml();
    public void beginSourceXml(ICpProxyListener aCallback);
    public String endSourceXml(long aAsyncHandle);
    public long syncSourceIndex();
    public void beginSourceIndex(ICpProxyListener aCallback);
    public long endSourceIndex(long aAsyncHandle);
    public void syncSetSourceIndex(long aValue);
    public void beginSetSourceIndex(long aValue, ICpProxyListener aCallback);
    public void endSetSourceIndex(long aAsyncHandle);
    public void syncSetSourceIndexByName(String aValue);
    public void beginSetSourceIndexByName(String aValue, ICpProxyListener aCallback);
    public void endSetSourceIndexByName(long aAsyncHandle);
    public Source syncSource(long aIndex);
    public void beginSource(long aIndex, ICpProxyListener aCallback);
    public Source endSource(long aAsyncHandle);
    public String syncAttributes();
    public void beginAttributes(ICpProxyListener aCallback);
    public String endAttributes(long aAsyncHandle);
    public long syncSourceXmlChangeCount();
    public void beginSourceXmlChangeCount(ICpProxyListener aCallback);
    public long endSourceXmlChangeCount(long aAsyncHandle);
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
    public void setPropertyProductRoomChanged(IPropertyChangeListener aProductRoomChanged);
    public String getPropertyProductRoom();
    public void setPropertyProductNameChanged(IPropertyChangeListener aProductNameChanged);
    public String getPropertyProductName();
    public void setPropertyProductInfoChanged(IPropertyChangeListener aProductInfoChanged);
    public String getPropertyProductInfo();
    public void setPropertyProductUrlChanged(IPropertyChangeListener aProductUrlChanged);
    public String getPropertyProductUrl();
    public void setPropertyProductImageUriChanged(IPropertyChangeListener aProductImageUriChanged);
    public String getPropertyProductImageUri();
    public void setPropertyStandbyChanged(IPropertyChangeListener aStandbyChanged);
    public boolean getPropertyStandby();
    public void setPropertySourceIndexChanged(IPropertyChangeListener aSourceIndexChanged);
    public long getPropertySourceIndex();
    public void setPropertySourceCountChanged(IPropertyChangeListener aSourceCountChanged);
    public long getPropertySourceCount();
    public void setPropertySourceXmlChanged(IPropertyChangeListener aSourceXmlChanged);
    public String getPropertySourceXml();
    public void setPropertyAttributesChanged(IPropertyChangeListener aAttributesChanged);
    public String getPropertyAttributes();
}

class SyncManufacturerAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncManufacturerAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

class SyncModelAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncModelAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

class SyncProductAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iRoom;
    private String iName;
    private String iInfo;
    private String iUrl;
    private String iImageUri;

    public SyncProductAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public String getRoom()
    {
        return iRoom;
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
        
        iRoom = result.getRoom();
        iName = result.getName();
        iInfo = result.getInfo();
        iUrl = result.getUrl();
        iImageUri = result.getImageUri();
    }
}

class SyncStandbyAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private boolean iValue;

    public SyncStandbyAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public boolean getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        boolean result = iService.endStandby(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSetStandbyAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;

    public SyncSetStandbyAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetStandby(aAsyncHandle);
        
    }
}

class SyncSourceCountAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private long iValue;

    public SyncSourceCountAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endSourceCount(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSourceXmlAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iValue;

    public SyncSourceXmlAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public String getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        String result = iService.endSourceXml(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSourceIndexAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private long iValue;

    public SyncSourceIndexAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endSourceIndex(aAsyncHandle);
        
        iValue = result;
    }
}

class SyncSetSourceIndexAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;

    public SyncSetSourceIndexAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetSourceIndex(aAsyncHandle);
        
    }
}

class SyncSetSourceIndexByNameAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;

    public SyncSetSourceIndexByNameAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        iService.endSetSourceIndexByName(aAsyncHandle);
        
    }
}

class SyncSourceAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iSystemName;
    private String iType;
    private String iName;
    private boolean iVisible;

    public SyncSourceAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public String getSystemName()
    {
        return iSystemName;
    }
    public String getType()
    {
        return iType;
    }
    public String getName()
    {
        return iName;
    }
    public boolean getVisible()
    {
        return iVisible;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        Source result = iService.endSource(aAsyncHandle);
        
        iSystemName = result.getSystemName();
        iType = result.getType();
        iName = result.getName();
        iVisible = result.getVisible();
    }
}

class SyncAttributesAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private String iValue;

    public SyncAttributesAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
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

class SyncSourceXmlChangeCountAvOpenhomeOrgProduct1 extends SyncProxyAction
{
    private CpProxyAvOpenhomeOrgProduct1 iService;
    private long iValue;

    public SyncSourceXmlChangeCountAvOpenhomeOrgProduct1(CpProxyAvOpenhomeOrgProduct1 aProxy)
    {
        iService = aProxy;
    }
    public long getValue()
    {
        return iValue;
    }
    protected void completeRequest(long aAsyncHandle)
    {
        long result = iService.endSourceXmlChangeCount(aAsyncHandle);
        
        iValue = result;
    }
}

/**
 * Proxy for the av.openhome.org:Product:1 UPnP service
 */
public class CpProxyAvOpenhomeOrgProduct1 extends CpProxy implements ICpProxyAvOpenhomeOrgProduct1
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
        private String iRoom;
        private String iName;
        private String iInfo;
        private String iUrl;
        private String iImageUri;

        public Product(
            String aRoom,
            String aName,
            String aInfo,
            String aUrl,
            String aImageUri
        )
        {
            iRoom = aRoom;
            iName = aName;
            iInfo = aInfo;
            iUrl = aUrl;
            iImageUri = aImageUri;
        }
        public String getRoom()
        {
            return iRoom;
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

    public class Source
    {
        private String iSystemName;
        private String iType;
        private String iName;
        private boolean iVisible;

        public Source(
            String aSystemName,
            String aType,
            String aName,
            boolean aVisible
        )
        {
            iSystemName = aSystemName;
            iType = aType;
            iName = aName;
            iVisible = aVisible;
        }
        public String getSystemName()
        {
            return iSystemName;
        }
        public String getType()
        {
            return iType;
        }
        public String getName()
        {
            return iName;
        }
        public boolean getVisible()
        {
            return iVisible;
        }
    }

    private Action iActionManufacturer;
    private Action iActionModel;
    private Action iActionProduct;
    private Action iActionStandby;
    private Action iActionSetStandby;
    private Action iActionSourceCount;
    private Action iActionSourceXml;
    private Action iActionSourceIndex;
    private Action iActionSetSourceIndex;
    private Action iActionSetSourceIndexByName;
    private Action iActionSource;
    private Action iActionAttributes;
    private Action iActionSourceXmlChangeCount;
    private PropertyString iManufacturerName;
    private PropertyString iManufacturerInfo;
    private PropertyString iManufacturerUrl;
    private PropertyString iManufacturerImageUri;
    private PropertyString iModelName;
    private PropertyString iModelInfo;
    private PropertyString iModelUrl;
    private PropertyString iModelImageUri;
    private PropertyString iProductRoom;
    private PropertyString iProductName;
    private PropertyString iProductInfo;
    private PropertyString iProductUrl;
    private PropertyString iProductImageUri;
    private PropertyBool iStandby;
    private PropertyUint iSourceIndex;
    private PropertyUint iSourceCount;
    private PropertyString iSourceXml;
    private PropertyString iAttributes;
    private IPropertyChangeListener iManufacturerNameChanged;
    private IPropertyChangeListener iManufacturerInfoChanged;
    private IPropertyChangeListener iManufacturerUrlChanged;
    private IPropertyChangeListener iManufacturerImageUriChanged;
    private IPropertyChangeListener iModelNameChanged;
    private IPropertyChangeListener iModelInfoChanged;
    private IPropertyChangeListener iModelUrlChanged;
    private IPropertyChangeListener iModelImageUriChanged;
    private IPropertyChangeListener iProductRoomChanged;
    private IPropertyChangeListener iProductNameChanged;
    private IPropertyChangeListener iProductInfoChanged;
    private IPropertyChangeListener iProductUrlChanged;
    private IPropertyChangeListener iProductImageUriChanged;
    private IPropertyChangeListener iStandbyChanged;
    private IPropertyChangeListener iSourceIndexChanged;
    private IPropertyChangeListener iSourceCountChanged;
    private IPropertyChangeListener iSourceXmlChanged;
    private IPropertyChangeListener iAttributesChanged;
    private Object iPropertyLock;

    /**
     * Constructor.
     * Use {@link #subscribe}/{@link #unsubscribe} to enable/disable querying of state variable and reporting of their changes.
     *
     * @param aDevice   the device to use.
     */

    public CpProxyAvOpenhomeOrgProduct1(CpDevice aDevice)
    {
        super("av-openhome-org", "Product", 1, aDevice);
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
        param = new ParameterString("Room", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("Name", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("Info", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("Url", allowedValues);
        iActionProduct.addOutputParameter(param);
        param = new ParameterString("ImageUri", allowedValues);
        iActionProduct.addOutputParameter(param);

        iActionStandby = new Action("Standby");
        param = new ParameterBool("Value");
        iActionStandby.addOutputParameter(param);

        iActionSetStandby = new Action("SetStandby");
        param = new ParameterBool("Value");
        iActionSetStandby.addInputParameter(param);

        iActionSourceCount = new Action("SourceCount");
        param = new ParameterUint("Value");
        iActionSourceCount.addOutputParameter(param);

        iActionSourceXml = new Action("SourceXml");
        param = new ParameterString("Value", allowedValues);
        iActionSourceXml.addOutputParameter(param);

        iActionSourceIndex = new Action("SourceIndex");
        param = new ParameterUint("Value");
        iActionSourceIndex.addOutputParameter(param);

        iActionSetSourceIndex = new Action("SetSourceIndex");
        param = new ParameterUint("Value");
        iActionSetSourceIndex.addInputParameter(param);

        iActionSetSourceIndexByName = new Action("SetSourceIndexByName");
        param = new ParameterString("Value", allowedValues);
        iActionSetSourceIndexByName.addInputParameter(param);

        iActionSource = new Action("Source");
        param = new ParameterUint("Index");
        iActionSource.addInputParameter(param);
        param = new ParameterString("SystemName", allowedValues);
        iActionSource.addOutputParameter(param);
        param = new ParameterString("Type", allowedValues);
        iActionSource.addOutputParameter(param);
        param = new ParameterString("Name", allowedValues);
        iActionSource.addOutputParameter(param);
        param = new ParameterBool("Visible");
        iActionSource.addOutputParameter(param);

        iActionAttributes = new Action("Attributes");
        param = new ParameterString("Value", allowedValues);
        iActionAttributes.addOutputParameter(param);

        iActionSourceXmlChangeCount = new Action("SourceXmlChangeCount");
        param = new ParameterUint("Value");
        iActionSourceXmlChangeCount.addOutputParameter(param);

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
        iProductRoomChanged = new PropertyChangeListener();
        iProductRoom = new PropertyString("ProductRoom",
            new PropertyChangeListener() {
                public void notifyChange() {
                    productRoomPropertyChanged();
                }
            }
        );
        addProperty(iProductRoom);
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
        iStandbyChanged = new PropertyChangeListener();
        iStandby = new PropertyBool("Standby",
            new PropertyChangeListener() {
                public void notifyChange() {
                    standbyPropertyChanged();
                }
            }
        );
        addProperty(iStandby);
        iSourceIndexChanged = new PropertyChangeListener();
        iSourceIndex = new PropertyUint("SourceIndex",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sourceIndexPropertyChanged();
                }
            }
        );
        addProperty(iSourceIndex);
        iSourceCountChanged = new PropertyChangeListener();
        iSourceCount = new PropertyUint("SourceCount",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sourceCountPropertyChanged();
                }
            }
        );
        addProperty(iSourceCount);
        iSourceXmlChanged = new PropertyChangeListener();
        iSourceXml = new PropertyString("SourceXml",
            new PropertyChangeListener() {
                public void notifyChange() {
                    sourceXmlPropertyChanged();
                }
            }
        );
        addProperty(iSourceXml);
        iAttributesChanged = new PropertyChangeListener();
        iAttributes = new PropertyString("Attributes",
            new PropertyChangeListener() {
                public void notifyChange() {
                    attributesPropertyChanged();
                }
            }
        );
        addProperty(iAttributes);
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
        SyncManufacturerAvOpenhomeOrgProduct1 sync = new SyncManufacturerAvOpenhomeOrgProduct1(this);
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
        SyncModelAvOpenhomeOrgProduct1 sync = new SyncModelAvOpenhomeOrgProduct1(this);
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
        SyncProductAvOpenhomeOrgProduct1 sync = new SyncProductAvOpenhomeOrgProduct1(this);
        beginProduct(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Product(
            sync.getRoom(),
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
        String room = Invocation.getOutputString(aAsyncHandle, index++);
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        String info = Invocation.getOutputString(aAsyncHandle, index++);
        String url = Invocation.getOutputString(aAsyncHandle, index++);
        String imageUri = Invocation.getOutputString(aAsyncHandle, index++);
        return new Product(
            room,
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
    public boolean syncStandby()
    {
        SyncStandbyAvOpenhomeOrgProduct1 sync = new SyncStandbyAvOpenhomeOrgProduct1(this);
        beginStandby(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endStandby}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginStandby(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionStandby, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionStandby.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginStandby} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginStandby} method.
     * @return the result of the previously invoked action.
     */
    public boolean endStandby(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        boolean value = Invocation.getOutputBool(aAsyncHandle, index++);
        return value;
    }
        
    /**
     * Invoke the action synchronously.
     * Blocks until the action has been processed on the device and sets any
     * output arguments.
     */
    public void syncSetStandby(boolean aValue)
    {
        SyncSetStandbyAvOpenhomeOrgProduct1 sync = new SyncSetStandbyAvOpenhomeOrgProduct1(this);
        beginSetStandby(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetStandby}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetStandby(boolean aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetStandby, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentBool((ParameterBool)iActionSetStandby.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetStandby} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetStandby} method.
     */
    public void endSetStandby(long aAsyncHandle)
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
    public long syncSourceCount()
    {
        SyncSourceCountAvOpenhomeOrgProduct1 sync = new SyncSourceCountAvOpenhomeOrgProduct1(this);
        beginSourceCount(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSourceCount}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSourceCount(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSourceCount, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSourceCount.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSourceCount} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSourceCount} method.
     * @return the result of the previously invoked action.
     */
    public long endSourceCount(long aAsyncHandle)
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
    public String syncSourceXml()
    {
        SyncSourceXmlAvOpenhomeOrgProduct1 sync = new SyncSourceXmlAvOpenhomeOrgProduct1(this);
        beginSourceXml(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSourceXml}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSourceXml(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSourceXml, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionSourceXml.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSourceXml} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSourceXml} method.
     * @return the result of the previously invoked action.
     */
    public String endSourceXml(long aAsyncHandle)
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
    public long syncSourceIndex()
    {
        SyncSourceIndexAvOpenhomeOrgProduct1 sync = new SyncSourceIndexAvOpenhomeOrgProduct1(this);
        beginSourceIndex(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSourceIndex}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSourceIndex(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSourceIndex, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSourceIndex.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSourceIndex} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSourceIndex} method.
     * @return the result of the previously invoked action.
     */
    public long endSourceIndex(long aAsyncHandle)
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
     */
    public void syncSetSourceIndex(long aValue)
    {
        SyncSetSourceIndexAvOpenhomeOrgProduct1 sync = new SyncSetSourceIndexAvOpenhomeOrgProduct1(this);
        beginSetSourceIndex(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetSourceIndex}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetSourceIndex(long aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetSourceIndex, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSetSourceIndex.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetSourceIndex} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetSourceIndex} method.
     */
    public void endSetSourceIndex(long aAsyncHandle)
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
     */
    public void syncSetSourceIndexByName(String aValue)
    {
        SyncSetSourceIndexByNameAvOpenhomeOrgProduct1 sync = new SyncSetSourceIndexByNameAvOpenhomeOrgProduct1(this);
        beginSetSourceIndexByName(aValue, sync.getListener());
        sync.waitToComplete();
        sync.reportError();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSetSourceIndexByName}.
     * 
     * @param aValue
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSetSourceIndexByName(String aValue, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSetSourceIndexByName, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentString((ParameterString)iActionSetSourceIndexByName.getInputParameter(inIndex++), aValue));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSetSourceIndexByName} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSetSourceIndexByName} method.
     */
    public void endSetSourceIndexByName(long aAsyncHandle)
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
    public Source syncSource(long aIndex)
    {
        SyncSourceAvOpenhomeOrgProduct1 sync = new SyncSourceAvOpenhomeOrgProduct1(this);
        beginSource(aIndex, sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return new Source(
            sync.getSystemName(),
            sync.getType(),
            sync.getName(),
            sync.getVisible()
        );
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSource}.
     * 
     * @param aIndex
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSource(long aIndex, ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSource, aCallback);
        int inIndex = 0;
        invocation.addInput(new ArgumentUint((ParameterUint)iActionSource.getInputParameter(inIndex++), aIndex));
        int outIndex = 0;
        invocation.addOutput(new ArgumentString((ParameterString)iActionSource.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionSource.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentString((ParameterString)iActionSource.getOutputParameter(outIndex++)));
        invocation.addOutput(new ArgumentBool((ParameterBool)iActionSource.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSource} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSource} method.
     * @return the result of the previously invoked action.
     */
    public Source endSource(long aAsyncHandle)
    {
        ProxyError errObj = Invocation.error(aAsyncHandle);
        if (errObj != null)
        {
            throw errObj;
        }
        int index = 0;
        String systemName = Invocation.getOutputString(aAsyncHandle, index++);
        String type = Invocation.getOutputString(aAsyncHandle, index++);
        String name = Invocation.getOutputString(aAsyncHandle, index++);
        boolean visible = Invocation.getOutputBool(aAsyncHandle, index++);
        return new Source(
            systemName,
            type,
            name,
            visible
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
        SyncAttributesAvOpenhomeOrgProduct1 sync = new SyncAttributesAvOpenhomeOrgProduct1(this);
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
    public long syncSourceXmlChangeCount()
    {
        SyncSourceXmlChangeCountAvOpenhomeOrgProduct1 sync = new SyncSourceXmlChangeCountAvOpenhomeOrgProduct1(this);
        beginSourceXmlChangeCount(sync.getListener());
        sync.waitToComplete();
        sync.reportError();

        return sync.getValue();
    }
    
    /**
     * Invoke the action asynchronously.
     * Returns immediately and will run the client-specified callback when the
     * action later completes.  Any output arguments can then be retrieved by
     * calling {@link #endSourceXmlChangeCount}.
     * 
     * @param aCallback listener to call back when action completes.
     *                  This is guaranteed to be run but may indicate an error.
     */
    public void beginSourceXmlChangeCount(ICpProxyListener aCallback)
    {
        Invocation invocation = iService.getInvocation(iActionSourceXmlChangeCount, aCallback);
        int outIndex = 0;
        invocation.addOutput(new ArgumentUint((ParameterUint)iActionSourceXmlChangeCount.getOutputParameter(outIndex++)));
        iService.invokeAction(invocation);
    }

    /**
     * Retrieve the output arguments from an asynchronously invoked action.
     * This may only be called from the callback set in the
     * {@link #beginSourceXmlChangeCount} method.
     *
     * @param aAsyncHandle  argument passed to the delegate set in the
     *          {@link #beginSourceXmlChangeCount} method.
     * @return the result of the previously invoked action.
     */
    public long endSourceXmlChangeCount(long aAsyncHandle)
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * Set a delegate to be run when the ProductRoom state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
     *
     * @param aProductRoomChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyProductRoomChanged(IPropertyChangeListener aProductRoomChanged)
    {
        synchronized (iPropertyLock)
        {
            iProductRoomChanged = aProductRoomChanged;
        }
    }

    private void productRoomPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iProductRoomChanged);
        }
    }
    /**
     * Set a delegate to be run when the ProductName state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * Set a delegate to be run when the Standby state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
     *
     * @param aStandbyChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertyStandbyChanged(IPropertyChangeListener aStandbyChanged)
    {
        synchronized (iPropertyLock)
        {
            iStandbyChanged = aStandbyChanged;
        }
    }

    private void standbyPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iStandbyChanged);
        }
    }
    /**
     * Set a delegate to be run when the SourceIndex state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
     *
     * @param aSourceIndexChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySourceIndexChanged(IPropertyChangeListener aSourceIndexChanged)
    {
        synchronized (iPropertyLock)
        {
            iSourceIndexChanged = aSourceIndexChanged;
        }
    }

    private void sourceIndexPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSourceIndexChanged);
        }
    }
    /**
     * Set a delegate to be run when the SourceCount state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
     *
     * @param aSourceCountChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySourceCountChanged(IPropertyChangeListener aSourceCountChanged)
    {
        synchronized (iPropertyLock)
        {
            iSourceCountChanged = aSourceCountChanged;
        }
    }

    private void sourceCountPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSourceCountChanged);
        }
    }
    /**
     * Set a delegate to be run when the SourceXml state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
     *
     * @param aSourceXmlChanged   the listener to call back when the state
     *          variable changes.
     */
    public void setPropertySourceXmlChanged(IPropertyChangeListener aSourceXmlChanged)
    {
        synchronized (iPropertyLock)
        {
            iSourceXmlChanged = aSourceXmlChanged;
        }
    }

    private void sourceXmlPropertyChanged()
    {
        synchronized (iPropertyLock)
        {
            reportEvent(iSourceXmlChanged);
        }
    }
    /**
     * Set a delegate to be run when the Attributes state variable changes.
     * Callbacks may be run in different threads but callbacks for a
     * CpProxyAvOpenhomeOrgProduct1 instance will not overlap.
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
     * Query the value of the ProductRoom property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the ProductRoom property.
     */
    public String getPropertyProductRoom()
    {
        propertyReadLock();
        String val = iProductRoom.getValue();
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
     * Query the value of the Standby property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the Standby property.
     */
    public boolean getPropertyStandby()
    {
        propertyReadLock();
        boolean val = iStandby.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the SourceIndex property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SourceIndex property.
     */
    public long getPropertySourceIndex()
    {
        propertyReadLock();
        long val = iSourceIndex.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the SourceCount property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SourceCount property.
     */
    public long getPropertySourceCount()
    {
        propertyReadLock();
        long val = iSourceCount.getValue();
        propertyReadUnlock();
        return val;
    }
    
    /**
     * Query the value of the SourceXml property.
     * This function is thread-safe and can only be called if {@link 
     * #subscribe} has been called and a first eventing callback received
     * more recently than any call to {@link #unsubscribe}.
     *
     * @return  value of the SourceXml property.
     */
    public String getPropertySourceXml()
    {
        propertyReadLock();
        String val = iSourceXml.getValue();
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
            iActionStandby.destroy();
            iActionSetStandby.destroy();
            iActionSourceCount.destroy();
            iActionSourceXml.destroy();
            iActionSourceIndex.destroy();
            iActionSetSourceIndex.destroy();
            iActionSetSourceIndexByName.destroy();
            iActionSource.destroy();
            iActionAttributes.destroy();
            iActionSourceXmlChangeCount.destroy();
            iManufacturerName.destroy();
            iManufacturerInfo.destroy();
            iManufacturerUrl.destroy();
            iManufacturerImageUri.destroy();
            iModelName.destroy();
            iModelInfo.destroy();
            iModelUrl.destroy();
            iModelImageUri.destroy();
            iProductRoom.destroy();
            iProductName.destroy();
            iProductInfo.destroy();
            iProductUrl.destroy();
            iProductImageUri.destroy();
            iStandby.destroy();
            iSourceIndex.destroy();
            iSourceCount.destroy();
            iSourceXml.destroy();
            iAttributes.destroy();
        }
    }
}

