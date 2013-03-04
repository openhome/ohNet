 

/**
* Service Proxy for CpProxyAvOpenhomeOrgMediaServer1
* @module ohnet
* @class MediaServer
*/
    
var CpProxyAvOpenhomeOrgMediaServer1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/av.openhome.org-MediaServer-1/control";  // upnp control url
    this.domain = "av-openhome-org";
    this.type = "MediaServer";
    this.version = "1";
    this.serviceName = "av.openhome.org-MediaServer-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};
    this.serviceProperties["ManufacturerName"] = new ohnet.serviceproperty("ManufacturerName","string");
    this.serviceProperties["ManufacturerInfo"] = new ohnet.serviceproperty("ManufacturerInfo","string");
    this.serviceProperties["ManufacturerUrl"] = new ohnet.serviceproperty("ManufacturerUrl","string");
    this.serviceProperties["ManufacturerImageUri"] = new ohnet.serviceproperty("ManufacturerImageUri","string");
    this.serviceProperties["ModelName"] = new ohnet.serviceproperty("ModelName","string");
    this.serviceProperties["ModelInfo"] = new ohnet.serviceproperty("ModelInfo","string");
    this.serviceProperties["ModelUrl"] = new ohnet.serviceproperty("ModelUrl","string");
    this.serviceProperties["ModelImageUri"] = new ohnet.serviceproperty("ModelImageUri","string");
    this.serviceProperties["ProductName"] = new ohnet.serviceproperty("ProductName","string");
    this.serviceProperties["ProductInfo"] = new ohnet.serviceproperty("ProductInfo","string");
    this.serviceProperties["ProductUrl"] = new ohnet.serviceproperty("ProductUrl","string");
    this.serviceProperties["ProductImageUri"] = new ohnet.serviceproperty("ProductImageUri","string");
    this.serviceProperties["Attributes"] = new ohnet.serviceproperty("Attributes","string");
    this.serviceProperties["QueryPort"] = new ohnet.serviceproperty("QueryPort","int");
    this.serviceProperties["BrowsePort"] = new ohnet.serviceproperty("BrowsePort","int");
    this.serviceProperties["UpdateCount"] = new ohnet.serviceproperty("UpdateCount","int");

                                                                                                    
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}


    

/**
* Adds a listener to handle "ManufacturerName" property change events
* @method ManufacturerName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ManufacturerName_Changed = function (stateChangedFunction) {
    this.serviceProperties.ManufacturerName.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ManufacturerInfo" property change events
* @method ManufacturerInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ManufacturerInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ManufacturerInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ManufacturerUrl" property change events
* @method ManufacturerUrl_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ManufacturerUrl_Changed = function (stateChangedFunction) {
    this.serviceProperties.ManufacturerUrl.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ManufacturerImageUri" property change events
* @method ManufacturerImageUri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ManufacturerImageUri_Changed = function (stateChangedFunction) {
    this.serviceProperties.ManufacturerImageUri.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ModelName" property change events
* @method ModelName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ModelName_Changed = function (stateChangedFunction) {
    this.serviceProperties.ModelName.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ModelInfo" property change events
* @method ModelInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ModelInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ModelInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ModelUrl" property change events
* @method ModelUrl_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ModelUrl_Changed = function (stateChangedFunction) {
    this.serviceProperties.ModelUrl.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ModelImageUri" property change events
* @method ModelImageUri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ModelImageUri_Changed = function (stateChangedFunction) {
    this.serviceProperties.ModelImageUri.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProductName" property change events
* @method ProductName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ProductName_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductName.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProductInfo" property change events
* @method ProductInfo_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ProductInfo_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductInfo.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProductUrl" property change events
* @method ProductUrl_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ProductUrl_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductUrl.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "ProductImageUri" property change events
* @method ProductImageUri_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.ProductImageUri_Changed = function (stateChangedFunction) {
    this.serviceProperties.ProductImageUri.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "Attributes" property change events
* @method Attributes_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.Attributes_Changed = function (stateChangedFunction) {
    this.serviceProperties.Attributes.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readStringParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "QueryPort" property change events
* @method QueryPort_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.QueryPort_Changed = function (stateChangedFunction) {
    this.serviceProperties.QueryPort.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "BrowsePort" property change events
* @method BrowsePort_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.BrowsePort_Changed = function (stateChangedFunction) {
    this.serviceProperties.BrowsePort.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}
    

/**
* Adds a listener to handle "UpdateCount" property change events
* @method UpdateCount_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.UpdateCount_Changed = function (stateChangedFunction) {
    this.serviceProperties.UpdateCount.addListener(function (state) 
    { 
        stateChangedFunction(ohnet.soaprequest.readIntParameter(state)); 
    });
}


/**
* A service action to Manufacturer
* @method Manufacturer
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.Manufacturer = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Manufacturer", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Name"] = ohnet.soaprequest.readStringParameter(result["Name"]); 
        result["Info"] = ohnet.soaprequest.readStringParameter(result["Info"]); 
        result["Url"] = ohnet.soaprequest.readStringParameter(result["Url"]); 
        result["ImageUri"] = ohnet.soaprequest.readStringParameter(result["ImageUri"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Model
* @method Model
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.Model = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Model", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Name"] = ohnet.soaprequest.readStringParameter(result["Name"]); 
        result["Info"] = ohnet.soaprequest.readStringParameter(result["Info"]); 
        result["Url"] = ohnet.soaprequest.readStringParameter(result["Url"]); 
        result["ImageUri"] = ohnet.soaprequest.readStringParameter(result["ImageUri"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Product
* @method Product
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.Product = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Product", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Name"] = ohnet.soaprequest.readStringParameter(result["Name"]); 
        result["Info"] = ohnet.soaprequest.readStringParameter(result["Info"]); 
        result["Url"] = ohnet.soaprequest.readStringParameter(result["Url"]); 
        result["ImageUri"] = ohnet.soaprequest.readStringParameter(result["ImageUri"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to Attributes
* @method Attributes
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.Attributes = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("Attributes", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readStringParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to QueryPort
* @method QueryPort
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.QueryPort = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("QueryPort", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to BrowsePort
* @method BrowsePort
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.BrowsePort = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("BrowsePort", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to UpdateCount
* @method UpdateCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyAvOpenhomeOrgMediaServer1.prototype.UpdateCount = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("UpdateCount", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Value"] = ohnet.soaprequest.readIntParameter(result["Value"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



