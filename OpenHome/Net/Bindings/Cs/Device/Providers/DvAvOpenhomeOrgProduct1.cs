using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using OpenHome.Net.Core;

namespace OpenHome.Net.Device.Providers
{
    public interface IDvProviderAvOpenhomeOrgProduct1 : IDisposable
    {

        /// <summary>
        /// Set the value of the ManufacturerName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyManufacturerName(string aValue);

        /// <summary>
        /// Get a copy of the value of the ManufacturerName property
        /// </summary>
        /// <returns>Value of the ManufacturerName property.</param>
        string PropertyManufacturerName();

        /// <summary>
        /// Set the value of the ManufacturerInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyManufacturerInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ManufacturerInfo property
        /// </summary>
        /// <returns>Value of the ManufacturerInfo property.</param>
        string PropertyManufacturerInfo();

        /// <summary>
        /// Set the value of the ManufacturerUrl property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyManufacturerUrl(string aValue);

        /// <summary>
        /// Get a copy of the value of the ManufacturerUrl property
        /// </summary>
        /// <returns>Value of the ManufacturerUrl property.</param>
        string PropertyManufacturerUrl();

        /// <summary>
        /// Set the value of the ManufacturerImageUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyManufacturerImageUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the ManufacturerImageUri property
        /// </summary>
        /// <returns>Value of the ManufacturerImageUri property.</param>
        string PropertyManufacturerImageUri();

        /// <summary>
        /// Set the value of the ModelName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyModelName(string aValue);

        /// <summary>
        /// Get a copy of the value of the ModelName property
        /// </summary>
        /// <returns>Value of the ModelName property.</param>
        string PropertyModelName();

        /// <summary>
        /// Set the value of the ModelInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyModelInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ModelInfo property
        /// </summary>
        /// <returns>Value of the ModelInfo property.</param>
        string PropertyModelInfo();

        /// <summary>
        /// Set the value of the ModelUrl property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyModelUrl(string aValue);

        /// <summary>
        /// Get a copy of the value of the ModelUrl property
        /// </summary>
        /// <returns>Value of the ModelUrl property.</param>
        string PropertyModelUrl();

