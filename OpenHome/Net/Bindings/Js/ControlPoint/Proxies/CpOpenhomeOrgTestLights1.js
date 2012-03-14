 

/**
* Service Proxy for CpProxyOpenhomeOrgTestLights1
* @module ohnet
* @class TestLights
*/
    
var CpProxyOpenhomeOrgTestLights1 = function(udn){ 

    this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/openhome.org-TestLights-1/control";  // upnp control url
    this.domain = "openhome-org";
    this.type = "TestLights";
    this.version = "1";
    this.serviceName = "openhome.org-TestLights-1";
    this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
    this.udn = udn;   // device name
    
    // Collection of service properties
    this.serviceProperties = {};

    
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyOpenhomeOrgTestLights1.prototype.subscribe = function (serviceAddedFunction) {
    ohnet.subscriptionmanager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyOpenhomeOrgTestLights1.prototype.unsubscribe = function () {
    ohnet.subscriptionmanager.removeService(this.subscriptionId);
}




/**
* A service action to GetCount
* @method GetCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetCount = function(successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetCount", this.url, this.domain, this.type, this.version);     
    request.send(function(result){
        result["Count"] = ohnet.soaprequest.readIntParameter(result["Count"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetRoom
* @method GetRoom
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetRoom = function(Index, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetRoom", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Index", Index);
    request.send(function(result){
        result["RoomName"] = ohnet.soaprequest.readStringParameter(result["RoomName"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetName
* @method GetName
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetName = function(Index, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetName", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Index", Index);
    request.send(function(result){
        result["FriendlyName"] = ohnet.soaprequest.readStringParameter(result["FriendlyName"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetPosition
* @method GetPosition
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetPosition = function(Index, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetPosition", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Index", Index);
    request.send(function(result){
        result["X"] = ohnet.soaprequest.readIntParameter(result["X"]); 
        result["Y"] = ohnet.soaprequest.readIntParameter(result["Y"]); 
        result["Z"] = ohnet.soaprequest.readIntParameter(result["Z"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to SetColor
* @method SetColor
* @param {Int} Index An action parameter
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.SetColor = function(Index, Color, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("SetColor", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Index", Index);
    request.writeIntParameter("Color", Color);
    request.send(function(result){
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetColor
* @method GetColor
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetColor = function(Index, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetColor", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Index", Index);
    request.send(function(result){
        result["Color"] = ohnet.soaprequest.readIntParameter(result["Color"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}


/**
* A service action to GetColorComponents
* @method GetColorComponents
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyOpenhomeOrgTestLights1.prototype.GetColorComponents = function(Color, successFunction, errorFunction){ 
    var request = new ohnet.soaprequest("GetColorComponents", this.url, this.domain, this.type, this.version);     
    request.writeIntParameter("Color", Color);
    request.send(function(result){
        result["Brightness"] = ohnet.soaprequest.readIntParameter(result["Brightness"]); 
        result["Red"] = ohnet.soaprequest.readIntParameter(result["Red"]); 
        result["Green"] = ohnet.soaprequest.readIntParameter(result["Green"]); 
        result["Blue"] = ohnet.soaprequest.readIntParameter(result["Blue"]); 
    
        if (successFunction){
            successFunction(result);
        }
    }, function(message, transport) {
        if (errorFunction) {errorFunction(message, transport);}
    });
}