        /// <summary>
        /// Set the value of the ModelImageUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyModelImageUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the ModelImageUri property
        /// </summary>
        /// <returns>Value of the ModelImageUri property.</param>
        string PropertyModelImageUri();

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductRoom(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <returns>Value of the ProductRoom property.</param>
        string PropertyProductRoom();

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductName(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <returns>Value of the ProductName property.</param>
        string PropertyProductName();

        /// <summary>
        /// Set the value of the ProductInfo property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductInfo(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductInfo property
        /// </summary>
        /// <returns>Value of the ProductInfo property.</param>
        string PropertyProductInfo();

        /// <summary>
        /// Set the value of the ProductUrl property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductUrl(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductUrl property
        /// </summary>
        /// <returns>Value of the ProductUrl property.</param>
        string PropertyProductUrl();

        /// <summary>
        /// Set the value of the ProductImageUri property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyProductImageUri(string aValue);

        /// <summary>
        /// Get a copy of the value of the ProductImageUri property
        /// </summary>
        /// <returns>Value of the ProductImageUri property.</param>
        string PropertyProductImageUri();

        /// <summary>
        /// Set the value of the Standby property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyStandby(bool aValue);

        /// <summary>
        /// Get a copy of the value of the Standby property
        /// </summary>
        /// <returns>Value of the Standby property.</param>
        bool PropertyStandby();

        /// <summary>
        /// Set the value of the SourceIndex property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySourceIndex(uint aValue);

        /// <summary>
        /// Get a copy of the value of the SourceIndex property
        /// </summary>
        /// <returns>Value of the SourceIndex property.</param>
        uint PropertySourceIndex();

        /// <summary>
        /// Set the value of the SourceCount property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySourceCount(uint aValue);

        /// <summary>
        /// Get a copy of the value of the SourceCount property
        /// </summary>
        /// <returns>Value of the SourceCount property.</param>
        uint PropertySourceCount();

        /// <summary>
        /// Set the value of the SourceXml property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertySourceXml(string aValue);

        /// <summary>
        /// Get a copy of the value of the SourceXml property
        /// </summary>
        /// <returns>Value of the SourceXml property.</param>
        string PropertySourceXml();

        /// <summary>
        /// Set the value of the Attributes property
        /// </summary>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        bool SetPropertyAttributes(string aValue);

        /// <summary>
        /// Get a copy of the value of the Attributes property
        /// </summary>
        /// <returns>Value of the Attributes property.</param>
        string PropertyAttributes();
    }
    /// <summary>
    /// Provider for the av.openhome.org:Product:1 UPnP service
    /// </summary>
    public class DvProviderAvOpenhomeOrgProduct1 : DvProvider, IDisposable, IDvProviderAvOpenhomeOrgProduct1
    {
        private GCHandle iGch;
        private ActionDelegate iDelegateManufacturer;
        private ActionDelegate iDelegateModel;
        private ActionDelegate iDelegateProduct;
        private ActionDelegate iDelegateStandby;
        private ActionDelegate iDelegateSetStandby;
        private ActionDelegate iDelegateSourceCount;
        private ActionDelegate iDelegateSourceXml;
        private ActionDelegate iDelegateSourceIndex;
        private ActionDelegate iDelegateSetSourceIndex;
        private ActionDelegate iDelegateSetSourceIndexByName;
        private ActionDelegate iDelegateSource;
        private ActionDelegate iDelegateAttributes;
        private ActionDelegate iDelegateSourceXmlChangeCount;
        private PropertyString iPropertyManufacturerName;
        private PropertyString iPropertyManufacturerInfo;
        private PropertyString iPropertyManufacturerUrl;
        private PropertyString iPropertyManufacturerImageUri;
        private PropertyString iPropertyModelName;
        private PropertyString iPropertyModelInfo;
        private PropertyString iPropertyModelUrl;
        private PropertyString iPropertyModelImageUri;
        private PropertyString iPropertyProductRoom;
        private PropertyString iPropertyProductName;
        private PropertyString iPropertyProductInfo;
        private PropertyString iPropertyProductUrl;
        private PropertyString iPropertyProductImageUri;
        private PropertyBool iPropertyStandby;
        private PropertyUint iPropertySourceIndex;
        private PropertyUint iPropertySourceCount;
        private PropertyString iPropertySourceXml;
        private PropertyString iPropertyAttributes;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="aDevice">Device which owns this provider</param>
        protected DvProviderAvOpenhomeOrgProduct1(DvDevice aDevice)
            : base(aDevice, "av.openhome.org", "Product", 1)
        {
            iGch = GCHandle.Alloc(this);
        }

        /// <summary>
        /// Enable the ManufacturerName property.
        /// </summary>
        public void EnablePropertyManufacturerName()
        {
            List<String> allowedValues = new List<String>();
            iPropertyManufacturerName = new PropertyString(new ParameterString("ManufacturerName", allowedValues));
            AddProperty(iPropertyManufacturerName);
        }

        /// <summary>
        /// Enable the ManufacturerInfo property.
        /// </summary>
        public void EnablePropertyManufacturerInfo()
        {
            List<String> allowedValues = new List<String>();
            iPropertyManufacturerInfo = new PropertyString(new ParameterString("ManufacturerInfo", allowedValues));
            AddProperty(iPropertyManufacturerInfo);
        }

        /// <summary>
        /// Enable the ManufacturerUrl property.
        /// </summary>
        public void EnablePropertyManufacturerUrl()
        {
            List<String> allowedValues = new List<String>();
            iPropertyManufacturerUrl = new PropertyString(new ParameterString("ManufacturerUrl", allowedValues));
            AddProperty(iPropertyManufacturerUrl);
        }

        /// <summary>
        /// Enable the ManufacturerImageUri property.
        /// </summary>
        public void EnablePropertyManufacturerImageUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyManufacturerImageUri = new PropertyString(new ParameterString("ManufacturerImageUri", allowedValues));
            AddProperty(iPropertyManufacturerImageUri);
        }

        /// <summary>
        /// Enable the ModelName property.
        /// </summary>
        public void EnablePropertyModelName()
        {
            List<String> allowedValues = new List<String>();
            iPropertyModelName = new PropertyString(new ParameterString("ModelName", allowedValues));
            AddProperty(iPropertyModelName);
        }

        /// <summary>
        /// Enable the ModelInfo property.
        /// </summary>
        public void EnablePropertyModelInfo()
        {
            List<String> allowedValues = new List<String>();
            iPropertyModelInfo = new PropertyString(new ParameterString("ModelInfo", allowedValues));
            AddProperty(iPropertyModelInfo);
        }

        /// <summary>
        /// Enable the ModelUrl property.
        /// </summary>
        public void EnablePropertyModelUrl()
        {
            List<String> allowedValues = new List<String>();
            iPropertyModelUrl = new PropertyString(new ParameterString("ModelUrl", allowedValues));
            AddProperty(iPropertyModelUrl);
        }

        /// <summary>
        /// Enable the ModelImageUri property.
        /// </summary>
        public void EnablePropertyModelImageUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyModelImageUri = new PropertyString(new ParameterString("ModelImageUri", allowedValues));
            AddProperty(iPropertyModelImageUri);
        }

        /// <summary>
        /// Enable the ProductRoom property.
        /// </summary>
        public void EnablePropertyProductRoom()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProductRoom = new PropertyString(new ParameterString("ProductRoom", allowedValues));
            AddProperty(iPropertyProductRoom);
        }

        /// <summary>
        /// Enable the ProductName property.
        /// </summary>
        public void EnablePropertyProductName()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProductName = new PropertyString(new ParameterString("ProductName", allowedValues));
            AddProperty(iPropertyProductName);
        }

        /// <summary>
        /// Enable the ProductInfo property.
        /// </summary>
        public void EnablePropertyProductInfo()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProductInfo = new PropertyString(new ParameterString("ProductInfo", allowedValues));
            AddProperty(iPropertyProductInfo);
        }

        /// <summary>
        /// Enable the ProductUrl property.
        /// </summary>
        public void EnablePropertyProductUrl()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProductUrl = new PropertyString(new ParameterString("ProductUrl", allowedValues));
            AddProperty(iPropertyProductUrl);
        }

        /// <summary>
        /// Enable the ProductImageUri property.
        /// </summary>
        public void EnablePropertyProductImageUri()
        {
            List<String> allowedValues = new List<String>();
            iPropertyProductImageUri = new PropertyString(new ParameterString("ProductImageUri", allowedValues));
            AddProperty(iPropertyProductImageUri);
        }

        /// <summary>
        /// Enable the Standby property.
        /// </summary>
        public void EnablePropertyStandby()
        {
            iPropertyStandby = new PropertyBool(new ParameterBool("Standby"));
            AddProperty(iPropertyStandby);
        }

        /// <summary>
        /// Enable the SourceIndex property.
        /// </summary>
        public void EnablePropertySourceIndex()
        {
            iPropertySourceIndex = new PropertyUint(new ParameterUint("SourceIndex"));
            AddProperty(iPropertySourceIndex);
        }

        /// <summary>
        /// Enable the SourceCount property.
        /// </summary>
        public void EnablePropertySourceCount()
        {
            iPropertySourceCount = new PropertyUint(new ParameterUint("SourceCount"));
            AddProperty(iPropertySourceCount);
        }

        /// <summary>
        /// Enable the SourceXml property.
        /// </summary>
        public void EnablePropertySourceXml()
        {
            List<String> allowedValues = new List<String>();
            iPropertySourceXml = new PropertyString(new ParameterString("SourceXml", allowedValues));
            AddProperty(iPropertySourceXml);
        }

        /// <summary>
        /// Enable the Attributes property.
        /// </summary>
        public void EnablePropertyAttributes()
        {
            List<String> allowedValues = new List<String>();
            iPropertyAttributes = new PropertyString(new ParameterString("Attributes", allowedValues));
            AddProperty(iPropertyAttributes);
        }

        /// <summary>
        /// Set the value of the ManufacturerName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerName has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyManufacturerName(string aValue)
        {
            if (iPropertyManufacturerName == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyManufacturerName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ManufacturerName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerName has previously been called.</remarks>
        /// <returns>Value of the ManufacturerName property.</returns>
        public string PropertyManufacturerName()
        {
            if (iPropertyManufacturerName == null)
                throw new PropertyDisabledError();
            return iPropertyManufacturerName.Value();
        }

        /// <summary>
        /// Set the value of the ManufacturerInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerInfo has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyManufacturerInfo(string aValue)
        {
            if (iPropertyManufacturerInfo == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyManufacturerInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ManufacturerInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerInfo has previously been called.</remarks>
        /// <returns>Value of the ManufacturerInfo property.</returns>
        public string PropertyManufacturerInfo()
        {
            if (iPropertyManufacturerInfo == null)
                throw new PropertyDisabledError();
            return iPropertyManufacturerInfo.Value();
        }

        /// <summary>
        /// Set the value of the ManufacturerUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerUrl has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyManufacturerUrl(string aValue)
        {
            if (iPropertyManufacturerUrl == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyManufacturerUrl, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ManufacturerUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerUrl has previously been called.</remarks>
        /// <returns>Value of the ManufacturerUrl property.</returns>
        public string PropertyManufacturerUrl()
        {
            if (iPropertyManufacturerUrl == null)
                throw new PropertyDisabledError();
            return iPropertyManufacturerUrl.Value();
        }

        /// <summary>
        /// Set the value of the ManufacturerImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerImageUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyManufacturerImageUri(string aValue)
        {
            if (iPropertyManufacturerImageUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyManufacturerImageUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ManufacturerImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyManufacturerImageUri has previously been called.</remarks>
        /// <returns>Value of the ManufacturerImageUri property.</returns>
        public string PropertyManufacturerImageUri()
        {
            if (iPropertyManufacturerImageUri == null)
                throw new PropertyDisabledError();
            return iPropertyManufacturerImageUri.Value();
        }

        /// <summary>
        /// Set the value of the ModelName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelName has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyModelName(string aValue)
        {
            if (iPropertyModelName == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyModelName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ModelName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelName has previously been called.</remarks>
        /// <returns>Value of the ModelName property.</returns>
        public string PropertyModelName()
        {
            if (iPropertyModelName == null)
                throw new PropertyDisabledError();
            return iPropertyModelName.Value();
        }

        /// <summary>
        /// Set the value of the ModelInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelInfo has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyModelInfo(string aValue)
        {
            if (iPropertyModelInfo == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyModelInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ModelInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelInfo has previously been called.</remarks>
        /// <returns>Value of the ModelInfo property.</returns>
        public string PropertyModelInfo()
        {
            if (iPropertyModelInfo == null)
                throw new PropertyDisabledError();
            return iPropertyModelInfo.Value();
        }

        /// <summary>
        /// Set the value of the ModelUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelUrl has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyModelUrl(string aValue)
        {
            if (iPropertyModelUrl == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyModelUrl, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ModelUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelUrl has previously been called.</remarks>
        /// <returns>Value of the ModelUrl property.</returns>
        public string PropertyModelUrl()
        {
            if (iPropertyModelUrl == null)
                throw new PropertyDisabledError();
            return iPropertyModelUrl.Value();
        }

        /// <summary>
        /// Set the value of the ModelImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelImageUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyModelImageUri(string aValue)
        {
            if (iPropertyModelImageUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyModelImageUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ModelImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyModelImageUri has previously been called.</remarks>
        /// <returns>Value of the ModelImageUri property.</returns>
        public string PropertyModelImageUri()
        {
            if (iPropertyModelImageUri == null)
                throw new PropertyDisabledError();
            return iPropertyModelImageUri.Value();
        }

        /// <summary>
        /// Set the value of the ProductRoom property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductRoom has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductRoom(string aValue)
        {
            if (iPropertyProductRoom == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProductRoom, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductRoom property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductRoom has previously been called.</remarks>
        /// <returns>Value of the ProductRoom property.</returns>
        public string PropertyProductRoom()
        {
            if (iPropertyProductRoom == null)
                throw new PropertyDisabledError();
            return iPropertyProductRoom.Value();
        }

        /// <summary>
        /// Set the value of the ProductName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductName has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductName(string aValue)
        {
            if (iPropertyProductName == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProductName, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductName property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductName has previously been called.</remarks>
        /// <returns>Value of the ProductName property.</returns>
        public string PropertyProductName()
        {
            if (iPropertyProductName == null)
                throw new PropertyDisabledError();
            return iPropertyProductName.Value();
        }

        /// <summary>
        /// Set the value of the ProductInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductInfo has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductInfo(string aValue)
        {
            if (iPropertyProductInfo == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProductInfo, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductInfo property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductInfo has previously been called.</remarks>
        /// <returns>Value of the ProductInfo property.</returns>
        public string PropertyProductInfo()
        {
            if (iPropertyProductInfo == null)
                throw new PropertyDisabledError();
            return iPropertyProductInfo.Value();
        }

        /// <summary>
        /// Set the value of the ProductUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductUrl has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductUrl(string aValue)
        {
            if (iPropertyProductUrl == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProductUrl, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductUrl property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductUrl has previously been called.</remarks>
        /// <returns>Value of the ProductUrl property.</returns>
        public string PropertyProductUrl()
        {
            if (iPropertyProductUrl == null)
                throw new PropertyDisabledError();
            return iPropertyProductUrl.Value();
        }

        /// <summary>
        /// Set the value of the ProductImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductImageUri has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyProductImageUri(string aValue)
        {
            if (iPropertyProductImageUri == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyProductImageUri, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the ProductImageUri property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyProductImageUri has previously been called.</remarks>
        /// <returns>Value of the ProductImageUri property.</returns>
        public string PropertyProductImageUri()
        {
            if (iPropertyProductImageUri == null)
                throw new PropertyDisabledError();
            return iPropertyProductImageUri.Value();
        }

        /// <summary>
        /// Set the value of the Standby property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStandby has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyStandby(bool aValue)
        {
            if (iPropertyStandby == null)
                throw new PropertyDisabledError();
            return SetPropertyBool(iPropertyStandby, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Standby property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyStandby has previously been called.</remarks>
        /// <returns>Value of the Standby property.</returns>
        public bool PropertyStandby()
        {
            if (iPropertyStandby == null)
                throw new PropertyDisabledError();
            return iPropertyStandby.Value();
        }

        /// <summary>
        /// Set the value of the SourceIndex property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceIndex has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySourceIndex(uint aValue)
        {
            if (iPropertySourceIndex == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySourceIndex, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SourceIndex property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceIndex has previously been called.</remarks>
        /// <returns>Value of the SourceIndex property.</returns>
        public uint PropertySourceIndex()
        {
            if (iPropertySourceIndex == null)
                throw new PropertyDisabledError();
            return iPropertySourceIndex.Value();
        }

        /// <summary>
        /// Set the value of the SourceCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceCount has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySourceCount(uint aValue)
        {
            if (iPropertySourceCount == null)
                throw new PropertyDisabledError();
            return SetPropertyUint(iPropertySourceCount, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SourceCount property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceCount has previously been called.</remarks>
        /// <returns>Value of the SourceCount property.</returns>
        public uint PropertySourceCount()
        {
            if (iPropertySourceCount == null)
                throw new PropertyDisabledError();
            return iPropertySourceCount.Value();
        }

        /// <summary>
        /// Set the value of the SourceXml property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceXml has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertySourceXml(string aValue)
        {
            if (iPropertySourceXml == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertySourceXml, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the SourceXml property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertySourceXml has previously been called.</remarks>
        /// <returns>Value of the SourceXml property.</returns>
        public string PropertySourceXml()
        {
            if (iPropertySourceXml == null)
                throw new PropertyDisabledError();
            return iPropertySourceXml.Value();
        }

        /// <summary>
        /// Set the value of the Attributes property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAttributes has previously been called.</remarks>
        /// <param name="aValue">New value for the property</param>
        /// <returns>true if the value has been updated; false if aValue was the same as the previous value</returns>
        public bool SetPropertyAttributes(string aValue)
        {
            if (iPropertyAttributes == null)
                throw new PropertyDisabledError();
            return SetPropertyString(iPropertyAttributes, aValue);
        }

        /// <summary>
        /// Get a copy of the value of the Attributes property
        /// </summary>
        /// <remarks>Can only be called if EnablePropertyAttributes has previously been called.</remarks>
        /// <returns>Value of the Attributes property.</returns>
        public string PropertyAttributes()
        {
            if (iPropertyAttributes == null)
                throw new PropertyDisabledError();
            return iPropertyAttributes.Value();
        }

        /// <summary>
        /// Signal that the action Manufacturer is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Manufacturer must be overridden if this is called.</remarks>
        protected void EnableActionManufacturer()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Manufacturer");
            action.AddOutputParameter(new ParameterRelated("Name", iPropertyManufacturerName));
            action.AddOutputParameter(new ParameterRelated("Info", iPropertyManufacturerInfo));
            action.AddOutputParameter(new ParameterRelated("Url", iPropertyManufacturerUrl));
            action.AddOutputParameter(new ParameterRelated("ImageUri", iPropertyManufacturerImageUri));
            iDelegateManufacturer = new ActionDelegate(DoManufacturer);
            EnableAction(action, iDelegateManufacturer, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Model is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Model must be overridden if this is called.</remarks>
        protected void EnableActionModel()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Model");
            action.AddOutputParameter(new ParameterRelated("Name", iPropertyModelName));
            action.AddOutputParameter(new ParameterRelated("Info", iPropertyModelInfo));
            action.AddOutputParameter(new ParameterRelated("Url", iPropertyModelUrl));
            action.AddOutputParameter(new ParameterRelated("ImageUri", iPropertyModelImageUri));
            iDelegateModel = new ActionDelegate(DoModel);
            EnableAction(action, iDelegateModel, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Product is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Product must be overridden if this is called.</remarks>
        protected void EnableActionProduct()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Product");
            action.AddOutputParameter(new ParameterRelated("Room", iPropertyProductRoom));
            action.AddOutputParameter(new ParameterRelated("Name", iPropertyProductName));
            action.AddOutputParameter(new ParameterRelated("Info", iPropertyProductInfo));
            action.AddOutputParameter(new ParameterRelated("Url", iPropertyProductUrl));
            action.AddOutputParameter(new ParameterRelated("ImageUri", iPropertyProductImageUri));
            iDelegateProduct = new ActionDelegate(DoProduct);
            EnableAction(action, iDelegateProduct, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Standby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Standby must be overridden if this is called.</remarks>
        protected void EnableActionStandby()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Standby");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyStandby));
            iDelegateStandby = new ActionDelegate(DoStandby);
            EnableAction(action, iDelegateStandby, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetStandby is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetStandby must be overridden if this is called.</remarks>
        protected void EnableActionSetStandby()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetStandby");
            action.AddInputParameter(new ParameterRelated("Value", iPropertyStandby));
            iDelegateSetStandby = new ActionDelegate(DoSetStandby);
            EnableAction(action, iDelegateSetStandby, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SourceCount must be overridden if this is called.</remarks>
        protected void EnableActionSourceCount()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SourceCount");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertySourceCount));
            iDelegateSourceCount = new ActionDelegate(DoSourceCount);
            EnableAction(action, iDelegateSourceCount, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceXml is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SourceXml must be overridden if this is called.</remarks>
        protected void EnableActionSourceXml()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SourceXml");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertySourceXml));
            iDelegateSourceXml = new ActionDelegate(DoSourceXml);
            EnableAction(action, iDelegateSourceXml, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SourceIndex must be overridden if this is called.</remarks>
        protected void EnableActionSourceIndex()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SourceIndex");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertySourceIndex));
            iDelegateSourceIndex = new ActionDelegate(DoSourceIndex);
            EnableAction(action, iDelegateSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSourceIndex is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetSourceIndex must be overridden if this is called.</remarks>
        protected void EnableActionSetSourceIndex()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetSourceIndex");
            action.AddInputParameter(new ParameterRelated("Value", iPropertySourceIndex));
            iDelegateSetSourceIndex = new ActionDelegate(DoSetSourceIndex);
            EnableAction(action, iDelegateSetSourceIndex, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SetSourceIndexByName is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SetSourceIndexByName must be overridden if this is called.</remarks>
        protected void EnableActionSetSourceIndexByName()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SetSourceIndexByName");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterString("Value", allowedValues));
            iDelegateSetSourceIndexByName = new ActionDelegate(DoSetSourceIndexByName);
            EnableAction(action, iDelegateSetSourceIndexByName, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Source is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Source must be overridden if this is called.</remarks>
        protected void EnableActionSource()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Source");
            List<String> allowedValues = new List<String>();
            action.AddInputParameter(new ParameterRelated("Index", iPropertySourceIndex));
            action.AddOutputParameter(new ParameterString("SystemName", allowedValues));
            action.AddOutputParameter(new ParameterString("Type", allowedValues));
            action.AddOutputParameter(new ParameterString("Name", allowedValues));
            action.AddOutputParameter(new ParameterBool("Visible"));
            iDelegateSource = new ActionDelegate(DoSource);
            EnableAction(action, iDelegateSource, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action Attributes is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// Attributes must be overridden if this is called.</remarks>
        protected void EnableActionAttributes()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("Attributes");
            action.AddOutputParameter(new ParameterRelated("Value", iPropertyAttributes));
            iDelegateAttributes = new ActionDelegate(DoAttributes);
            EnableAction(action, iDelegateAttributes, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Signal that the action SourceXmlChangeCount is supported.
        /// </summary>
        /// <remarks>The action's availability will be published in the device's service.xml.
        /// SourceXmlChangeCount must be overridden if this is called.</remarks>
        protected void EnableActionSourceXmlChangeCount()
        {
            OpenHome.Net.Core.Action action = new OpenHome.Net.Core.Action("SourceXmlChangeCount");
            action.AddOutputParameter(new ParameterUint("Value"));
            iDelegateSourceXmlChangeCount = new ActionDelegate(DoSourceXmlChangeCount);
            EnableAction(action, iDelegateSourceXmlChangeCount, GCHandle.ToIntPtr(iGch));
        }

        /// <summary>
        /// Manufacturer action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Manufacturer action for the owning device.
        ///
        /// Must be implemented iff EnableActionManufacturer was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        protected virtual void Manufacturer(IDvInvocation aInvocation, out string aName, out string aInfo, out string aUrl, out string aImageUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Model action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Model action for the owning device.
        ///
        /// Must be implemented iff EnableActionModel was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        protected virtual void Model(IDvInvocation aInvocation, out string aName, out string aInfo, out string aUrl, out string aImageUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Product action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Product action for the owning device.
        ///
        /// Must be implemented iff EnableActionProduct was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aRoom"></param>
        /// <param name="aName"></param>
        /// <param name="aInfo"></param>
        /// <param name="aUrl"></param>
        /// <param name="aImageUri"></param>
        protected virtual void Product(IDvInvocation aInvocation, out string aRoom, out string aName, out string aInfo, out string aUrl, out string aImageUri)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Standby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Standby action for the owning device.
        ///
        /// Must be implemented iff EnableActionStandby was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Standby(IDvInvocation aInvocation, out bool aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetStandby action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetStandby action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetStandby was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetStandby(IDvInvocation aInvocation, bool aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceCount was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SourceCount(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceXml action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceXml action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceXml was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SourceXml(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceIndex was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SourceIndex(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceIndex action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndex action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndex was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetSourceIndex(IDvInvocation aInvocation, uint aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SetSourceIndexByName action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SetSourceIndexByName action for the owning device.
        ///
        /// Must be implemented iff EnableActionSetSourceIndexByName was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SetSourceIndexByName(IDvInvocation aInvocation, string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Source action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Source action for the owning device.
        ///
        /// Must be implemented iff EnableActionSource was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aIndex"></param>
        /// <param name="aSystemName"></param>
        /// <param name="aType"></param>
        /// <param name="aName"></param>
        /// <param name="aVisible"></param>
        protected virtual void Source(IDvInvocation aInvocation, uint aIndex, out string aSystemName, out string aType, out string aName, out bool aVisible)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// Attributes action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// Attributes action for the owning device.
        ///
        /// Must be implemented iff EnableActionAttributes was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void Attributes(IDvInvocation aInvocation, out string aValue)
        {
            throw (new ActionDisabledError());
        }

        /// <summary>
        /// SourceXmlChangeCount action.
        /// </summary>
        /// <remarks>Will be called when the device stack receives an invocation of the
        /// SourceXmlChangeCount action for the owning device.
        ///
        /// Must be implemented iff EnableActionSourceXmlChangeCount was called.</remarks>
        /// <param name="aInvocation">Interface allowing querying of aspects of this particular action invocation.</param>
        /// <param name="aValue"></param>
        protected virtual void SourceXmlChangeCount(IDvInvocation aInvocation, out uint aValue)
        {
            throw (new ActionDisabledError());
        }

        private static int DoManufacturer(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string name;
            string info;
            string url;
            string imageUri;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Manufacturer(invocation, out name, out info, out url, out imageUri);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Manufacturer");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Manufacturer" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Manufacturer" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Name", name);
                invocation.WriteString("Info", info);
                invocation.WriteString("Url", url);
                invocation.WriteString("ImageUri", imageUri);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Manufacturer" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoModel(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string name;
            string info;
            string url;
            string imageUri;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Model(invocation, out name, out info, out url, out imageUri);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Model");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Model" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Model" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Name", name);
                invocation.WriteString("Info", info);
                invocation.WriteString("Url", url);
                invocation.WriteString("ImageUri", imageUri);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Model" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoProduct(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string room;
            string name;
            string info;
            string url;
            string imageUri;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Product(invocation, out room, out name, out info, out url, out imageUri);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Product");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Product" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Product" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Room", room);
                invocation.WriteString("Name", name);
                invocation.WriteString("Info", info);
                invocation.WriteString("Url", url);
                invocation.WriteString("ImageUri", imageUri);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Product" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoStandby(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Standby(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Standby");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Standby" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Standby" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteBool("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Standby" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetStandby(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            bool value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadBool("Value");
                invocation.ReadEnd();
                self.SetStandby(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetStandby");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetStandby" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetStandby" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetStandby" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSourceCount(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SourceCount(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SourceCount");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SourceCount" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceCount" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceCount" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSourceXml(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SourceXml(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SourceXml");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SourceXml" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceXml" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceXml" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSourceIndex(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SourceIndex(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SourceIndex");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SourceIndex" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceIndex" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceIndex" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetSourceIndex(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadUint("Value");
                invocation.ReadEnd();
                self.SetSourceIndex(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetSourceIndex");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetSourceIndex" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetSourceIndex" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetSourceIndex" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSetSourceIndexByName(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                value = invocation.ReadString("Value");
                invocation.ReadEnd();
                self.SetSourceIndexByName(invocation, value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SetSourceIndexByName");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SetSourceIndexByName" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetSourceIndexByName" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SetSourceIndexByName" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSource(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint index;
            string systemName;
            string type;
            string name;
            bool visible;
            try
            {
                invocation.ReadStart();
                index = invocation.ReadUint("Index");
                invocation.ReadEnd();
                self.Source(invocation, index, out systemName, out type, out name, out visible);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Source");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Source" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Source" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("SystemName", systemName);
                invocation.WriteString("Type", type);
                invocation.WriteString("Name", name);
                invocation.WriteBool("Visible", visible);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Source" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoAttributes(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            string value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.Attributes(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "Attributes");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "Attributes" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Attributes" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteString("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "Attributes" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        private static int DoSourceXmlChangeCount(IntPtr aPtr, IntPtr aInvocation)
        {
            GCHandle gch = GCHandle.FromIntPtr(aPtr);
            DvProviderAvOpenhomeOrgProduct1 self = (DvProviderAvOpenhomeOrgProduct1)gch.Target;
            DvInvocation invocation = new DvInvocation(aInvocation);
            uint value;
            try
            {
                invocation.ReadStart();
                invocation.ReadEnd();
                self.SourceXmlChangeCount(invocation, out value);
            }
            catch (ActionError e)
            {
                invocation.ReportActionError(e, "SourceXmlChangeCount");
                return -1;
            }
            catch (PropertyUpdateError)
            {
                invocation.ReportError(501, String.Format("Invalid value for property {0}", new object[] { "SourceXmlChangeCount" }));
                return -1;
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceXmlChangeCount" });
                System.Diagnostics.Debug.WriteLine("         Only ActionError or PropertyUpdateError should be thrown by actions");
                return -1;
            }
            try
            {
                invocation.WriteStart();
                invocation.WriteUint("Value", value);
                invocation.WriteEnd();
            }
            catch (ActionError)
            {
                return -1;
            }
            catch (System.Exception e)
            {
                System.Diagnostics.Debug.WriteLine("WARNING: unexpected exception {0} thrown by {1}", new object[] { e, "SourceXmlChangeCount" });
                System.Diagnostics.Debug.WriteLine("       Only ActionError can be thrown by action response writer");
            }
            return 0;
        }

        /// <summary>
        /// Must be called for each class instance.  Must be called before Core.Library.Close().
        /// </summary>
        public virtual void Dispose()
        {
            if (DisposeProvider())
                iGch.Free();
        }
    }
}

